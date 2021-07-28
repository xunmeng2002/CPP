#include "TradeApi.h"
#include "Common.h"
#include "CryptoppEncode.h"
#include "Logger.h"
#include "GlobalParam.h"
#include "TcpThread.h"


TradeApi::TradeApi(AccountInfo* accountInfo)
	:m_ParseBuffDataLen(0), m_SessionID(0), m_ConnectStatus(ConnectStatus::NotConnected), m_AccountInfo(accountInfo)
{
	m_SendBuff = new char[BUFF_SIZE];
	m_ParseBuff = new char[BUFF_SIZE];
	m_LogBuff = new char[BUFF_SIZE];
	m_CacheList = new CacheList();
	m_FixMessage = new FixMessage();

	m_AccountLogonStatus = LogonStatus::NotLogged;
	m_IsOnResendRequest = false;
}

void TradeApi::OnRecv(char* buff, int len)
{
	m_CacheList->PushBack(buff, len);
}

void TradeApi::Parse()
{
	while (!m_CacheList->IsEmpty())
	{
		int len = 0;
		int popLen = 0;
		char* data = (char*)m_CacheList->GetData(len);

		int itemLen = 0;
		while (GetItemEnd((char*)data, len - popLen, itemLen))
		{
			int tag = -1;
			string value;
			if (m_ParseBuffDataLen > 0)
			{
				memcpy(m_ParseBuff + m_ParseBuffDataLen, data, itemLen);
				m_ParseBuffDataLen += itemLen;
				if (ParseOneItem(m_ParseBuff, m_ParseBuffDataLen, tag, value))
				{
					m_FixMessage->AddItem(tag, value);
				}
				m_ParseBuffDataLen = 0;
			}
			else
			{
				if (ParseOneItem(data, itemLen, tag, value))
				{
					m_FixMessage->AddItem(tag, value);
				}
			}
			popLen += itemLen;
			data += itemLen;


			if (tag == 10)
			{
				OnFixMessage();
			}
		}
		if (len - popLen > 0)
		{
			memcpy(m_ParseBuff + m_ParseBuffDataLen, data, len - popLen);
			m_ParseBuffDataLen += len - popLen;
		}
		m_CacheList->PopFront(nullptr, len);
	}
}

void TradeApi::OnSessionConnected(int sessionID)
{
	m_SessionID = sessionID;
	m_ConnectStatus = ConnectStatus::Connected;
}

void TradeApi::OnSessionDisConnected(int sessionID)
{
	m_SessionID = 0;
	m_ConnectStatus = ConnectStatus::NotConnected;
	m_AccountLogonStatus = LogonStatus::NotLogged;
}

void TradeApi::OnFixMessage()
{
	m_FixMessage->ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Debug, "OnFixMessage: %s", m_LogBuff);

	auto rspField = ParseRspField();
	if (rspField == nullptr)
	{
		WRITE_LOG(LogLevel::Error, "ParseRspField Failed");
		return;
	}
	CheckAndUpdateRecvSeqNum(rspField->MsgSeqNum);

	if (rspField->MsgType == "0")
	{
		OnRspHeartBeat(rspField);
	}
	else if (rspField->MsgType == "1")
	{
		OnRspTestRequest(rspField);
	}
	else if (rspField->MsgType == "2")
	{
		OnResendRequest(rspField);
	}
	else if (rspField->MsgType == "3")
	{
		OnSessionLevelReject(rspField);
	}
	else if (rspField->MsgType == "4")
	{
		OnRspSequenceReset(rspField);
	}
	else if (rspField->MsgType == "5")
	{
		OnRspLogout(rspField);
	}
	else if (rspField->MsgType == "A")
	{
		OnRspLogon(rspField);
	}
}

void TradeApi::CheckLogonStatus()
{
	if (m_ConnectStatus != ConnectStatus::Connected)
	{
		return;
	}
	if (m_AccountLogonStatus == LogonStatus::NotLogged)
	{
		auto ret = ReqLogon();
		if (ret >= 0)
		{
			m_AccountLogonStatus = LogonStatus::Logging;
		}
	}
}

bool TradeApi::Send(const string& funcName, ReqFieldBase* reqField)
{
	auto len = reqField->MakePackage(m_SendBuff, BUFF_SIZE);

	m_ReqFields.insert(make_pair(atoi(reqField->MsgSeqNum.c_str()), reqField));

	reqField->ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "%s %s", funcName.c_str(), m_LogBuff);
	return TcpThread::GetInstance().Send(m_SessionID, m_SendBuff, len);
}



int TradeApi::ReqLogon()
{
	ReqLogonField* reqLogonField = new ReqLogonField();
	reqLogonField->SetHead(m_AccountInfo->SenderCompID + "U", m_AccountInfo->SenderSubID, m_AccountInfo->TargetCompID, m_AccountInfo->TargetSubID);

	reqLogonField->HeartBtInt = m_AccountInfo->HeartBtInt;
	reqLogonField->ResetSeqNumFlag = m_AccountInfo->ResetSeqNumFlag;
	reqLogonField->ApplicationSystemName = m_AccountInfo->ApplicationSystemName;
	reqLogonField->ApplicationSystemVersion = m_AccountInfo->ApplicationSystemVersion;
	reqLogonField->ApplicationSystemVendor = m_AccountInfo->ApplicationSystemVendor;
	reqLogonField->EncodedTextLen = ItoA(m_AccountInfo->AccountID.length());
	reqLogonField->EncodedText = m_AccountInfo->AccountID;
	reqLogonField->EncryptedPasswordMethod = m_AccountInfo->EncryptedPasswordMethod;

	std::string canonicalRequest = GetCanonicalReq(*reqLogonField);
	std::string encodedHmac = calculateHMAC(m_AccountInfo->SecretKey, canonicalRequest);
	reqLogonField->EncryptedPasswordLen = ItoA(encodedHmac.length());
	reqLogonField->EncryptedPassword = encodedHmac;	

	return Send(__func__, reqLogonField);
}

int TradeApi::ReqLogout()
{
	ReqLogoutField* reqLogoutField = new ReqLogoutField();
	SetHead(reqLogoutField);

	return Send(__func__, reqLogoutField);
}

int TradeApi::ReqHeartBeat(const string& testReqID)
{
	ReqHeartBeatField* reqHeartBeatField = new ReqHeartBeatField();
	SetHead(reqHeartBeatField);

	reqHeartBeatField->TestReqID = testReqID;
	
	return Send(__func__, reqHeartBeatField);
}

int TradeApi::ReqTestRequest()
{
	ReqTestRequestField* reqTestRequestField = new ReqTestRequestField();
	SetHead(reqTestRequestField);

	reqTestRequestField->TestReqID = "Hello World";

	return Send(__func__, reqTestRequestField);
}

int TradeApi::ReqResendRequest(int startSeqNum, int endSeqNum)
{
	m_IsOnResendRequest = true;

	ReqResendRequestField* reqResendRequestField = new ReqResendRequestField();
	SetHead(reqResendRequestField);

	if (endSeqNum >= startSeqNum + 2500)
	{
		endSeqNum = startSeqNum + 2499;
	}
	m_ResendStartSeqNum = startSeqNum;
	m_ResendEndSeqNum = endSeqNum;

	reqResendRequestField->BeginSeqNo = ItoA(startSeqNum);
	reqResendRequestField->EndSeqNo = ItoA(endSeqNum);

	return Send(__func__, reqResendRequestField);
}

int TradeApi::ReqSequenceReset(string msgSeqNum)
{
	ReqSequenceResetField* reqSequenceResetField = new ReqSequenceResetField();
	SetHead(reqSequenceResetField);
	reqSequenceResetField->MsgSeqNum = msgSeqNum;
	
	reqSequenceResetField->NewSeqNo = ItoA(GlobalParam::GetInstance().GetNextSendSeqNum() + 1);
	reqSequenceResetField->GapFillFlag = "Y";

	return Send(__func__, reqSequenceResetField);
}

int TradeApi::ReqNewOrder()
{
	ReqNewOrderField* reqNewOrderField = new ReqNewOrderField();
	SetHead(reqNewOrderField);

	reqNewOrderField->Account = "2F5004";
	reqNewOrderField->ClOrdID = "5";
	reqNewOrderField->HandInst = "1";
	reqNewOrderField->CustOrderHandlingInst = "Y";
	reqNewOrderField->OrderQty = "5";
	reqNewOrderField->OrdType = "1";
	reqNewOrderField->Price = "";
	reqNewOrderField->Side = "1";
	reqNewOrderField->Symbol = "";
	reqNewOrderField->TimeInForce = "0";
	reqNewOrderField->TransactTime = GetUtcTime();
	reqNewOrderField->ManualOrderIndicator = "Y";
	reqNewOrderField->NoAllocs = "";
	reqNewOrderField->AllocAccount = "";
	reqNewOrderField->StopPx = "";
	reqNewOrderField->SecurityDesc = "GEZ8";
	reqNewOrderField->MinQty = "1";
	reqNewOrderField->SecurityType = "FUT";
	reqNewOrderField->CustomerOrFirm = "0";
	reqNewOrderField->MaxShow = "1";
	reqNewOrderField->ExpireDate = "";
	reqNewOrderField->SelfMatchPreventionID = "";
	reqNewOrderField->SelfMatchPreventionInstruction = "";
	reqNewOrderField->CtiCode = "4";
	reqNewOrderField->AvgPxGroupID = "";
	reqNewOrderField->ClearingTradePriceType = "";
	reqNewOrderField->AvgPXIndicator = "";
	reqNewOrderField->Memo = "";
	reqNewOrderField->GiveUpFirm = "";
	reqNewOrderField->CmtaGiveupCD = "";
	reqNewOrderField->CorrelationClOrdID = "5";
	reqNewOrderField->MarketSegmentID = "99";

	return Send(__func__, reqNewOrderField);
}



void TradeApi::OnRspLogon(RspFieldBase* rspField)
{
	m_AccountLogonStatus = LogonStatus::Logged;
	m_SenderCompID = rspField->TargetCompID;
}

void TradeApi::OnRspLogout(RspFieldBase* rspField)
{
	auto rspLogoutField = (RspLogoutField*)rspField;
	if (!rspLogoutField->NextExpectedMsgSeqNum.empty())
	{
		GlobalParam::GetInstance().SetNextSendSeqNum(atoi(rspLogoutField->NextExpectedMsgSeqNum.c_str()));
	}
	ResetMarks();
}

void TradeApi::OnRspHeartBeat(RspFieldBase* rspField)
{
	
}

void TradeApi::OnRspTestRequest(RspFieldBase* rspField)
{
	auto rspTestRequestField = (RspTestRequestField*)rspField;
	ReqHeartBeat(rspTestRequestField->TestReqID);
}

void TradeApi::OnSessionLevelReject(RspFieldBase* rspField)
{
	
}

void TradeApi::OnResendRequest(RspFieldBase* rspField)
{
	RspResendRequestField* rspResendRequestField = (RspResendRequestField*)rspField;
	
	ReqSequenceReset(rspResendRequestField->BeginSeqNo);
}

void TradeApi::OnRspSequenceReset(RspFieldBase* rspField)
{
	auto rspSequenceResetField = (RspSequenceResetField*)rspField;
	auto newSeqNo = atoi(rspSequenceResetField->NewSeqNo.c_str());
	if (m_IsOnResendRequest)
	{
		m_ResendStartSeqNum = newSeqNo;
		if (newSeqNo >= m_ResendEndSeqNum)
		{
			m_IsOnResendRequest = false;
		}
	}
	GlobalParam::GetInstance().ResetLastRecvSeqNum(newSeqNo);
}


void TradeApi::SetHead(ReqFieldBase* reqField)
{
	reqField->SetHead(m_SenderCompID, m_AccountInfo->SenderSubID, m_AccountInfo->TargetCompID, m_AccountInfo->TargetSubID);
}

void TradeApi::CheckAndUpdateRecvSeqNum(string seqNum)
{
	int seqNumInt = atoi(seqNum.c_str());
	if (m_IsOnResendRequest)
	{
		if (seqNumInt >= m_ResendStartSeqNum && seqNumInt < m_ResendEndSeqNum)
		{
			WRITE_LOG(LogLevel::Debug, "OnResendRequest. m_ResendStartSeqNum[%d], m_ResendEndSeqNum[%d], seqNumInt[%d]", m_ResendStartSeqNum, m_ResendEndSeqNum, seqNumInt);
			m_ResendStartSeqNum = seqNumInt;
		}
		else if (seqNumInt == m_ResendEndSeqNum)
		{
			WRITE_LOG(LogLevel::Info, "OnResendRequest. m_ResendStartSeqNum[%d], m_ResendEndSeqNum[%d], seqNumInt[%d]", m_ResendStartSeqNum, m_ResendEndSeqNum, seqNumInt);
			m_IsOnResendRequest = false;
		}
		else if (seqNumInt > m_ResendEndSeqNum)
		{
			GlobalParam::GetInstance().SetLastRecvSeqNum(seqNumInt);
		}
	}
	else
	{
		int nextExpectSeqNum = GlobalParam::GetInstance().GetNextExpectSeqNum();
		if (seqNumInt == nextExpectSeqNum)
		{
			GlobalParam::GetInstance().SetLastRecvSeqNum(seqNumInt);
		}
		else if (seqNumInt > nextExpectSeqNum && m_AccountLogonStatus == LogonStatus::Logged)
		{
			ReqResendRequest(nextExpectSeqNum, seqNumInt);
		}
	}
}

RspFieldBase* TradeApi::ParseRspField()
{
	RspFieldBase* rspField = nullptr;
	auto msgType = m_FixMessage->GetMessageType();
	if (msgType == "0")
	{
		rspField = new RspHeartBeatField(m_FixMessage);
	}
	else if (msgType == "1")
	{
		rspField = new RspTestRequestField(m_FixMessage);
	}
	else if (msgType == "2")
	{
		rspField = new RspResendRequestField(m_FixMessage);
	}
	else if (msgType == "3")
	{
		rspField = new RspSessionLevelRejectField(m_FixMessage);
	}
	else if (msgType == "4")
	{
		rspField = new RspSequenceResetField(m_FixMessage);
	}
	else if (msgType == "5")
	{
		rspField = new RspLogoutField(m_FixMessage);	
	}
	else if (msgType == "A")
	{
		rspField = new RspLogonField(m_FixMessage);
	}
	if (rspField)
	{
		m_RspFields.insert(make_pair(atoi(rspField->MsgSeqNum.c_str()), rspField));

		rspField->ToString(m_LogBuff, BUFF_SIZE);
		WRITE_LOG(LogLevel::Info, "%s", m_LogBuff);
	}
	m_FixMessage->Items.clear();
	return rspField;
}

void TradeApi::ResetMarks()
{
	m_IsOnResendRequest = false;
}