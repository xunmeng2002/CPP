#pragma once

#include "ThreadBase.h"
#include "TradeSpi.h"
#include "MyEvent.h"
#include "AccountInfo.h"
#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>

using namespace std;

class FixMessage;
class FixMessageParse;
class TradeApi;

class WorkThread : public ThreadBase, public TradeSpi
{
	WorkThread(const char* name = "WorkThread");
	WorkThread(const WorkThread&) = delete;
	WorkThread& operator=(const WorkThread&) = delete;
public:
	static WorkThread& GetInstance();
	bool Init();
	virtual void ThreadExit() override;
	virtual void Run() override;
	
	void OnEvent(MyEvent* myEvent);
	void OnEventResendRequest(int beginSeqNo, int endSeqNo);
	void OnRecv(int sessionID, char* buff, int len);

public:
	bool Verify(FixMessage* fixMessage, bool checkTooHigh = true, bool checkTooLow = true);
	void OnMsgSeqTooHigh(FixMessage* fixMessage, int msgSeqNum, int expectSeqNum);
	void OnMsgSeqTooLow(FixMessage* fixMessage, int msgSeqNum, int expectSeqNum);
	bool NextQueue();
	bool CheckAndSendResendRequest();

	virtual void OnFixMessage(FixMessage* fixMessage) override;

	virtual void OnRspLogon(FixMessage* fixMessage) override;

	virtual void OnRspLogout(FixMessage* fixMessage) override;

	virtual void OnRspHeartBeat(FixMessage* fixMessage) override;

	virtual void OnRspTestRequest(FixMessage* fixMessage) override;

	virtual void OnRspResendRequest(FixMessage* fixMessage) override;

	virtual void OnRspSessionLevelReject(FixMessage* fixMessage) override;

	virtual void OnRspSequenceReset(FixMessage* fixMessage) override;

	virtual void OnExecutionReport(FixMessage* fixMessage) override;



private:
	void CheckEvent();
	void HandleEvent();
	void CheckConnectStatus();
	void CheckLogonStatus();
	void CheckAndParsePackage();
	void CheckRequest();


	void Reset();
	void AddReqHeader();
	int ReqLogon();
	int ReqLogout();
	int ReqHeartBeat(string testReqID);
	int ReqTestRequest(string testReqID);
	int ReqResendRequest(int startSeqNum, int endSeqNum);
	int ReqSequenceReset(const string& beginSeqNum);
	int ReqNewOrder();


	bool IsOnResend()
	{
		return !(m_ResendRange.first == 0 && m_ResendRange.second == 0);
	}

private:
	static WorkThread m_Instance;

	list<MyEvent*> m_MyEvents;
	mutex m_MyEventMutex;
	std::mutex m_ThreadMutex;
	std::condition_variable m_ThreadConditionVariable;

	string m_SenderCompID;
	AccountInfo m_AccountInfo;
	FixMessage* m_FixMessage;
	TradeApi* m_TradeApi;
	FixMessageParse* m_FixMessageParse;

	ConnectStatus m_ConnectStatus;
	LogonStatus m_LogonStatus;

	std::pair<int, int> m_ResendRange;
	std::map<int, FixMessage*> m_FixMessages;
};

