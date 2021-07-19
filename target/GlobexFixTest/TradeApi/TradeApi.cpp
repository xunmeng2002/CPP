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
	m_SendOrderMark = false;
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
	WRITE_LOG(LogLevel::Info, "OnFixMessage: %s", m_LogBuff);

	auto msgType = m_FixMessage->GetMessageType();
	if (msgType.empty())
	{
		WRITE_LOG(LogLevel::Error, "Cannot Find MsgType[%s]", msgType.c_str());
	}
	else if (msgType == "0")
	{
		OnRspHeartBeat();
	}
	else if (msgType == "1")
	{
		OnRspTestRequest();
	}
	else if (msgType == "3")
	{
		OnSessionLevelReject();
	}
	else if (msgType == "5")
	{
		OnRspLogout();
	}
	else if (msgType == "A")
	{
		OnRspLogon();
	}
	else
	{
		WRITE_LOG(LogLevel::Error, "UnSupported MsgType[%s]", msgType.c_str());
	}

	m_FixMessage->Items.clear();
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



int TradeApi::ReqLogon()
{
	ReqLogonField reqLogonField;
	reqLogonField.BeginString = m_AccountInfo->BeginString;
	reqLogonField.BodyLength = "";
	reqLogonField.MsgType = "A";
	reqLogonField.MsgSeqNum = ItoA(GlobalParam::GetInstance().GetNextExpectedMsgSeqNum());
	reqLogonField.SenderCompID = m_AccountInfo->SenderCompID + "U";
	reqLogonField.SenderSubID = m_AccountInfo->SenderSubID;
	reqLogonField.SendingTime = GetUtcTime();
	reqLogonField.TargetCompID = m_AccountInfo->TargetCompID;
	reqLogonField.TargetSubID = m_AccountInfo->TargetSubID;
	reqLogonField.OrigSendingTime = "";
	reqLogonField.SenderLocationID = m_AccountInfo->SenderLocationID;
	reqLogonField.LastMsgSeqNumProcessed = "";

	reqLogonField.HeartBtInt = m_AccountInfo->HeartBtInt;
	reqLogonField.ResetSeqNumFlag = m_AccountInfo->ResetSeqNumFlag;
	reqLogonField.ApplicationSystemName = m_AccountInfo->ApplicationSystemName;
	reqLogonField.ApplicationSystemVersion = m_AccountInfo->ApplicationSystemVersion;
	reqLogonField.ApplicationSystemVendor = m_AccountInfo->ApplicationSystemVendor;
	reqLogonField.EncodedTextLen = ItoA(m_AccountInfo->AccountID.length());
	reqLogonField.EncodedText = m_AccountInfo->AccountID;
	reqLogonField.EncryptedPasswordMethod = m_AccountInfo->EncryptedPasswordMethod;

	std::string canonicalRequest = GetCanonicalReq(reqLogonField);
	std::string encodedHmac = calculateHMAC(m_AccountInfo->SecretKey, canonicalRequest);
	reqLogonField.EncryptedPasswordLen = ItoA(encodedHmac.length());
	reqLogonField.EncryptedPassword = encodedHmac;

	auto len = reqLogonField.MakePackage(m_SendBuff, BUFF_SIZE);
	TcpThread::GetInstance().Send(m_SessionID, m_SendBuff, len);
	return 0;
}

int TradeApi::ReqHeartBeat(const string& testReqID)
{
	ReqHeartBeatField reqHeartBeatField;
	reqHeartBeatField.BeginString = m_AccountInfo->BeginString;
	reqHeartBeatField.BodyLength = "";
	reqHeartBeatField.MsgType = "0";
	reqHeartBeatField.MsgSeqNum = ItoA(GlobalParam::GetInstance().GetNextExpectedMsgSeqNum());
	reqHeartBeatField.SenderCompID = m_SenderCompID;
	reqHeartBeatField.SenderSubID = m_AccountInfo->SenderSubID;
	reqHeartBeatField.SendingTime = GetUtcTime();
	reqHeartBeatField.TargetCompID = m_AccountInfo->TargetCompID;
	reqHeartBeatField.TargetSubID = m_AccountInfo->TargetSubID;
	reqHeartBeatField.OrigSendingTime = "";
	reqHeartBeatField.SenderLocationID = m_AccountInfo->SenderLocationID;
	reqHeartBeatField.LastMsgSeqNumProcessed = "";

	reqHeartBeatField.TestReqID = testReqID;
	
	auto len = reqHeartBeatField.MakePackage(m_SendBuff, BUFF_SIZE);
	TcpThread::GetInstance().Send(m_SessionID, m_SendBuff, len);
	return 0;
}

int TradeApi::ReqNewOrder()
{
	ReqNewOrderField reqNewOrderField;
	reqNewOrderField.BeginString = m_AccountInfo->BeginString;
	reqNewOrderField.BodyLength = "";
	reqNewOrderField.MsgType = "D";
	reqNewOrderField.MsgSeqNum = ItoA(GlobalParam::GetInstance().GetNextExpectedMsgSeqNum());
	reqNewOrderField.SenderCompID = m_SenderCompID;
	reqNewOrderField.SenderSubID = m_AccountInfo->SenderSubID;
	reqNewOrderField.SendingTime = GetUtcTime();
	reqNewOrderField.TargetCompID = m_AccountInfo->TargetCompID;
	reqNewOrderField.TargetSubID = m_AccountInfo->TargetSubID;
	reqNewOrderField.OrigSendingTime = "";
	reqNewOrderField.SenderLocationID = m_AccountInfo->SenderLocationID;
	reqNewOrderField.LastMsgSeqNumProcessed = "";

	reqNewOrderField.Account = "2F5004";
	reqNewOrderField.ClOrdID = "5";
	reqNewOrderField.HandInst = "1";
	reqNewOrderField.CustOrderHandlingInst = "Y";
	reqNewOrderField.OrderQty = "5";
	reqNewOrderField.OrdType = "1";
	reqNewOrderField.Price = "";
	reqNewOrderField.Side = "1";
	reqNewOrderField.Symbol = "";
	reqNewOrderField.TimeInForce = "0";
	reqNewOrderField.TransactTime = GetUtcTime();
	reqNewOrderField.ManualOrderIndicator = "Y";
	reqNewOrderField.NoAllocs = "";
	reqNewOrderField.AllocAccount = "";
	reqNewOrderField.StopPx = "";
	reqNewOrderField.SecurityDesc = "1GLBJ0";
	reqNewOrderField.MinQty = "1";
	reqNewOrderField.SecurityType = "FUT";
	reqNewOrderField.CustomerOrFirm = "0";
	reqNewOrderField.MaxShow = "1";
	reqNewOrderField.ExpireDate = "";
	reqNewOrderField.SelfMatchPreventionID = "";
	reqNewOrderField.SelfMatchPreventionInstruction = "";
	reqNewOrderField.CtiCode = "4";
	reqNewOrderField.AvgPxGroupID = "";
	reqNewOrderField.ClearingTradePriceType = "";
	reqNewOrderField.AvgPXIndicator = "";
	reqNewOrderField.Memo = "";
	reqNewOrderField.GiveUpFirm = "";
	reqNewOrderField.CmtaGiveupCD = "";
	reqNewOrderField.CorrelationClOrdID = "5";


	auto len = reqNewOrderField.MakePackage(m_SendBuff, BUFF_SIZE);
	TcpThread::GetInstance().Send(m_SessionID, m_SendBuff, len);
	return 0;
}



void TradeApi::OnRspLogon()
{
	RspLogonField rspLogonField(m_FixMessage);
	rspLogonField.ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "OnRspLogon  RspLogonField: %s", m_LogBuff);

	m_SenderCompID = rspLogonField.TargetCompID;
}

void TradeApi::OnRspLogout()
{
	RspLogoutField rspLogoutField(m_FixMessage);
	rspLogoutField.ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "OnRspLogout  RspLogoutField: %s", m_LogBuff);

	if (!rspLogoutField.NextExpectedMsgSeqNum.empty())
	{
		GlobalParam::GetInstance().SetNextExpectedMsgSeqNum(atoi(rspLogoutField.NextExpectedMsgSeqNum.c_str()));
	}
}

void TradeApi::OnRspHeartBeat()
{
	RspHeartBeatField rspHeartBeatField(m_FixMessage);
	rspHeartBeatField.ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "OnRspHeartBeatField  RspHeartBeatField: %s", m_LogBuff);

	ReqHeartBeat("");
}

void TradeApi::OnRspTestRequest()
{
	RspTestRequestField rspTestRequestField(m_FixMessage);
	rspTestRequestField.ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "OnRspTestRequest  RspTestRequestField: %s", m_LogBuff);

	ReqHeartBeat(rspTestRequestField.TestReqID);

	if (!m_SendOrderMark)
	{
		m_SendOrderMark = true;
		ReqNewOrder();
	}
}

void TradeApi::OnSessionLevelReject()
{
	RspSessionLevelRejectField rspSessionLevelRejectField(m_FixMessage);
	rspSessionLevelRejectField.ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "OnSessionLevelReject  RspSessionLevelRejectField: %s", m_LogBuff);
}
