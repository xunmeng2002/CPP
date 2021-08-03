#include "TcpThread.h"
#include "Logger.h"
#include "WorkThread.h"

using namespace std;

TcpThread TcpThread::m_Instance;

TcpThread::TcpThread(const char* name)
	:ThreadBase(name), m_AddressLen(sizeof(sockaddr))
{
	m_ConnectTimeOut.tv_sec = 5;
	m_ConnectTimeOut.tv_usec = 0;

	m_TimeOut.tv_sec = 1;
	m_TimeOut.tv_usec = 0;
}
TcpThread& TcpThread::GetInstance()
{
	return m_Instance;
}

void TcpThread::SetTcpInfo(long micro_seconds, int af, int type, int protocol)
{
	m_TimeOut.tv_sec = micro_seconds / 1000000;
	m_TimeOut.tv_usec = micro_seconds % 1000000;
	m_AF = af;
	m_Type = type;
	m_Protocol = protocol;

	memset(&m_ServerAddress, 0, sizeof(m_ServerAddress));
	m_ServerAddress.sin_family = af;
}
bool TcpThread::Init()
{
	return true;
}
int TcpThread::Connect(const char* ip, unsigned short port)
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
		return SOCKET_ERROR;
	}

	ret = connect(socketID, (sockaddr*)&m_ServerAddress, m_AddressLen);
	WRITE_LOG(LogLevel::Info, "Connect Server: ret[%d]\n", ret);

	int sessionID = ++m_MaxSessionID;
	ConnectData* connectData = new ConnectData(sessionID, socketID, ip, port);
	lock_guard<mutex> guard(m_ConnectingSocketMutex);
	m_ConnectingSocket.push_back(connectData);
	return sessionID;
}
void TcpThread::DisConnect(int sessionID)
{
	lock_guard<mutex> guard(m_DisConnectSessionMutex);
	m_DisConnectSessions.push_back(GetSessionData(sessionID));
}
bool TcpThread::Send(int sessionID, const char* data, int length)
{
	lock_guard<mutex> guard(m_ConnectDataMutex);
	if (m_ConnectDatas.find(sessionID) == m_ConnectDatas.end())
	{
		return false;
	}
	auto connectionData = m_ConnectDatas[sessionID];
	return connectionData->Send(data, length);
}

void TcpThread::Run()
{
	DisConnectSessions();
	OnConncect();
	PrepareFds();
	::select(0, &m_RecvFds, &m_SendFds, nullptr, &m_TimeOut);
	OnSend();
	OnRecv();
}
void TcpThread::DisConnectSessions()
{
	lock_guard<mutex> guard(m_DisConnectSessionMutex);
	for (auto& connectData : m_DisConnectSessions)
	{
		RemoveSessionData(connectData);
	}
	m_DisConnectSessions.clear();
}
void TcpThread::OnConncect()
{
	lock_guard<mutex> guard(m_ConnectingSocketMutex);
	if (m_ConnectingSocket.size() == 0)
		return;
	for (auto& connectData : m_ConnectingSocket)
	{
		FD_ZERO(&m_ConnectFds);
		FD_SET(connectData->SocketID, &m_ConnectFds);
	}
	auto ret = select(0, NULL, &m_ConnectFds, NULL, &m_ConnectTimeOut);
	WRITE_LOG(LogLevel::Info, "Connect Select: ret[%d]\n", ret);
	for (auto& connectData : m_ConnectingSocket)
	{
		if (ret == 0)
		{
			RemoveSessionData(connectData);
		}
		else if (ret < 0 || !FD_ISSET(connectData->SocketID, &m_ConnectFds))
		{
			RemoveSessionData(connectData);
		}
		else
		{
			AddSessionData(connectData);
		}
	}
	m_ConnectingSocket.clear();
}
void TcpThread::PrepareFds()
{
	FD_ZERO(&m_RecvFds);
	FD_ZERO(&m_SendFds);

	lock_guard<mutex> guard(m_ConnectDataMutex);
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
void TcpThread::OnSend()
{
	lock_guard<mutex> guard(m_ConnectDataMutex);
	for (auto& it : m_ConnectDatas)
	{
		auto connectData = it.second;
		if (FD_ISSET(connectData->SocketID, &m_SendFds))
		{
			if (connectData->OnSend() < 0)
			{
				lock_guard<mutex> guard(m_DisConnectSessionMutex);
				m_DisConnectSessions.push_back(connectData);
			}
		}
	}
}
void TcpThread::OnRecv()
{
	for (auto& it : m_SocketIndex)
	{
		SOCKET socketID = it.first;
		int sessionID = it.second;
		if (FD_ISSET(socketID, &m_RecvFds))
		{
			int len = recv(socketID, m_RecvBuffer, MAX_SINGLE_MESSAGE_LENGTH - 1, 0);
			if (len > 0)
			{
				m_RecvBuffer[len] = '\0';
				WRITE_LOG(LogLevel::Debug, "OnRecv: SessionID[%d], len[%d], [%s]", sessionID, len, m_RecvBuffer);
				WorkThread::GetInstance().OnRecv(sessionID, m_RecvBuffer, len);
			}
			else
			{
				WRITE_LOG(LogLevel::Info, "OnRecv: SessionID[%d], len[%d] DisConnect", sessionID, len);
				DisConnect(sessionID);
			}
		}
	}
}

void TcpThread::AddSessionData(ConnectData* connectData)
{
	WRITE_LOG(LogLevel::Info, "New Connection. SessionID[%d], Socket[%lld], ClientIP[%s], ClientPort[%d]", connectData->SessionID, connectData->SocketID, connectData->ClientIP, connectData->ClientPort);
	{
		lock_guard<mutex> guard(m_ConnectDataMutex);
		m_ConnectDatas.insert(make_pair(connectData->SessionID, connectData));
		m_SocketIndex.insert(make_pair(connectData->SocketID, connectData->SessionID));
	}
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_CONNECTED;
	myEvent->NumParams.push_back(connectData->SessionID);
	WorkThread::GetInstance().OnEvent(myEvent);
}
void TcpThread::RemoveSessionData(ConnectData* connectData)
{
	WRITE_LOG(LogLevel::Info, "Close Connection: SessionID[%d]", connectData->SessionID);
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DISCONNECTED;
	myEvent->NumParams.push_back(connectData->SessionID);
	WorkThread::GetInstance().OnEvent(myEvent);

	lock_guard<mutex> guard(m_ConnectDataMutex);
	m_ConnectDatas.erase(connectData->SessionID);
	m_SocketIndex.erase(connectData->SocketID);
	::closesocket(connectData->SocketID);
	delete connectData;
}
ConnectData* TcpThread::GetSessionData(int sessionID)
{
	lock_guard<mutex> guard(m_ConnectDataMutex);
	return m_ConnectDatas[sessionID];
}
void TcpThread::ClearSessions()
{
	m_SocketIndex.clear();
	lock_guard<mutex> guard(m_ConnectDataMutex);
	for (auto& it : m_ConnectDatas)
	{
		::closesocket(it.second->SocketID);
		delete it.second;
	}
	m_ConnectDatas.clear();
}