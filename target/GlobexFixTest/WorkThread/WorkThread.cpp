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

	m_IsDoResendRequest = false;
	m_TestReqID = "Hello World!";
}

WorkThread& WorkThread::GetInstance()
{
	return m_Instance;
}
bool WorkThread::Init()
{
	ReadAccountInfo(&m_AccountInfo);
	m_HeartBeatSecond = atoi(m_AccountInfo.HeartBtInt.c_str());
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
	CheckSendHeartBeat();
	CheckRecvHeartBeat();
	CheckTestRequstReply();
}
void WorkThread::OnEventSequenceGap(int beginSeqNo, int endSeqNo)
{
	endSeqNo = endSeqNo < (beginSeqNo + 2499) ? endSeqNo : (beginSeqNo + 2499);
	m_ResendRange = make_pair(beginSeqNo, endSeqNo);

	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_ON_SEQUENCE_GAP;
	myEvent->NumParams.push_back(beginSeqNo);
	myEvent->NumParams.push_back(endSeqNo);
	
	OnEvent(myEvent);
}
void WorkThread::OnEventDoResendRequest(int beginSeqNo, int endSeqNo)
{
	if (m_IsDoResendRequest)
	{
		return;
	}
	m_IsDoResendRequest = true;
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_RESEND_REQUEST;
	myEvent->NumParams.push_back(beginSeqNo);
	myEvent->NumParams.push_back(endSeqNo);
	
	OnEvent(myEvent);
}
void WorkThread::OnEventDoLogout()
{
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_REQ_LOGOUT;

	OnEvent(myEvent);
}
void WorkThread::OnRecv(int sessionID, char* buff, int len)
{
	m_FixMessageParse->OnRecv(buff, len);
	m_ThreadConditionVariable.notify_one();
}
void WorkThread::UpdateLastSendTime()
{
	m_LastSendTimeCount = 0;
	m_LastSendTimePoint = chrono::steady_clock().now();
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
		WRITE_LOG(LogLevel::Info, "Already sent ResendRequest FROM:[%d] TO:[%d], MsgSeqNum:[%d], Send again!!!", m_ResendRange.first, m_ResendRange.second, msgSeqNum);
		OnEventSequenceGap(m_ResendRange.first, m_ResendRange.second);
	}
	else
	{
		OnEventSequenceGap(expectSeqNum, msgSeqNum - 1);
	}
}
void WorkThread::OnMsgSeqTooLow(FixMessage* fixMessage, int msgSeqNum, int expectSeqNum)
{
	auto possDupFlag = fixMessage->GetPossDupFlag();
	auto msgType = fixMessage->GetMessageType();
	fixMessage->ToString(m_LogBuff, BUFF_SIZE);
	if (possDupFlag != "Y" || msgType != "4")
	{
		WRITE_LOG(LogLevel::Error, "MsgSeqNum too low, Expect:[%d], Receive:[%d], FixMessage:%s", expectSeqNum, msgSeqNum, m_LogBuff);
		OnEventDoLogout();
	}
	FixMessage::Free(fixMessage);
}
bool WorkThread::NextQueue()
{
	if (m_FixMessages.size() == 0)
	{
		return false;
	}
	auto nextExpectSeqNum = GlobalParam::GetInstance().GetNextExpectSeqNum();
	auto it = m_FixMessages.begin();
	auto msgSeqNum = it->first;
	if (msgSeqNum < nextExpectSeqNum)
	{
		it->second->ToString(m_LogBuff, BUFF_SIZE);
		WRITE_LOG(LogLevel::Warning, "Find MsgSeqNum Less than Expect in Queue. FixMessage: %s", m_LogBuff);
		m_FixMessages.erase(it);
		return true;
	}
	else if (msgSeqNum == nextExpectSeqNum)
	{
		auto fixMessage = it->second;
		m_FixMessages.erase(it);
		OnFixMessage(fixMessage);
		return true;
	}
	if (!IsOnResend())
	{
		OnEventSequenceGap(nextExpectSeqNum, msgSeqNum - 1);
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
		if (!Verify(fixMessage))
		{
			return;
		}
		GlobalParam::GetInstance().SetLastRecvSeqNum(seqNum);
		GlobalParam::GetInstance().IncreaseNextExpectSeqNum();
		if (msgType == "8")
		{
			OnExecutionReport(fixMessage);
		}
		else
		{
			fixMessage->ToString(m_LogBuff, BUFF_SIZE);
			WRITE_LOG(LogLevel::Error, "UnKnown MsgType:[%s], FixMessage:%s", msgType.c_str(), m_LogBuff);
		}
	}

	m_LastRecvTimeCount = 0;
	m_LastRecvTimePoint = chrono::steady_clock::now();
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

	if (m_AlreadySendTestRequest && m_TestReqID == rspField.TestReqID)
	{
		m_AlreadySendTestRequest = false;
		m_TestRequestSendTimeCount = 0;
	}
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
	GlobalParam::GetInstance().IncreaseNextExpectSeqNum();

	ReqHeartBeat(rspField.TestReqID);
}
void WorkThread::OnRspResendRequest(FixMessage* fixMessage)
{
	RspResendRequestField rspField(fixMessage);
	TradeSpi::OnRspResendRequest(&rspField);
	
	auto msgSeqNum = atoi(fixMessage->GetMsgSeqNum().c_str());
	auto nextExpectSeqNum = GlobalParam::GetInstance().GetNextExpectSeqNum();
	if (nextExpectSeqNum == msgSeqNum)
	{
		GlobalParam::GetInstance().SetLastRecvSeqNum(rspField.MsgSeqNum);
		GlobalParam::GetInstance().IncreaseNextExpectSeqNum();
	}
	OnEventDoResendRequest(atoi(rspField.BeginSeqNo.c_str()), atoi(rspField.EndSeqNo.c_str()));
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


void WorkThread::HandleEvent()
{
	MyEvent* myEvent = nullptr;
	while (myEvent = GetEvent())
	{
		bool shouldRepush = false;
		switch (myEvent->EventID)
		{
		case EVENT_ON_CONNECTED:
		{
			auto& ip = myEvent->StringParams[0];
			auto prot = myEvent->NumParams[0];
			auto sessionID = myEvent->NumParams[1];
			m_TradeApi->OnSessionConnected(sessionID);
			m_ConnectStatus = ConnectStatus::Connected;
			break;
		}
		case EVENT_ON_DISCONNECTED:
		{
			auto& ip = myEvent->StringParams[0];
			auto prot = myEvent->NumParams[0];
			auto sessionID = myEvent->NumParams[1];

			m_ConnectStatus = ConnectStatus::NotConnected;
			Reset();
			break;
		}
		case EVENT_ON_SEQUENCE_GAP:
		{
			if (m_LogonStatus == LogonStatus::Logged)
			{
				auto startSeqNum = myEvent->NumParams[0];
				auto endSeqNum = myEvent->NumParams[1];
				ReqResendRequest(startSeqNum, endSeqNum);
			}
			break;
		}
		case EVENT_DO_RESEND_REQUEST:
		{
			if (m_LogonStatus == LogonStatus::Logged)
			{
				auto beginSeqNum = myEvent->NumParams[0];
				auto endSeqNum = myEvent->NumParams[1];
				DoResendRequest(beginSeqNum, endSeqNum);
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
			else
			{
				shouldRepush = true;
			}
			break;
		}
		case EVENT_DO_REQ_LOGOUT:
		{
			if (m_ConnectStatus == ConnectStatus::Connected)
			{
				ReqLogout();
			}
			break;
		}
		case EVENT_DO_REQ_NEW_ORDER:
		{
			if (m_LogonStatus == LogonStatus::Logged && !m_IsDoResendRequest)
			{
				ReqNewOrder();
			}
			else
			{
				shouldRepush = true;
			}
			break;
		}
		default:
			_ASSERT(false);
			break;
		}
		if (shouldRepush)
		{
			OnEvent(myEvent);
		}
		else
		{
			MyEvent::Free(myEvent);
		}
	}
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
void WorkThread::CheckSendHeartBeat()
{
	if (++m_LastSendTimeCount < m_HeartBeatSecond)
	{
		return;
	}
	auto timeDiff = chrono::steady_clock::now() - m_LastSendTimePoint;
	auto timeDiffSecond = chrono::duration_cast<chrono::seconds>(timeDiff);
	if (timeDiffSecond.count() >= m_HeartBeatSecond)
	{
		ReqHeartBeat("");
	}
}
void WorkThread::CheckRecvHeartBeat()
{
	if (++m_LastRecvTimeCount < m_HeartBeatSecond)
	{
		return;
	}
	auto timeDiff = chrono::steady_clock::now() - m_LastRecvTimePoint;
	auto timeDiffSecond = chrono::duration_cast<chrono::seconds>(timeDiff);
	if (timeDiffSecond.count() >= m_HeartBeatSecond)
	{
		m_AlreadySendTestRequest = true;
		m_TestRequestSendTimeCount = 0;
		m_TestRequestSendTimePoint = chrono::steady_clock::now();
		ReqTestRequest(m_TestReqID);
	}
}
void WorkThread::CheckTestRequstReply()
{
	if (!m_AlreadySendTestRequest)
	{
		return;
	}
	if (++m_TestRequestSendTimeCount < m_HeartBeatSecond)
	{
		return;
	}
	auto timeDiff = chrono::steady_clock::now() - m_TestRequestSendTimePoint;
	auto timeDiffSecond = chrono::duration_cast<chrono::seconds>(timeDiff);
	if (timeDiffSecond.count() >= m_HeartBeatSecond)
	{
		OnEventDoLogout();
	}
}




void WorkThread::Reset()
{
	m_LogonStatus = LogonStatus::NotLogged;
	m_AlreadySendLogout = false;
	m_ResendRange = make_pair(0, 0);
	m_FixMessages.clear();
}
void WorkThread::AddReqHeader(string msgSeqNum)
{
	m_FixMessage = FixMessage::Allocate();
	m_FixMessage->SetItem(8, m_AccountInfo.BeginString);
	if (msgSeqNum.empty())
	{
		m_FixMessage->SetItem(34, ItoA(GlobalParam::GetInstance().GetNextSendSeqNum()));
	}
	else
	{
		m_FixMessage->SetItem(34, msgSeqNum);
	}
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
	if (m_AlreadySendLogout)
		return 0;
	m_AlreadySendLogout = true;
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
	AddReqHeader();
	ReqResendRequestField reqField(m_FixMessage);
	reqField.PossDupFlag = "Y";

	reqField.BeginSeqNo = ItoA(startSeqNum);
	reqField.EndSeqNo = ItoA(endSeqNum);

	GlobalParam::GetInstance().SetNextExpectSeqNum(startSeqNum);
	return m_TradeApi->ReqResendRequest(&reqField);
}
void WorkThread::DoResendRequest(int startSeqNum, int endSeqNum)
{
	m_IsDoResendRequest = false;
	endSeqNum = GlobalParam::GetInstance().GetNextSendSeqNum();
	if (m_AppReqFields.size() == 0)
	{
		ReqSequenceReset(startSeqNum, endSeqNum);
		return;
	}
	int currSeqNum = startSeqNum;
	for (auto it = m_AppReqFields.begin(); it != m_AppReqFields.end(); ++it)
	{
		if (it->first < currSeqNum)
		{
			continue;
		}
		if (it->first > currSeqNum)
		{
			ReqSequenceReset(currSeqNum, it->first);
			currSeqNum = it->first;
		}
		it->second->SendingTime = GetUtcTime();
		it->second->PossDupFlag = "Y";
		it->second->LastMsgSeqNumProcessed = ItoA(GlobalParam::GetInstance().GetLastRecvSeqNum());
		m_TradeApi->SendResendRequest(it->second);
		currSeqNum++;
	}
	if (currSeqNum < endSeqNum)
	{
		ReqSequenceReset(currSeqNum, endSeqNum);
	}
}
int WorkThread::ReqSequenceReset(int beginSeqNum, int endSeqNum)
{
	AddReqHeader(ItoA(beginSeqNum));
	ReqSequenceResetField reqField(m_FixMessage);
	reqField.PossDupFlag = "Y";
	reqField.NewSeqNo = ItoA(endSeqNum);
	reqField.GapFillFlag = "Y";

	return m_TradeApi->ReqSequenceReset(&reqField);
}
int WorkThread::ReqNewOrder()
{
	AddReqHeader();
	ReqNewOrderField* reqField = new ReqNewOrderField(m_FixMessage);
	reqField->Account = "2F5004";
	reqField->ClOrdID = ItoA(GlobalParam::GetInstance().GetClOrdID());
	reqField->HandInst = "1";
	reqField->CustOrderHandlingInst = "Y";
	reqField->OrderQty = "1";
	reqField->OrdType = "2";
	reqField->Price = "100";
	reqField->Side = "1";
	reqField->Symbol = "";
	reqField->TimeInForce = "0";
	reqField->TransactTime = GetUtcTime();
	reqField->ManualOrderIndicator = "Y";
	reqField->NoAllocs = "";
	reqField->AllocAccount = "";
	reqField->StopPx = "";
	//reqField->SecurityDesc = "GEZ8";
	reqField->SecurityDesc = "0GLBZ0";
	reqField->MinQty = "1";
	reqField->SecurityType = "FUT";
	reqField->CustomerOrFirm = "0";
	reqField->MaxShow = "1";
	reqField->ExpireDate = "";
	reqField->SelfMatchPreventionID = "";
	reqField->SelfMatchPreventionInstruction = "";
	reqField->CtiCode = "4";
	reqField->AvgPxGroupID = "";
	reqField->ClearingTradePriceType = "";
	reqField->AvgPXIndicator = "";
	reqField->Memo = "";
	reqField->GiveUpFirm = "";
	reqField->CmtaGiveupCD = "";
	reqField->CorrelationClOrdID = reqField->ClOrdID;
	//reqField->MarketSegmentID = "99";
	//reqField->MarketSegmentID = "931";
	reqField->MarketSegmentID = "925";

	int ret = m_TradeApi->ReqNewOrder(reqField);

	reqField->OrigSendingTime = reqField->SendingTime;
	m_AppReqFields[atoi(reqField->MsgSeqNum.c_str())] = reqField;

	return ret;
}
