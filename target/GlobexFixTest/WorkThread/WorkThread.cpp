#include "WorkThread.h"
#include  "Logger.h"
#include "TcpThread.h"
#include "MemCacheTemplateSingleton.h"
#include "GlobalParam.h"
#include "CryptoppEncode.h"
#include "FixMessageParse.h"
#include "TradeApi.h"



WorkThread WorkThread::m_Instance;

WorkThread::WorkThread(const char* name)
	:ThreadBase(name)
{
	m_FixMessage = nullptr;
	m_TradeApi = new TradeApi();
	m_FixMessageParse = new FixMessageParse(this);
}

WorkThread& WorkThread::GetInstance()
{
	return m_Instance;
}
bool WorkThread::Init()
{
	ReadAccountInfo(&m_AccountInfo);
	return true;
}
void WorkThread::ThreadExit()
{

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
void WorkThread::OnEvent(MyEvent* myEvent)
{
	lock_guard<mutex> guard(m_MyEventMutex);
	m_MyEvents.push_back(myEvent);

	m_ThreadConditionVariable.notify_one();
}
void WorkThread::OnEventResendRequest(int beginSeqNo, int endSeqNo)
{
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_RESEND_REQUEST;
	myEvent->NumParams.push_back(beginSeqNo);
	myEvent->NumParams.push_back(endSeqNo);
	lock_guard<mutex> guard(m_MyEventMutex);
	m_MyEvents.push_back(myEvent);

	m_ThreadConditionVariable.notify_one();
}
void WorkThread::OnRecv(int sessionID, char* buff, int len)
{
	m_FixMessageParse->OnRecv(buff, len);
	m_ThreadConditionVariable.notify_one();
}

bool WorkThread::Verify(FixMessage* fixMessage, bool checkTooHigh, bool checkTooLow)
{
	auto msgSeqNum = atoi(fixMessage->GetMsgSeqNum().c_str());
	auto nextExpectSeqNum = GlobalParam::GetInstance().GetNextExpectSeqNum();
	if (checkTooHigh && msgSeqNum > nextExpectSeqNum)
	{
		OnMsgSeqTooHigh(fixMessage, msgSeqNum, nextExpectSeqNum);
		return false;
	}
	if (checkTooLow && msgSeqNum < nextExpectSeqNum)
	{
		OnMsgSeqTooLow(fixMessage, msgSeqNum, nextExpectSeqNum);
		return false;
	}
	if (IsOnResend())
	{
		if (msgSeqNum >= m_ResendRange.second)
		{
			WRITE_LOG(LogLevel::Info, "ResendRequest for messages FROM:[%d] TO:[%d] has been satisfied.", m_ResendRange.first, m_ResendRange.second);
			m_ResendRange = std::make_pair(0, 0);
		}
	}
	return true;
}
void WorkThread::OnMsgSeqTooHigh(FixMessage* fixMessage, int msgSeqNum, int expectSeqNum)
{
	fixMessage->ToString(m_LogBuff, BUFF_SIZE);
	m_FixMessages[msgSeqNum] = fixMessage;
	WRITE_LOG(LogLevel::Info, "MsgSeqNum too high, Expect:[%d] Receive:[%d]", expectSeqNum, msgSeqNum);
	WRITE_LOG(LogLevel::Info, "Restore FixMessage:[%s]", m_LogBuff);

	if (IsOnResend())
	{
		WRITE_LOG(LogLevel::Info, "Already sent ResendRequest FROM:[%d] TO:[%d], Not sending another", m_ResendRange.first, m_ResendRange.second);
	}
	else
	{
		OnEventResendRequest(expectSeqNum, msgSeqNum - 1);
	}
}
void WorkThread::OnMsgSeqTooLow(FixMessage* fixMessage, int msgSeqNum, int expectSeqNum)
{
	auto possDupFlag = fixMessage->GetPossDupFlag();
	auto msgType = fixMessage->GetMessageType();
	if (possDupFlag != "Y" || msgType != "4")
	{
		WRITE_LOG(LogLevel::Error, "MsgSeqNum too low, Expect:[%d], Receive:[%d]", expectSeqNum, msgSeqNum);
		ReqLogout();
	}
	FixMessage::Free(fixMessage);
}
bool WorkThread::NextQueue()
{
	auto nextExpectSeqNum = GlobalParam::GetInstance().GetNextExpectSeqNum();
	if (m_FixMessages.find(nextExpectSeqNum) != m_FixMessages.end())
	{
		auto fixMessage = m_FixMessages[nextExpectSeqNum];
		m_FixMessages.erase(nextExpectSeqNum);
		OnFixMessage(fixMessage);
		return true;
	}
	return false;
}
bool WorkThread::CheckAndSendResendRequest()
{
	auto nextExpectSeqNum = GlobalParam::GetInstance().GetNextExpectSeqNum();
	while (m_FixMessages.size() > 0)
	{
		auto it = m_FixMessages.begin();
		auto msgSeqNum = it->first;
		if (msgSeqNum <= nextExpectSeqNum)
		{
			it->second->ToString(m_LogBuff, BUFF_SIZE);
			WRITE_LOG(LogLevel::Warning, "Find MsgSeqNum Less than Expect in Queue. FixMessage: %s", m_LogBuff);
			m_FixMessages.erase(it);
		}
		else
		{
			OnEventResendRequest(nextExpectSeqNum, msgSeqNum - 1);
			return true;
		}
	}
	return false;
}


void WorkThread::OnFixMessage(FixMessage* fixMessage)
{
	auto msgType = fixMessage->GetMessageType();
	auto seqNum = fixMessage->GetMsgSeqNum();
	if (msgType.empty() || seqNum.empty())
	{
		fixMessage->ToString(m_LogBuff, BUFF_SIZE);
		WRITE_LOG(LogLevel::Error, "Invalid FixMessage:[%s]", m_LogBuff);
	}
	else if (msgType == "A")
	{
		OnRspLogon(fixMessage);
	}
	else if (msgType == "5")
	{
		OnRspLogout(fixMessage);
	}
	else if (msgType == "0")
	{
		OnRspHeartBeat(fixMessage);
	}
	else if (msgType == "1")
	{
		OnRspTestRequest(fixMessage);
	}
	else if (msgType == "2")
	{
		OnRspResendRequest(fixMessage);
	}
	else if (msgType == "3")
	{
		OnRspSessionLevelReject(fixMessage);
	}
	else if (msgType == "4")
	{
		OnRspSequenceReset(fixMessage);
	}
	else
	{
		if (Verify(fixMessage))
		{
			GlobalParam::GetInstance().SetLastRecvSeqNum(seqNum);
			GlobalParam::GetInstance().IncreaseNextExpectSeqNum();
		}
	}
}
void WorkThread::OnRspLogon(FixMessage* fixMessage)
{
	auto resetSeqNumFlag = fixMessage->GetItem(141);
	auto msgSeqNum = atoi(fixMessage->GetMsgSeqNum().c_str());
	if (resetSeqNumFlag == "Y")
	{
		WRITE_LOG(LogLevel::Info, "Reset Sequence Num to 1");
		GlobalParam::GetInstance().SetNextExpectSeqNum(1);
	}
	else
	{
		GlobalParam::GetInstance().SetNextExpectSeqNum(msgSeqNum + 1);
	}

	RspLogonField rspField(fixMessage);
	TradeSpi::OnRspLogon(&rspField);
	
	m_LogonStatus = LogonStatus::Logged;
	m_SenderCompID = rspField.TargetCompID;
}
void WorkThread::OnRspLogout(FixMessage* fixMessage)
{
	RspLogoutField rspField(fixMessage);
	TradeSpi::OnRspLogout(&rspField);
	if (m_LogonStatus != LogonStatus::Logout)
	{
		ReqLogout();
	}

	if (!rspField.NextExpectedMsgSeqNum.empty())
	{
		GlobalParam::GetInstance().SetNextSendSeqNum(rspField.NextExpectedMsgSeqNum);
	}
	GlobalParam::GetInstance().SetLastRecvSeqNum(rspField.MsgSeqNum);
	GlobalParam::GetInstance().IncreaseNextExpectSeqNum();

	Reset();
}
void WorkThread::OnRspHeartBeat(FixMessage* fixMessage)
{
	if (!Verify(fixMessage))
	{
		return;
	}

	RspHeartBeatField rspField(fixMessage);
	TradeSpi::OnRspHeartBeat(&rspField);

	GlobalParam::GetInstance().SetLastRecvSeqNum(rspField.MsgSeqNum);
	GlobalParam::GetInstance().IncreaseNextExpectSeqNum();
}
void WorkThread::OnRspTestRequest(FixMessage* fixMessage)
{
	if (!Verify(fixMessage))
	{
		return;
	}
	RspTestRequestField rspField(fixMessage);
	TradeSpi::OnRspTestRequest(&rspField);

	GlobalParam::GetInstance().SetLastRecvSeqNum(rspField.MsgSeqNum);
	auto msgSeqNum = atoi(fixMessage->GetMsgSeqNum().c_str());
	auto nextExpectSeqNum = GlobalParam::GetInstance().GetNextExpectSeqNum();
	if (msgSeqNum == nextExpectSeqNum)
	{
		GlobalParam::GetInstance().IncreaseNextExpectSeqNum();
	}

	ReqHeartBeat(rspField.TestReqID);
}
void WorkThread::OnRspResendRequest(FixMessage* fixMessage)
{
	RspResendRequestField rspField(fixMessage);
	TradeSpi::OnRspResendRequest(&rspField);
	
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_SEQUENCE_RESET;
	myEvent->StringParams.push_back(rspField.BeginSeqNo);
	OnEvent(myEvent);
}
void WorkThread::OnRspSessionLevelReject(FixMessage* fixMessage)
{
	if (!Verify(fixMessage))
	{
		return;
	}
	RspSessionLevelRejectField rspField(fixMessage);
	TradeSpi::OnRspSessionLevelReject(&rspField);

	GlobalParam::GetInstance().SetLastRecvSeqNum(rspField.MsgSeqNum);
	GlobalParam::GetInstance().IncreaseNextExpectSeqNum();
}
void WorkThread::OnRspSequenceReset(FixMessage* fixMessage)
{
	auto isGapFill = fixMessage->GetItem(123);
	if (isGapFill == "Y" && !Verify(fixMessage))
	{
		return;
	}

	RspSequenceResetField rspField(fixMessage);
	TradeSpi::OnRspSequenceReset(&rspField);

	auto nextExpectSeqNum = GlobalParam::GetInstance().GetNextExpectSeqNum();
	auto newSeqNo = atoi(rspField.NewSeqNo.c_str());
	WRITE_LOG(LogLevel::Info, "Received SequenceReset FROM [%d] To [%d]", nextExpectSeqNum, newSeqNo);

	GlobalParam::GetInstance().SetLastRecvSeqNum(rspField.MsgSeqNum);

	if (IsOnResend() && newSeqNo > m_ResendRange.second)
	{
		GlobalParam::GetInstance().SetNextExpectSeqNum(m_ResendRange.second + 1);
		m_ResendRange = make_pair(0, 0);
	}
	else
	{
		GlobalParam::GetInstance().SetNextExpectSeqNum(newSeqNo);
	}
}
void WorkThread::OnExecutionReport(FixMessage* fixMessage)
{
	ExecutionReportField rspField(fixMessage);
	TradeSpi::OnExecutionReport(&rspField);
}


void WorkThread::CheckEvent()
{
	unique_lock<mutex> guard(m_ThreadMutex);
	m_ThreadConditionVariable.wait_for(guard, std::chrono::seconds(1), [&] {return !m_MyEvents.empty();});
}
void WorkThread::HandleEvent()
{
	lock_guard<mutex> guard(m_MyEventMutex);
	for (auto& myEvent : m_MyEvents)
	{
		switch (myEvent->EventID)
		{
		case EVENT_CONNECTED:
		{
			auto sessionID = myEvent->NumParams[0];
			m_TradeApi->OnSessionConnected(sessionID);
			m_ConnectStatus = ConnectStatus::Connected;
			break;
		}
		case EVENT_DISCONNECTED:
		{
			m_ConnectStatus = ConnectStatus::NotConnected;
			m_LogonStatus = LogonStatus::NotLogged;
			break;
		}
		case EVENT_DO_RESEND_REQUEST:
		{
			if (m_LogonStatus == LogonStatus::Logged)
			{
				auto startSeqNum = myEvent->NumParams[0];
				auto endSeqNum = myEvent->NumParams[1];
				ReqResendRequest(startSeqNum, endSeqNum);
			}
			break;
		}
		case EVENT_DO_SEQUENCE_RESET:
		{
			if (m_LogonStatus == LogonStatus::Logged)
			{
				auto beginSeqNum = myEvent->StringParams[0];
				ReqSequenceReset(beginSeqNum);
			}
			break;
		}
		case EVENT_DO_TEST_REQUEST:
		{
			if (m_LogonStatus == LogonStatus::Logged)
			{
				auto testReqID = myEvent->StringParams[0];
				ReqTestRequest(testReqID);
			}
			break;
		}
		case EVENT_DO_REQ_LOGOUT:
		{
			if (m_LogonStatus != LogonStatus::Logout)
			{
				ReqLogout();
			}
			break;
		}
		
		default:
			_ASSERT(false);
			break;
		}
		MyEvent::Free(myEvent);
	}
	m_MyEvents.clear();
}
void WorkThread::CheckConnectStatus()
{
	if (m_ConnectStatus == ConnectStatus::NotConnected)
	{
		TcpThread::GetInstance().Connect(m_AccountInfo.IP.c_str(), atoi(m_AccountInfo.Port.c_str()));
		m_ConnectStatus = ConnectStatus::Connecting;
	}
}
void WorkThread::CheckLogonStatus()
{
	if (m_ConnectStatus == ConnectStatus::Connected && m_LogonStatus == LogonStatus::NotLogged)
	{
		m_LogonStatus = LogonStatus::Logging;
		ReqLogon();
	}
}
void WorkThread::CheckAndParsePackage()
{
	m_FixMessageParse->Parse();
}
void WorkThread::CheckRequest()
{

}


void WorkThread::Reset()
{
	m_ResendRange = make_pair(0, 0);
	m_FixMessages.clear();
}
void WorkThread::AddReqHeader()
{
	m_FixMessage = FixMessage::Allocate();
	m_FixMessage->SetItem(8, m_AccountInfo.BeginString);
	m_FixMessage->SetItem(34, ItoA(GlobalParam::GetInstance().GetNextSendSeqNum()));
	m_FixMessage->SetItem(43, "N");
	m_FixMessage->SetItem(49, m_SenderCompID);
	m_FixMessage->SetItem(50, m_AccountInfo.SenderSubID);
	m_FixMessage->SetItem(52, GetUtcTime());
	m_FixMessage->SetItem(56, m_AccountInfo.TargetCompID);
	m_FixMessage->SetItem(57, m_AccountInfo.TargetSubID);

	m_FixMessage->SetItem(142, m_AccountInfo.SenderLocationID);
	m_FixMessage->SetItem(369, ItoA(GlobalParam::GetInstance().GetLastRecvSeqNum()));
}
int WorkThread::ReqLogon()
{
	AddReqHeader();
	m_FixMessage->SetItem(49, m_AccountInfo.SenderCompID);
	ReqLogonField reqLogonField(m_FixMessage);

	reqLogonField.HeartBtInt = m_AccountInfo.HeartBtInt;
	reqLogonField.ResetSeqNumFlag = m_AccountInfo.ResetSeqNumFlag;
	reqLogonField.ApplicationSystemName = m_AccountInfo.ApplicationSystemName;
	reqLogonField.ApplicationSystemVersion = m_AccountInfo.ApplicationSystemVersion;
	reqLogonField.ApplicationSystemVendor = m_AccountInfo.ApplicationSystemVendor;
	reqLogonField.EncodedTextLen = ItoA(m_AccountInfo.AccountID.length());
	reqLogonField.EncodedText = m_AccountInfo.AccountID;
	reqLogonField.EncryptedPasswordMethod = m_AccountInfo.EncryptedPasswordMethod;

	std::string canonicalRequest = GetCanonicalReq(reqLogonField);
	std::string encodedHmac = calculateHMAC(m_AccountInfo.SecretKey, canonicalRequest);
	reqLogonField.EncryptedPasswordLen = ItoA(encodedHmac.length());
	reqLogonField.EncryptedPassword = encodedHmac;

	return m_TradeApi->ReqLogon(&reqLogonField);
}
int WorkThread::ReqLogout()
{
	AddReqHeader();
	ReqLogoutField reqField(m_FixMessage);

	m_LogonStatus = LogonStatus::Logout;
	return m_TradeApi->ReqLogout(&reqField);
}
int WorkThread::ReqHeartBeat(string testReqID)
{
	AddReqHeader();
	ReqHeartBeatField reqField(m_FixMessage);
	reqField.TestReqID = testReqID;

	return m_TradeApi->ReqHeartBeat(&reqField);
}
int WorkThread::ReqTestRequest(string testReqID)
{
	AddReqHeader();
	ReqTestRequestField reqField(m_FixMessage);
	reqField.TestReqID = testReqID;

	return m_TradeApi->ReqTestRequest(&reqField);
}
int WorkThread::ReqResendRequest(int startSeqNum, int endSeqNum)
{
	if (IsOnResend())
	{
		WRITE_LOG(LogLevel::Info, "Already sent ResendRequest FROM:[%d] TO:[%d], Not sending another", m_ResendRange.first, m_ResendRange.second);
		return 0;
	}
	AddReqHeader();
	ReqResendRequestField reqField(m_FixMessage);

	endSeqNum = endSeqNum < (startSeqNum + 2499) ? endSeqNum : (startSeqNum + 2499);
	m_ResendRange = make_pair(startSeqNum, endSeqNum);

	reqField.BeginSeqNo = ItoA(startSeqNum);
	reqField.EndSeqNo = ItoA(endSeqNum);

	GlobalParam::GetInstance().SetNextExpectSeqNum(startSeqNum);
	return m_TradeApi->ReqResendRequest(&reqField);
}
int WorkThread::ReqSequenceReset(const string& beginSeqNum)
{
	AddReqHeader();
	ReqSequenceResetField reqField(m_FixMessage);
	reqField.PossDupFlag = "Y";
	auto nextSendSeqNum = reqField.MsgSeqNum;
	GlobalParam::GetInstance().SetNextSendSeqNum(nextSendSeqNum);
	reqField.MsgSeqNum = beginSeqNum;
	reqField.NewSeqNo = nextSendSeqNum;
	reqField.GapFillFlag = "N";

	return m_TradeApi->ReqSequenceReset(&reqField);
}
int WorkThread::ReqNewOrder()
{
	AddReqHeader();
	ReqNewOrderField reqField(m_FixMessage);
	reqField.Account = "2F5004";
	reqField.ClOrdID = "5";
	reqField.HandInst = "1";
	reqField.CustOrderHandlingInst = "Y";
	reqField.OrderQty = "5";
	reqField.OrdType = "1";
	reqField.Price = "";
	reqField.Side = "1";
	reqField.Symbol = "";
	reqField.TimeInForce = "0";
	reqField.TransactTime = GetUtcTime();
	reqField.ManualOrderIndicator = "Y";
	reqField.NoAllocs = "";
	reqField.AllocAccount = "";
	reqField.StopPx = "";
	reqField.SecurityDesc = "GEZ8";
	reqField.MinQty = "1";
	reqField.SecurityType = "FUT";
	reqField.CustomerOrFirm = "0";
	reqField.MaxShow = "1";
	reqField.ExpireDate = "";
	reqField.SelfMatchPreventionID = "";
	reqField.SelfMatchPreventionInstruction = "";
	reqField.CtiCode = "4";
	reqField.AvgPxGroupID = "";
	reqField.ClearingTradePriceType = "";
	reqField.AvgPXIndicator = "";
	reqField.Memo = "";
	reqField.GiveUpFirm = "";
	reqField.CmtaGiveupCD = "";
	reqField.CorrelationClOrdID = "5";
	reqField.MarketSegmentID = "99";

	return m_TradeApi->ReqNewOrder(&reqField);
}
