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
    OverlappedData* overlappedData;

    auto bOK = IOCompletePort::GetInstance().GetStatus(&len, (PULONG_PTR)&socket, (LPOVERLAPPED*)&overlappedData, 5000);
    WRITE_LOG(LogLevel::Debug, "CompletionKey:[%d], Len:[%d], Ret:[%d].", socket, len, bOK);
    if (overlappedData == nullptr)
    {
        WRITE_LOG(LogLevel::Info, "CompetionKey:[%d], OverlappedData is null.", socket);
        return;
    }
    if (!bOK)
    {
        WRITE_LOG(LogLevel::Warning, "GetQueuedCompletionStatus Failed. ErrorID:[%d] SOCKET:[%lld].", GetLastError(), overlappedData->ConnectSocket);
        PostDisConnect(overlappedData->SessionID);
        overlappedData->Free();
        return;
    }
    if (len == 0 && (overlappedData->EventID == EventSend || overlappedData->EventID == EventRecv))
    {
        WRITE_LOG(LogLevel::Debug, "Disconnect SOCKET:[%lld].", overlappedData->ConnectSocket);
        PostDisConnect(overlappedData->SessionID);
        overlappedData->Free();
        return;
    }

    switch (overlappedData->EventID)
    {
    case EventConnect:
        ConnectComplete(overlappedData, len);
        break;
    case EventDisConnect:
        DisConnectComplete(overlappedData, len);
        break;
    case EventAccept:
        AcceptComplete(overlappedData, len);
        break;
    case EventSend:
        SendComplete(overlappedData, len);
        break;
    case EventRecv:
        RecvComplete(overlappedData, len);
        break;
    default:
        WRITE_LOG(LogLevel::Error, "INVALID EventID:[%d] SOCKET:[%lld].", overlappedData->EventID, overlappedData->ConnectSocket);
        assert(false);
        break;
    }
    overlappedData->Free();
}

bool TcpIOCP::PostConnect(const char* ip, int port)
{
    auto connectSocket = PrepareSocket();
    if (connectSocket == INVALID_SOCKET)
    {
        WRITE_ERROR_LOG(GetLastError(), "CreateSocket Failed.");
        return false;
    }
    OverlappedData* overlappedData = OverlappedData::Allocate();
    overlappedData->EventID = EventConnect;
    overlappedData->SessionID = ++m_LastSessionID;
    overlappedData->ConnectSocket = connectSocket;
    overlappedData->WsaBuffer.len = sizeof(overlappedData->Buffer);
    overlappedData->WsaBuffer.buf = overlappedData->Buffer;
    memset(overlappedData->Buffer, 0, sizeof(overlappedData->Buffer));
    overlappedData->RemoteAddress.sin_family = AF_INET;
    overlappedData->RemoteAddress.sin_addr.S_un.S_addr = inet_addr(ip);
    overlappedData->RemoteAddress.sin_port = htons(port);

    WRITE_LOG(LogLevel::Info, "PostConnect For SessionID:[%d] SOCKET:[%lld].", overlappedData->SessionID, overlappedData->ConnectSocket);
    DWORD transBytes = 0;
    if (!SocketApi::GetInstance().ConnectEx(overlappedData->ConnectSocket, (const sockaddr*)&overlappedData->RemoteAddress, sizeof(SOCKADDR_IN),
        NULL, 0, &transBytes, (LPOVERLAPPED)overlappedData) && WSAGetLastError() != ERROR_IO_PENDING)
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
    auto overlappedData = OverlappedData::Allocate();
    overlappedData->EventID = EventDisConnect;
    overlappedData->SessionID = sessionID;
    overlappedData->ConnectSocket = connectData->SocketID;
    if (!SocketApi::GetInstance().DisconnectEx(overlappedData->ConnectSocket, (LPOVERLAPPED)overlappedData, TF_REUSE_SOCKET, 0) && WSAGetLastError() != ERROR_IO_PENDING)
    {
        WRITE_ERROR_LOG(WSAGetLastError(), "Call DisconnectEx Failed.");
        return false;
    }

    return true;
}
bool TcpIOCP::PostAccept()
{
    OverlappedData* overlappedData = OverlappedData::Allocate();
    overlappedData->EventID = EventAccept;
    overlappedData->SessionID = ++m_LastSessionID;
    overlappedData->ConnectSocket = AllocateSocket();
    if (overlappedData->ConnectSocket == INVALID_SOCKET)
    {
        WRITE_ERROR_LOG(GetLastError(), "CreateSocket Failed.");
        overlappedData->Free();
        return false;
    }
    overlappedData->WsaBuffer.len = sizeof(overlappedData->Buffer);
    overlappedData->WsaBuffer.buf = overlappedData->Buffer;
    memset(overlappedData->Buffer, 0, sizeof(overlappedData->Buffer));

    WRITE_LOG(LogLevel::Info, "PostAccept SessionID:[%d] SOCKET:[%lld].", overlappedData->SessionID, overlappedData->ConnectSocket);
    DWORD transBytes = 0;
    if (!SocketApi::GetInstance().AcceptEx(m_InitSocket, overlappedData->ConnectSocket, overlappedData->WsaBuffer.buf, 0,
        (sizeof(SOCKADDR_IN) + 16), (sizeof(SOCKADDR_IN) + 16), &transBytes, (LPOVERLAPPED)overlappedData) && WSAGetLastError() != ERROR_IO_PENDING)
    {
        WRITE_LOG(LogLevel::Error, "Call AcceptEx Failed. Socket:[%lld]", overlappedData->ConnectSocket);
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
        auto overlappedData = OverlappedData::Allocate();
        overlappedData->EventID = EventSend;
        overlappedData->SessionID = tcpEvent->SessionID;
        overlappedData->ConnectSocket = connectData->SocketID;
        overlappedData->WsaBuffer.len = currSendLen;
        overlappedData->WsaBuffer.buf = overlappedData->Buffer;
        memcpy(overlappedData->Buffer, tcpEvent->ReadPos, currSendLen);

        if (WSASend(overlappedData->ConnectSocket, &overlappedData->WsaBuffer, 1, &transBytes, flag, (LPOVERLAPPED)overlappedData, NULL) == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
        {
            WRITE_ERROR_LOG(WSAGetLastError(), "PostSend: WSASend failed.");
            overlappedData->Free();
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
    auto overlappedData = OverlappedData::Allocate();
    overlappedData->EventID = EventRecv;
    overlappedData->SessionID = sessionID;
    overlappedData->ConnectSocket = sock;
    overlappedData->WsaBuffer.len = sizeof(overlappedData->Buffer);
    overlappedData->WsaBuffer.buf = overlappedData->Buffer;
    memset(overlappedData->Buffer, 0, sizeof(overlappedData->Buffer));

    DWORD transBytes = 0, flag = 0;
    if (WSARecv(overlappedData->ConnectSocket, &overlappedData->WsaBuffer, 1, &transBytes, &flag, (LPOVERLAPPED)overlappedData, NULL) == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING)
    {
        WRITE_ERROR_LOG(WSAGetLastError(), "PostRecv: WSARecv failed.");
        PostDisConnect(overlappedData->SessionID);
        overlappedData->Free();
        return false;
    }
    return true;
}

void TcpIOCP::ConnectComplete(OverlappedData* overlappedData, int len)
{
    WRITE_LOG(LogLevel::Info, "ConnectComplete  SOCKET:[%lld] Len:[%d], WSALen:[%d].",
        overlappedData->ConnectSocket, len, overlappedData->WsaBuffer.len);
    AddConnect(overlappedData);
    PostRecv(overlappedData->SessionID, overlappedData->ConnectSocket);
}
void TcpIOCP::DisConnectComplete(OverlappedData* overlappedData, int len)
{
    RemoveConnect(overlappedData);
    FreeSocket(overlappedData->ConnectSocket);
}
void TcpIOCP::AcceptComplete(OverlappedData* overlappedData, int len)
{
    SOCKADDR_IN* remoteAddr = NULL;
    SOCKADDR_IN* localAddr = NULL;
    int remoteLen = sizeof(SOCKADDR_IN), localLen = sizeof(SOCKADDR_IN);
    SocketApi::GetInstance().GetAcceptExSockAddrs(overlappedData->WsaBuffer.buf, 0,
        (sizeof(SOCKADDR_IN) + 16), (sizeof(SOCKADDR_IN) + 16), (LPSOCKADDR*)&localAddr, &localLen, (LPSOCKADDR*)&remoteAddr, &remoteLen);

    WRITE_LOG(LogLevel::Info, "AcceptComplete: From <%s:%d> SOCKET:[%lld] Len:[%d], WSALen:[%d].",
        inet_ntoa(remoteAddr->sin_addr), ntohs(remoteAddr->sin_port), overlappedData->ConnectSocket, len, overlappedData->WsaBuffer.len);

    if (!IOCompletePort::GetInstance().AssociateDevice((HANDLE)overlappedData->ConnectSocket, overlappedData->ConnectSocket))
    {
        WRITE_LOG(LogLevel::Warning, "Associate CompletionPort Failed, SessionID:[%d] Socket:[%lld]", overlappedData->SessionID, overlappedData->ConnectSocket);
    }
    AddConnect(overlappedData);
    PostRecv(overlappedData->SessionID, overlappedData->ConnectSocket);
    PostAccept();
}
void TcpIOCP::SendComplete(OverlappedData* overlappedData, int len)
{
    WRITE_LOG(LogLevel::Info, "SendComplete  SessionID:[%d] SOCKET:[%lld], WsaLen=[%d], Len=[%d].", overlappedData->SessionID, overlappedData->ConnectSocket, overlappedData->WsaBuffer.len, len);
    m_TotalSendLen += len;
    if (len < overlappedData->WsaBuffer.len)
    {
        WRITE_LOG(LogLevel::Warning, "Sendlen:[%d] Less than TargetLen:[%d].", len, overlappedData->WsaBuffer.len);
        PostDisConnect(overlappedData->SessionID);
    }
}
void TcpIOCP::RecvComplete(OverlappedData* overlappedData, int len)
{
    WRITE_LOG(LogLevel::Info, "RecvComplete  SessionID:[%d] SOCKET:[%lld], WsaLen=[%d], Len=[%d].", overlappedData->SessionID, overlappedData->ConnectSocket, overlappedData->WsaBuffer.len, len);
    m_TotalRecvLen += len;

    overlappedData->EventID = EventRecv;
    overlappedData->WsaBuffer.len = len;

    TcpEvent* tcpEvent = TcpEvent::Allocate();
    tcpEvent->EventID = EventRecv;
    tcpEvent->SessionID = overlappedData->SessionID;
    tcpEvent->IP = inet_ntoa(overlappedData->RemoteAddress.sin_addr);
    tcpEvent->Port = ntohs(overlappedData->RemoteAddress.sin_port);
    memcpy(tcpEvent->Buff, overlappedData->WsaBuffer.buf, overlappedData->WsaBuffer.len);
    tcpEvent->Length = overlappedData->WsaBuffer.len;
    tcpEvent->ReadPos[tcpEvent->Length] = '\0';
    
    m_TcpSubscriber->OnRecv(tcpEvent);
    PostRecv(overlappedData->SessionID, overlappedData->ConnectSocket);
}
void TcpIOCP::AddConnect(OverlappedData* overlappedData)
{
    WRITE_LOG(LogLevel::Info, "AddConnect  SessionID:[%d] Socket:[%lld].", overlappedData->SessionID, overlappedData->ConnectSocket);

    auto connectData = ConnectData::Allocate(overlappedData->SessionID, overlappedData->ConnectSocket, inet_ntoa(overlappedData->RemoteAddress.sin_addr), ntohs(overlappedData->RemoteAddress.sin_port));
    m_ConnectDatas.insert(make_pair(overlappedData->SessionID, connectData));
    m_TcpSubscriber->OnConnect(connectData->SessionID, connectData->RemoteIP.c_str(), connectData->RemotePort);
}
void TcpIOCP::RemoveConnect(OverlappedData* overlappedData)
{
    WRITE_LOG(LogLevel::Info, "RemoveConnect  SessionID:[%d] Socket:[%lld].", overlappedData->SessionID, overlappedData->ConnectSocket);
    auto connectData = GetConnect(overlappedData->SessionID);
    if (connectData == nullptr)
    {
        WRITE_LOG(LogLevel::Warning, "Get ConnectData Failed while RemoveConnect For SessionID:[%d].", connectData->SessionID);
        return;
    }
    m_ConnectDatas[overlappedData->SessionID]->Free();
    m_ConnectDatas.erase(overlappedData->SessionID);
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