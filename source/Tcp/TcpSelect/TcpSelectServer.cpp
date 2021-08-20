#include "TcpSelectServer.h"
#include "Logger.h"
#include "MyEvent.h"

using namespace std;


TcpSelectServer::TcpSelectServer(TcpSubscriber* subscriber)
	:TcpSelectBase("TcpSelectServer", subscriber)
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
}
bool TcpSelectServer::Init()
{
	m_ListenSocket = ::socket(m_AF, m_Type, m_Protocol);
	WRITE_LOG(LogLevel::Info, "create socket: m_ListenSocket[%lld].\n", m_ListenSocket);
	if (m_ListenSocket == INVALID_SOCKET)
	{
		return false;
	}
	if (!Listen())
	{
		closesocket(m_ListenSocket);
		return false;
	}
	return true;
}
bool TcpSelectServer::Listen()
{
	int on = 1;
	int ret = setsockopt(m_ListenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
	WRITE_LOG(LogLevel::Info, "setsockopt: ret[%d].\n", ret);

	unsigned long unblock = 1;
	ret = ::ioctlsocket(m_ListenSocket, FIONBIO, &unblock);
	WRITE_LOG(LogLevel::Info, "ioctlsocket: ret[%d].\n", ret);
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	ret = ::bind(m_ListenSocket, (sockaddr*)&m_ListenAddress, sizeof(m_ListenAddress));
	WRITE_LOG(LogLevel::Info, "bind: ret[%d].\n", ret);
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	ret = ::listen(m_ListenSocket, m_Backlog);
	WRITE_LOG(LogLevel::Info, "listen: ret[%d].\n", ret);
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	return true;
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
			WRITE_LOG(LogLevel::Info, "accept: socketID[%lld]", socketID);
			if (socketID == INVALID_SOCKET)
			{
				break;
			}
			auto sessionID = ++m_MaxSessionID;
			auto ip = inet_ntoa(m_RemoteAddress.sin_addr);
			auto port = ntohs(m_RemoteAddress.sin_port);

			auto connectData = ConnectData::Allocate(sessionID, socketID, ip, port);
			AddConnect(connectData);
		}
	}
}
