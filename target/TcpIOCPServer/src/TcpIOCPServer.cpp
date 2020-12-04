#include "TcpIOCPServer.h"
#include "WorkThread.h"
#include "WorkThreadManage.h"
#include "MemCacheTemplateSingleton.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include "Logger.h"
#include "SocketApi.h"
#include "IOCompletePort.h"


using namespace std;

#define EXIT_CODE 0
#define MAX_ACCPET_NUM 10

TcpIOCPServer TcpIOCPServer::m_Instance;

TcpIOCPServer::TcpIOCPServer()
    :TcpIOCP("TcpIOCPServer"), m_Family(0), m_Port(0), m_ServerAddress({0}), m_ServerSocket(INVALID_SOCKET)
{

}
TcpIOCPServer::~TcpIOCPServer()
{
}

TcpIOCPServer& TcpIOCPServer::GetInstance()
{
    return m_Instance;
}

bool TcpIOCPServer::Init()
{
    if (!Create())
        return false;
    if (!TryBind())
        return false;
    if (!Listen())
        return false;
    return SocketApi::GetInstance().Init(m_ServerSocket);
}
void TcpIOCPServer::Stop()
{
    IOCompletePort::GetInstance().PostStatus(0, (DWORD)EXIT_CODE, NULL);
    m_ShouldRun.store(false);
}

void TcpIOCPServer::SetSocketInfo(int port, const char* ip, int family)
{
    m_Family = family;
    m_IP = ip;
    m_Port = port;
    m_ServerAddress.sin_family = family;
    m_ServerAddress.sin_addr.S_un.S_addr = inet_addr(m_IP.c_str());
    m_ServerAddress.sin_port = htons(port);
}

void TcpIOCPServer::ThreadInit()
{
    ThreadBase::ThreadInit();
    for (auto i = 0; i < MAX_ACCPET_NUM; i++)
    {
        if (!PostAccept())
        {
            WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "ThreadInit PostAccept Failed.");
            m_ShouldRun.store(false);
            break;
        }
    }
}
void TcpIOCPServer::Run()
{
    DWORD len;
    SOCKET socket;
    SocketData* socketData;

    auto bOK = IOCompletePort::GetInstance().GetStatus(&len, (PULONG_PTR)&socket, (LPOVERLAPPED*)&socketData, INFINITE);
    WRITE_LOG(LogLayer::Normal, LogLevel::Info, "CompletionKey = [%d], Len = [%d], Ret = [%d].", socket, len, bOK);
    if (socketData == nullptr)
    {
        WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "Thread Eixt. CompetionKey:[%d], SocketData is null.", socket);
        m_ShouldRun.store(false);
        return;
    }
    if (!bOK)
    {
        WRITE_ERROR_LOG(GetLastError(), "GetQueuedCompletionStatus Failed.");
        RemoveConnect(socketData);
        return;
    }
    if (len == 0 && (socketData->Operate == OperateType::Send || socketData->Operate == OperateType::Recv))
    {
        WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "Disconnect SOCKET=[%d].", socketData->ConnectSocket);
        RemoveConnect(socketData);
        return;
    }

    switch (socketData->Operate)
    {
    case OperateType::Accept:
        OnAcceptComplete(socketData, len);
        break;
    case OperateType::Send:
        OnSendComplete(socketData, len);
        break;
    case OperateType::Recv:
        OnRecvComplete(socketData, len);
        break;
    case OperateType::Disconnect:
        RemoveConnect(socketData);
        break;
    case OperateType::Invalid:
    default:
        WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "INVALID OPERATE TYPE[%d] SOCKET=[%d].", socketData->Operate, socketData->ConnectSocket);
        assert(false);
    }
}
void TcpIOCPServer::ThreadExit()
{
    
    closesocket(m_ServerSocket);
    for (auto& it : m_ConnectInfos)
    {
        closesocket(it.second.ConnectSocket);
    }
    m_ConnectInfos.clear();
    
    TcpIOCP::ThreadExit();
}

bool TcpIOCPServer::Create(int nMaxConcurrency)
{
    if (m_ServerSocket == INVALID_SOCKET)
    {
        //m_ServerSocket = socket(m_Family, SOCK_STREAM, IPPROTO_TCP);
        m_ServerSocket  = WSASocket(m_Family, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
        if (m_ServerSocket == INVALID_SOCKET)
        {
            WRITE_ERROR_LOG(WSAGetLastError(), "Create Socket Failed.");
            return false;
        }
        WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "Create ServerSocket = [%d].", m_ServerSocket);
    }
    int on = 1;
    if (setsockopt(m_ServerSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) != 0)
    {
        WRITE_ERROR_LOG(GetLastError(), "setsockopt Failed. ErrorID:[%d], result:[%d]");
        return false;
    }
    if (!IOCompletePort::GetInstance().Create())
    {
        WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "Create IOCompletePort Failed.");
        return false;
    }
    if (!IOCompletePort::GetInstance().AssociateDevice((HANDLE)m_ServerSocket, m_ServerSocket))
    {
        WRITE_ERROR_LOG(GetLastError(), "AssociateDevice Failed.");
        return false;
    }
    return true;
}
bool TcpIOCPServer::TryBind()
{
    if (bind(m_ServerSocket, (sockaddr*)&m_ServerAddress, sizeof(m_ServerAddress)) == SOCKET_ERROR)
    {
        WRITE_ERROR_LOG(WSAGetLastError(), "Bind Failed.");
        closesocket(m_ServerSocket);
        return false;
    }
    return true;
}
bool TcpIOCPServer::Listen(int backLog)
{
    if (listen(m_ServerSocket, backLog) == SOCKET_ERROR)
    {
        WRITE_ERROR_LOG(WSAGetLastError(), "Listen Failed.");
        closesocket(m_ServerSocket);
        return false;
    }
    return true;
}

bool TcpIOCPServer::PostAccept()
{
    SocketData* socketData = MemCacheTemplateSingleton<SocketData>::GetInstance().Allocate();
    socketData->ConnectSocket = AllocateSocket();
    if (socketData->ConnectSocket == INVALID_SOCKET)
    {
        WRITE_ERROR_LOG(GetLastError(), "CreateSocket Failed.");
        MemCacheTemplateSingleton<SocketData>::GetInstance().Free(socketData);
        return false;
    }
    socketData->WsaBuffer.len = sizeof(socketData->Buffer);
    socketData->WsaBuffer.buf = socketData->Buffer;
    memset(socketData->Buffer, 0, sizeof(socketData->Buffer));
    socketData->Operate = OperateType::Accept;

    WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "PostAccept SOCKET:[%lld].", socketData->ConnectSocket);
    DWORD transBytes = 0;
    if (!SocketApi::GetInstance().AcceptEx(m_ServerSocket, socketData->ConnectSocket, socketData->WsaBuffer.buf, 0,
        (sizeof(SOCKADDR_IN) + 16), (sizeof(SOCKADDR_IN) + 16), &transBytes, (LPOVERLAPPED)socketData) && WSAGetLastError() != ERROR_IO_PENDING)
    {
        WRITE_LOG(LogLayer::Normal, LogLevel::Error, "Call AcceptEx Failed. Socket:[%lld]", socketData->ConnectSocket);
        WRITE_ERROR_LOG(WSAGetLastError(), "Call AcceptEx Failed.");
        return false;
    }
    return true;
}
void TcpIOCPServer::OnAcceptComplete(SocketData* socketData, int len)
{
    SOCKADDR_IN* remoteAddr = NULL;
    SOCKADDR_IN* localAddr = NULL;
    int remoteLen = sizeof(SOCKADDR_IN), localLen = sizeof(SOCKADDR_IN);
    SocketApi::GetInstance().GetAcceptExSockAddrs(socketData->WsaBuffer.buf, 0,
        (sizeof(SOCKADDR_IN) + 16), (sizeof(SOCKADDR_IN) + 16), (LPSOCKADDR*)&localAddr, &localLen, (LPSOCKADDR*)&remoteAddr, &remoteLen);
    
    WRITE_LOG(LogLayer::Normal, LogLevel::Info, "OnAcceptComplete: From <%s:%d> SOCKET:[%lld] Len:[%d], WSALen:[%d].",
        inet_ntoa(remoteAddr->sin_addr), ntohs(remoteAddr->sin_port),
        socketData->ConnectSocket, len, socketData->WsaBuffer.len);
    
    if (!IOCompletePort::GetInstance().AssociateDevice((HANDLE)socketData->ConnectSocket, socketData->ConnectSocket))
    {
        WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "Associate CompletionPort Failed, SessionID:[%d] Socket:[%lld]", socketData->SessionID, socketData->ConnectSocket);
    }
    AddConnect(socketData);
    PostAccept();
}
