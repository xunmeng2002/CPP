#include "WorkThreadBase.h"
#include "Logger.h"
#include "MemCacheTemplateSingleton.h"
#include "WorkThreadManage.h"

using namespace std;

WorkThreadBase::WorkThreadBase(int workThreadID)
	:ThreadBase("WorkThread"), m_WorkThreadID(workThreadID)
{
	
}
WorkThreadBase::~WorkThreadBase()
{
	
}

int WorkThreadBase::GetSessionNum()
{
	lock_guard<mutex> guard(m_SessionIDMutex);
	return m_SessionIDs.size();
}

void WorkThreadBase::OnRecvMessage(SocketData* socketData)
{
	lock_guard<mutex> guard(m_RecvMessageListMutex);
	m_RecvMessageList.push_back(socketData);

	m_ThreadConditionVariable.notify_one();
}

void WorkThreadBase::PrintSessions()
{
	WRITE_LOG(LogLevel::Info, "PrintSessions: SessionSize:[%d]", m_SessionIDs.size());
	for (auto it : m_SessionIDs)
	{
		WRITE_LOG(LogLevel::Info, "WorkThread:[%d] SessionID:[%d] Socket:[%lld]", m_WorkThreadID, it.first, it.second);
	}
}

void WorkThreadBase::ThreadInit()
{
	WRITE_LOG(LogLevel::Info, "WorkThread:%d Start.", m_WorkThreadID);
}
void WorkThreadBase::Run()
{
	while (m_ShouldRun.load())
	{
		auto socketData = GetRecvMessage();
		if (socketData == nullptr)
		{
			continue;
		}
		switch (socketData->EventID)
		{
		case EventOnConnected:
			HandleNewConnect(socketData);
			break;
		case EventOnDisConnected:
			HandleDisConnect(socketData);
			break;
		case EventRecv:
			HandleRecvMessage(socketData);
			break;
		}
		MemCacheTemplateSingleton<SocketData>::GetInstance().Free(socketData);
	}
}
void WorkThreadBase::ThreadExit()
{
	WRITE_LOG(LogLevel::Info, "WorkThread:[%d] Exit.", m_WorkThreadID);
}

SocketData* WorkThreadBase::GetRecvMessage()
{
	unique_lock<mutex> guard(m_RecvMessageListMutex);
	m_ThreadConditionVariable.wait_for(guard, std::chrono::seconds(1), [&] {
		return !m_RecvMessageList.empty();
		});
	if (m_RecvMessageList.empty())
	{
		return nullptr;
	}
	auto socketData = m_RecvMessageList.front();
	m_RecvMessageList.pop_front();
	return socketData;
}
void WorkThreadBase::HandleNewConnect(SocketData* socketData)
{
	WorkThreadManage::GetInstance().AddConnect();
	lock_guard<mutex> guard(m_SessionIDMutex);
	m_SessionIDs.insert(make_pair(socketData->SessionID, socketData->ConnectSocket));
	WRITE_LOG(LogLevel::Info, "WorkThread:[%d] NewConnect SessionID:[%d] Socket:[%lld]",
		m_WorkThreadID, socketData->SessionID, socketData->ConnectSocket);
}
void WorkThreadBase::HandleDisConnect(SocketData* socketData)
{
	WorkThreadManage::GetInstance().RemoveConnect();
	lock_guard<mutex> guard(m_SessionIDMutex);
	m_SessionIDs.erase(socketData->SessionID);
	WRITE_LOG(LogLevel::Info, "WorkThread:[%d] DisConnect SessionID:%d", m_WorkThreadID, socketData->SessionID);
}