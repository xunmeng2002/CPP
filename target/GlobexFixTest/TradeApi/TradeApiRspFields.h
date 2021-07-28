#pragma once

#include "TradeApiDataStruct.h"


class RspHeader
{
public:
	RspHeader(const string& fieldName, FixMessage* fixMessage);

	int ToString(char* buff, int size);
	int ToStream(char* buff);
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
	string FieldName;

	char HeadBuff[HEAD_LEN];
	unordered_map<int, string> Items;
};

class RspFieldBase : public RspHeader, public Trailer
{
public:
	RspFieldBase(const string& fieldName, FixMessage* fixMessage);

	int MakePackage(char* buff, int size);
	virtual int ToString(char* buff, int size) = 0;
	virtual int ToStream(char* buff) = 0;
};

class RspLogonField : public RspFieldBase
{
public:
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
	RspTestRequestField(FixMessage* fixMessage);

	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string TestReqID;
};

class RspHeartBeatField : public RspFieldBase
{
public:
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


class RspResendRequestField : public RspFieldBase
{
public:
	RspResendRequestField(FixMessage* fixMessage);

	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string BeginSeqNo;
	string EndSeqNo;
};

class RspSequenceResetField : public RspFieldBase
{
public:
	RspSequenceResetField(FixMessage* fixMessage);

	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff) override;

public:
	string NewSeqNo;
	string GapFillFlag;
};