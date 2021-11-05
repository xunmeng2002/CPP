#include "TcpIOCP.h"
#include "Logger.h"
#include "Logger.h"
#include "SocketApi.h"
#include "MemCacheTemplate.h"
#include "MemCacheTemplateSingleton.h"
#include "SocketMemCache.h"
#include "IOCompletePort.h"
#include "WorkThreadBase.h"
#include "WorkThreadManage.h"


thread_local SocketMemCache t_SocketMemCache;
thread_local MemCacheTemplate<ConnectInfo> t_ConnectInfoCache;

TcpIOCP::TcpIOCP(const char* name)
    :ThreadBase(name), m_LastSessionID(0), m_TotalSendLen(0L), m_TotalRecvLen(0L)
{

}
TcpIOCP::~TcpIOCP()
{

}

bool TcpIOCP::Send(int sessionID, const char* data, int len)
{
    auto connectInfo = GetConnectInfo(sessionID);
    if (connectInfo == nullptr)
        return false;
    auto connectSocket = connectInfo->ConnectSocket;
    WRITE_LOG(LogLevel::Debug, "SendMessage  sessionID:[%d] Socket:[%lld] Len:[%d].", sessionID, connectSocket, len);
    int sendLen = 0;
    while (len - sendLen > 0)
    {
        int currSendLen = 0;
        if (!PostSend(sessionID, connectSocket, data + sendLen, len - sendLen, currSendLen) || currSendLen == 0)
        {
            return false;
        }
        sendLen += currSendLen;
    }
    return true;
}
void TcpIOCP::CloseConnect(int sessionID)
{
    auto connectInfo = GetConnectInfo(sessionID);
    if (connectInfo == nullptr)
        return;
    auto socketData = MemCacheTemplateSingleton<SocketData>::GetInstance().Allocate();
    socketData->SessionID = sessionID;
    socketData->ConnectSocket = connectInfo->ConnectSocket;
    PostDisConnect(socketData);
}

void TcpIOCP::ThreadExit()
{
    ThreadBase::ThreadExit();
    WRITE_LOG(LogLevel::Info, "TotalSendLen:[%lld], TotalRecvLen:[%lld]", m_TotalSendLen, m_TotalRecvLen);
}

SOCKET TcpIOCP::AllocateSocket()
{
    return t_SocketMemCache.Allocate();
}
void TcpIOCP::FreeSocket(SOCKET socket)
{
    t_SocketMemCache.Free(socket);
}

bool TcpIOCP::PostSend(int sessionID, SOCKET sock, const char* data, int len, int& sendLen)
{
    DWORD transBytes = 0, flag = 0;
    sendLen = len >= MESSAGE_SIZE ? MESSAGE_SIZE : len;

    WRITE_LOG(LogLevel::Debug, "PostSend Socket:[%lld]", sock);
    auto socketData = MemCacheTemplateSingleton<SocketData>::GetInstance().Allocate();
    socketData->SessionID = sessionID;
    socketData->ConnectSocket = sock;
    socketData->WsaBuffer.len = sendLen;
    socketData->WsaBuffer.buf = socketData->Buffer;
    memcpy(socketData->Buffer, data, sendLen);
    socketData->Operate = OperateType::Send;

    if (WSASend(socketData->ConnectSocket, &socketData->WsaBuffer, 1, &transBytes, flag, (LPOVERLAPPED)socketData, NULL) == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
    {
        WRITE_ERROR_LOG(WSAGetLastError(), "PostSend: WSASend failed.");
        PostDisConnect(socketData);
        return false;
    }
    return true;
}
bool TcpIOCP::PostRecv(int sessionID, SOCKET sock)
{
    WRITE_LOG(LogLevel::Debug, "PostRecv SessionID:[%d] Socket:[%lld]", sessionID, sock);
    auto socketData = MemCacheTemplateSingleton<SocketData>::GetInstance().Allocate();
    socketData->SessionID = sessionID;
    socketData->ConnectSocket = sock;
    socketData->WsaBuffer.len = sizeof(socketData->Buffer);
    socketData->WsaBuffer.buf = socketData->Buffer;
    memset(socketData->Buffer, 0, sizeof(socketData->Buffer));
    socketData->Operate = OperateType::Recv;

    DWORD transBytes = 0, flag = 0;
    if (WSARecv(socketData->ConnectSocket, &socketData->WsaBuffer, 1, &transBytes, &flag, (LPOVERLAPPED)socketData, NULL) == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
    {
        WRITE_ERROR_LOG(WSAGetLastError(), "PostRecv: WSARecv failed.");
        PostDisConnect(socketData);
        return false;
    }
    return true;
}
bool TcpIOCP::PostDisConnect(SocketData* socketData)
{
    WRITE_LOG(LogLevel::Debug, "PostDisConnect For SessionID:[%d], Socket:[%lld].", socketData->SessionID, socketData->ConnectSocket);
    socketData->Operate = OperateType::Disconnect;
    return IOCompletePort::GetInstance().PostStatus(0, socketData->ConnectSocket, socketData);
}

void TcpIOCP::OnSendComplete(SocketData* socketData, int len)
{
    WRITE_LOG(LogLevel::Debug, "OnSendComplete  SessionID:[%d] SOCKET:[%lld], WsaLen=[%d], Len=[%d].",
        socketData->SessionID, socketData->ConnectSocket, socketData->WsaBuffer.len, len);
    m_TotalSendLen += len;
    if (len < socketData->WsaBuffer.len)
    {
        WRITE_ERROR_LOG(-1, "Sendlen Less than TargetLen.");
        PostDisConnect(socketData);
    }
    else
    {
        socketData->Clear();
        MemCacheTemplateSingleton<SocketData>::GetInstance().Free(socketData);
    }
}
void TcpIOCP::OnRecvComplete(SocketData* socketData, int len)
{
    WRITE_LOG(LogLevel::Debug, "OnRecvComplete  SessionID:[%d] SOCKET:[%lld], WsaLen=[%d], Len=[%d].",
        socketData->SessionID, socketData->ConnectSocket, socketData->WsaBuffer.len, len);
    m_TotalRecvLen += len;

    PostRecv(socketData->SessionID, socketData->ConnectSocket);

    socketData->Event = EventType::Recv;
    socketData->WsaBuffer.len = len;
    auto connectInfo = GetConnectInfo(socketData->SessionID);
    if (connectInfo == nullptr)
    {
        WRITE_LOG(LogLevel::Debug, "Cannot Find ConnectInfo, RemoveConnect. SessionID:[%d]", socketData->SessionID);
        RemoveConnect(socketData);
        return;
    }
    connectInfo->WorkThread->OnRecvMessage(socketData);
}
void TcpIOCP::AddConnect(SocketData* socketData)
{
    WRITE_LOG(LogLevel::Debug, "AddConnect  SessionID:[%d] Socket:[%lld].", socketData->SessionID, socketData->ConnectSocket);
    socketData->SessionID = ++m_LastSessionID;
    PostRecv(socketData->SessionID, socketData->ConnectSocket);

    auto workThread = WorkThreadManage::GetInstance().DispatchWorkThread();
    AddConnectInfo(socketData->SessionID, socketData->ConnectSocket, workThread);
    socketData->Event = EventType::NewConnect;
    workThread->OnRecvMessage(socketData);
}
void TcpIOCP::RemoveConnect(SocketData* socketData)
{
    WRITE_LOG(LogLevel::Debug, "RemoveConnect  SessionID:[%d] Socket:[%lld].", socketData->SessionID, socketData->ConnectSocket);
    
    SocketApi::GetInstance().DisconnectEx(socketData->ConnectSocket, NULL, TF_REUSE_SOCKET, 0);
    FreeSocket(socketData->ConnectSocket);

    socketData->Event = EventType::DisConnect;
    auto workThread = RemoveConnectInfo(socketData->SessionID);
    if (workThread)
    {
        workThread->OnRecvMessage(socketData);
    }
    else
    {
        MemCacheTemplateSingleton<SocketData>::GetInstance().Free(socketData);
    }
}

ConnectInfo* TcpIOCP::GetConnectInfo(int sessionID)
{
    lock_guard<mutex> guard(m_ConnectInfoMutex);
    if (m_ConnectInfos.find(sessionID) == m_ConnectInfos.end())
    {
        return nullptr;
    }
    return m_ConnectInfos[sessionID];
}
void TcpIOCP::AddConnectInfo(int sessionID, SOCKET connectSocket, WorkThreadBase* workThread)
{
    auto connectInfo = t_ConnectInfoCache.Allocate();
    connectInfo->SetConnectInfo(connectSocket, workThread);

    lock_guard<mutex> guard(m_ConnectInfoMutex);
    m_ConnectInfos.insert(make_pair(sessionID, connectInfo));
}
WorkThreadBase* TcpIOCP::RemoveConnectInfo(int sessionID)
{
    lock_guard<mutex> guard(m_ConnectInfoMutex);
    if (m_ConnectInfos.find(sessionID) == m_ConnectInfos.end())
    {
        return nullptr;
    }
    auto connectInfo = m_ConnectInfos[sessionID];
    auto workThread = connectInfo->WorkThread;

    t_ConnectInfoCache.Free(connectInfo);
    m_ConnectInfos.erase(sessionID);
    return workThread;
}