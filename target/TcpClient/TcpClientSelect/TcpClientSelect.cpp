#include "TcpClientSelect.h"
#include "Logger.h"
#include <iostream>

using namespace std;

TcpClientSelect TcpClientSelect::m_Instance;

TcpClientSelect::TcpClientSelect(const char* name)
	:ThreadBase(name), m_AddressLen(sizeof(sockaddr))
{

}

TcpClientSelect& TcpClientSelect::GetInstance()
{
	return m_Instance;
}

void TcpClientSelect::SetTcpInfo(long micro_seconds, int af, int type, int protocol)
{
	m_TimeOut.tv_sec = micro_seconds / 1000000;
	m_TimeOut.tv_usec = micro_seconds % 1000000;
	m_AF = af;
	m_Type = type;
	m_Protocol = protocol;

	memset(&m_ServerAddress, 0, sizeof(m_ServerAddress));
	m_ServerAddress.sin_family = af;
}
bool TcpClientSelect::Init()
{
	return true;
}

int TcpClientSelect::Connect(const char* ip, unsigned short port)
{
	m_ServerAddress.sin_addr.S_un.S_addr = inet_addr(ip);
	m_ServerAddress.sin_port = htons(port);

	SOCKET socketID = socket(m_AF, m_Type, 0);
	int on = 1;
	int ret = setsockopt(socketID, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
	WRITE_LOG(LogLevel::Info, "setsockopt: ret[%d].\n", ret);

	unsigned long unblock = 1;
	ret = ::ioctlsocket(socketID, FIONBIO, &unblock);
	WRITE_LOG(LogLevel::Info, "ioctlsocket: ret[%d].\n", ret);
	if (ret == SOCKET_ERROR)
	{
		closesocket(socketID);
		return ret;
	}

	ret = connect(socketID, (sockaddr*)&m_ServerAddress, m_AddressLen);
	WRITE_LOG(LogLevel::Info, "Connect Server: ret[%d]\n", ret);
	if (ret < 0)
	{
		fd_set writefds;
		struct timeval timeout;
		FD_ZERO(&writefds);
		FD_SET(socketID, &writefds);
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		ret = select(0, NULL, &writefds, NULL, &timeout);
		WRITE_LOG(LogLevel::Info, "Connect Select: ret[%d]\n", ret);
		if (ret == 0)
		{
			WRITE_LOG(LogLevel::Info, "Connect Failed due to timeout");
			closesocket(socketID);
			return SOCKET_ERROR;
		}
		if (ret < 0 || !FD_ISSET(socketID, &writefds))
		{
			WRITE_LOG(LogLevel::Info, "Connect Failed.");
			closesocket(socketID);
			return SOCKET_ERROR;
		}
	}
	
	auto sessionID = ++m_MaxSessionID;
	AddConnect(sessionID, socketID, ip, port);
	return sessionID;
}
void TcpClientSelect::DisConnect(int sessionID)
{
	lock_guard<mutex> guard(m_DisConnectSessionMutex);
	m_DisConnectSessions.push_back(sessionID);
}
bool TcpClientSelect::Send(int sessionID, const char* data, int length)
{
	lock_guard<mutex> guard(m_ConnectDataMutex);
	if (m_ConnectDatas.find(sessionID) == m_ConnectDatas.end())
	{
		return false;
	}
	auto connectionData = m_ConnectDatas[sessionID];
	return connectionData->Send(data, length);
}

void TcpClientSelect::Run()
{
	DisConnectSessions();
	PrepareFds();
	::select(0, &m_RecvFds, &m_SendFds, nullptr, &m_TimeOut);
	OnSend();
	OnRecv();
}
void TcpClientSelect::DisConnectSessions()
{
	lock_guard<mutex> guard(m_DisConnectSessionMutex);
	for (auto& sessionID : m_DisConnectSessions)
	{
		RemoveConnect(sessionID);
	}
	m_DisConnectSessions.clear();
}
void TcpClientSelect::PrepareFds()
{
	FD_ZERO(&m_RecvFds);
	FD_ZERO(&m_SendFds);

	for (auto& it : m_ConnectDatas)
	{
		if (it.second != nullptr)
		{
			auto socketID = it.second->SocketID;
			FD_SET(socketID, &m_RecvFds);
			if (it.second && !it.second->SendCache->IsEmpty())
			{
				FD_SET(socketID, &m_SendFds);
			}
		}
	}
}
void TcpClientSelect::OnSend()
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
void TcpClientSelect::OnRecv()
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

				ExecuteCommand(sessionID);
			}
			else
			{
				DisConnect(sessionID);
			}
		}
	}
}

void TcpClientSelect::ExecuteCommand(int sessionID)
{
	if (strcmp(m_RecvBuffer, "quit") == 0)
	{
		DisConnect(sessionID);
	}
	if (strcmp(m_RecvBuffer, "stop") == 0)
	{
		m_ShouldRun = false;
	}
}
void TcpClientSelect::AddConnect(int sessionID, SOCKET socketID, const char* ip, unsigned short port)
{
	WRITE_LOG(LogLevel::Info, "New Connection. SessionID[%d], Socket[%lld], ClientIP[%s], ClientPort[%d]", sessionID, socketID, ip, port);
	m_SocketIndex.insert(make_pair(socketID, sessionID));
	{
		lock_guard<mutex> guard(m_ConnectDataMutex);
		m_ConnectDatas.insert(make_pair(sessionID, new ConnectData(sessionID, socketID, ip, port)));
	}
}
void TcpClientSelect::RemoveConnect(int sessionID)
{
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
	m_SocketIndex.erase(socketID);
	::closesocket(socketID);
	WRITE_LOG(LogLevel::Info, "Close Connection: SessionID[%d], SocketID[%lld]", sessionID, socketID);
}

void TcpClientSelect::ClearSessions()
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


void TcpClientSelectTest()
{
	TcpClientSelect::GetInstance().SetTcpInfo(6000);
	TcpClientSelect::GetInstance().Init();
	TcpClientSelect::GetInstance().Start();

	list<int> sessionIDs;
	for (auto i = 0; i < 10; i++)
	{
		auto sessionID = TcpClientSelect::GetInstance().Connect("127.0.0.1", 6000);
		if (sessionID != SOCKET_ERROR)
		{
			sessionIDs.push_back(sessionID);
		}
	}
	char sendBuff[1024] = { 0 };
	int count = 0;
	while (true)
	{
		printf("Please input data:");
		cin >> sendBuff;

		for (auto& sessionID : sessionIDs)
		{
			if (sessionID % 2 == count)
			{
				TcpClientSelect::GetInstance().Send(sessionID, sendBuff, strlen(sendBuff));
			}
		}
		count++;
		count %= 2;
	}


	TcpClientSelect::GetInstance().Join();
}
