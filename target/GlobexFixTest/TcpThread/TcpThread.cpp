#include "TcpThread.h"
#include "Logger.h"
#include "WorkThread.h"
#include "MyEvent.h"

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
void TcpThread::Connect(const char* ip, unsigned short port)
{
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_CONNECT;
	myEvent->StringParams.push_back(ip);
	myEvent->NumParams.push_back(port);
	OnEvent(myEvent);
}
void TcpThread::DisConnect(int sessionID)
{
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DISCONNECT;
	myEvent->NumParams.push_back(sessionID);
	OnEvent(myEvent);
}
bool TcpThread::Send(int sessionID, const char* data, int length)
{
	auto connectionData = GetSessionData(sessionID);
	if (connectionData != nullptr)
	{
		return connectionData->Send(data, length);
	}
	WRITE_LOG(LogLevel::Error, "Send Failed SessionID:[%d]", sessionID);
	return false;
}

void TcpThread::Run()
{
	HandleEvent();
	PrepareFds();
	OnConncect();
	::select(0, &m_RecvFds, &m_SendFds, nullptr, &m_TimeOut);
	OnSend();
	OnRecv();
}
void TcpThread::HandleEvent()
{
	MyEvent* myEvent = nullptr;
	while (myEvent = GetEvent())
	{
		switch (myEvent->EventID)
		{
		case EVENT_CONNECT:
		{
			DoConnect(myEvent->StringParams[0], myEvent->NumParams[0]);
			break;
		}
		case EVENT_DISCONNECT:
		{
			DoDisConnect(myEvent->NumParams[0]);
			break;
		}
		default:
			break;
		}
		MyEvent::Free(myEvent);
	}
}
void TcpThread::DoConnect(const string& ip, int port)
{
	m_ServerAddress.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
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
		NotifyConnectStatus(ip, port, -1, EVENT_ON_DISCONNECTED);
		return ;
	}

	ret = connect(socketID, (sockaddr*)&m_ServerAddress, m_AddressLen);
	WRITE_LOG(LogLevel::Info, "Connect Server: ret[%d]\n", ret);

	int sessionID = ++m_MaxSessionID;
	ConnectData* connectData = ConnectData::Allocate(sessionID, socketID, ip, port);
	m_ConnectingSocket.push_back(connectData);
}
void TcpThread::DoDisConnect(int sessionID)
{
	auto connectData = GetSessionData(sessionID);
	if (connectData == nullptr)
	{
		WRITE_LOG(LogLevel::Warning, "DoDisConnect While ConnectData is nullptr, SessionID:[%d]", sessionID);
		return;
	}
	NotifyConnectStatus(connectData->ClientIP, connectData->ClientPort, connectData->SessionID, EVENT_ON_DISCONNECTED);
	RemoveSessionData(connectData);
}
void TcpThread::OnConncect()
{
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
			NotifyConnectStatus(connectData->ClientIP, connectData->ClientPort, connectData->SessionID, EVENT_ON_DISCONNECTED);
			ConnectData::Free(connectData);
		}
		else if (ret < 0 || !FD_ISSET(connectData->SocketID, &m_ConnectFds))
		{
			NotifyConnectStatus(connectData->ClientIP, connectData->ClientPort, connectData->SessionID, EVENT_ON_DISCONNECTED);
			ConnectData::Free(connectData);
		}
		else
		{
			NotifyConnectStatus(connectData->ClientIP, connectData->ClientPort, connectData->SessionID, EVENT_ON_CONNECTED);
			AddSessionData(connectData);
		}
	}
	m_ConnectingSocket.clear();
}
void TcpThread::PrepareFds()
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
				DisConnect(connectData->SessionID);
			}
		}
	}
}
void TcpThread::OnRecv()
{
	for (auto& it : m_ConnectDatas)
	{
		auto connectData = it.second;
		auto socketID = connectData->SocketID;
		int sessionID = connectData->SessionID;
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

void TcpThread::NotifyConnectStatus(const string& ip, int port, int sessionID, int eventID)
{
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = eventID;
	myEvent->StringParams.push_back(ip);
	myEvent->NumParams.push_back(port);
	myEvent->NumParams.push_back(sessionID);
	WorkThread::GetInstance().OnEvent(myEvent);
}
void TcpThread::AddSessionData(ConnectData* connectData)
{
	WRITE_LOG(LogLevel::Info, "New Connection. SessionID[%d], Socket[%lld], ClientIP[%s], ClientPort[%d]", connectData->SessionID, connectData->SocketID, connectData->ClientIP.c_str(), connectData->ClientPort);
	lock_guard<mutex> guard(m_ConnectDataMutex);
	m_ConnectDatas.insert(make_pair(connectData->SessionID, connectData));
}
void TcpThread::RemoveSessionData(ConnectData* connectData)
{
	WRITE_LOG(LogLevel::Info, "DisConnection. SessionID[%d], Socket[%lld], ClientIP[%s], ClientPort[%d]", connectData->SessionID, connectData->SocketID, connectData->ClientIP.c_str(), connectData->ClientPort);
	ConnectData::Free(connectData);
	lock_guard<mutex> guard(m_ConnectDataMutex);
	m_ConnectDatas.erase(connectData->SessionID);
}
ConnectData* TcpThread::GetSessionData(int sessionID)
{
	lock_guard<mutex> guard(m_ConnectDataMutex);
	if (m_ConnectDatas.find(sessionID) != m_ConnectDatas.end())
	{
		return m_ConnectDatas[sessionID];
	}
	return nullptr;
}