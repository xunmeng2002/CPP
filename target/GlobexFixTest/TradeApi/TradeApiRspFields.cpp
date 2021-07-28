#include "TradeApiRspFields.h"


RspHeader::RspHeader(const string& fieldName, FixMessage* fixMessage)
	:FieldName(fieldName)
{
	BeginString = fixMessage->GetItem(8);
	BodyLength = fixMessage->GetItem(9);
	MsgType = fixMessage->GetItem(35);
	MsgSeqNum = fixMessage->GetItem(34);
	SenderCompID = fixMessage->GetItem(49);
	SenderSubID = fixMessage->GetItem(50);
	SendingTime = fixMessage->GetItem(52);
	TargetCompID = fixMessage->GetItem(56);
	TargetSubID = fixMessage->GetItem(57);
	OrigSendingTime = fixMessage->GetItem(122);
	TargetLocationID = fixMessage->GetItem(143);
	LastMsgSeqNumProcessed = fixMessage->GetItem(369);
}
int RspHeader::ToString(char* buff, int size)
{
	int len = 0;
	len += sprintf(buff, "%s:", FieldName.c_str());

	len += WriteString(buff + len, size - len, "BeginString", BeginString);
	len += WriteString(buff + len, size - len, "BodyLength", BodyLength);
	len += WriteString(buff + len, size - len, "MsgType", MsgType);
	len += WriteString(buff + len, size - len, "MsgSeqNum", MsgSeqNum);
	len += WriteString(buff + len, size - len, "SenderCompID", SenderCompID);
	len += WriteString(buff + len, size - len, "SenderSubID", SenderSubID);
	len += WriteString(buff + len, size - len, "SendingTime", SendingTime);
	len += WriteString(buff + len, size - len, "TargetCompID", TargetCompID);
	len += WriteString(buff + len, size - len, "TargetSubID", TargetSubID);
	len += WriteString(buff + len, size - len, "OrigSendingTime", OrigSendingTime);
	len += WriteString(buff + len, size - len, "TargetLocationID", TargetLocationID);
	len += WriteString(buff + len, size - len, "LastMsgSeqNumProcessed", LastMsgSeqNumProcessed);
	return len;
}
int RspHeader::ToStream(char* buff)
{
	int len = 0;
	len += WriteStream(buff + len, 8, BeginString);
	len += WriteStream(buff + len, 9, BodyLength);
	len += WriteStream(buff + len, 35, MsgType);
	len += WriteStream(buff + len, 34, MsgSeqNum);
	len += WriteStream(buff + len, 49, SenderCompID);
	len += WriteStream(buff + len, 50, SenderSubID);
	len += WriteStream(buff + len, 52, SendingTime);
	len += WriteStream(buff + len, 56, TargetCompID);
	len += WriteStream(buff + len, 57, TargetSubID);
	len += WriteStream(buff + len, 122, OrigSendingTime);
	len += WriteStream(buff + len, 143, TargetLocationID);
	len += WriteStream(buff + len, 369, LastMsgSeqNumProcessed);
	return len;
}
int RspHeader::AddHead(char* buff, int bodyLen)
{
	char temp[8];
	sprintf(temp, "%05d", bodyLen);
	BodyLength = temp;
	int len = 0;
	len += WriteStream(HeadBuff + len, 8, BeginString);
	len += WriteStream(HeadBuff + len, 9, BodyLength);
	_ASSERT(len == HEAD_LEN);
	memcpy(buff, HeadBuff, HEAD_LEN);
	return len;
}


RspFieldBase::RspFieldBase(const string& fieldName, FixMessage* fixMessage)
	: RspHeader(fieldName, fixMessage), Trailer(fixMessage)
{

}
int RspFieldBase::MakePackage(char* buff, int size)
{
	auto len = ToStream(buff + HEAD_LEN);
	len += AddHead(buff, len);
	len += AddTrailer(buff, len);
	return len;
}


RspLogonField::RspLogonField(FixMessage* fixMessage)
	:RspFieldBase("RspLogonField", fixMessage)
{
	HeartBtInt = fixMessage->GetItem(108);
	ResetSeqNumFlag = fixMessage->GetItem(141);
	ApplicationSystemName = fixMessage->GetItem(1603);
	ApplicationSystemVersion = fixMessage->GetItem(1604);
	ApplicationSystemVendor = fixMessage->GetItem(1605);
	SplitMsg = fixMessage->GetItem(9553);
}
int RspLogonField::ToString(char* buff, int size)
{
	int len = 0;
	len += RspHeader::ToString(buff + len, size - len);

	len += WriteString(buff + len, size - len, "HeartBtInt", HeartBtInt);
	len += WriteString(buff + len, size - len, "ResetSeqNumFlag", ResetSeqNumFlag);
	len += WriteString(buff + len, size - len, "ApplicationSystemName", ApplicationSystemName);
	len += WriteString(buff + len, size - len, "ApplicationSystemVersion", ApplicationSystemVersion);
	len += WriteString(buff + len, size - len, "ApplicationSystemVendor", ApplicationSystemVendor);
	len += WriteString(buff + len, size - len, "SplitMsg", SplitMsg);

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int RspLogonField::ToStream(char* buff)
{
	int len = 0;
	len += RspHeader::ToStream(buff + len);

	len += WriteStream(buff + len, 108, HeartBtInt);
	len += WriteStream(buff + len, 141, ResetSeqNumFlag);
	len += WriteStream(buff + len, 1603, ApplicationSystemName);
	len += WriteStream(buff + len, 1604, ApplicationSystemVersion);
	len += WriteStream(buff + len, 1605, ApplicationSystemVendor);
	len += WriteStream(buff + len, 9553, SplitMsg);
	return len;
}


RspLogoutField::RspLogoutField(FixMessage* fixMessage)
	:RspFieldBase("RspLogoutField", fixMessage)
{
	Text = fixMessage->GetItem(58);
	NextExpectedMsgSeqNum = fixMessage->GetItem(789);
	SplitMsg = fixMessage->GetItem(9553);

}
int RspLogoutField::ToString(char* buff, int size)
{
	int len = 0;
	len += RspHeader::ToString(buff + len, size - len);

	len += WriteString(buff + len, size - len, "Text", Text);
	len += WriteString(buff + len, size - len, "NextExpectedMsgSeqNum", NextExpectedMsgSeqNum);
	len += WriteString(buff + len, size - len, "SplitMsg", SplitMsg);

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int RspLogoutField::ToStream(char* buff)
{
	int len = 0;
	len += RspHeader::ToStream(buff + len);

	len += WriteStream(buff + len, 58, Text);
	len += WriteStream(buff + len, 789, NextExpectedMsgSeqNum);
	len += WriteStream(buff + len, 9553, SplitMsg);

	return len;
}


RspTestRequestField::RspTestRequestField(FixMessage* fixMessage)
	:RspFieldBase("RspTestRequestField", fixMessage)
{
	TestReqID = fixMessage->GetItem(112);
}
int RspTestRequestField::ToString(char* buff, int size)
{
	int len = 0;
	len += RspHeader::ToString(buff + len, size - len);

	len += WriteString(buff + len, size - len, "TestReqID", TestReqID);

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int RspTestRequestField::ToStream(char* buff)
{
	int len = 0;
	len += RspHeader::ToStream(buff + len);

	len += WriteStream(buff + len, 112, TestReqID);

	return len;
}


RspHeartBeatField::RspHeartBeatField(FixMessage* fixMessage)
	:RspFieldBase("RspHeartBeatField", fixMessage)
{
	TestReqID = fixMessage->GetItem(112);
	SplitMsg = fixMessage->GetItem(9553);
}
int RspHeartBeatField::ToString(char* buff, int size)
{
	int len = 0;
	len += RspHeader::ToString(buff + len, size - len);

	len += WriteString(buff + len, size - len, "TestReqID", TestReqID);
	len += WriteString(buff + len, size - len, "SplitMsg", SplitMsg);

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int RspHeartBeatField::ToStream(char* buff)
{
	int len = 0;
	len += RspHeader::ToStream(buff + len);

	len += WriteStream(buff + len, 112, TestReqID);
	len += WriteStream(buff + len, 9553, SplitMsg);

	return len;
}


RspSessionLevelRejectField::RspSessionLevelRejectField(FixMessage* fixMessage)
	:RspFieldBase("RspSessionLevelRejectField", fixMessage)
{
	RefSeqNum = fixMessage->GetItem(45);
	Text = fixMessage->GetItem(58);
	RefTagID = fixMessage->GetItem(371);
	SessionRejectReason = fixMessage->GetItem(373);
	ManualOrderIndicator = fixMessage->GetItem(1028);
	SplitMsg = fixMessage->GetItem(9553);
}
int RspSessionLevelRejectField::ToString(char* buff, int size)
{
	int len = 0;
	len += RspHeader::ToString(buff + len, size - len);

	len += WriteString(buff + len, size - len, "RefSeqNum", RefSeqNum);
	len += WriteString(buff + len, size - len, "Text", Text);
	len += WriteString(buff + len, size - len, "RefTagID", RefTagID);
	len += WriteString(buff + len, size - len, "SessionRejectReason", SessionRejectReason);
	len += WriteString(buff + len, size - len, "ManualOrderIndicator", ManualOrderIndicator);
	len += WriteString(buff + len, size - len, "SplitMsg", SplitMsg);

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int RspSessionLevelRejectField::ToStream(char* buff)
{
	int len = 0;
	len += RspHeader::ToStream(buff + len);

	len += WriteStream(buff + len, 45, RefSeqNum);
	len += WriteStream(buff + len, 58, Text);
	len += WriteStream(buff + len, 371, RefTagID);
	len += WriteStream(buff + len, 373, SessionRejectReason);
	len += WriteStream(buff + len, 1028, ManualOrderIndicator);
	len += WriteStream(buff + len, 9553, SplitMsg);

	return len;
}


RspResendRequestField::RspResendRequestField(FixMessage* fixMessage)
	:RspFieldBase("RspResendRequestField", fixMessage)
{
	BeginSeqNo = fixMessage->GetItem(7);
	EndSeqNo = fixMessage->GetItem(16);
}
int RspResendRequestField::ToString(char* buff, int size)
{
	int len = 0;
	len += RspHeader::ToString(buff + len, size - len);

	len += WriteString(buff + len, size - len, "BeginSeqNo", BeginSeqNo);
	len += WriteString(buff + len, size - len, "EndSeqNo", EndSeqNo);

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int RspResendRequestField::ToStream(char* buff)
{
	int len = 0;
	len += RspHeader::ToStream(buff + len);

	len += WriteStream(buff + len, 7, BeginSeqNo);
	len += WriteStream(buff + len, 16, EndSeqNo);

	return len;
}


RspSequenceResetField::RspSequenceResetField(FixMessage* fixMessage)
	:RspFieldBase("RspSequenceResetField", fixMessage)
{
	NewSeqNo = fixMessage->GetItem(36);
	GapFillFlag = fixMessage->GetItem(123);
}
int RspSequenceResetField::ToString(char* buff, int size)
{
	int len = 0;
	len += RspHeader::ToString(buff + len, size - len);

	len += WriteString(buff + len, size - len, "NewSeqNo", NewSeqNo);
	len += WriteString(buff + len, size - len, "GapFillFlag", GapFillFlag);

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int RspSequenceResetField::ToStream(char* buff)
{
	int len = 0;
	len += RspHeader::ToStream(buff + len);

	len += WriteStream(buff + len, 36, NewSeqNo);
	len += WriteStream(buff + len, 123, GapFillFlag);

	return len;
}
