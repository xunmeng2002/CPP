#pragma once

#include "TradeApiDataStruct.h"


class RspHeader
{
public:
	RspHeader() {}
	RspHeader(FixMessage* fixMessage);

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
	string TargetLocationID;
	string LastMsgSeqNumProcessed;

protected:
	char HeadBuff[HEAD_LEN];
	unordered_map<int, string> Items;
};

class RspFieldBase : public RspHeader, public Trailer
{
public:
	RspFieldBase() {}
	RspFieldBase(FixMessage* fixMessage);

	int MakePackage(char* buff, int size);
	virtual int ToStream(char* buff) override = 0;
};

class RspLogonField : public RspFieldBase
{
public:
	RspLogonField() {}
	RspLogonField(FixMessage* fixMessage);

	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string HeartBtInt;
	string ResetSeqNumFlag;
	string ApplicationSystemName;
	string ApplicationSystemVersion;
	string ApplicationSystemVendor;
	string SplitMsg;
};

class RspLogoutField : public RspFieldBase
{
public:
	RspLogoutField() {}
	RspLogoutField(FixMessage* fixMessage);

	virtual int ToString(char* buff, int size);
protected:
	virtual int ToStream(char* buff) override;

public:
	string Text;
	string NextExpectedMsgSeqNum;
	string SplitMsg;
};

class RspTestRequestField : public RspFieldBase
{
public:
	RspTestRequestField() {}
	RspTestRequestField(FixMessage* fixMessage);

	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string TestReqID;
};

class RspHeartBeatField : public RspFieldBase
{
public:
	RspHeartBeatField() {}
	RspHeartBeatField(FixMessage* fixMessage);


	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string TestReqID;
	string SplitMsg;
};


class RspSessionLevelRejectField : public RspFieldBase
{
public:
	RspSessionLevelRejectField() {}
	RspSessionLevelRejectField(FixMessage* fixMessage);


	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string RefSeqNum;
	string Text;
	string RefTagID;
	string SessionRejectReason;
	string ManualOrderIndicator;
	string SplitMsg;
};

