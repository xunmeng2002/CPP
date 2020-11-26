#include "TcpBase.h"
#include "Logger.h"
#include "Logger.h"
#include "SocketApi.h"
#include "MemCacheTemplate.h"
#include "SocketMemCache.h"
#include "IOCompletePort.h"
#include "WorkThreadBase.h"
#include "WorkThreadManage.h"


TcpBase::TcpBase(const char* name)
    :ThreadBase(name), m_LastSessionID(0)
{

}
TcpBase::~TcpBase()
{

}

bool TcpBase::Send(int sessionID, const char* data, int len)
{
    if (m_ConnectInfos.find(sessionID) == m_ConnectInfos.end())
    {
        return false;
    }
    auto connectSocket = m_ConnectInfos[sessionID].ConnectSocket;
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
void TcpBase::CloseConnect(int sessionID)
{
    if (m_ConnectInfos.find(sessionID) == m_ConnectInfos.end())
    {
        return;
    }
    auto socketData = MemCacheTemplate<SocketData>::GetInstance().Allocate();
    socketData->SessionID = sessionID;
    socketData->ConnectSocket = m_ConnectInfos[sessionID].ConnectSocket;
    PostDisConnect(socketData);
}

bool TcpBase::PostDisConnect(SocketData* socketData)
{
    WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "PostDisConnect For SessionID:[%d], Socket:[%lld].",
        socketData->SessionID, socketData->ConnectSocket);
    socketData->Operate = OperateType::Disconnect;
    return IOCompletePort::GetInstance().PostStatus(0, socketData->ConnectSocket, socketData);
}
bool TcpBase::PostSend(int sessionID, SOCKET sock, const char* data, int len, int& sendLen)
{
    DWORD transBytes = 0, flag = 0;
    sendLen = len >= MESSAGE_SIZE ? MESSAGE_SIZE : len;

    WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "PostSend Socket:[%lld]", sock);
    auto socketData = MemCacheTemplate<SocketData>::GetInstance().Allocate();
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
bool TcpBase::PostRecv(int sessionID, SOCKET sock)
{
    WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "PostRecv SessionID:[%d] Socket:[%lld]", sessionID, sock);
    auto socketData = MemCacheTemplate<SocketData>::GetInstance().Allocate();
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


void TcpBase::OnSendComplete(SocketData* socketData, int len)
{
    WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "OnSendComplete:SocketData:[%p] SOCKET=[%lld], WsaLen=[%d], Len=[%d].",
        socketData, socketData->ConnectSocket, socketData->WsaBuffer.len, len);
    if (len < socketData->WsaBuffer.len)
    {
        WRITE_ERROR_LOG(-1, "Sendlen Less than TargetLen.");
        PostDisConnect(socketData);
    }
    else
    {
        socketData->Clear();
        MemCacheTemplate<SocketData>::GetInstance().Free(socketData);
    }
}
void TcpBase::OnRecvComplete(SocketData* socketData, int len)
{
    PostRecv(socketData->SessionID, socketData->ConnectSocket);

    socketData->Event = EventType::Recv;
    socketData->WsaBuffer.len = len;
    if (m_ConnectInfos.find(socketData->SessionID) == m_ConnectInfos.end())
    {
        WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "Cannot Find ConnectInfo, RemoveConnect. SessionID:[%d]", socketData->SessionID);
        RemoveConnect(socketData);
        return;
    }
    m_ConnectInfos[socketData->SessionID].WorkThread->OnRecvMessage(socketData);
}
void TcpBase::AddConnect(SocketData* socketData)
{
    WRITE_LOG(LogLayer::Normal, LogLevel::Debug, "AddConnect SessionID:[%d] Socket:[%lld].", socketData->SessionID, socketData->ConnectSocket);
    socketData->SessionID = ++m_LastSessionID;
    PostRecv(socketData->SessionID, socketData->ConnectSocket);

    auto workThread = WorkThreadManage::GetInstance().DispatchWorkThread();
    m_ConnectInfos.insert(make_pair(socketData->SessionID, ConnectInfo(socketData->ConnectSocket, workThread)));
    socketData->Event = EventType::NewConnect;
    workThread->OnRecvMessage(socketData);
}
void TcpBase::RemoveConnect(SocketData* socketData)
{
    WRITE_LOG(LogLayer::Normal, LogLevel::Info, "RemoveConnect SessionID:[%d] Socket:[%lld].", socketData->SessionID, socketData->ConnectSocket);
    
    SocketApi::GetInstance().DisconnectEx(socketData->ConnectSocket, NULL, TF_REUSE_SOCKET, 0);
    SocketMemCache::GetInstance().Free(socketData->ConnectSocket);
    if (m_ConnectInfos.find(socketData->SessionID) != m_ConnectInfos.end())
    {
        socketData->Event = EventType::DisConnect;
        auto workThread = m_ConnectInfos[socketData->SessionID].WorkThread;
        workThread->OnRecvMessage(socketData);
        m_ConnectInfos.erase(socketData->SessionID);
    }
    else
    {
        MemCacheTemplate<SocketData>::GetInstance().Free(socketData);
    }
}