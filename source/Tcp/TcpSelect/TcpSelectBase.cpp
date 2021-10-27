#include "TcpSelectBase.h"
#include "Logger.h"
#include "MyEvent.h"


TcpSelectBase::TcpSelectBase(const char* name, TcpSubscriber* subscriber)
	:ThreadBase(name), m_Subscriber(subscriber), m_AddressLen(sizeof(sockaddr)), m_AF(AF_INET), m_Type(SOCK_STREAM), m_Protocol(IPPROTO_TCP)
{
	memset(&m_RemoteAddress, 0, sizeof(m_RemoteAddress));
	m_MaxSessionID = 0;
	FD_ZERO(&m_RecvFds);
	FD_ZERO(&m_SendFds);

	m_ConnectTimeOut.tv_sec = 5;
	m_ConnectTimeOut.tv_usec = 0;
	m_TimeOut.tv_sec = 1;
	m_TimeOut.tv_usec = 0;
}
void TcpSelectBase::SetTcpInfo(long timeOut, int af, int type, int protocol)
{
	m_TimeOut.tv_sec = timeOut / 1000000;
	m_TimeOut.tv_usec = timeOut % 1000000;
	m_AF = af;
	m_Type = type;
	m_Protocol = protocol;

	m_RemoteAddress.sin_family = af;
}
void TcpSelectBase::DisConnect(int sessionID)
{
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DISCONNECT;
	myEvent->NumParams.push_back(sessionID);
	OnEvent(myEvent);
}
void TcpSelectBase::Send(int sessionID, const char* data, int length)
{
	TcpEvent* tcpEvent = TcpEvent::Allocate();
	tcpEvent->EventID = EVENT_ON_TCP_SEND;
	tcpEvent->SessionID = sessionID;
	memcpy(tcpEvent->Buff, data, length);
	tcpEvent->Length = length;

	OnEvent(tcpEvent);
}
void TcpSelectBase::Send(TcpEvent* tcpEvent)
{
	OnEvent(tcpEvent);
}

void TcpSelectBase::Run()
{
	HandleEvent();
	CheckConnect();
	PrepareFds();
	::select(0, &m_RecvFds, &m_SendFds, nullptr, &m_TimeOut);
	DoAccept();
	DoSend();
	DoRecv();
}
void TcpSelectBase::HandleEvent()
{
	TcpEvent* tcpEvent = nullptr;
	while (tcpEvent = (TcpEvent*)GetEvent())
	{
		bool shouldFree = true;
		switch (tcpEvent->EventID)
		{
		case EVENT_CONNECT:
		{
			DoConnect(tcpEvent->IP, tcpEvent->Port);
			break;
		}
		case EVENT_DISCONNECT:
		{
			DoDisConnect(tcpEvent->SessionID);
			break;
		}
		case EVENT_ON_TCP_SEND:
		{
			PushSendEvent(tcpEvent);
			shouldFree = false;
			break;
		}
		default:
			break;
		}
		if (shouldFree)
		{
			tcpEvent->Free();
		}
	}
}
void TcpSelectBase::DoDisConnect(int sessionID)
{
	auto connectData = GetConnect(sessionID);
	if (connectData == nullptr)
	{
		WRITE_LOG(LogLevel::Warning, "DoDisConnect While ConnectData is nullptr, SessionID:[%d]", sessionID);
		return;
	}
	RemoveConnect(connectData);
}
void TcpSelectBase::PrepareFds()
{
	FD_ZERO(&m_RecvFds);
	FD_ZERO(&m_SendFds);
	for (auto& it : m_ConnectDatas)
	{
		FD_SET(it.second->SocketID, &m_RecvFds);
		if (!m_SendEvents[it.first].empty())
			FD_SET(it.second->SocketID, &m_SendFds);
	}
}
void TcpSelectBase::DoSend()
{
	for (auto& it : m_ConnectDatas)
	{
		auto connectData = it.second;
		if (FD_ISSET(connectData->SocketID, &m_SendFds))
		{
			while (!m_SendEvents[it.first].empty())
			{
				auto tcpEvent = m_SendEvents[it.first].front();
				int len = send(connectData->SocketID, tcpEvent->ReadPos, tcpEvent->Length, 0);
				if (len <= 0)
				{
					WRITE_LOG(LogLevel::Info, "DisConnect For Send len = [%d]", len);
					DisConnect(connectData->SessionID);
					break;
				}
				else if (len < tcpEvent->Length)
				{
					WRITE_LOG(LogLevel::Info, "OnSend, Send Less than expect. Expect Len[%d], Send Len[%d], Buff[%s]", tcpEvent->Length, len, tcpEvent->ReadPos);
					tcpEvent->ReadPos += len;
					tcpEvent->Length -= len;
					break;
				}
				else
				{
					WRITE_LOG(LogLevel::Info, "OnSend Send Len[%d], Buff[%s]", tcpEvent->Length, tcpEvent->ReadPos);
					m_SendEvents[it.first].pop_front();
					tcpEvent->Free();
				}
			}
		}
	}
}
void TcpSelectBase::DoRecv()
{
	for (auto& it : m_ConnectDatas)
	{
		auto connectData = it.second;
		auto socketID = connectData->SocketID;
		int sessionID = connectData->SessionID;
		if (FD_ISSET(socketID, &m_RecvFds))
		{
			TcpEvent* tcpEvent = TcpEvent::Allocate();
			int len = recv(socketID, tcpEvent->Buff, BuffSize - 1, 0);
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

				m_Subscriber->OnRecv(tcpEvent);
			}
		}
	}
}

void TcpSelectBase::AddConnect(ConnectData* connectData)
{
	WRITE_LOG(LogLevel::Info, "New Connection. SessionID[%d], Socket[%lld], RemoteIP[%s], RemotePort[%d]", connectData->SessionID, connectData->SocketID, connectData->RemoteIP.c_str(), connectData->RemotePort);
	m_Subscriber->OnConnect(connectData->SessionID, connectData->RemoteIP.c_str(), connectData->RemotePort);

	m_ConnectDatas.insert(make_pair(connectData->SessionID, connectData));
	m_SendEvents.insert(make_pair(connectData->SessionID, list<TcpEvent*>()));
}
void TcpSelectBase::RemoveConnect(ConnectData* connectData)
{
	WRITE_LOG(LogLevel::Info, "DisConnection. SessionID[%d], Socket[%lld], RemoteIP[%s], RemotePort[%d]", connectData->SessionID, connectData->SocketID, connectData->RemoteIP.c_str(), connectData->RemotePort);
	m_Subscriber->OnDisConnect(connectData->SessionID, connectData->RemoteIP.c_str(), connectData->RemotePort);

	for (auto tcpEvent : m_SendEvents[connectData->SessionID])
	{
		tcpEvent->Free();
	}
	m_SendEvents.erase(connectData->SessionID);
	m_ConnectDatas.erase(connectData->SessionID);
	connectData->Free();
}
ConnectData* TcpSelectBase::GetConnect(int sessionID)
{
	if (m_ConnectDatas.find(sessionID) != m_ConnectDatas.end())
	{
		return m_ConnectDatas[sessionID];
	}
	return nullptr;
}

TcpEvent* TcpSelectBase::GetSendEvent(int sessionID)
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
void TcpSelectBase::PushSendEvent(TcpEvent* tcpEvent)
{
	m_SendEvents[tcpEvent->SessionID].push_back(tcpEvent);
}