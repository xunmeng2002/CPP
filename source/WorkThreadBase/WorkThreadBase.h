#include "SocketDataStruct.h"
#include "ThreadBase.h"
#include <map>
#include <set>
#include <list>
#include <mutex>
#include <condition_variable>

#pragma once


class WorkThreadBase : public ThreadBase
{
public:
	WorkThreadBase(int workThreadID);
	~WorkThreadBase();
	int GetSessionNum();
	virtual void OnRecvMessage(SocketData* socketData);

	virtual void CloseConnects() = 0;
	virtual void SendTestMessage(const std::string& message) = 0;
protected:
	virtual void ThreadInit() override;
	virtual void Run() override;
	virtual void ThreadExit() override;

	SocketData* GetRecvMessage();
	virtual void HandleNewConnect(SocketData* socketData);
	virtual void HandleDisConnect(SocketData* socketData);
	virtual void HandleRecvMessage(SocketData* socketData) = 0;

protected:
	int m_WorkThreadID;

	std::set<int> m_SessionIDs;
	std::mutex m_SessionIDMutex;

	std::list<SocketData*> m_RecvMessageList;
	std::mutex m_RecvMessageListMutex;
	std::condition_variable m_ThreadConditionVariable;
};