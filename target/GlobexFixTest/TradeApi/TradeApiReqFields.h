#pragma once

#include "TradeApiDataStruct.h"

class ReqHeader
{
public:
	ReqHeader(const string& fieldName, const string& msgType);

	int ToString(char* buff, int size);
	int ToStream(char* buff);
	int AddHead(char* buff, int bodyLen);
	void SetHead(const string& senderCompID, const string& senderSubID, const string& targetCompID, const string& targetSubID);

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
	string FieldName;

	char HeadBuff[HEAD_LEN];
	unordered_map<int, string> Items;
};

class ReqFieldBase : public ReqHeader, public Trailer
{
public:
	ReqFieldBase(const string& fieldName, const string& msgType)
		:ReqHeader(fieldName, msgType)
	{}

	int MakePackage(char* buff, int size);
	virtual int ToString(char* buff, int size) = 0;
	virtual int ToStream(char* buff) = 0;
};

class ReqLogonField : public ReqFieldBase
{
public:
	ReqLogonField()
		:ReqFieldBase("ReqLogonField", "A")
	{}

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

class ReqLogoutField : public ReqFieldBase
{
public:
	ReqLogoutField()
		:ReqFieldBase("ReqLogoutField", "5") 
	{}

	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:

};


class ReqTestRequestField : public ReqFieldBase
{
public:
	ReqTestRequestField()
		:ReqFieldBase("ReqTestRequestField", "1")
	{}
	
	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string TestReqID;
};


class ReqHeartBeatField : public ReqFieldBase
{
public:
	ReqHeartBeatField()
		:ReqFieldBase("ReqHeartBeatField", "0")
	{}

	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string TestReqID;
	string SplitMsg;
};


class ReqResendRequestField : public ReqFieldBase
{
public:
	ReqResendRequestField()
		:ReqFieldBase("ReqResendRequestField", "2")
	{}

	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string BeginSeqNo;
	string EndSeqNo;
};


class ReqSequenceResetField : public ReqFieldBase
{
public:
	ReqSequenceResetField()
		:ReqFieldBase("ReqSequenceResetField", "2")
	{}

	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string NewSeqNo;
	string GapFillFlag;
};


class ReqNewOrderField : public ReqFieldBase
{
public:
	ReqNewOrderField()
		:ReqFieldBase("ReqNewOrderField", "D")
	{}

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
	string MarketSegmentID;
};

