#pragma once

#include "ThreadBase.h"
#include "TradeSpi.h"
#include "AccountInfo.h"
#include "Mdb.h"
#include "TradeApiReqFields.h"
#include "MyEvent.h"
#include "TcpEvent.h"
#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>
#include <chrono>

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
	
	void OnEventSequenceGap(int beginSeqNo, int endSeqNo);
	void OnEventDoResendRequest(int beginSeqNo, int endSeqNo);
	void OnEventDoLogout();
	void OnEventTestRequest(const string& testReqID = "");
	void OnRecv(TcpEvent* tcpEvent);
	void UpdateLastSendTime();

public:
	bool Verify(FixMessage* fixMessage, bool checkTooHigh = true, bool checkTooLow = true);
	void OnMsgSeqTooHigh(FixMessage* fixMessage, int msgSeqNum, int expectSeqNum);
	void OnMsgSeqTooLow(FixMessage* fixMessage, int msgSeqNum, int expectSeqNum);
	bool NextQueue();

	virtual void OnFixMessage(FixMessage* fixMessage) override;

	virtual void OnRspLogon(FixMessage* fixMessage) override;

	virtual void OnRspLogout(FixMessage* fixMessage) override;

	virtual void OnRspHeartBeat(FixMessage* fixMessage) override;

	virtual void OnRspTestRequest(FixMessage* fixMessage) override;

	virtual void OnRspResendRequest(FixMessage* fixMessage) override;

	virtual void OnRspSessionLevelReject(FixMessage* fixMessage) override;

	virtual void OnRspSequenceReset(FixMessage* fixMessage) override;

	virtual void OnExecutionReport(FixMessage* fixMessage) override;

	virtual void OnRspOrderCancelReject(FixMessage* fixMessage) override;



private:
	void HandleEvent();
	void CheckConnectStatus();
	void CheckLogonStatus();
	void CheckAndParsePackage();
	void CheckRequest();
	void CheckSendHeartBeat();
	void CheckRecvHeartBeat();
	void CheckTestRequstReply();


	void Reset();
	void AddReqHeader(string msgSeqNum = "");
	void ReqLogon();
	void ReqLogout();
	void ReqHeartBeat(string testReqID);
	void ReqTestRequest(string testReqID);
	void ReqResendRequest(int startSeqNum, int endSeqNum);
	void DoResendRequest(int startSeqNum, int endSeqNum);
	void ReqSequenceReset(int beginSeqNum, int endSeqNum);
	void ReqNewOrder(const string& marketSegmentID, const string& instrumentID, const string& orderType, const string& price, const string& stopPrice, int orderQty);
	void ReqOrderCancelRequest(const string& origOrderLocalID);
	void ReqOrderCancelReplaceRequest(const string& origOrderLocalID, const string& newPrice, int newVolume);


	void RecordRequest(ReqHeader* reqField);
	Order* GetOrder(string orderLocalID);
	void AddNewOrder(ReqNewOrderField* reqNewOrder);
	void UpdateOrder(ExecutionReportField* executionReport);
	void AddNewTrade(ExecutionReportField* executionReport, Order* order);
	void ModifyTrade(ExecutionReportField* executionReport, Order* order);
	void CancelTrade(ExecutionReportField* executionReport, Order* order);
	void ReportOrder();
	void ReportTrade();
	
	bool IsOnResend()
	{
		return !(m_ResendRange.first == 0 && m_ResendRange.second == 0);
	}

private:
	static WorkThread m_Instance;

	std::mutex m_ThreadMutex;

	string m_SenderCompID;
	AccountInfo m_AccountInfo;
	FixMessage* m_FixMessage;
	TradeApi* m_TradeApi;
	FixMessageParse* m_FixMessageParse;

	ConnectStatus m_ConnectStatus;
	LogonStatus m_LogonStatus;

	std::pair<int, int> m_ResendRange;
	std::map<int, FixMessage*> m_FixMessages;
	std::map<int, ReqHeader*> m_AppReqFields;
	bool m_IsDoResendRequest;

	int m_HeartBeatSecond;
	int m_LastSendTimeCount;
	chrono::steady_clock::time_point m_LastSendTimePoint;
	int m_LastRecvTimeCount;
	chrono::steady_clock::time_point m_LastRecvTimePoint;
	bool m_AlreadySendTestRequest;
	string m_TestReqID;
	int m_TestRequestSendTimeCount;
	chrono::steady_clock::time_point m_TestRequestSendTimePoint;

	map<string, Order*> m_Orders;
	map<string, Trade*> m_Trades;
};

