#pragma once
#include <string>

using namespace std;

struct ReqHeader
{
	string BeginString;
	int BodyLength;
	string MsgType;
	int MsgSeqNum;
	bool PossDupFlag;
	string SenderCompID;
	string SenderSubID;
	string SendingTime;
	int LastMsgSeqNumProcessed;
	string TargetCompID;
	string TargetSubID;
	string OrigSendingTime;
	string SenderLocationID;
};

struct RspHeader
{
	string BeginString;
	int BodyLength;
	string MsgType;
	int MsgSeqNum;
	bool PossDupFlag;
	string SenderCompID;
	string SenderSubID;
	string SendingTime;
	string TargetCompID;
	string TargetSubID;
	bool PossResend;
	string OrigSendingTime;
	int LastSeqNumProcessed;
	string TargetLocationID;
};

struct Trailer
{
	string CheckSum;
};

struct ReqLogon
{
	int HeartBtInt;
	bool ResetSeqNumFlag;
	string ApplicationSystemName;
	string ApplicationSystemVersion;
	string ApplicationSystemVendor;
	int EncodedTextLen;
	string EncodedText;
	string EncryptedPasswordMethod;
	int EncryptedPasswordLen;
	string EncryptedPassword;
};

struct RspLogon
{
	int HeartBtInt;
	bool ResetSeqNumFlag;
	string ApplicationSystemName;
	string ApplicationSystemVersion;
	string ApplicationSystemVendor;
	int SplitMsg;
};

struct RspLogout
{
	string Text;
	int NextExpectedMsgSeqNum;
	int SplitMsg;
};
