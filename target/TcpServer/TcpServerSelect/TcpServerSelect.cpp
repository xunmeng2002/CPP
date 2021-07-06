#include "TcpServerSelect.h"
#include "Logger.h"

using namespace std;

TcpServerSelect TcpServerSelect::m_Instance;

TcpServerSelect::TcpServerSelect(const char* name)
	:ThreadBase(name), m_AddressLen(sizeof(sockaddr))
{

}

TcpServerSelect& TcpServerSelect::GetInstance()
{
	return m_Instance;
}

void TcpServerSelect::SetTcpInfo(unsigned short port, long micro_seconds, int af, int type, int protocol, int backlog)
{
	m_TimeOut.tv_sec = micro_seconds / 1000000;
	m_TimeOut.tv_usec = micro_seconds % 1000000;
	m_Port = port;
	m_AF = af;
	m_Type = type;
	m_Protocol = protocol;
	m_Backlog = backlog;

	memset(&m_ServerAddress, 0, sizeof(m_ServerAddress));
	m_ServerAddress.sin_family = af;
	m_ServerAddress.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	m_ServerAddress.sin_port = htons(port);
}
bool TcpServerSelect::Init()
{
	m_ListenSocketID = ::socket(m_AF, m_Type, m_Protocol);
	WRITE_LOG(LogLevel::Info, "create socket: m_ListenSocketID[%lld].\n", m_ListenSocketID);
	if (m_ListenSocketID == INVALID_SOCKET)
	{
		return false;
	}
	if (!Listen())
	{
		closesocket(m_ListenSocketID);
		return false;
	}
	return true;
}

void TcpServerSelect::DisConnect(int sessionID)
{
	lock_guard<mutex> guard(m_DisConnectSessionMutex);
	m_DisConnectSessions.push_back(sessionID);
}
bool TcpServerSelect::Send(int sessionID, const char* data, int length)
{
	lock_guard<mutex> guard(m_ConnectDataMutex);
	if (m_ConnectDatas.find(sessionID) == m_ConnectDatas.end())
	{
		return false;
	}
	auto connectionData = m_ConnectDatas[sessionID];
	return connectionData->Send(data, length);
}

void TcpServerSelect::Run()
{
	DisConnectSessions();
	PrepareFds();
	::select(0, &m_RecvFds, &m_SendFds, nullptr, &m_TimeOut);
	OnAccept();
	OnSend();
	OnRecv();
}
bool TcpServerSelect::Listen()
{
	int on = 1;
	int ret = setsockopt(m_ListenSocketID, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
	WRITE_LOG(LogLevel::Info, "setsockopt: ret[%d].\n", ret);

	unsigned long unblock = 1;
	ret = ::ioctlsocket(m_ListenSocketID, FIONBIO, &unblock);
	WRITE_LOG(LogLevel::Info, "ioctlsocket: ret[%d].\n", ret);
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	ret = ::bind(m_ListenSocketID, (sockaddr*)&m_ServerAddress, sizeof(m_ServerAddress));
	WRITE_LOG(LogLevel::Info, "bind: ret[%d].\n", ret);
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	ret = ::listen(m_ListenSocketID, m_Backlog);
	WRITE_LOG(LogLevel::Info, "listen: ret[%d].\n", ret);
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}
void TcpServerSelect::DisConnectSessions()
{
	lock_guard<mutex> guard(m_DisConnectSessionMutex);
	for (auto& sessionID : m_DisConnectSessions)
	{
		RemoveConnect(sessionID);
	}
	m_DisConnectSessions.clear();
}
void TcpServerSelect::PrepareFds()
{
	FD_ZERO(&m_RecvFds);
	FD_ZERO(&m_SendFds);
	FD_SET(m_ListenSocketID, &m_RecvFds);

	for (auto& it : m_ConnectDatas)
	{
		auto socketID = it.second->SocketID;
		FD_SET(socketID, &m_RecvFds);
		if (it.second && !it.second->SendCache->IsEmpty())
		{
			FD_SET(socketID, &m_SendFds);
		}
	}
}
void TcpServerSelect::OnAccept()
{
	if (FD_ISSET(m_ListenSocketID, &m_RecvFds))
	{
		for (int i = 0; i < m_Backlog; i++)
		{
			SOCKET socketID = accept(m_ListenSocketID, (sockaddr*)&m_ClientAddress, &m_AddressLen);
			WRITE_LOG(LogLevel::Info, "accept: socketID[%lld]", socketID);
			if (socketID == INVALID_SOCKET)
			{
				break;
			}
			auto sessionID = ++m_MaxSessionID;
			auto ip = inet_ntoa(m_ClientAddress.sin_addr);
			auto port = ntohs(m_ClientAddress.sin_port);

			AddConnect(sessionID, socketID, ip, port);
		}
	}
}
void TcpServerSelect::OnSend()
{
	for (auto& it : m_ConnectDatas)
	{
		auto connectData = it.second;
		if (FD_ISSET(connectData->SocketID, &m_SendFds))
		{
			if (connectData->OnSend() < 0)
			{
				lock_guard<mutex> guard(m_DisConnectSessionMutex);
				m_DisConnectSessions.push_back(it.first);
			}
		}
	}
}
void TcpServerSelect::OnRecv()
{
	for (auto& it : m_SocketIndex)
	{
		SOCKET socketID = it.first;
		int sessionID = it.second;
		if (FD_ISSET(socketID, &m_RecvFds))
		{
			int len = recv(socketID, m_RecvBuffer, MAX_SINGLE_MESSAGE_LENGTH - 1, 0);
			WRITE_LOG(LogLevel::Info, "SessionID[%d], Socket[%lld], Recv len[%d]", sessionID, socketID, len);
			if (len > 0)
			{
				m_RecvBuffer[len] = '\0';
				WRITE_LOG(LogLevel::Info, "recv:[%s]", m_RecvBuffer);

				Send(sessionID, m_RecvBuffer, len);
			}
			else
			{
				DisConnect(sessionID);
			}
		}
	}
}

void TcpServerSelect::AddConnect(int sessionID, SOCKET socketID, const char* ip, unsigned short port)
{
	WRITE_LOG(LogLevel::Info, "New Connection. SessionID[%d], Socket[%lld], ClientIP[%s], ClientPort[%d]", sessionID, socketID, ip, port);
	//WorkThread::GetInstance().AddSession(sessionID, ip, port);
	{
		m_SocketIndex.insert(make_pair(socketID, sessionID));
	}
	
	{
		lock_guard<mutex> guard(m_ConnectDataMutex);
		m_ConnectDatas.insert(make_pair(sessionID, new ConnectData(sessionID, socketID, ip, port)));
	}
}
void TcpServerSelect::RemoveConnect(int sessionID)
{
	//WorkThread::GetInstance().RemoveSession(sessionID);
	SOCKET socketID = SOCKET_ERROR;
	{
		lock_guard<mutex> guard(m_ConnectDataMutex);
		if (m_ConnectDatas.find(sessionID) != m_ConnectDatas.end())
		{
			socketID = m_ConnectDatas[sessionID]->SocketID;
			delete m_ConnectDatas[sessionID];
			m_ConnectDatas.erase(sessionID);
		}
	}
	WRITE_LOG(LogLevel::Info, "Close Connection: SessionID[%d], SocketID[%lld]", sessionID, socketID);
	m_SocketIndex.erase(socketID);
	::closesocket(socketID);	
}

void TcpServerSelect::ClearSessions()
{
	{
		lock_guard<mutex> guard(m_ConnectDataMutex);
		for (auto& it : m_ConnectDatas)
		{
			delete it.second;
		}
		m_ConnectDatas.clear();
	}
	m_SocketIndex.clear();
}


void TcpServerSelectTest()
{
	TcpServerSelect::GetInstance().SetTcpInfo(6000);
	TcpServerSelect::GetInstance().Init();
	TcpServerSelect::GetInstance().Start();
	TcpServerSelect::GetInstance().Join();
}
