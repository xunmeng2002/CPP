#include "TcpSelectServer.h"
#include "Logger.h"
#include "Event.h"

using namespace std;


TcpSelectServer::TcpSelectServer()
	:TcpSelectBase("TcpSelectServer")
{
	m_ListenSocket = INVALID_SOCKET;
	memset(&m_ListenAddress, 0, sizeof(m_ListenAddress));
	m_Backlog = 5;
}
void TcpSelectServer::SetBindAddress(const char* ip, int port, int backLog)
{
	m_ListenAddress.sin_family = m_AF;
	m_ListenAddress.sin_addr.S_un.S_addr = inet_addr(ip);
	m_ListenAddress.sin_port = htons(port);
	
	m_Backlog = backLog;
	
	WRITE_LOG(LogLevel::Info, "TcpSelectServer SetBindAddress IP[%s], Port[%d]", ip, port);
}
bool TcpSelectServer::Init()
{
	m_ListenSocket = ::socket(m_AF, m_Type, m_Protocol);
	WRITE_LOG(LogLevel::Info, "create socket: m_ListenSocket[%lld].\n", m_ListenSocket);
	if (m_ListenSocket == INVALID_SOCKET)
	{
		return false;
	}
	if (SetSockReuse(m_ListenSocket) == SOCKET_ERROR || SetSockUnblock(m_ListenSocket) == SOCKET_ERROR || SetSockNodelay(m_ListenSocket) == SOCKET_ERROR)
	{
		closesocket(m_ListenSocket);
		return false;
	}
	if (Bind() == SOCKET_ERROR || Listen() == SOCKET_ERROR)
	{
		closesocket(m_ListenSocket);
		return false;
	}
	return true;
}
int TcpSelectServer::Bind()
{
	auto ret = ::bind(m_ListenSocket, (sockaddr*)&m_ListenAddress, sizeof(m_ListenAddress));
	WRITE_LOG(LogLevel::Info, "bind: Port[%d], ret[%d].\n", ntohs(m_ListenAddress.sin_port), ret);
	return ret;
}
int TcpSelectServer::Listen()
{
	auto ret = ::listen(m_ListenSocket, m_Backlog);
	WRITE_LOG(LogLevel::Info, "listen: ret[%d].\n", ret)
	return ret;
}
void TcpSelectServer::PrepareFds()
{
	TcpSelectBase::PrepareFds();
	FD_SET(m_ListenSocket, &m_RecvFds);
}
void TcpSelectServer::DoAccept()
{
	if (FD_ISSET(m_ListenSocket, &m_RecvFds))
	{
		for (int i = 0; i < m_Backlog; i++)
		{
			SOCKET socketID = accept(m_ListenSocket, (sockaddr*)&m_RemoteAddress, &m_AddressLen);
			if (socketID == INVALID_SOCKET)
			{
				break;
			}
			SetSockNodelay(socketID);

			auto sessionID = ++m_MaxSessionID;
			auto ip = inet_ntoa(m_RemoteAddress.sin_addr);
			auto port = ntohs(m_RemoteAddress.sin_port);
			WRITE_LOG(LogLevel::Info, "accept: SessionID[%d], SocketID[%lld], RemoteIP[%s], RemotePort[%d]", sessionID, socketID, ip, port);

			auto connectData = ConnectData::Allocate(sessionID, socketID, ip, port);
			AddConnect(connectData);
		}
	}
}
