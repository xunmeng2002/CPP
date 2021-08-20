#include "TcpSelectClient.h"
#include "Logger.h"
#include "WorkThread.h"

using namespace std;

TcpSelectClient::TcpSelectClient(TcpSubscriber* subscriber)
	:TcpSelectBase("TcpSelectClient", subscriber)
{
	FD_ZERO(&m_ConnectFds);
}

bool TcpSelectClient::Init()
{
	return true;
}
void TcpSelectClient::Connect(const char* ip, int port)
{
	TcpEvent* tcpEvent = TcpEvent::Allocate();
	tcpEvent->EventID = EVENT_CONNECT;
	tcpEvent->IP = ip;
	tcpEvent->Port = port;
	OnEvent(tcpEvent);
}

void TcpSelectClient::DoConnect(const string& ip, int port)
{
	m_RemoteAddress.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	m_RemoteAddress.sin_port = htons(port);

	SOCKET socketID = socket(m_AF, m_Type, 0);
	int on = 1;
	int ret = setsockopt(socketID, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
	WRITE_LOG(LogLevel::Info, "setsockopt: ret[%d].\n", ret);

	unsigned long unblock = 1;
	ret = ::ioctlsocket(socketID, FIONBIO, &unblock);
	WRITE_LOG(LogLevel::Info, "ioctlsocket: ret[%d].\n", ret);

	ret = connect(socketID, (sockaddr*)&m_RemoteAddress, m_AddressLen);
	WRITE_LOG(LogLevel::Info, "Connect Server: ret[%d]\n", ret);

	int sessionID = ++m_MaxSessionID;
	ConnectData* connectData = ConnectData::Allocate(sessionID, socketID, ip, port);
	m_ConnectingSocket.push_back(connectData);
}
void TcpSelectClient::CheckConnect()
{
	if (m_ConnectingSocket.size() == 0)
		return;
	FD_ZERO(&m_ConnectFds);
	for (auto& connectData : m_ConnectingSocket)
	{
		FD_SET(connectData->SocketID, &m_ConnectFds);
	}
	auto ret = select(0, NULL, &m_ConnectFds, NULL, &m_ConnectTimeOut);
	WRITE_LOG(LogLevel::Info, "Connect Select: ret[%d]\n", ret);
	while (!m_ConnectingSocket.empty())
	{
		auto connectData = m_ConnectingSocket.front();
		m_ConnectingSocket.pop_front();
		if (ret <= 0)
		{
			RemoveConnect(connectData);
		}
		else if (!FD_ISSET(connectData->SocketID, &m_ConnectFds))
		{
			RemoveConnect(connectData);
		}
		else
		{
			AddConnect(connectData);
		}
	}
}
