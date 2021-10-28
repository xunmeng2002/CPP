#include "FixEngine.h"
#include "FixUtility.h"
#include "MyEvent.h"
#include "FixItems.h"
#include "Utility.h"
#include "TimeUtility.h"
#include "CryptoppEncode.h"
#include "FixEnumTransfer.h"



FixEngine::FixEngine()
	:ThreadBase("FixEngine"), m_LastResendRequestField(nullptr), m_Mdb(nullptr)
{
	m_TcpClient = new TcpSelectClient();
	m_FixSpi = new FixSpiImpl();
	m_LogBuff = new char[BuffSize];

	m_ConnectStatus = ConnectStatus::NotConnected;
	m_LogonStatus = LogonStatus::NotLogged;
	m_SessionID = 0;
	m_FixMessage = new FixMessage();

	m_ParseBuff = new char[BuffSize];
	m_ParseBuffDataLen = 0;

	m_IsDoResendRequest = false;
	m_ResendRange = make_pair(0, 0);
	
	m_HeartBeatSecond = 30;
	m_AlreadySendTestRequest = false;
	::memset(m_TestReqID, 0, sizeof(m_TestReqID));
	memcpy(m_TestReqID, "Hello World!", sizeof("Hello World!"));
	auto now = chrono::steady_clock::now();
	m_LastSendTimePoint = now;
	m_LastRecvTimePoint = now;
	m_TestRequestSendTimePoint = now;

	m_FixAuditTrail = new FixAuditTrail();
}
FixEngine::~FixEngine()
{
	if (m_TcpClient)
	{
		delete m_TcpClient;
	}
	m_TcpClient = nullptr;
	if (m_FixSpi)
	{
		delete m_FixSpi;
	}
	m_FixSpi = nullptr;
	if (m_LogBuff)
	{
		delete m_LogBuff;
	}
	m_LogBuff = nullptr;

	if (m_FixMessage)
	{
		delete m_FixMessage;
	}
	m_FixMessage = nullptr;
	if (m_ParseBuff)
	{
		delete m_ParseBuff;
	}
	m_ParseBuff = nullptr;
	if (m_FixAuditTrail)
	{
		delete m_FixAuditTrail;
	}
	m_FixAuditTrail = nullptr;

	sqlite3_close(m_Mdb);
}
void FixEngine::RegisterMdbPublisher(MdbPublisher* mdbPublisher)
{
	m_FixSpi->RegisterSubscriber(mdbPublisher);
}
void FixEngine::RegisterAddress(const string& primaryIP, int primaryPort, const string& backupIP, int backupPort)
{
	m_IPAddresses.push_back(new IPAddress{ primaryIP, primaryPort });
	m_IPAddresses.push_back(new IPAddress{ backupIP, backupPort });
}
bool FixEngine::Init(const char* dbName)
{
	sqlite3_open(dbName, &m_Mdb);
	FixMdb::GetInstance().SetDB(m_Mdb);
	FixMdb::GetInstance().SetCallback(this);
	
	FixMdb::GetInstance().CreateAllTables();
	FixMdb::GetInstance().SelectAllTables();

	if (AccountInfo::GetInstance().RecordFixAuditTrail)
	{
		FixAuditTrailWriter::GetInstance().Init();
	}

	m_TcpClient->Subscriber(this);
	m_TcpClient->SetTcpInfo();
	return m_TcpClient->Init();
}
bool FixEngine::Start()
{
	if (!ThreadBase::Start())
	{
		return false;
	}
	return m_TcpClient->Start();
}
void FixEngine::Stop()
{
	m_TcpClient->Stop();
	ThreadBase::Stop();
}
void FixEngine::Join()
{
	m_TcpClient->Join();
	ThreadBase::Join();
}
void FixEngine::InitReqMessage(FixReqHeader* reqField)
{
	reqField->ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "InitReqMessage: %s", m_LogBuff);
	m_AppReqFields.insert(make_pair(atoi(reqField->MsgSeqNum.c_str()), reqField));
}
void FixEngine::InitRspMessage(FixRspHeader* rspField)
{
	rspField->ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "InitRspMessage: %s", m_LogBuff);
	m_AppRspFields.insert(make_pair(atoi(rspField->MsgSeqNum.c_str()), rspField));
}

void FixEngine::ReqInsertOrder(Order* order)
{
	auto& accountInfo = AccountInfo::GetInstance();
	auto fixReqNewOrder = new FixReqNewOrderField(PrepareReqHeader());
	fixReqNewOrder->Account = accountInfo.Account;
	fixReqNewOrder->ClOrdID = ItoA(order->OrderLocalID);
	fixReqNewOrder->HandInst = "1";
	fixReqNewOrder->CustOrderHandlingInst = "Y";
	fixReqNewOrder->OrderQty = ItoA(order->Volume);
	fixReqNewOrder->OrdType = (char)ToFixPriceType(order->OrderPriceType);
	if (order->OrderPriceType == OrderPriceType::LimitPrice)
	{
		fixReqNewOrder->Price = FtoA(order->Price);
	}
	fixReqNewOrder->Side = (char)ToFixDirection(order->Direction);
	fixReqNewOrder->Symbol = "";
	fixReqNewOrder->TimeInForce = (char)ToFixTimeInForce(order->TimeCondition);
	fixReqNewOrder->TransactTime = GetUtcTime();
	fixReqNewOrder->ManualOrderIndicator = "Y";
	fixReqNewOrder->NoAllocs = "";
	fixReqNewOrder->AllocAccount = "";
	fixReqNewOrder->StopPx = "";
	fixReqNewOrder->MarketSegmentID = order->MarketSegmentID;
	fixReqNewOrder->SecurityDesc = order->InstrumentID;
	if (order->VolumeCondition == VolumeCondition::CV)
	{
		fixReqNewOrder->MinQty = ItoA(order->Volume);
	}
	else if (order->VolumeCondition == VolumeCondition::MV)
	{
		fixReqNewOrder->MinQty = ItoA(order->MinVolume);
	}
	fixReqNewOrder->SecurityType = FIX_Future;
	fixReqNewOrder->CustomerOrFirm = "0";
	fixReqNewOrder->MaxShow = order->TimeCondition == TimeCondition::IOC ? "" : "1";
	fixReqNewOrder->ExpireDate = order->GTDDate;
	fixReqNewOrder->SelfMatchPreventionID = "";
	fixReqNewOrder->SelfMatchPreventionInstruction = "";
	fixReqNewOrder->CtiCode = "4";
	fixReqNewOrder->AvgPxGroupID = "";
	fixReqNewOrder->ClearingTradePriceType = "";
	fixReqNewOrder->AvgPXIndicator = "";
	fixReqNewOrder->Memo = "";
	fixReqNewOrder->GiveUpFirm = "";
	fixReqNewOrder->CmtaGiveupCD = "";
	fixReqNewOrder->CorrelationClOrdID = fixReqNewOrder->ClOrdID;

	ReqNewOrder(fixReqNewOrder);
}
void FixEngine::ReqInsertOrderCancel(OrderCancel* orderCancel)
{
	auto& accountInfo = AccountInfo::GetInstance();
	auto fixReqOrderCancel = new FixReqOrderCancelRequestField(PrepareReqHeader());
	fixReqOrderCancel->Account = accountInfo.Account;
	fixReqOrderCancel->ClOrdID = ItoA(orderCancel->OrderLocalID);
	fixReqOrderCancel->OrderID = orderCancel->OrderSysID;
	fixReqOrderCancel->OrigClOrdID = ItoA(orderCancel->OrigOrderLocalID);
	fixReqOrderCancel->Side = (char)ToFixDirection(orderCancel->Direction);
	fixReqOrderCancel->Symbol = "";
	fixReqOrderCancel->TransactTime = GetUtcTime();
	fixReqOrderCancel->ManualOrderIndicator = "Y";
	fixReqOrderCancel->Memo = "";
	fixReqOrderCancel->SecurityDesc = orderCancel->InstrumentID;
	fixReqOrderCancel->SecurityType = FIX_Future;
	fixReqOrderCancel->CorrelationClOrdID = ItoA(orderCancel->OrigOrderLocalID);

	ReqOrderCancelRequest(fixReqOrderCancel);
}

void FixEngine::OnConnect(int sessionID, const char* ip, int port)
{
	TcpEvent* tcpEvent = TcpEvent::Allocate();
	tcpEvent->EventID = EVENT_ON_CONNECTED;
	tcpEvent->SessionID = sessionID;
	tcpEvent->IP = ip;
	tcpEvent->Port = port;

	OnEvent(tcpEvent);
}
void FixEngine::OnDisConnect(int sessionID, const char* ip, int port)
{
	TcpEvent* tcpEvent = TcpEvent::Allocate();
	tcpEvent->EventID = EVENT_ON_DISCONNECTED;
	tcpEvent->SessionID = sessionID;
	tcpEvent->IP = ip;
	tcpEvent->Port = port;

	OnEvent(tcpEvent);
}
void FixEngine::OnRecv(TcpEvent* tcpEvent)
{
	OnEvent(tcpEvent);
}


void FixEngine::ReqLogon(FixReqLogonField* reqField)
{
	OnEventFixMessage(reqField);
}
void FixEngine::ReqLogout(FixReqLogoutField* reqField)
{
	OnEventFixMessage(reqField);
}
void FixEngine::ReqHeartBeat(FixReqHeartBeatField* reqField)
{
	OnEventFixMessage(reqField);
}
void FixEngine::ReqTestRequest(FixReqTestRequestField* reqField)
{
	OnEventFixMessage(reqField);
}
void FixEngine::ReqNewOrder(FixReqNewOrderField* reqField)
{
	OnEventFixMessage(reqField);
}
void FixEngine::ReqOrderCancelRequest(FixReqOrderCancelRequestField* reqField)
{
	OnEventFixMessage(reqField);
}
void FixEngine::ReqOrderCancelReplaceRequest(FixReqOrderCancelReplaceRequestField* reqField)
{
	OnEventFixMessage(reqField);
}
void FixEngine::ReqOrderStatusRequest(FixReqOrderStatusRequestField* reqField)
{
	OnEventFixMessage(reqField);
}


void FixEngine::Run()
{
	CheckEvent();
	HandleEvent();
	CheckConnectStatus();
	CheckLogonStatus();
	CheckAndParsePackage();
	CheckHeartBeat();
}
void FixEngine::HandleEvent()
{
	Event* event = nullptr;
	TcpEvent* tcpEvent = nullptr;
	MyEvent* myEvent = nullptr;
	bool shouldFree = true;
	while (event = GetEvent())
	{
		shouldFree = true;
		switch (event->EventID)
		{
		case EVENT_ON_CONNECTED:
		{
			HandleConnect(((TcpEvent*)event)->SessionID);
			m_FixSpi->OnFixConnected();
			break;
		}
		case EVENT_ON_DISCONNECTED:
		{
			HandleDisConnect(((TcpEvent*)event)->SessionID);
			m_FixSpi->OnFixDisConnected();
			break;
		}
		case EVENT_ON_TCP_RECV:
		{
			tcpEvent = (TcpEvent*)event;
			m_RecvDatas.push_back(tcpEvent);
			shouldFree = false;
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
			auto beginSeqNum = myEvent->NumParams[0];
			auto endSeqNum = myEvent->NumParams[1];
			DoResendRequest(beginSeqNum, endSeqNum);
			break;
		}
		case EVENT_ON_FIX_MESSAGE:
		{
			myEvent = (MyEvent*)event;
			auto field = (FixReqHeader*)myEvent->Field;
			SendRequest(field);
			RecordRequest(field);
			myEvent->Field = nullptr;
			break;
		}
		default:
			_ASSERT(false);
			break;
		}
		if (shouldFree)
		{
			event->Free();
		}
	}
}
void FixEngine::OnEventSequenceGap(int beginSeqNo, int endSeqNo)
{
	endSeqNo = endSeqNo < (beginSeqNo + 2499) ? endSeqNo : (beginSeqNo + 2499);
	m_ResendRange = make_pair(beginSeqNo, endSeqNo);

	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_ON_SEQUENCE_GAP;
	myEvent->NumParams.push_back(beginSeqNo);
	myEvent->NumParams.push_back(endSeqNo);
	OnEvent(myEvent);
}
void FixEngine::OnEventResendLastResendRequest()
{
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_ON_RESEND_LAST_RESEND_REQUEST;
	OnEvent(myEvent);
}
void FixEngine::OnEventDoResendRequest(int beginSeqNo, int endSeqNo)
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
void FixEngine::OnEventHeartBeat(const string& testReqID)
{
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_HEART_BEAT;
	myEvent->StringParams.push_back(testReqID);
	OnEvent(myEvent);
}
void FixEngine::OnEventTestRequest(const string& testReqID)
{
	MyEvent* myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_TEST_REQUEST;
	myEvent->StringParams.push_back(testReqID);
	OnEvent(myEvent);
}
void FixEngine::OnEventFixMessage(FixReqHeader* reqField)
{
	auto myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_ON_FIX_MESSAGE;
	myEvent->Field = reqField;

	OnEvent(myEvent);
}

void FixEngine::CheckConnectStatus()
{
	if (m_ConnectStatus != ConnectStatus::NotConnected)
	{
		return;
	}
	m_TcpClient->Connect(m_IPAddresses.front()->IP.c_str(), m_IPAddresses.front()->Port);
	m_ConnectStatus = ConnectStatus::Connecting;
}
void FixEngine::CheckLogonStatus()
{
	if (m_ConnectStatus == ConnectStatus::Connected && m_LogonStatus == LogonStatus::NotLogged)
	{
		m_LogonStatus = LogonStatus::Logging;
		ReqLogon();
	}
}
void FixEngine::CheckAndParsePackage()
{
	if (m_RecvDatas.empty())
		return;
	while (!m_RecvDatas.empty())
	{
		auto tcpEvent = m_RecvDatas.front();
		m_RecvDatas.pop_front();

		int itemLen = 0;
		while (GetItemEnd(tcpEvent->ReadPos, tcpEvent->Length, itemLen))
		{
			int tag = -1;
			string value;
			if (m_ParseBuffDataLen > 0)
			{
				memcpy(m_ParseBuff + m_ParseBuffDataLen, tcpEvent->ReadPos, itemLen);
				m_ParseBuffDataLen += itemLen;
				if (ParseOneItem(m_ParseBuff, m_ParseBuffDataLen, tag, value))
				{
					m_FixMessage->SetItem(tag, value);
				}
				else
				{
					_ASSERT(false);
				}
				m_ParseBuffDataLen = 0;
			}
			else
			{
				if (ParseOneItem(tcpEvent->ReadPos, itemLen, tag, value))
				{
					m_FixMessage->SetItem(tag, value);
				}
				else
				{
					_ASSERT(false);
				}
			}
			tcpEvent->ReadPos += itemLen;
			tcpEvent->Length -= itemLen;

			if (tag == 10)
			{
				HandleFixMessage(m_FixMessage);
				m_FixMessage = FixMessage::Allocate();
			}
		}
		if (tcpEvent->Length > 0)
		{
			memcpy(m_ParseBuff + m_ParseBuffDataLen, tcpEvent->ReadPos, tcpEvent->Length);
			m_ParseBuffDataLen += tcpEvent->Length;
		}
		tcpEvent->Free();
	}
	while (NextQueue());
}
void FixEngine::CheckHeartBeat()
{
	if (m_ConnectStatus != ConnectStatus::Connected || m_LogonStatus != LogonStatus::Logged)
		return;
	auto now = chrono::steady_clock::now();
	auto lastSendTimeDiff = chrono::duration_cast<chrono::seconds>(now - m_LastSendTimePoint);
	if (lastSendTimeDiff.count() > m_HeartBeatSecond)
	{
		auto reqField = new FixReqHeartBeatField(PrepareReqHeader());
		reqField->TestReqID = "From CheckHeartBeat";
		ReqHeartBeat(reqField);
	}
	if (!m_AlreadySendTestRequest)
	{
		auto lastRecvTimeDiff = chrono::duration_cast<chrono::seconds>(now - m_LastRecvTimePoint);
		if (lastRecvTimeDiff.count() > m_HeartBeatSecond)
		{
			auto reqField = new FixReqTestRequestField(PrepareReqHeader());
			reqField->TestReqID = m_TestReqID;
			ReqTestRequest(reqField);

			m_AlreadySendTestRequest = true;
			m_TestRequestSendTimePoint = now;
		}
	}
	else
	{
		auto lastRecvTimeDiff = chrono::duration_cast<chrono::seconds>(now - m_TestRequestSendTimePoint);
		if (lastRecvTimeDiff.count() > m_HeartBeatSecond)
		{
			m_ConnectStatus = ConnectStatus::DisConnecting;
			m_TcpClient->DisConnect(m_SessionID);
		}
	}
}


void FixEngine::HandleConnect(int sessionID)
{
	m_ConnectStatus = ConnectStatus::Connected;
	m_SessionID = sessionID;
	m_FixMessage->Clear();
	m_ParseBuffDataLen = 0;
	m_ResendRange = make_pair(0, 0);
	m_IsDoResendRequest = false;
	m_AlreadySendTestRequest = false;
}
void FixEngine::HandleDisConnect(int sessionID)
{
	m_ConnectStatus = ConnectStatus::NotConnected;
	m_LogonStatus = LogonStatus::NotLogged;
	auto ip =  m_IPAddresses.front();
	m_IPAddresses.pop_front();
	m_IPAddresses.push_back(ip);
	for (auto tcpEvent : m_RecvDatas)
	{
		tcpEvent->Free();
	}
	m_RecvDatas.clear();

	for (auto& it : m_FixMessages)
	{
		it.second->Free();
	}
	m_FixMessages.clear();
}
void FixEngine::HandleFixMessage(FixMessage* fixMessage)
{
	UpdateLastRecvTime();
	auto msgType = fixMessage->GetMessageType();
	if (msgType == FIX_Message_RspLogon)
	{
		OnFixRspLogon(fixMessage);
	}
	else if (msgType == FIX_Message_RspLogout)
	{
		OnFixRspLogout(fixMessage);
	}
	else if (msgType == FIX_Message_RspHeartBeat)
	{
		OnFixRspHeartBeat(fixMessage);
	}
	else if (msgType == FIX_Message_RspTestRequest)
	{
		OnFixRspTestRequest(fixMessage);
	}
	else if (msgType == FIX_Message_RspResendRequest)
	{
		OnFixRspResendRequest(fixMessage);
	}
	else if (msgType == FIX_Message_RspSessionLevelReject)
	{
		OnFixRspSessionLevelReject(fixMessage);
	}
	else if (msgType == FIX_Message_RspSequenceReset)
	{
		OnFixRspSequenceReset(fixMessage);
	}
	else
	{
		if (!Verify(fixMessage))
		{
			return;
		}
		RecordFixAuditTrail(fixMessage, "FROM CME");
		if (msgType == FIX_Message_ExecutionReport)
		{
			OnFixExecutionReport(fixMessage);
		}
		else if (msgType == FIX_Message_RspOrderCancelReject)
		{
			OnFixRspOrderCancelReject(fixMessage);
		}
		else
		{
			fixMessage->ToString(m_LogBuff, BUFF_SIZE);
			WRITE_LOG(LogLevel::Error, "UnKnown MsgType:[%s], FixMessage:%s", msgType.c_str(), m_LogBuff);
		}

	}
}
bool FixEngine::Verify(FixMessage* fixMessage, bool checkTooHigh, bool checkTooLow)
{
	auto msgType = fixMessage->GetMessageType();
	if (msgType == FIX_Message_ReqSequenceReset)
		return true;
	auto msgSeqNum = atoi(fixMessage->GetMsgSeqNum().c_str());
	auto nextExpectSeqNum = SeqNum::GetInstance().GetNextExpectSeqNum();
	if (checkTooHigh && msgSeqNum > nextExpectSeqNum)
	{
		DoMsgSeqTooHigh(fixMessage, msgSeqNum, nextExpectSeqNum);
		return false;
	}
	if (checkTooLow && msgSeqNum < nextExpectSeqNum)
	{
		DoMsgSeqTooLow(fixMessage, msgSeqNum, nextExpectSeqNum);
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
	SeqNum::GetInstance().SetLastRecvSeqNum(msgSeqNum);
	return true;
}
void FixEngine::DoMsgSeqTooHigh(FixMessage* fixMessage, int msgSeqNum, int expectSeqNum)
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
void FixEngine::DoMsgSeqTooLow(FixMessage* fixMessage, int msgSeqNum, int expectSeqNum)
{
	auto possDupFlag = fixMessage->GetPossDupFlag();
	auto msgType = fixMessage->GetMessageType();
	fixMessage->ToString(m_LogBuff, BUFF_SIZE);
	if (possDupFlag == "Y")
	{
		WRITE_LOG(LogLevel::Info, "Duplicate Message. FixMessage:%s", expectSeqNum, msgSeqNum, m_LogBuff);
	}
	else
	{
		WRITE_LOG(LogLevel::Info, "MsgSeqNum too low, Expect:[%d], Receive:[%d], FixMessage:%s", expectSeqNum, msgSeqNum, m_LogBuff);
		m_TcpClient->DisConnect(m_SessionID);
	}
	fixMessage->Free();
}
bool FixEngine::NextQueue()
{
	if (m_FixMessages.size() == 0)
	{
		return false;
	}
	auto nextExpectSeqNum = SeqNum::GetInstance().GetNextExpectSeqNum();
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
		HandleFixMessage(fixMessage);
		return true;
	}
	if (!IsOnResend())
	{
		OnEventSequenceGap(nextExpectSeqNum, msgSeqNum - 1);
	}
	return false;
}
bool FixEngine::IsOnResend()
{
	return !(m_ResendRange.first == 0 && m_ResendRange.second == 0);
}
void FixEngine::ReqLogon()
{
	auto reqLogonField = new FixReqLogonField(PrepareReqHeader());
	auto& accountInfo = AccountInfo::GetInstance();
	reqLogonField->SenderCompID = accountInfo.LogonSenderCompID;

	reqLogonField->HeartBtInt = accountInfo.HeartBtInt;
	reqLogonField->ResetSeqNumFlag = accountInfo.ResetSeqNumFlag;
	reqLogonField->ApplicationSystemName = accountInfo.ApplicationSystemName;
	reqLogonField->ApplicationSystemVersion = accountInfo.ApplicationSystemVersion;
	reqLogonField->ApplicationSystemVendor = accountInfo.ApplicationSystemVendor;
	reqLogonField->EncodedTextLen = ItoA(accountInfo.AccessID.length());
	reqLogonField->EncodedText = accountInfo.AccessID;
	reqLogonField->EncryptedPasswordMethod = accountInfo.EncryptedPasswordMethod;

	std::string canonicalRequest = GetCanonicalReq(*reqLogonField);
	std::string encodedHmac = calculateHMAC(accountInfo.SecretKey, canonicalRequest);
	reqLogonField->EncryptedPasswordLen = ItoA(encodedHmac.length());
	reqLogonField->EncryptedPassword = encodedHmac;

	ReqLogon(reqLogonField);
}
void FixEngine::ReqResendRequest(int startSeqNum, int endSeqNum)
{
	FixReqResendRequestField reqField(PrepareReqHeader());

	reqField.BeginSeqNo = ItoA(startSeqNum);
	reqField.EndSeqNo = ItoA(endSeqNum);
	SendRequest(&reqField);

	m_LastResendRequestField = std::move(reqField);
}
void FixEngine::ResendLastResendRequest()
{
	m_LastResendRequestField.SendingTime = GetUtcTime();
	m_LastResendRequestField.PossDupFlag = "Y";

	SendRequest(&m_LastResendRequestField, true);
}
void FixEngine::DoResendRequest(int startSeqNum, int endSeqNum)
{
	m_IsDoResendRequest = false;
	endSeqNum = SeqNum::GetInstance().GetNextSendSeqNum();
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
		it->second->LastMsgSeqNumProcessed = ItoA(SeqNum::GetInstance().GetLastRecvSeqNum());
		SendRequest(it->second, true);
		currSeqNum++;
	}
	if (currSeqNum < endSeqNum)
	{
		ReqSequenceReset(currSeqNum, endSeqNum, "N");
	}
}
void FixEngine::ReqSequenceReset(int beginSeqNum, int endSeqNum, const string& gapFill)
{
	FixReqSequenceResetField reqField(PrepareReqHeader(ItoA(beginSeqNum)));
	reqField.PossDupFlag = "Y";
	reqField.NewSeqNo = ItoA(endSeqNum);
	reqField.GapFillFlag = gapFill;;

	SendRequest(&reqField, true);
}

void FixEngine::OnFixRspLogon(FixMessage* fixMessage)
{
	
	auto resetSeqNumFlag = fixMessage->GetItem(141);
	if (resetSeqNumFlag == "Y")
	{
		WRITE_LOG(LogLevel::Info, "Reset Sequence Num to 1");
		SeqNum::GetInstance().ResetSeqNum();
	}
	if (!Verify(fixMessage, false, true))
	{
		return;
	}
	m_LogonStatus = LogonStatus::Logged;
	auto nextExpectSeqNum = SeqNum::GetInstance().GetNextExpectSeqNum();
	auto msgSeqNum = atoi(fixMessage->GetMsgSeqNum().c_str());
	if (msgSeqNum > nextExpectSeqNum)
	{
		DoMsgSeqTooHigh(fixMessage, msgSeqNum, nextExpectSeqNum);
	}
	else
	{
		auto rspField = new FixRspLogonField(fixMessage);
		m_FixSpi->OnFixRspLogon(rspField);
		
		RecordResponse(rspField);
	}
}
void FixEngine::OnFixRspLogout(FixMessage* fixMessage)
{
	auto rspField = new FixRspLogoutField(fixMessage);
	m_FixSpi->OnFixRspLogout(rspField);
	RecordResponse(rspField);

	if (rspField->NextExpectedMsgSeqNum == "1")
	{
		SeqNum::GetInstance().ResetSeqNum();
	}
	else if (!rspField->NextExpectedMsgSeqNum.empty())
	{
		SeqNum::GetInstance().SetNextSendSeqNum(rspField->NextExpectedMsgSeqNum);
	}
	SeqNum::GetInstance().SetLastRecvSeqNum(rspField->MsgSeqNum);

	m_LogonStatus = LogonStatus::Logout;
	m_TcpClient->DisConnect(m_SessionID);
}
void FixEngine::OnFixRspHeartBeat(FixMessage* fixMessage)
{
	if (!Verify(fixMessage))
	{
		return;
	}
	auto rspField = new FixRspHeartBeatField(fixMessage);
	m_FixSpi->OnFixRspHeartBeat(rspField);
	RecordResponse(rspField);

	if (m_AlreadySendTestRequest && rspField->TestReqID == string(m_TestReqID))
	{
		m_AlreadySendTestRequest = false;
	}
}
void FixEngine::OnFixRspTestRequest(FixMessage* fixMessage)
{
	if (!Verify(fixMessage))
	{
		return;
	}
	auto rspField = new FixRspTestRequestField(fixMessage);
	m_FixSpi->OnFixRspTestRequest(rspField);
	RecordResponse(rspField);

	auto reqField = new FixReqHeartBeatField(PrepareReqHeader());
	reqField->TestReqID = rspField->TestReqID;
	ReqHeartBeat(reqField);
}
void FixEngine::OnFixRspResendRequest(FixMessage* fixMessage)
{
	Verify(fixMessage, false, false);
	auto rspField = new FixRspResendRequestField(fixMessage);
	m_FixSpi->OnFixRspResendRequest(rspField);
	RecordResponse(rspField);

	OnEventDoResendRequest(atoi(rspField->BeginSeqNo.c_str()), atoi(rspField->EndSeqNo.c_str()));
}
void FixEngine::OnFixRspSessionLevelReject(FixMessage* fixMessage)
{
	if (!Verify(fixMessage))
	{
		return;
	}
	auto rspField = new FixRspSessionLevelRejectField(fixMessage);
	m_FixSpi->OnFixRspSessionLevelReject(rspField);

	RecordResponse(rspField);
}
void FixEngine::OnFixRspSequenceReset(FixMessage* fixMessage)
{
	auto isGapFill = fixMessage->GetItem(123);
	if (isGapFill == "Y" && !Verify(fixMessage))
	{
		return;
	}
	auto rspField = new FixRspSequenceResetField(fixMessage);
	m_FixSpi->OnFixRspSequenceReset(rspField);
	RecordResponse(rspField);
	
	auto nextExpectSeqNum = SeqNum::GetInstance().GetNextExpectSeqNum();
	auto newSeqNo = atoi(rspField->NewSeqNo.c_str());
	WRITE_LOG(LogLevel::Info, "Received SequenceReset FROM [%d] To [%d]", nextExpectSeqNum, newSeqNo);

	if (IsOnResend() && newSeqNo > m_ResendRange.second)
	{
		SeqNum::GetInstance().SetLastRecvSeqNum(m_ResendRange.second);
		m_ResendRange = make_pair(0, 0);
	}
	else
	{
		SeqNum::GetInstance().SetLastRecvSeqNum(newSeqNo - 1);
	}
}
void FixEngine::OnFixExecutionReport(FixMessage* fixMessage)
{
	auto rspField = new FixExecutionReportField(fixMessage);
	m_FixSpi->OnFixExecutionReport(rspField);

	RecordResponse(rspField);
}
void FixEngine::OnFixRspOrderCancelReject(FixMessage* fixMessage)
{
	auto rspField = new FixRspOrderCancelRejectField(fixMessage);
	m_FixSpi->OnFixRspOrderCancelReject(rspField);

	RecordResponse(rspField);
}

void FixEngine::RecordRequest(FixReqHeader* reqField)
{
	FixMdb::GetInstance().InsertRecord(reqField);

	if (reqField->MsgClass == "app")
	{
		reqField->OrigSendingTime = reqField->SendingTime;
		m_AppReqFields[atoi(reqField->MsgSeqNum.c_str())] = reqField;
	}
	else
	{
		delete reqField;
	}
}
void FixEngine::RecordResponse(FixRspHeader* rspField)
{
	m_AppRspFields[atoi(rspField->MsgSeqNum.c_str())] = rspField;

	FixMdb::GetInstance().InsertRecord(rspField);
}
void FixEngine::UpdateLastSendTime()
{
	m_LastSendTimePoint = chrono::steady_clock().now();
}
void FixEngine::UpdateLastRecvTime()
{
	m_LastRecvTimePoint = chrono::steady_clock::now();
}
void FixEngine::RecordFixAuditTrail(FixMessage* fixMessage, string messageDirection)
{
	if (!AccountInfo::GetInstance().RecordFixAuditTrail)
		return;
	m_FixAuditTrail->SetMessage(fixMessage, messageDirection);

	FixAuditTrailWriter::GetInstance().WriteFixAuditTrailRecord(m_FixAuditTrail);
}
