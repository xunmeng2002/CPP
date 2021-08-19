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
void TcpThread::Send(int sessionID, const char* data, int length)
{
	TcpEvent* tcpEvent = TcpEvent::Allocate();
	tcpEvent->EventID = EVENT_ON_TCP_SEND;
	tcpEvent->SessionID = sessionID;
	memcpy(tcpEvent->Buff, data, length);
	tcpEvent->Length = length;

	OnEvent(tcpEvent);
}
void TcpThread::Send(TcpEvent* tcpEvent)
{
	OnEvent(tcpEvent);
}

void TcpThread::Run()
{
	HandleEvent();
	PrepareFds();
	OnConncect();
	::select(0, &m_RecvFds, &m_SendFds, nullptr, &m_TimeOut);
	DoSend();
	DoRecv();
}
void TcpThread::HandleEvent()
{
	Event* event = nullptr;
	MyEvent* myEvent = nullptr;
	TcpEvent* tcpEvent = nullptr;
	while (event = GetEvent())
	{
		bool shouldFree = true;
		switch (event->EventID)
		{
		case EVENT_CONNECT:
		{
			myEvent = (MyEvent*)event;
			DoConnect(myEvent->StringParams[0], myEvent->NumParams[0]);
			break;
		}
		case EVENT_DISCONNECT:
		{
			myEvent = (MyEvent*)event;
			DoDisConnect(myEvent->NumParams[0]);
			break;
		}
		case EVENT_ON_TCP_SEND:
		{
			tcpEvent = (TcpEvent*)event;
			PushSendEvent(tcpEvent);
			shouldFree = false;
			break;
		}
		default:
			break;
		}
		if (shouldFree)
		{
			event->Free();
		}
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
			connectData->Free();
		}
		else if (ret < 0 || !FD_ISSET(connectData->SocketID, &m_ConnectFds))
		{
			NotifyConnectStatus(connectData->ClientIP, connectData->ClientPort, connectData->SessionID, EVENT_ON_DISCONNECTED);
			connectData->Free();
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
		if (!m_SendEvents[it.first].empty())
		{
			FD_SET(it.second->SocketID, &m_SendFds);
		}
		FD_SET(it.second->SocketID, &m_RecvFds);
	}
}
void TcpThread::DoSend()
{
	for (auto& it : m_ConnectDatas)
	{
		auto connectData = it.second;
		if (FD_ISSET(connectData->SocketID, &m_SendFds))
		{
			while (auto tcpEvent = GetSendEvent(it.first))
			{
				int len = send(connectData->SocketID, tcpEvent->ReadPos, tcpEvent->Length, 0);
				if (len <= 0)
				{
					WRITE_LOG(LogLevel::Info, "DisConnect For Send len = [%d]", len);
					DisConnect(connectData->SessionID);
					tcpEvent->Free();
					break;
				}
				else if (len < tcpEvent->Length)
				{
					WRITE_LOG(LogLevel::Info, "OnSend, Send Less than expect. Expect Len[%d], Send Len[%d], Buff[%s]", tcpEvent->Length, len, tcpEvent->ReadPos);
					tcpEvent->ReadPos += len;
					tcpEvent->Length -= len;
					RePushSendEvent(tcpEvent);
					break;
				}
				else
				{
					WRITE_LOG(LogLevel::Debug, "OnSend Send Len[%d], Buff[%s]", tcpEvent->Length, tcpEvent->ReadPos);
				}
				tcpEvent->Free();
			}
		}
	}
}
void TcpThread::DoRecv()
{
	for (auto& it : m_ConnectDatas)
	{
		auto connectData = it.second;
		auto socketID = connectData->SocketID;
		int sessionID = connectData->SessionID;
		if (FD_ISSET(socketID, &m_RecvFds))
		{
			TcpEvent* tcpEvent = TcpEvent::Allocate();
			int len = recv(socketID, tcpEvent->Buff, BUFF_SIZE - 1, 0);
			if (len <= 0)
			{
				WRITE_LOG(LogLevel::Info, "OnRecv: SessionID[%d], len[%d] DisConnect", sessionID, len);
				tcpEvent->Free();
				DisConnect(sessionID);
			}
			else
			{
				tcpEvent->Buff[len] = '\0';
				WRITE_LOG(LogLevel::Debug, "OnRecv: SessionID[%d], len[%d], [%s]", sessionID, len, tcpEvent->Buff);
				tcpEvent->EventID = EVENT_ON_TCP_RECV;
				tcpEvent->SessionID = sessionID;
				tcpEvent->Length = len;

				WorkThread::GetInstance().OnRecv(tcpEvent);
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
	m_ConnectDatas.insert(make_pair(connectData->SessionID, connectData));
	m_SendEvents.insert(make_pair(connectData->SessionID, list<TcpEvent*>()));
}
void TcpThread::RemoveSessionData(ConnectData* connectData)
{
	WRITE_LOG(LogLevel::Info, "DisConnection. SessionID[%d], Socket[%lld], ClientIP[%s], ClientPort[%d]", connectData->SessionID, connectData->SocketID, connectData->ClientIP.c_str(), connectData->ClientPort);
	for (auto tcpEvent : m_SendEvents[connectData->SessionID])
	{
		tcpEvent->Free();
	}
	m_SendEvents.erase(connectData->SessionID);
	m_ConnectDatas.erase(connectData->SessionID);
	connectData->Free();
}
ConnectData* TcpThread::GetSessionData(int sessionID)
{
	if (m_ConnectDatas.find(sessionID) != m_ConnectDatas.end())
	{
		return m_ConnectDatas[sessionID];
	}
	return nullptr;
}
TcpEvent* TcpThread::GetSendEvent(int sessionID)
{
	if (m_SendEvents.find(sessionID) == m_SendEvents.end())
	{
		return nullptr;
	}
	if (m_SendEvents[sessionID].empty())
	{
		return nullptr;
	}
	auto tcpEvent = m_SendEvents[sessionID].front();
	m_SendEvents[sessionID].pop_front();
	return tcpEvent;
}
void TcpThread::PushSendEvent(TcpEvent* tcpEvent)
{
	m_SendEvents[tcpEvent->SessionID].push_back(tcpEvent);
}
void TcpThread::RePushSendEvent(TcpEvent* tcpEvent)
{
	m_SendEvents[tcpEvent->SessionID].push_front(tcpEvent);
}