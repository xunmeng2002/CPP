#pragma once

#include "ThreadBase.h"
#include "TradeApi.h"
#include "CacheList.h"
#include "AccountInfo.h"
#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>

using namespace std;

#define EVENT_CONNECTED 1
#define EVENT_DISCONNECTED 2

struct ConnectEvent
{
	int EventID;
	int SessionID;
	string IP;
	unsigned int Port;
};


class WorkThread : public ThreadBase
{
	WorkThread(const char* name = "WorkThread");
	WorkThread(const WorkThread&) = delete;
	WorkThread& operator=(const WorkThread&) = delete;
public:
	static WorkThread& GetInstance();
	bool Init();
	virtual void Run();
	void OnSessionConnected(const char* ip, unsigned int port, int sessionID);
	void OnSessionDisConnected(const char* ip, unsigned int port, int sessionID);
	void OnRecv(int sessionID, char* buff, int len);

private:
	void CheckEvent();
	void HandleEvent();
	void CheckConnectStatus();
	void CheckLogonStatus();
	void CheckAndParsePackage();
	void CheckRequest();

	void AddSessionApi(int sessionID, TradeApi* tradeApi);
	void RemoveSessionApi(int sessionID);
	TradeApi* GetSessionApi(int sessionID);

private:
	static WorkThread m_Instance;

	list<ConnectEvent*> m_ConnectEvents;
	mutex m_ConnectEventMutex;

	std::mutex m_ThreadMutex;
	std::condition_variable m_ThreadConditionVariable;

	map<Address, TradeApi*> m_TradeApis;

	map<Address, ConnectStatus> m_ConnectStatus;

	map<int, TradeApi*> m_SessionApis;
};

