#pragma once

#include "TradeApiDataStruct.h"

class ReqHeader
{
public:
	ReqHeader() {}
	ReqHeader(FixMessage* fixMessage);

	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff);
	int AddHead(char* buff, int bodyLen);

public:
	string BeginString;
	string BodyLength;
	string MsgType;
	string MsgSeqNum;
	string SenderCompID;
	string SenderSubID;
	string SendingTime;
	string TargetCompID;
	string TargetSubID;
	string OrigSendingTime;
	string SenderLocationID;
	string LastMsgSeqNumProcessed;

protected:
	char HeadBuff[HEAD_LEN];
	unordered_map<int, string> Items;
};

class ReqFieldBase : public ReqHeader, public Trailer
{
public:
	ReqFieldBase() {}
	ReqFieldBase(FixMessage* fixMessage);

	int MakePackage(char* buff, int size);
	virtual int ToStream(char* buff) override = 0;
};

class ReqLogonField : public ReqFieldBase
{
public:
	ReqLogonField() {}
	ReqLogonField(FixMessage* fixMessage);

	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string HeartBtInt;
	string ResetSeqNumFlag;
	string ApplicationSystemName;
	string ApplicationSystemVersion;
	string ApplicationSystemVendor;
	string EncodedTextLen;
	string  EncodedText;
	string EncryptedPasswordMethod;
	string EncryptedPasswordLen;
	string EncryptedPassword;
};

class ReqHeartBeatField : public ReqFieldBase
{
public:
	ReqHeartBeatField() {}
	ReqHeartBeatField(FixMessage* fixMessage);


	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string TestReqID;
	string SplitMsg;
};

class ReqNewOrderField : public ReqFieldBase
{
public:
	ReqNewOrderField() {}
	ReqNewOrderField(FixMessage* fixMessage);

	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string Account;
	string ClOrdID;
	string HandInst;
	string CustOrderHandlingInst;
	string OrderQty;
	string OrdType;
	string Price;
	string Side;
	string Symbol;
	string TimeInForce;
	string TransactTime;
	string ManualOrderIndicator;
	string NoAllocs;
	string AllocAccount;
	string StopPx;
	string SecurityDesc;
	string MinQty;
	string SecurityType;
	string CustomerOrFirm;
	string MaxShow;
	string ExpireDate;
	string SelfMatchPreventionID;
	string SelfMatchPreventionInstruction;
	string CtiCode;
	string AvgPxGroupID;
	string ClearingTradePriceType;
	string AvgPXIndicator;
	string Memo;
	string GiveUpFirm;
	string CmtaGiveupCD;
	string CorrelationClOrdID;
};

