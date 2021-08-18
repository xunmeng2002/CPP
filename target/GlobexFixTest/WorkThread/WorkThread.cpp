#include "WorkThread.h"
#include  "Logger.h"
#include "TcpThread.h"
#include "MemCacheTemplateSingleton.h"
#include "GlobalParam.h"
#include "CryptoppEncode.h"
#include "FixMessageParse.h"
#include "TradeApi.h"
#include "TradeApiTables.h"




WorkThread WorkThread::m_Instance;

WorkThread::WorkThread(const char* name)
	:ThreadBase(name), m_LastResendRequestField(m_FixMessage)
{
	m_FixMessage = nullptr;
	m_TradeApi = new TradeApi();
	m_FixMessageParse = new FixMessageParse(this);
	
	m_IsLastConnectPrimary = false;
	m_IsDoResendRequest = false;
	m_TestReqID = "Hello World!";

	m_AlreadySendTestRequest = false;
	m_AlreadySendLogout = false;
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
void WorkThread::InitReqMessage(ReqHeader* reqHeader)
{
	reqHeader->ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "InitReqMessage: %s", m_LogBuff);
	m_AppReqFields.insert(make_pair(atoi(reqHeader->MsgSeqNum.c_str()), reqHeader));
}
void WorkThread::InitRspMessage(RspHeader* rspHeader)
{
	rspHeader->ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "InitRspMessage: %s", m_LogBuff);
	m_AppRspFields.insert(make_pair(atoi(rspHeader->MsgSeqNum.c_str()), rspHeader));
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
void WorkThread::OnEventResendLastResendRequest()
{
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_ON_RESEND_LAST_RESEND_REQUEST;

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
	m_AlreadySendLogout = true;
}
void WorkThread::OnEventTestRequest(const string& testReqID)
{
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_TEST_REQUEST;
	if (testReqID.empty())
	{
		myEvent->StringParams.push_back(m_TestReqID);
	}
	else
	{
		myEvent->StringParams.push_back(testReqID);
	}
	OnEvent(myEvent);
}
void WorkThread::OnRecv(TcpEvent* tcpEvent)
{
	OnEvent(tcpEvent);
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
	GlobalParam::GetInstance().SetLastRecvSeqNum(msgSeqNum);
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
		OnEventResendLastResendRequest();
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
	WRITE_LOG(LogLevel::Info, "MsgSeqNum too low, Expect:[%d], Receive:[%d], FixMessage:%s", expectSeqNum, msgSeqNum, m_LogBuff);
	if (possDupFlag != "Y" && msgType != "4")
	{
		OnEventDoLogout();
	}
	fixMessage->Free();
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
		if (msgType == "8")
		{
			OnExecutionReport(fixMessage);
		}
		else if (msgType == "9")
		{
			OnRspOrderCancelReject(fixMessage);
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
	m_LogonStatus = LogonStatus::Logged;
	m_SenderCompID = fixMessage->GetItem(56);

	auto resetSeqNumFlag = fixMessage->GetItem(141);
	if (resetSeqNumFlag == "Y")
	{
		WRITE_LOG(LogLevel::Info, "Reset Sequence Num to 1");
		GlobalParam::GetInstance().SetLastRecvSeqNum(1);
	}
	else if (!Verify(fixMessage, true, true))
	{
		return;
	}
	RspLogonField rspField(fixMessage);
	TradeSpi::OnRspLogon(&rspField);
}
void WorkThread::OnRspLogout(FixMessage* fixMessage)
{
	RspLogoutField rspField(fixMessage);
	TradeSpi::OnRspLogout(&rspField);

	if (rspField.NextExpectedMsgSeqNum == "1")
	{
		ResetSequenceNum();
	}
	else if (!rspField.NextExpectedMsgSeqNum.empty())
	{
		GlobalParam::GetInstance().SetNextSendSeqNum(rspField.NextExpectedMsgSeqNum);
	}
	GlobalParam::GetInstance().SetLastRecvSeqNum(rspField.MsgSeqNum);

	m_LogonStatus = LogonStatus::Logout;
	ResetConnect();
}
void WorkThread::OnRspHeartBeat(FixMessage* fixMessage)
{
	if (!Verify(fixMessage))
	{
		return;
	}

	RspHeartBeatField rspField(fixMessage);
	TradeSpi::OnRspHeartBeat(&rspField);

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
	RecordResponse(&rspField);
}
void WorkThread::OnRspSequenceReset(FixMessage* fixMessage)
{
	RspSequenceResetField rspField(fixMessage);
	TradeSpi::OnRspSequenceReset(&rspField);

	auto nextExpectSeqNum = GlobalParam::GetInstance().GetNextExpectSeqNum();
	auto newSeqNo = atoi(rspField.NewSeqNo.c_str());
	WRITE_LOG(LogLevel::Info, "Received SequenceReset FROM [%d] To [%d]", nextExpectSeqNum, newSeqNo);

	if (IsOnResend() && newSeqNo > m_ResendRange.second)
	{
		GlobalParam::GetInstance().SetLastRecvSeqNum(m_ResendRange.second);
		m_ResendRange = make_pair(0, 0);
	}
	else
	{
		GlobalParam::GetInstance().SetLastRecvSeqNum(newSeqNo - 1);
	}
}
void WorkThread::OnExecutionReport(FixMessage* fixMessage)
{
	ExecutionReportField rspField(fixMessage);
	TradeSpi::OnExecutionReport(&rspField);
	RecordResponse(&rspField);

	auto order = UpdateOrder(&rspField);
	if (order == nullptr)
	{
		return;
	}
	if (order->OrderStatus == OrderStatus::PartiallyFilled || order->OrderStatus == OrderStatus::Filled)
	{
		AddNewTrade(&rspField, order);
	}
	else if (order->OrderStatus == OrderStatus::TradeCorrect)
	{
		ModifyTrade(&rspField, order);
	}
	else if (order->OrderStatus == OrderStatus::TradeCancel)
	{
		CancelTrade(&rspField, order);
	}
	ReportOrder();
	ReportTrade();
}
void WorkThread::OnRspOrderCancelReject(FixMessage* fixMessage)
{
	RspOrderCancelRejectField rspField(fixMessage);
	TradeSpi::OnRspOrderCancelReject(&rspField);
	RecordResponse(&rspField);
}


void WorkThread::HandleEvent()
{
	Event* event = nullptr;
	TcpEvent* tcpEvent = nullptr;
	MyEvent* myEvent = nullptr;
	while (event = GetEvent())
	{
		bool shouldRepush = false;
		switch (event->EventID)
		{
		case EVENT_ON_CONNECTED:
		{
			myEvent = (MyEvent*)event;
			auto& ip = myEvent->StringParams[0];
			auto prot = myEvent->NumParams[0];
			auto sessionID = myEvent->NumParams[1];
			m_TradeApi->OnSessionConnected(sessionID);
			m_ConnectStatus = ConnectStatus::Connected;
			break;
		}
		case EVENT_ON_DISCONNECTED:
		{
			myEvent = (MyEvent*)event;
			auto& ip = myEvent->StringParams[0];
			auto prot = myEvent->NumParams[0];
			auto sessionID = myEvent->NumParams[1];

			m_ConnectStatus = ConnectStatus::NotConnected;
			m_LogonStatus = LogonStatus::NotLogged;
			ResetConnect();
			break;
		}
		case EVENT_ON_SEQUENCE_GAP:
		{
			myEvent = (MyEvent*)event;
			auto startSeqNum = myEvent->NumParams[0];
			auto endSeqNum = myEvent->NumParams[1];
			ReqResendRequest(startSeqNum, endSeqNum);
			break;
		}
		case EVENT_ON_RESEND_LAST_RESEND_REQUEST:
		{
			ResendLastResendRequest();
			break;
		}
		case EVENT_DO_RESEND_REQUEST:
		{
			myEvent = (MyEvent*)event;
			if (m_LogonStatus == LogonStatus::Logged)
			{
				auto beginSeqNum = myEvent->NumParams[0];
				auto endSeqNum = myEvent->NumParams[1];
				DoResendRequest(beginSeqNum, endSeqNum);
				OnEventTestRequest();
			}
			break;
		}
		case EVENT_DO_TEST_REQUEST:
		{
			myEvent = (MyEvent*)event;
			if (m_LogonStatus == LogonStatus::Logged)
			{
				auto& testReqID = myEvent->StringParams[0];
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
			myEvent = (MyEvent*)event;
			if (m_LogonStatus == LogonStatus::Logged && !m_IsDoResendRequest)
			{
				const string& marketSegmentID = myEvent->StringParams[0];
				const string& instrumentID = myEvent->StringParams[1];
				const string& orderType = myEvent->StringParams[2];
				const string& price = myEvent->StringParams[3];
				const string& stopPrice = myEvent->StringParams[4];
				int orderQty = myEvent->NumParams[0];
				ReqNewOrder(marketSegmentID, instrumentID, orderType, price, stopPrice, orderQty);
			}
			else
			{
				shouldRepush = true;
			}
			break;
		}
		case EVENT_DO_REQ_ORDER_CANCEL:
		{
			myEvent = (MyEvent*)event;
			if (m_LogonStatus == LogonStatus::Logged && !m_IsDoResendRequest)
			{
				auto& orderLocalID = myEvent->StringParams[0];
				ReqOrderCancelRequest(orderLocalID);
			}
			else
			{
				shouldRepush = true;
			}
			break;
		}
		case EVENT_DO_REQ_ORDER_CANCEL_REPLACE:
		{
			myEvent = (MyEvent*)event;
			if (m_LogonStatus == LogonStatus::Logged && !m_IsDoResendRequest)
			{
				auto& origOrderLocalID = myEvent->StringParams[0];
				auto& price = myEvent->StringParams[1];
				int orderQty = myEvent->NumParams[0];
				ReqOrderCancelReplaceRequest(origOrderLocalID, price, orderQty);
			}
			else
			{
				shouldRepush = true;
			}
			break;
		}
		case EVENT_ON_TCP_RECV:
		{
			tcpEvent = (TcpEvent*)event;
			m_FixMessageParse->OnRecv(tcpEvent->Buff, tcpEvent->Length);
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
			event->Free();
		}
	}
}
void WorkThread::CheckConnectStatus()
{
	if (m_ConnectStatus != ConnectStatus::NotConnected)
	{
		return;
	}
	auto& port = m_IsLastConnectPrimary ? m_AccountInfo.BackupPort : m_AccountInfo.PrimaryPort;
	m_IsLastConnectPrimary = !m_IsLastConnectPrimary;
	TcpThread::GetInstance().Connect(m_AccountInfo.IP.c_str(), atoi(port.c_str()));
	m_ConnectStatus = ConnectStatus::Connecting;
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
	if (!m_AlreadySendTestRequest && timeDiffSecond.count() >= m_HeartBeatSecond)
	{
		m_AlreadySendTestRequest = true;
		m_TestRequestSendTimeCount = 0;
		m_TestRequestSendTimePoint = chrono::steady_clock::now();
		OnEventTestRequest();
	}
}
void WorkThread::CheckTestRequstReply()
{
	if (!m_AlreadySendTestRequest || m_AlreadySendLogout)
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

void WorkThread::ResetSequenceNum()
{
	GlobalParam::GetInstance().ResetSeqNum();
	TradeApiTables::GetInstance().TruncateAllTables();
	for (auto& it : m_AppReqFields)
	{
		delete it.second;
	}
	m_AppReqFields.clear();
}
void WorkThread::ResetConnect()
{
	m_ResendRange = make_pair(0, 0);
	m_FixMessages.clear();
	m_AlreadySendLogout = false;
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
void WorkThread::ReqLogon()
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

	m_TradeApi->ReqLogon(&reqLogonField);
}
void WorkThread::ReqLogout()
{
	AddReqHeader();
	ReqLogoutField reqField(m_FixMessage);

	m_LogonStatus = LogonStatus::Logout;
	m_TradeApi->ReqLogout(&reqField);
}
void WorkThread::ReqHeartBeat(string testReqID)
{
	AddReqHeader();
	ReqHeartBeatField reqField(m_FixMessage);
	reqField.TestReqID = testReqID;

	m_TradeApi->ReqHeartBeat(&reqField);
}
void WorkThread::ReqTestRequest(string testReqID)
{
	AddReqHeader();
	ReqTestRequestField reqField(m_FixMessage);
	reqField.TestReqID = testReqID;

	m_TradeApi->ReqTestRequest(&reqField);
}
void WorkThread::ReqResendRequest(int startSeqNum, int endSeqNum)
{
	AddReqHeader();
	ReqResendRequestField reqField(m_FixMessage);

	reqField.BeginSeqNo = ItoA(startSeqNum);
	reqField.EndSeqNo = ItoA(endSeqNum);

	m_TradeApi->ReqResendRequest(&reqField);

	m_LastResendRequestField = std::move(reqField);
}
void WorkThread::ResendLastResendRequest()
{
	m_LastResendRequestField.SendingTime = GetUtcTime();
	m_LastResendRequestField.PossDupFlag = "Y";

	m_TradeApi->SendResendRequest(&m_LastResendRequestField);
}
void WorkThread::DoResendRequest(int startSeqNum, int endSeqNum)
{
	m_IsDoResendRequest = false;
	endSeqNum = GlobalParam::GetInstance().GetNextSendSeqNum();
	if (m_AppReqFields.size() == 0)
	{
		ReqSequenceReset(startSeqNum, endSeqNum, "N");
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
		ReqSequenceReset(currSeqNum, endSeqNum, "N");
	}
}
void WorkThread::ReqSequenceReset(int beginSeqNum, int endSeqNum, const string& gapFil)
{
	AddReqHeader(ItoA(beginSeqNum));
	ReqSequenceResetField reqField(m_FixMessage);
	reqField.PossDupFlag = "Y";
	reqField.NewSeqNo = ItoA(endSeqNum);
	reqField.GapFillFlag = gapFil;

	m_TradeApi->ReqSequenceReset(&reqField);
}
void WorkThread::ReqNewOrder(const string& marketSegmentID, const string& instrumentID, const string& orderType, const string& price, const string& stopPrice, int orderQty)
{
	AddReqHeader();
	ReqNewOrderField* reqField = new ReqNewOrderField(m_FixMessage);
	reqField->Account = "2F5004";
	reqField->ClOrdID = ItoA(GlobalParam::GetInstance().GetClOrdID());
	reqField->HandInst = "1";
	reqField->CustOrderHandlingInst = "Y";
	reqField->OrderQty = ItoA(orderQty);
	reqField->OrdType = orderType;
	reqField->Price = price;
	reqField->Side = "1";
	reqField->Symbol = "";
	reqField->TimeInForce = "0";
	reqField->TransactTime = GetUtcTime();
	reqField->ManualOrderIndicator = "Y";
	reqField->NoAllocs = "";
	reqField->AllocAccount = "";
	reqField->StopPx = stopPrice;
	reqField->SecurityDesc = instrumentID;
	reqField->MinQty = "";
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
	reqField->MarketSegmentID = marketSegmentID;

	m_TradeApi->ReqNewOrder(reqField);
	AddNewOrder(reqField);
	RecordRequest(reqField);
}
void WorkThread::ReqOrderCancelRequest(const string& origOrderLocalID)
{
	auto order = GetOrderForOrderLocalID(origOrderLocalID);
	if (order == nullptr)
	{
		return;
	}
	AddReqHeader();
	ReqOrderCancelRequestField* reqField = new ReqOrderCancelRequestField(m_FixMessage);
	reqField->Account = order->AccountID;
	reqField->ClOrdID = ItoA(GlobalParam::GetInstance().GetClOrdID());;
	reqField->OrderID = order->OrderSysID;
	
	reqField->Side = ToString(order->Direction);
	reqField->Symbol = order->Symbol;
	reqField->TransactTime = GetUtcTime();
	reqField->ManualOrderIndicator = "Y";
	reqField->SecurityDesc = order->InstrumentID;
	reqField->SecurityType = order->SecurityType;
	reqField->CorrelationClOrdID = reqField->ClOrdID;
	
	m_TradeApi->ReqOrderCancelRequest(reqField);
	RecordRequest(reqField);
}
void WorkThread::ReqOrderCancelReplaceRequest(const string& origOrderLocalID, const string& newPrice, int newVolume)
{
	auto order = GetOrderForOrderLocalID(origOrderLocalID);
	if (order == nullptr)
	{
		return;
	}
	AddReqHeader();
	ReqOrderCancelReplaceRequestField* reqField = new ReqOrderCancelReplaceRequestField(m_FixMessage);
	reqField->Account = order->AccountID;
	reqField->ClOrdID = ItoA(GlobalParam::GetInstance().GetClOrdID());
	reqField->HandInst = "1";
	reqField->OrderID = order->OrderSysID;
	reqField->OrderQty = ItoA(newVolume);
	reqField->CustOrderHandlingInst = "Y";
	reqField->OrdType = ToString(order->OrderType);
	reqField->OrigClOrdID = order->OrderLocalID;
	reqField->Price = newPrice;
	reqField->Side = ToString(order->Direction);
	reqField->Symbol = "";
	reqField->TimeInForce = "0";
	reqField->ManualOrderIndicator = "Y";
	reqField->TransactTime = GetUtcTime();
	reqField->SecurityDesc = order->InstrumentID;
	reqField->MinQty = "";
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
	reqField->CorrelationClOrdID = reqField->ClOrdID;
	reqField->OFMOverride = "";
	
	m_TradeApi->ReqOrderCancelReplaceRequest(reqField);
	RecordRequest(reqField);
}
void WorkThread::ReqOrderStatusRequest(const string& origOrderLocalID)
{
	auto order = GetOrderForOrderLocalID(origOrderLocalID);
	if (order == nullptr)
	{
		return;
	}
	AddReqHeader();
	ReqOrderStatusRequestField* reqField = new ReqOrderStatusRequestField(m_FixMessage);
	reqField->ClOrdID = ItoA(GlobalParam::GetInstance().GetClOrdID());;
	reqField->OrderID = order->OrderSysID;

	reqField->Side = ToString(order->Direction);
	reqField->Symbol = order->Symbol;
	reqField->TransactTime = GetUtcTime();
	reqField->ManualOrderIndicator = "Y";
	reqField->SecurityDesc = order->InstrumentID;
	reqField->SecurityType = order->SecurityType;
	reqField->CorrelationClOrdID = reqField->ClOrdID;

	m_TradeApi->ReqOrderStatusRequest(reqField);
	RecordRequest(reqField);
}

void WorkThread::RecordRequest(ReqHeader* reqField)
{
	TradeApiTables::GetInstance().InsertRecord(reqField);

	reqField->OrigSendingTime = reqField->SendingTime;
	m_AppReqFields[atoi(reqField->MsgSeqNum.c_str())] = reqField;
}
void WorkThread::RecordResponse(RspHeader* rspField)
{
	TradeApiTables::GetInstance().InsertRecord(rspField);
}
Order* WorkThread::GetOrder(string orderID)
{
	if (m_Orders.find(orderID) != m_Orders.end())
	{
		return m_Orders[orderID];
	}
	WRITE_LOG(LogLevel::Warning, "Cannot Find Order For OrderID:[%s]", orderID.c_str());
	return nullptr;
}
Order* WorkThread::GetOrderForOrderLocalID(string orderLocalID)
{
	if (m_Orders.find(orderLocalID) != m_Orders.end())
	{
		return m_Orders[orderLocalID];
	}
	return nullptr;
}
Order* WorkThread::GetOrderForOrderSysID(string orderSysID)
{
	auto it = find_if(m_Orders.begin(), m_Orders.end(), [&](const pair<string, Order*>& item) {
		return item.second->OrderSysID == orderSysID;
		});
	if (it != m_Orders.end())
	{
		return it->second;
	}
	return nullptr;
}
Order* WorkThread::AddNewOrder(ReqNewOrderField* reqNewOrde)
{
	Order* order = new Order();
	order->BrokerID = "";
	order->AccountID = reqNewOrde->Account;
	order->ExchangeID = reqNewOrde->MarketSegmentID;
	order->InstrumentID = reqNewOrde->SecurityDesc;
	order->Direction = DirectionConvert(reqNewOrde->Side);
	order->OrderType = OrderTypeConvert(reqNewOrde->OrdType);
	order->Price = atof(reqNewOrde->Price.c_str());
	order->Volume = atoi(reqNewOrde->OrderQty.c_str());
	order->VolumeTraded = 0;
	order->OrderStatus = OrderStatus::Undefined;
	order->OrderLocalID = reqNewOrde->ClOrdID;
	order->OrderSysID = "";
	order->Symbol = reqNewOrde->Symbol;
	order->TimeInForce = TimeInForceConvert(reqNewOrde->TimeInForce);
	order->TransactTime = reqNewOrde->TransactTime;
	order->SecurityType = reqNewOrde->SecurityType;

	m_Orders.insert(make_pair(order->OrderLocalID, order));
	return order;
}
Order* WorkThread::AddNewOrder(ExecutionReportField* executionReport)
{
	Order* order = new Order();
	order->BrokerID = "";
	order->AccountID = executionReport->Account;
	order->ExchangeID = executionReport->MarketSegmentID;
	order->InstrumentID = executionReport->SecurityDesc;
	order->Direction = DirectionConvert(executionReport->Side);
	order->OrderType = OrderTypeConvert(executionReport->OrdType);
	order->Price = atof(executionReport->Price.c_str());
	order->Volume = atoi(executionReport->OrderQty.c_str());
	order->VolumeTraded = atoi(executionReport->LastQty.c_str());
	order->OrderStatus = OrderStatus::Undefined;
	order->OrderLocalID = executionReport->ClOrdID;
	order->OrderSysID = executionReport->OrderID;
	order->Symbol = executionReport->Symbol;
	order->TimeInForce = TimeInForceConvert(executionReport->TimeInForce);
	order->TransactTime = executionReport->TransactTime;
	order->SecurityType = executionReport->SecurityType;

	m_Orders.insert(make_pair(order->OrderLocalID, order));
	return order;
}
Order* WorkThread::UpdateOrder(ExecutionReportField* executionReport)
{
	auto order = GetOrderForOrderLocalID(executionReport->ClOrdID);
	if (order == nullptr)
	{
		order = GetOrderForOrderSysID(executionReport->OrderID);
		if (order == nullptr)
		{
			WRITE_LOG(LogLevel::Warning, "Can't Find Order For ExecutionReport while OrderLocalID:[%s], OrderSysID:[%s]", executionReport->ClOrdID.c_str(), executionReport->OrderID.c_str());
			return AddNewOrder(executionReport);
		}
	}
	order->OrderSysID = executionReport->OrderID;
	order->OrderStatus = OrderStatusConvert(executionReport->OrderStatus);
	order->Price = atof(executionReport->Price.c_str());
	order->Volume = atoi(executionReport->OrderQty.c_str());
	order->VolumeTraded += atoi(executionReport->LastQty.c_str());
	order->Symbol = executionReport->Symbol;
	return order;
}
void WorkThread::AddNewTrade(ExecutionReportField* executionReport, Order* order)
{
	Trade* trade = new Trade();
	trade->BrokerID = "";
	trade->AccountID = executionReport->Account;
	trade->ExchangeID = order->ExchangeID;
	trade->InstrumentID = executionReport->SecurityDesc;
	trade->Direction = order->Direction;
	trade->Price = atof(executionReport->LastPx.c_str());
	trade->Volume = atoi(executionReport->LastQty.c_str());
	trade->TradeID = executionReport->MDTradeEntryID;
	trade->OrderLocalID = executionReport->ClOrdID;
	trade->OrderSysID = executionReport->OrderID;
	trade->Symbol = executionReport->Symbol;
	trade->TimeInForce = TimeInForceConvert(executionReport->TimeInForce);
	trade->TransactTime = executionReport->TransactTime;

	m_Trades.insert(make_pair(trade->TradeID, trade));
}
void WorkThread::ModifyTrade(ExecutionReportField* executionReport, Order* order)
{
	if (m_Trades.find(executionReport->MDTradeEntryID) == m_Trades.end())
	{
		WRITE_LOG(LogLevel::Error, "Can't Find Trade for MDTradeEntryID[%s]", executionReport->MDTradeEntryID.c_str());
		return;
	}
	auto trade = m_Trades[executionReport->MDTradeEntryID];
	trade->Price = atof(executionReport->LastPx.c_str());
	trade->Volume = atoi(executionReport->LastQty.c_str());
}
void WorkThread::CancelTrade(ExecutionReportField* executionReport, Order* order)
{
	if (m_Trades.find(executionReport->MDTradeEntryID) == m_Trades.end())
	{
		WRITE_LOG(LogLevel::Error, "Can't Find Trade for MDTradeEntryID[%s]", executionReport->MDTradeEntryID.c_str());
		return;
	}
	auto trade = m_Trades[executionReport->MDTradeEntryID];
	m_Trades.erase(trade->TradeID);
	delete trade;
}

void WorkThread::ReportOrder()
{
	for (auto& it : m_Orders)
	{
		it.second->ToString(m_LogBuff, BUFF_SIZE);
		WRITE_LOG(LogLevel::Info, "%s", m_LogBuff);
	}
}
void WorkThread::ReportTrade()
{
	for (auto& it : m_Trades)
	{
		it.second->ToString(m_LogBuff, BUFF_SIZE);
		WRITE_LOG(LogLevel::Info, "%s", m_LogBuff);
	}
}
