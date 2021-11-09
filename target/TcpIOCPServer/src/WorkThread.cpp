#include "WorkThread.h"
#include "Logger.h"
#include "TcpIOCPClient.h"

using namespace std;

WorkThread WorkThread::m_Instance;
WorkThread::WorkThread()
	:ThreadBase("WorkThread"), m_TcpPublisher(nullptr)
{

}
WorkThread::~WorkThread()
{

}

WorkThread& WorkThread::GetInstance()
{
	return m_Instance;
}
void WorkThread::RegisterTcp(TcpPublisher* tcpPublisher)
{
	m_TcpPublisher = tcpPublisher;
}

void WorkThread::OnConnect(int sessionID, const char* ip, int port)
{
	TcpEvent* tcpEvent = TcpEvent::Allocate();
	tcpEvent->EventID = EventOnConnected;
	tcpEvent->SessionID = sessionID;
	tcpEvent->IP = string(ip);
	tcpEvent->Port = port;
	OnEvent(tcpEvent);
}
void WorkThread::OnDisConnect(int sessionID, const char* ip, int port)
{
	TcpEvent* tcpEvent = TcpEvent::Allocate();
	tcpEvent->EventID = EventOnDisConnected;
	tcpEvent->SessionID = sessionID;
	tcpEvent->IP = string(ip);
	tcpEvent->Port = port;
	OnEvent(tcpEvent);
}
void WorkThread::OnRecv(TcpEvent* tcpEvent)
{
	OnEvent(tcpEvent);
}
void WorkThread::CloseConnects()
{
	TcpEvent* tcpEvent = TcpEvent::Allocate();
	tcpEvent->EventID = EventDisConnect;
	OnEvent(tcpEvent);
}
void WorkThread::Send(const char* data, int len)
{
	TcpEvent* tcpEvent = TcpEvent::Allocate();
	tcpEvent->EventID = EventDisConnect;
	memcpy(tcpEvent->Buff, data, len);
	tcpEvent->Length = len;

	OnEvent(tcpEvent);
}

void WorkThread::HandleEvent()
{
	Event* event = nullptr;
	TcpEvent* tcpEvent = nullptr;
	while (event = GetEvent())
	{
		switch (event->EventID)
		{
		case EventOnConnected:
		{
			tcpEvent = (TcpEvent*)event;
			AddConnect(tcpEvent->SessionID, tcpEvent->IP.c_str(), tcpEvent->Port);
			break;
		}
		case EventOnDisConnected:
		{
			tcpEvent = (TcpEvent*)event;
			RemoveConnect(tcpEvent->SessionID, tcpEvent->IP.c_str(), tcpEvent->Port);
			break;
		}
		case EventRecv:
		{
			HandleRecvData((TcpEvent*)event);
			break;
		}
		case EventDisConnect:
		{
			HandleDisConnects();
			break;
		}
		case EventSend:
		{
			HandleSendData((TcpEvent*)event);
			break;
		}
		}
		event->Free();
	}
}
void WorkThread::AddConnect(int sessionID, const char* ip, int port)
{
	m_ConnectDatas.insert(make_pair(sessionID, ConnectData::Allocate(sessionID, 0, ip, port)));
}
void WorkThread::RemoveConnect(int sessionID, const char* ip, int port)
{
	if (m_ConnectDatas.find(sessionID) != m_ConnectDatas.end())
	{
		m_ConnectDatas[sessionID]->Free();
	}
	m_ConnectDatas.erase(sessionID);
}
void WorkThread::HandleRecvData(TcpEvent* tcpEvent)
{
	WRITE_LOG(LogLevel::Info, "RecvData From SessionID:[%d], Address:[%s:%d], Data:[%s]", tcpEvent->SessionID, tcpEvent->IP.c_str(), tcpEvent->Port, tcpEvent->ReadPos);

	static char buff[1024];
	int len = sprintf(buff, "ServerRsponse For SessionID:[%d] Address:[%s:%d] Data:[%s]", tcpEvent->SessionID, tcpEvent->IP.c_str(), tcpEvent->Port, tcpEvent->ReadPos);
	m_TcpPublisher->Send(tcpEvent->SessionID, buff, len);
}
void WorkThread::HandleDisConnects()
{
	for (auto& it : m_ConnectDatas)
	{
		m_TcpPublisher->DisConnect(it.first);
	}
}
void WorkThread::HandleSendData(TcpEvent* tcpEvent)
{
	for (auto& it : m_ConnectDatas)
	{
		m_TcpPublisher->Send(it.first, tcpEvent->ReadPos, tcpEvent->Length);
	}
}