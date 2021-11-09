#include "TcpIOCP.h"
#include "Logger.h"
#include "Logger.h"
#include "SocketApi.h"
#include "MemCacheTemplate.h"
#include "SocketMemCache.h"
#include "IOCompletePort.h"
#include <assert.h>


#define EXIT_CODE 0

thread_local SocketMemCache t_SocketMemCache;


TcpIOCP::TcpIOCP(const char* name)
    :ThreadBase(name), m_TcpSubscriber(nullptr), m_LastSessionID(0), m_TotalSendLen(0L), m_TotalRecvLen(0L), m_InitSocket(INVALID_SOCKET), m_LocalAddress({ 0 })
{

}
TcpIOCP::~TcpIOCP()
{

}

void TcpIOCP::SetLocalAddress(const char* ip, int port)
{
    m_LocalAddress.sin_family = AF_INET;
    m_LocalAddress.sin_addr.S_un.S_addr = inet_addr(ip);
    m_LocalAddress.sin_port = htons(port);

    WRITE_LOG(LogLevel::Info, "Udp SetBindAddress IP[%s], Port[%d]", ip, port);
}
void TcpIOCP::RegisterSubscriber(TcpSubscriber* tcpSubscriber)
{
    m_TcpSubscriber = tcpSubscriber;
}
bool TcpIOCP::Init()
{
    m_InitSocket = AllocateSocket();
    if (m_InitSocket == INVALID_SOCKET)
    {
        WRITE_LOG(LogLevel::Error, "Create SOCKET Failed.");
        return false;
    }
    int on = 1;
    if (setsockopt(m_InitSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) != 0)
    {
        WRITE_ERROR_LOG(GetLastError(), "setsockopt Failed. ErrorID:[%d], result:[%d]");
        return false;
    }
    if (!SocketApi::GetInstance().Init(m_InitSocket))
    {
        return false;
    }
    if (!IOCompletePort::GetInstance().Create())
    {
        WRITE_ERROR_LOG(LogLevel::Error, "Create IOCompletePort Failed.");
        return false;
    }
    if (!IOCompletePort::GetInstance().AssociateDevice((HANDLE)m_InitSocket, m_InitSocket))
    {
        WRITE_ERROR_LOG(GetLastError(), "AssociateDevice Failed.");
        return false;
    }
    return true;
}
void TcpIOCP::Stop()
{
    IOCompletePort::GetInstance().PostStatus(0, (DWORD)EXIT_CODE, NULL);
    m_ShouldRun.store(false);
}

void TcpIOCP::DisConnect(int sessionID)
{
    TcpEvent* tcpEvent = TcpEvent::Allocate();
    tcpEvent->EventID = EventDisConnect;
    tcpEvent->SessionID = sessionID;
    OnEvent(tcpEvent);
}
void TcpIOCP::Send(int sessionID, const char* data, int len)
{
    TcpEvent* tcpEvent = TcpEvent::Allocate();
    tcpEvent->EventID = EventSend;
    tcpEvent->SessionID = sessionID;
    memcpy(tcpEvent->Buff, data, len);
    tcpEvent->Length = len;
    tcpEvent->Buff[len] = '\0';
    OnEvent(tcpEvent);
}
void TcpIOCP::Send(TcpEvent* tcpEvent)
{
    OnEvent(tcpEvent);
}


void TcpIOCP::Run()
{
    HandleEvent();
    HandleCompletePortEvent();
}
void TcpIOCP::ThreadExit()
{
    ThreadBase::ThreadExit();
    WRITE_LOG(LogLevel::Info, "TotalSendLen:[%lld], TotalRecvLen:[%lld]", m_TotalSendLen, m_TotalRecvLen);
}
void TcpIOCP::HandleEvent()
{
    Event* event = nullptr;
    TcpEvent* tcpEvent = nullptr;
    while (event = GetEvent())
    {
        switch (event->EventID)
        {
        case EventConnect:
        {
            tcpEvent = (TcpEvent*)event;
            PostConnect(tcpEvent->IP.c_str(), tcpEvent->Port);
            break;
        }
        case EventDisConnect:
        {
            tcpEvent = (TcpEvent*)event;
            PostDisConnect(tcpEvent->SessionID);
            break;
        }
        case EventSend:
        {
            PostSend((TcpEvent*)event);
            break;
        }
        }
        event->Free();
    }
}
void TcpIOCP::HandleCompletePortEvent()
{
    DWORD len;
    SOCKET socket;
    SocketData* socketData;

    auto bOK = IOCompletePort::GetInstance().GetStatus(&len, (PULONG_PTR)&socket, (LPOVERLAPPED*)&socketData, 5000);
    WRITE_LOG(LogLevel::Debug, "CompletionKey:[%d], Len:[%d], Ret:[%d].", socket, len, bOK);
    if (socketData == nullptr)
    {
        WRITE_LOG(LogLevel::Info, "CompetionKey:[%d], SocketData is null.", socket);
        return;
    }
    if (!bOK)
    {
        WRITE_LOG(LogLevel::Warning, "GetQueuedCompletionStatus Failed. ErrorID:[%d] SOCKET:[%lld].", GetLastError(), socketData->ConnectSocket);
        PostDisConnect(socketData->SessionID);
        socketData->Free();
        return;
    }
    if (len == 0 && (socketData->EventID == EventSend || socketData->EventID == EventRecv))
    {
        WRITE_LOG(LogLevel::Debug, "Disconnect SOCKET:[%lld].", socketData->ConnectSocket);
        PostDisConnect(socketData->SessionID);
        socketData->Free();
        return;
    }

    switch (socketData->EventID)
    {
    case EventConnect:
        ConnectComplete(socketData, len);
        break;
    case EventDisConnect:
        DisConnectComplete(socketData, len);
        break;
    case EventAccept:
        AcceptComplete(socketData, len);
        break;
    case EventSend:
        SendComplete(socketData, len);
        break;
    case EventRecv:
        RecvComplete(socketData, len);
        break;
    default:
        WRITE_LOG(LogLevel::Error, "INVALID EventID:[%d] SOCKET:[%lld].", socketData->EventID, socketData->ConnectSocket);
        assert(false);
        break;
    }
    socketData->Free();
}

bool TcpIOCP::PostConnect(const char* ip, int port)
{
    auto connectSocket = PrepareSocket();
    if (connectSocket == INVALID_SOCKET)
    {
        WRITE_ERROR_LOG(GetLastError(), "CreateSocket Failed.");
        return false;
    }
    SocketData* socketData = SocketData::Allocate();
    socketData->EventID = EventConnect;
    socketData->SessionID = ++m_LastSessionID;
    socketData->ConnectSocket = connectSocket;
    socketData->WsaBuffer.len = sizeof(socketData->Buffer);
    socketData->WsaBuffer.buf = socketData->Buffer;
    memset(socketData->Buffer, 0, sizeof(socketData->Buffer));
    socketData->RemoteAddress.sin_family = AF_INET;
    socketData->RemoteAddress.sin_addr.S_un.S_addr = inet_addr(ip);
    socketData->RemoteAddress.sin_port = htons(port);

    WRITE_LOG(LogLevel::Info, "PostConnect For SessionID:[%d] SOCKET:[%lld].", socketData->SessionID, socketData->ConnectSocket);
    DWORD transBytes = 0;
    if (!SocketApi::GetInstance().ConnectEx(socketData->ConnectSocket, (const sockaddr*)&socketData->RemoteAddress, sizeof(SOCKADDR_IN),
        NULL, 0, &transBytes, (LPOVERLAPPED)socketData) && WSAGetLastError() != ERROR_IO_PENDING)
    {
        WRITE_ERROR_LOG(WSAGetLastError(), "Call ConnectEx Failed.");
        return false;
    }
    return true;
}
bool TcpIOCP::PostDisConnect(int sessionID)
{
    auto connectData = GetConnect(sessionID);
    if (connectData == nullptr)
    {
        WRITE_LOG(LogLevel::Warning, "Get ConnectData Failed while PostDisConnect For SessionID:[%d].", sessionID);
        return false;
    }

    WRITE_LOG(LogLevel::Info, "PostDisConnect For SessionID:[%d], Socket:[%lld].", sessionID, connectData->SocketID);
    auto socketData = SocketData::Allocate();
    socketData->EventID = EventDisConnect;
    socketData->SessionID = sessionID;
    socketData->ConnectSocket = connectData->SocketID;
    if (!SocketApi::GetInstance().DisconnectEx(socketData->ConnectSocket, (LPOVERLAPPED)socketData, TF_REUSE_SOCKET, 0) && WSAGetLastError() != ERROR_IO_PENDING)
    {
        WRITE_ERROR_LOG(WSAGetLastError(), "Call DisconnectEx Failed.");
        return false;
    }

    return true;
}
bool TcpIOCP::PostAccept()
{
    SocketData* socketData = SocketData::Allocate();
    socketData->EventID = EventAccept;
    socketData->SessionID = ++m_LastSessionID;
    socketData->ConnectSocket = AllocateSocket();
    if (socketData->ConnectSocket == INVALID_SOCKET)
    {
        WRITE_ERROR_LOG(GetLastError(), "CreateSocket Failed.");
        socketData->Free();
        return false;
    }
    socketData->WsaBuffer.len = sizeof(socketData->Buffer);
    socketData->WsaBuffer.buf = socketData->Buffer;
    memset(socketData->Buffer, 0, sizeof(socketData->Buffer));

    WRITE_LOG(LogLevel::Info, "PostAccept SessionID:[%d] SOCKET:[%lld].", socketData->SessionID, socketData->ConnectSocket);
    DWORD transBytes = 0;
    if (!SocketApi::GetInstance().AcceptEx(m_InitSocket, socketData->ConnectSocket, socketData->WsaBuffer.buf, 0,
        (sizeof(SOCKADDR_IN) + 16), (sizeof(SOCKADDR_IN) + 16), &transBytes, (LPOVERLAPPED)socketData) && WSAGetLastError() != ERROR_IO_PENDING)
    {
        WRITE_LOG(LogLevel::Error, "Call AcceptEx Failed. Socket:[%lld]", socketData->ConnectSocket);
        WRITE_ERROR_LOG(WSAGetLastError(), "Call AcceptEx Failed.");
        return false;
    }
    return true;
}
bool TcpIOCP::PostSend(TcpEvent* tcpEvent)
{
    auto connectData = GetConnect(tcpEvent->SessionID);
    if (connectData == nullptr)
    {
        WRITE_LOG(LogLevel::Warning, "Get ConnectData Failed while PostSend For SessionID:[%d].", tcpEvent->SessionID);
        return false;
    }
    WRITE_LOG(LogLevel::Info, "WSASend sessionID:[%d] Len:[%d], Data:[%s].", tcpEvent->SessionID, tcpEvent->Length, tcpEvent->ReadPos);
    while (tcpEvent->Length > 0)
    {
        DWORD transBytes = 0, flag = 0;
        int currSendLen = tcpEvent->Length >= MESSAGE_SIZE ? MESSAGE_SIZE : tcpEvent->Length;
        auto socketData = SocketData::Allocate();
        socketData->EventID = EventSend;
        socketData->SessionID = tcpEvent->SessionID;
        socketData->ConnectSocket = connectData->SocketID;
        socketData->WsaBuffer.len = currSendLen;
        socketData->WsaBuffer.buf = socketData->Buffer;
        memcpy(socketData->Buffer, tcpEvent->ReadPos, currSendLen);

        if (WSASend(socketData->ConnectSocket, &socketData->WsaBuffer, 1, &transBytes, flag, (LPOVERLAPPED)socketData, NULL) == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
        {
            WRITE_ERROR_LOG(WSAGetLastError(), "PostSend: WSASend failed.");
            socketData->Free();
            PostDisConnect(tcpEvent->SessionID);
            return false;
        }

        tcpEvent->Length -= currSendLen;
        tcpEvent->ReadPos += currSendLen;
    }
    return true;
}
bool TcpIOCP::PostRecv(int sessionID, SOCKET sock)
{
    WRITE_LOG(LogLevel::Info, "PostRecv SessionID:[%d] Socket:[%lld]", sessionID, sock);
    auto socketData = SocketData::Allocate();
    socketData->EventID = EventRecv;
    socketData->SessionID = sessionID;
    socketData->ConnectSocket = sock;
    socketData->WsaBuffer.len = sizeof(socketData->Buffer);
    socketData->WsaBuffer.buf = socketData->Buffer;
    memset(socketData->Buffer, 0, sizeof(socketData->Buffer));

    DWORD transBytes = 0, flag = 0;
    if (WSARecv(socketData->ConnectSocket, &socketData->WsaBuffer, 1, &transBytes, &flag, (LPOVERLAPPED)socketData, NULL) == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
    {
        WRITE_ERROR_LOG(WSAGetLastError(), "PostRecv: WSARecv failed.");
        PostDisConnect(socketData->SessionID);
        socketData->Free();
        return false;
    }
    return true;
}

void TcpIOCP::ConnectComplete(SocketData* socketData, int len)
{
    WRITE_LOG(LogLevel::Info, "ConnectComplete  SOCKET:[%lld] Len:[%d], WSALen:[%d].",
        socketData->ConnectSocket, len, socketData->WsaBuffer.len);
    AddConnect(socketData);
    PostRecv(socketData->SessionID, socketData->ConnectSocket);
}
void TcpIOCP::DisConnectComplete(SocketData* socketData, int len)
{
    RemoveConnect(socketData);
    FreeSocket(socketData->ConnectSocket);
}
void TcpIOCP::AcceptComplete(SocketData* socketData, int len)
{
    SOCKADDR_IN* remoteAddr = NULL;
    SOCKADDR_IN* localAddr = NULL;
    int remoteLen = sizeof(SOCKADDR_IN), localLen = sizeof(SOCKADDR_IN);
    SocketApi::GetInstance().GetAcceptExSockAddrs(socketData->WsaBuffer.buf, 0,
        (sizeof(SOCKADDR_IN) + 16), (sizeof(SOCKADDR_IN) + 16), (LPSOCKADDR*)&localAddr, &localLen, (LPSOCKADDR*)&remoteAddr, &remoteLen);

    WRITE_LOG(LogLevel::Info, "AcceptComplete: From <%s:%d> SOCKET:[%lld] Len:[%d], WSALen:[%d].",
        inet_ntoa(remoteAddr->sin_addr), ntohs(remoteAddr->sin_port), socketData->ConnectSocket, len, socketData->WsaBuffer.len);

    if (!IOCompletePort::GetInstance().AssociateDevice((HANDLE)socketData->ConnectSocket, socketData->ConnectSocket))
    {
        WRITE_LOG(LogLevel::Warning, "Associate CompletionPort Failed, SessionID:[%d] Socket:[%lld]", socketData->SessionID, socketData->ConnectSocket);
    }
    AddConnect(socketData);
    PostRecv(socketData->SessionID, socketData->ConnectSocket);
    PostAccept();
}
void TcpIOCP::SendComplete(SocketData* socketData, int len)
{
    WRITE_LOG(LogLevel::Info, "SendComplete  SessionID:[%d] SOCKET:[%lld], WsaLen=[%d], Len=[%d].", socketData->SessionID, socketData->ConnectSocket, socketData->WsaBuffer.len, len);
    m_TotalSendLen += len;
    if (len < socketData->WsaBuffer.len)
    {
        WRITE_LOG(LogLevel::Warning, "Sendlen:[%d] Less than TargetLen:[%d].", len, socketData->WsaBuffer.len);
        PostDisConnect(socketData->SessionID);
    }
}
void TcpIOCP::RecvComplete(SocketData* socketData, int len)
{
    WRITE_LOG(LogLevel::Info, "RecvComplete  SessionID:[%d] SOCKET:[%lld], WsaLen=[%d], Len=[%d].", socketData->SessionID, socketData->ConnectSocket, socketData->WsaBuffer.len, len);
    m_TotalRecvLen += len;

    socketData->EventID = EventRecv;
    socketData->WsaBuffer.len = len;

    TcpEvent* tcpEvent = TcpEvent::Allocate();
    tcpEvent->EventID = EventRecv;
    tcpEvent->SessionID = socketData->SessionID;
    tcpEvent->IP = inet_ntoa(socketData->RemoteAddress.sin_addr);
    tcpEvent->Port = ntohs(socketData->RemoteAddress.sin_port);
    memcpy(tcpEvent->Buff, socketData->WsaBuffer.buf, socketData->WsaBuffer.len);
    tcpEvent->Length = socketData->WsaBuffer.len;
    tcpEvent->ReadPos[tcpEvent->Length] = '\0';
    
    m_TcpSubscriber->OnRecv(tcpEvent);
    PostRecv(socketData->SessionID, socketData->ConnectSocket);
}
void TcpIOCP::AddConnect(SocketData* socketData)
{
    WRITE_LOG(LogLevel::Info, "AddConnect  SessionID:[%d] Socket:[%lld].", socketData->SessionID, socketData->ConnectSocket);

    auto connectData = ConnectData::Allocate(socketData->SessionID, socketData->ConnectSocket, inet_ntoa(socketData->RemoteAddress.sin_addr), ntohs(socketData->RemoteAddress.sin_port));
    m_ConnectDatas.insert(make_pair(socketData->SessionID, connectData));
    m_TcpSubscriber->OnConnect(connectData->SessionID, connectData->RemoteIP.c_str(), connectData->RemotePort);
}
void TcpIOCP::RemoveConnect(SocketData* socketData)
{
    WRITE_LOG(LogLevel::Info, "RemoveConnect  SessionID:[%d] Socket:[%lld].", socketData->SessionID, socketData->ConnectSocket);
    auto connectData = GetConnect(socketData->SessionID);
    if (connectData == nullptr)
    {
        WRITE_LOG(LogLevel::Warning, "Get ConnectData Failed while RemoveConnect For SessionID:[%d].", connectData->SessionID);
        return;
    }
    m_ConnectDatas[socketData->SessionID]->Free();
    m_ConnectDatas.erase(socketData->SessionID);
}
ConnectData* TcpIOCP::GetConnect(int sessionID)
{
    if (m_ConnectDatas.find(sessionID) == m_ConnectDatas.end())
    {
        return nullptr;
    }
    return m_ConnectDatas[sessionID];
}

SOCKET TcpIOCP::AllocateSocket()
{
    return t_SocketMemCache.Allocate();
}
SOCKET TcpIOCP::PrepareSocket()
{
    auto sock = t_SocketMemCache.Allocate();
    if (bind(sock, (const sockaddr*)&m_LocalAddress, sizeof(SOCKADDR_IN)) != 0)
    {
        WRITE_LOG(LogLevel::Error, "Bind Failed. ErrorID:[%d], Socket:[%lld]", GetLastError(), sock);
        closesocket(sock);
        return INVALID_SOCKET;
    }
    if (!IOCompletePort::GetInstance().AssociateDevice((HANDLE)sock, sock))
    {
        WRITE_LOG(LogLevel::Error, "Associate CompletionPort Failed. ErrorID:[%d], Socket:[%lld]", GetLastError(), sock);
        closesocket(sock);
        return INVALID_SOCKET;
    }
    return sock;
}
void TcpIOCP::FreeSocket(SOCKET socket)
{
    t_SocketMemCache.Free(socket);
}