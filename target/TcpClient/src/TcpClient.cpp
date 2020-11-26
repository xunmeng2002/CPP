#include "TcpClient.h"
#include "IOCompletePort.h"
#include "SocketApi.h"
#include "SocketMemCache.h"
#include "Logger.h"
#include <assert.h>

using namespace std;

#define EXIT_CODE 0

TcpClient TcpClient::m_Instance;

TcpClient::TcpClient()
    :TcpBase("TcpClient"), m_Family(0), m_ServerIP(""), m_ServerPort(0), m_ServerAddress({ 0 }), m_LocalAddress({0}), m_InitSocket(INVALID_SOCKET)
{

}
TcpClient::~TcpClient()
{

}

TcpClient& TcpClient::GetInstance()
{
    return m_Instance;
}
bool TcpClient::Init()
{
    if (!Create())
    {
        return false;
    }
    return SocketApi::GetInstance().Init(m_InitSocket);
}
void TcpClient::Stop()
{
    IOCompletePort::GetInstance().PostStatus(0, (DWORD)EXIT_CODE, NULL);
    m_ShouldRun.store(false);
}
void TcpClient::SetServerAddress(const char* address, int port, int family)
{
    m_Family = family;
    m_ServerIP = address;
    m_ServerPort = port;
    
    m_ServerAddress.sin_family = family;
    m_ServerAddress.sin_addr.S_un.S_addr = inet_addr(address);
    m_ServerAddress.sin_port = htons(port);

    ZeroMemory(&m_LocalAddress, sizeof(sockaddr_in));
    m_LocalAddress.sin_family = family;
    m_LocalAddress.sin_addr.S_un.S_addr = INADDR_ANY;
    m_LocalAddress.sin_port = 0;
}
bool TcpClient::Connect()
{
    return PostConnect();
}

void TcpClient::ThreadInit()
{
    WRITE_LOG(LogLayer::Normal, LogLevel::Info, "TcpClient Start.");
}
void TcpClient::Run()
{
    DWORD len;
    SOCKET socket;
    SocketData* socketData;

    auto bOK = IOCompletePort::GetInstance().GetStatus(&len, (PULONG_PTR)&socket, (LPOVERLAPPED*)&socketData, INFINITE);
    WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "CompletionKey = [%d], Len = [%d], Ret = [%d].", socket, len, bOK);
    if (socketData == nullptr)
    {
        WRITE_LOG(LogLayer::Normal, LogLevel::Info, "Thread Eixt. CompetionKey:[%d], SocketData is null.", socket);
        m_ShouldRun.store(false);
        return;
    }
    if (!bOK)
    {
        WRITE_ERROR_LOG(GetLastError(), "GetQueuedCompletionStatus Failed.");
        WRITE_LOG(LogLayer::Normal, LogLevel::Info, "GetQueuedCompletionStatus Failed. SOCKET=[%d].", socketData->ConnectSocket);
        RemoveConnect(socketData);
        return;
    }
    if (len == 0 && (socketData->Operate == OperateType::Send || socketData->Operate == OperateType::Recv))
    {
        WRITE_LOG(LogLayer::Normal, LogLevel::Info, "Disconnect SOCKET=[%d].", socketData->ConnectSocket);
        RemoveConnect(socketData);
        return;
    }

    switch (socketData->Operate)
    {
    case OperateType::Connect:
        OnConnectComplete(socketData, len);
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
        WRITE_LOG(LogLayer::System, LogLevel::Error, "INVALID OPERATE TYPE[%d] SOCKET=[%d].", socketData->Operate, socketData->ConnectSocket);
        assert(false);
    }
}
void TcpClient::ThreadExit()
{
    WRITE_LOG(LogLayer::Normal, LogLevel::Info, "TcpClient Exit.");
}

bool TcpClient::Create(int maxConcurrency)
{
    if (!IOCompletePort::GetInstance().Create())
    {
        WRITE_ERROR_LOG(-1, "Create IOCompletePort Failed.");
        return false;
    }
    m_InitSocket = SocketMemCache::GetInstance().Allocate();
    return true;
}
bool TcpClient::PostConnect()
{
    auto connectSocket = SocketMemCache::GetInstance().Allocate();
    if(connectSocket == INVALID_SOCKET)
    {
        WRITE_ERROR_LOG(GetLastError(), "CreateSocket Failed.");
        return false;
    }
    if (bind(connectSocket, (const sockaddr*)&m_LocalAddress, sizeof(SOCKADDR_IN)) != 0)
    {
        WRITE_ERROR_LOG(GetLastError(), "Bind Failed.");
        SocketMemCache::GetInstance().Free(connectSocket);
        return false;
    }
    if (!IOCompletePort::GetInstance().AssociateDevice((HANDLE)connectSocket, connectSocket))
    {
        WRITE_ERROR_LOG(GetLastError(), "Associate CompletionPort Failed, Socket.");
        SocketMemCache::GetInstance().Free(connectSocket);
        return false;
    }

    SocketData* socketData = MemCacheTemplate<SocketData>::GetInstance().Allocate();
    socketData->ConnectSocket = connectSocket;
    socketData->WsaBuffer.len = sizeof(socketData->Buffer);
    socketData->WsaBuffer.buf = socketData->Buffer;
    memset(socketData->Buffer, 0, sizeof(socketData->Buffer));
    socketData->Operate = OperateType::Connect;

    WRITE_LOG(LogLayer::Normal, LogLevel::Info, "PostConnect SOCKET:[%lld].", socketData->ConnectSocket);
    DWORD transBytes = 0;
    if (!SocketApi::GetInstance().ConnectEx(socketData->ConnectSocket, (const sockaddr*)&m_ServerAddress, sizeof(SOCKADDR),
        NULL, 0, &transBytes, (LPOVERLAPPED)socketData) && WSAGetLastError() != ERROR_IO_PENDING)
    {
        WRITE_ERROR_LOG(WSAGetLastError(), "Call ConnectEx Failed.");
        return false;
    }
    return true;
}
void TcpClient::OnConnectComplete(SocketData* socketData, int len)
{
    WRITE_LOG(LogLayer::Normal, LogLevel::Info, "OnConnectComplete: SocketData:[%p] SOCKET=[%d] Len=[%d], WSALen=[%d], WSAData=[%s].",
        socketData, socketData->ConnectSocket, len, socketData->WsaBuffer.len, socketData->WsaBuffer.buf);

    AddConnect(socketData);
}