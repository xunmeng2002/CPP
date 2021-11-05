#pragma once
#include <list>
#include "ThreadBase.h"
#include "DataType.h"
#include "SeqNum.h"
#include "FixMdb.h"
#include "TcpSelectClient.h"
#include "MdbEngine.h"
#include "FixAuditTrail.h"
#include "FixAuditTrailWriter.h"


struct sqlite3;
class FixEngine : public ThreadBase, public TcpSubscriber, public MdbSubscriber, public FixTableCallback
{
public:
	FixEngine();
	~FixEngine();
	void RegisterMdbPublisher(MdbPublisher* mdbPublisher);
	void RegisterAddress(const string& primaryIP, int primaryPort, const string& backupIP, int backupPort);
	bool Init(const char* dbName = "");
	void InitInstruments();
	virtual bool Start() override;
	virtual void Stop() override;
	virtual void Join() override;

	virtual void InitReqMessage(FixReqHeader* reqField) override;
	virtual void InitRspMessage(FixRspHeader* rspField) override;
	virtual void SelectFixProductCallback(FixProduct* field) override;
	virtual void SelectFixInstrumentCallback(FixInstrument* field) override;
	void ClearInitMessage();

	virtual void ReqInsertOrder(Order* order)  override;
	virtual void ReqInsertOrderCancel(OrderCancel* orderCancel)  override;
	void HandleInsertOrder(Order* order);
	void HandleInsertOrderCancel(OrderCancel* orderCancel);

	virtual void OnConnect(int sessionID, const char* ip, int port) override;
	virtual void OnDisConnect(int sessionID, const char* ip, int port) override;
	virtual void OnRecv(TcpEvent* tcpEvent) override;

	void ReqLogon(FixReqLogonField* reqField);
	void ReqLogout(FixReqLogoutField* reqField);
	void ReqHeartBeat(FixReqHeartBeatField* reqField);
	void ReqTestRequest(FixReqTestRequestField* reqField);

protected:
	virtual void Run() override;
	virtual void HandleEvent() override;
	void OnEventSequenceGap(int beginSeqNo, int endSeqNo);
	void OnEventResendLastResendRequest();
	void OnEventDoResendRequest(int beginSeqNo, int endSeqNo);
	void OnEventFixMessage(FixReqHeader* reqField);
	void CheckConnectStatus();
	void CheckLogonStatus();
	void CheckAndParsePackage();
	void CheckHeartBeat();

	void HandleConnect(int sessionID);
	void HandleDisConnect(int sessionID);
	void HandleFixMessage(FixMessage* fixMessage);
	bool Verify(FixMessage* fixMessage, bool checkTooHigh = true, bool checkTooLow = true);
	void DoMsgSeqTooHigh(FixMessage* fixMessage, int msgSeqNum, int expectSeqNum);
	void DoMsgSeqTooLow(FixMessage* fixMessage, int msgSeqNum, int expectSeqNum);
	bool NextQueue();
	bool IsOnResend();
	void ReqLogon();
	void ReqResendRequest(int startSeqNum, int endSeqNum);
	void ResendLastResendRequest();
	void DoResendRequest(int startSeqNum, int endSeqNum);
	void ReqSequenceReset(int beginSeqNum, int endSeqNum, const string& gapFill = "Y");

	void OnFixRspLogon(FixMessage* fixMessage);
	void OnFixRspLogout(FixMessage* fixMessage);
	void OnFixRspHeartBeat(FixMessage* fixMessage);
	void OnFixRspTestRequest(FixMessage* fixMessage);
	void OnFixRspResendRequest(FixMessage* fixMessage);
	void OnFixRspSessionLevelReject(FixMessage* fixMessage);
	void OnFixRspSequenceReset(FixMessage* fixMessage);
	void OnFixExecutionReport(FixMessage* fixMessage);
	void OnFixRspOrderCancelReject(FixMessage* fixMessage);

	
	void RecordRequest(FixReqHeader* reqField);
	void RecordResponse(FixRspHeader* rspField);
	void UpdateLastSendTime();
	void UpdateLastRecvTime();
	void RecordFixAuditTrail(FixMessage* fixMessage, string messageDirection);

	template<typename T>
	void SendRequest(T* reqField, bool isResend = false)
	{
		TcpEvent* tcpEvent = TcpEvent::Allocate();
		tcpEvent->EventID = EventSend;
		tcpEvent->SessionID = m_SessionID;
		auto len = reqField->ToStream(tcpEvent->Buff);
		tcpEvent->Length = len;

		UpdateLastSendTime();
		m_TcpClient->Send(tcpEvent);

		if (reqField->MsgClass == "app")
		{
			RecordFixAuditTrail(reqField->GetFixMessage(), "TO CME");
		}
	}

private:
	FixInstrument* GetFixInstrumentFromBroker(const string& exchangeID, const string& instrumentID);
	FixInstrument* GetFixInstrumentFromExchange(const string& exchangeID, const string& itcAlias);
	void OnRtnOrder(FixExecutionReportField* rspField);
	void OnRtnTrade(FixExecutionReportField* rspField);
	void OnErrRtnOrderCancel(FixRspOrderCancelRejectField* rspField);
	template<typename T>
	void WriteFixLog(T* fixField)
	{
		fixField->ToString(m_LogBuff, BuffSize);
		WRITE_LOG(LogLevel::Info, "%s", m_LogBuff);
	}

private:
	sqlite3* m_Mdb;
	TcpSelectClient* m_TcpClient;
	MdbPublisher* m_MdbPublisher;
	char* m_LogBuff;
	std::list<IPAddress*> m_IPAddresses;

	ConnectStatus m_ConnectStatus;
	LogonStatus m_LogonStatus;
	int m_SessionID;
	FixMessage* m_FixMessage;
	std::map<int, FixMessage*> m_FixMessages;
	std::map<int, FixReqHeader*> m_AppReqFields;
	std::map<int, FixRspHeader*> m_AppRspFields;
	std::set<FixProduct*> m_FixProducts;
	std::set<FixInstrument*> m_FixInstruments;
	list<TcpEvent*> m_RecvDatas;
	char* m_ParseBuff;
	int m_ParseBuffDataLen;

	bool m_IsDoResendRequest;
	std::pair<int, int> m_ResendRange;
	FixReqResendRequestField m_LastResendRequestField;
	
	int m_HeartBeatSecond;
	bool m_AlreadySendTestRequest;
	char m_TestReqID[128];
	chrono::steady_clock::time_point m_LastSendTimePoint;
	chrono::steady_clock::time_point m_LastRecvTimePoint;
	chrono::steady_clock::time_point m_TestRequestSendTimePoint;

	FixAuditTrail* m_FixAuditTrail;
};

