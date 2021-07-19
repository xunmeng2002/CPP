#include "WorkThread.h"
#include  "Logger.h"
#include "TcpThread.h"
#include "MemCacheTemplateSingleton.h"

WorkThread WorkThread::m_Instance;

WorkThread::WorkThread(const char* name)
	:ThreadBase(name)
{

}

WorkThread& WorkThread::GetInstance()
{
	return m_Instance;
}
bool WorkThread::Init()
{
	map<Address, AccountInfo*> accountInfos;
	ReadAccountInfo(accountInfos);
	for (auto& it : accountInfos)
	{
		TradeApi* tradeApi = new TradeApi(it.second);
		m_TradeApis[it.first] = tradeApi;

		m_ConnectStatus[it.first] = ConnectStatus::NotConnected;
	}
	return true;
}
void WorkThread::Run()
{
	CheckEvent();
	HandleEvent();
	CheckConnectStatus();
	CheckLogonStatus();
	CheckAndParsePackage();
	CheckRequest();
}
void WorkThread::OnSessionConnected(const char* ip, unsigned int port, int sessionID)
{
	ConnectEvent* connectEvent = MemCacheTemplateSingleton<ConnectEvent>::GetInstance().Allocate();
	connectEvent->EventID = EVENT_CONNECTED;
	connectEvent->SessionID = sessionID;
	connectEvent->IP = ip;
	connectEvent->Port = port;

	lock_guard<mutex> guard(m_ConnectEventMutex);
	m_ConnectEvents.push_back(connectEvent);

	m_ThreadConditionVariable.notify_one();
}
void WorkThread::OnSessionDisConnected(const char* ip, unsigned int port, int sessionID)
{
	ConnectEvent* connectEvent = MemCacheTemplateSingleton<ConnectEvent>::GetInstance().Allocate();
	connectEvent->EventID = EVENT_DISCONNECTED;
	connectEvent->SessionID = sessionID;
	connectEvent->IP = ip;
	connectEvent->Port = port;

	lock_guard<mutex> guard(m_ConnectEventMutex);
	m_ConnectEvents.push_back(connectEvent);
	
	m_ThreadConditionVariable.notify_one();
}
void WorkThread::OnRecv(int sessionID, char* buff, int len)
{
	auto tradeApi = GetSessionApi(sessionID);
	if (tradeApi)
	{
		tradeApi->OnRecv(buff, len);
	}
	m_ThreadConditionVariable.notify_one();
}


void WorkThread::CheckEvent()
{
	unique_lock<mutex> guard(m_ThreadMutex);
	m_ThreadConditionVariable.wait_for(guard, std::chrono::seconds(1));
}
void WorkThread::HandleEvent()
{
	lock_guard<mutex> guard(m_ConnectEventMutex);
	for (auto& connectEvent : m_ConnectEvents)
	{
		switch (connectEvent->EventID)
		{
		case EVENT_CONNECTED:
		{
			Address address(connectEvent->IP, connectEvent->Port);
			if (m_ConnectStatus.find(address) != m_ConnectStatus.end())
			{
				m_ConnectStatus[address] = ConnectStatus::Connected;
			}
			else
			{
				_ASSERT(false);
				WRITE_LOG(LogLevel::Error, "Cannot find ConnectStatus for Address IP[%s], Port[%s].", address.IP.c_str(), address.Port.c_str());
			}
			if (m_TradeApis.find(address) != m_TradeApis.end())
			{
				auto tradeApi = m_TradeApis[address];
				tradeApi->OnSessionConnected(connectEvent->SessionID);
				AddSessionApi(connectEvent->SessionID, tradeApi);
			}
			else
			{
				_ASSERT(false);
				WRITE_LOG(LogLevel::Error, "Cannot find TradeApi for Address IP[%s], Port[%s].", address.IP.c_str(), address.Port.c_str());
			}
			break;
		}
		case EVENT_DISCONNECTED:
		{
			Address address(connectEvent->IP, connectEvent->Port);

			if (m_ConnectStatus.find(address) != m_ConnectStatus.end())
			{
				m_ConnectStatus[address] = ConnectStatus::NotConnected;
			}
			else
			{
				_ASSERT(false);
				WRITE_LOG(LogLevel::Error, "Cannot find ConnectStatus for Address IP[%s], Port[%s].", address.IP.c_str(), address.Port.c_str());
			}
			if (m_TradeApis.find(address) != m_TradeApis.end())
			{
				auto tradeApi = m_TradeApis[address];
				tradeApi->OnSessionDisConnected(connectEvent->SessionID);
				RemoveSessionApi(connectEvent->SessionID);
			}
			else
			{
				_ASSERT(false);
				WRITE_LOG(LogLevel::Error, "Cannot find TradeApi for Address IP[%s], Port[%s].", address.IP.c_str(), address.Port.c_str());
			}
			break;
		}
		default:
			_ASSERT(false);
			break;
		}
		MemCacheTemplateSingleton<ConnectEvent>::GetInstance().Free(connectEvent);
	}
	m_ConnectEvents.clear();
}
void WorkThread::CheckConnectStatus()
{
	for (auto& it : m_ConnectStatus)
	{
		if (it.second == ConnectStatus::NotConnected)
		{
			TcpThread::GetInstance().Connect(it.first.IP.c_str(), atoi(it.first.Port.c_str()));
			it.second = ConnectStatus::Connecting;
		}
	}
}
void WorkThread::CheckLogonStatus()
{
	for (auto& it : m_TradeApis)
	{
		it.second->CheckLogonStatus();
	}
}
void WorkThread::CheckAndParsePackage()
{
	for (auto& it : m_SessionApis)
	{
		it.second->Parse();
	}
}
void WorkThread::CheckRequest()
{

}

void WorkThread::AddSessionApi(int sessionID, TradeApi* tradeApi)
{
	m_SessionApis[sessionID] = tradeApi;
}
void WorkThread::RemoveSessionApi(int sessionID)
{
	if (m_SessionApis.find(sessionID) != m_SessionApis.end())
	{
		m_SessionApis.erase(sessionID);
	}
}
TradeApi* WorkThread::GetSessionApi(int sessionID)
{
	if (m_SessionApis.find(sessionID) != m_SessionApis.end())
	{
		return m_SessionApis[sessionID];
	}
	return nullptr;
}