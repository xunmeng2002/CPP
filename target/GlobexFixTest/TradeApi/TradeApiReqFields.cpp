#include "TradeApiReqFields.h"
#include "Logger.h"
#include "Common.h"



ReqHeader::ReqHeader(FixMessage* fixMessage)
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
	SenderLocationID = fixMessage->GetItem(142);
	LastMsgSeqNumProcessed = fixMessage->GetItem(369);
}
int ReqHeader::ToString(char* buff, int size)
{
	int len = 0;
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
	len += WriteString(buff + len, size - len, "SenderLocationID", SenderLocationID);
	len += WriteString(buff + len, size - len, "LastMsgSeqNumProcessed", LastMsgSeqNumProcessed);
	return len;
}
int ReqHeader::ToStream(char* buff)
{
	int len = 0;
	len += WriteStream(buff + len, 35, MsgType);
	len += WriteStream(buff + len, 34, MsgSeqNum);
	len += WriteStream(buff + len, 49, SenderCompID);
	len += WriteStream(buff + len, 50, SenderSubID);
	len += WriteStream(buff + len, 52, SendingTime);
	len += WriteStream(buff + len, 56, TargetCompID);
	len += WriteStream(buff + len, 57, TargetSubID);
	len += WriteStream(buff + len, 122, OrigSendingTime);
	len += WriteStream(buff + len, 142, SenderLocationID);
	len += WriteStream(buff + len, 369, LastMsgSeqNumProcessed);
	return len;
}
int ReqHeader::AddHead(char* buff, int bodyLen)
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


ReqFieldBase::ReqFieldBase(FixMessage* fixMessage)
	: ReqHeader(fixMessage), Trailer(fixMessage)
{

}
int ReqFieldBase::MakePackage(char* buff, int size)
{
	auto len = ToStream(buff + HEAD_LEN);
	len += AddHead(buff, len);
	len += AddTrailer(buff, len);
	return len;
}


ReqLogonField::ReqLogonField(FixMessage* fixMessage)
	:ReqFieldBase(fixMessage)
{
	HeartBtInt = fixMessage->GetItem(108);
	ResetSeqNumFlag = fixMessage->GetItem(141);
	ApplicationSystemName = fixMessage->GetItem(1603);
	ApplicationSystemVersion = fixMessage->GetItem(1604);
	ApplicationSystemVendor = fixMessage->GetItem(1605);
	EncodedTextLen = fixMessage->GetItem(354);
	EncodedText = fixMessage->GetItem(355);
	EncryptedPasswordMethod = fixMessage->GetItem(1400);
	EncryptedPasswordLen = fixMessage->GetItem(1401);
	EncryptedPassword = fixMessage->GetItem(1402);
}
int ReqLogonField::ToString(char* buff, int size)
{
	int len = 0;
	len += ReqHeader::ToString(buff + len, size - len);

	len += WriteString(buff + len, size - len, "HeartBtInt", HeartBtInt);
	len += WriteString(buff + len, size - len, "ResetSeqNumFlag", ResetSeqNumFlag);
	len += WriteString(buff + len, size - len, "ApplicationSystemName", ApplicationSystemName);
	len += WriteString(buff + len, size - len, "ApplicationSystemVersion", ApplicationSystemVersion);
	len += WriteString(buff + len, size - len, "ApplicationSystemVendor", ApplicationSystemVendor);
	len += WriteString(buff + len, size - len, "EncodedTextLen", EncodedTextLen);
	len += WriteString(buff + len, size - len, "EncodedText", EncodedText);
	len += WriteString(buff + len, size - len, "EncryptedPasswordMethod", EncryptedPasswordMethod);
	len += WriteString(buff + len, size - len, "EncryptedPasswordLen", EncryptedPasswordLen);
	len += WriteString(buff + len, size - len, "EncryptedPassword", EncryptedPassword);

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int ReqLogonField::ToStream(char* buff)
{
	int len = 0;
	len += ReqHeader::ToStream(buff + len);

	len += WriteStream(buff + len, 108, HeartBtInt);
	len += WriteStream(buff + len, 141, ResetSeqNumFlag);
	len += WriteStream(buff + len, 1603, ApplicationSystemName);
	len += WriteStream(buff + len, 1604, ApplicationSystemVersion);
	len += WriteStream(buff + len, 1605, ApplicationSystemVendor);
	len += WriteStream(buff + len, 354, EncodedTextLen);
	len += WriteStream(buff + len, 355, EncodedText);
	len += WriteStream(buff + len, 1400, EncryptedPasswordMethod);
	len += WriteStream(buff + len, 1401, EncryptedPasswordLen);
	len += WriteStream(buff + len, 1402, EncryptedPassword);
	return len;
}


ReqHeartBeatField::ReqHeartBeatField(FixMessage* fixMessage)
	:ReqFieldBase(fixMessage)
{
	TestReqID = fixMessage->GetItem(112);
	SplitMsg = fixMessage->GetItem(9553);
}
int ReqHeartBeatField::ToString(char* buff, int size)
{
	int len = 0;
	len += ReqHeader::ToString(buff + len, size - len);

	len += WriteString(buff + len, size - len, "TestReqID", TestReqID);
	len += WriteString(buff + len, size - len, "SplitMsg", SplitMsg);

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int ReqHeartBeatField::ToStream(char* buff)
{
	int len = 0;
	len += ReqHeader::ToStream(buff + len);

	len += WriteStream(buff + len, 112, TestReqID);
	len += WriteStream(buff + len, 9553, SplitMsg);

	return len;
}


ReqNewOrderField::ReqNewOrderField(FixMessage* fixMessage)
	:ReqFieldBase(fixMessage)
{
	Account = fixMessage->GetItem(1);
	ClOrdID = fixMessage->GetItem(11);
	HandInst = fixMessage->GetItem(21);
	CustOrderHandlingInst = fixMessage->GetItem(1031);
	OrderQty = fixMessage->GetItem(38);
	OrdType = fixMessage->GetItem(40);
	Price = fixMessage->GetItem(44);
	Side = fixMessage->GetItem(54);
	Symbol = fixMessage->GetItem(55);
	TimeInForce = fixMessage->GetItem(59);
	TransactTime = fixMessage->GetItem(60);
	ManualOrderIndicator = fixMessage->GetItem(1028);
	NoAllocs = fixMessage->GetItem(78);
	AllocAccount = fixMessage->GetItem(79);
	StopPx = fixMessage->GetItem(99);
	SecurityDesc = fixMessage->GetItem(107);
	MinQty = fixMessage->GetItem(110);
	SecurityType = fixMessage->GetItem(167);
	CustomerOrFirm = fixMessage->GetItem(204);
	MaxShow = fixMessage->GetItem(210);
	ExpireDate = fixMessage->GetItem(432);
	SelfMatchPreventionID = fixMessage->GetItem(7928);
	SelfMatchPreventionInstruction = fixMessage->GetItem(8000);
	CtiCode = fixMessage->GetItem(9702);
	AvgPxGroupID = fixMessage->GetItem(1731);
	ClearingTradePriceType = fixMessage->GetItem(1598);
	AvgPXIndicator = fixMessage->GetItem(819);
	Memo = fixMessage->GetItem(5149);
	GiveUpFirm = fixMessage->GetItem(9707);
	CmtaGiveupCD = fixMessage->GetItem(9708);
	CorrelationClOrdID = fixMessage->GetItem(9717);
}

int ReqNewOrderField::ToString(char* buff, int size)
{
	int len = 0;
	len += ReqHeader::ToString(buff + len, size - len);

	len += WriteString(buff + len, size - len, "Account", Account);
	len += WriteString(buff + len, size - len, "ClOrdID", ClOrdID);
	len += WriteString(buff + len, size - len, "HandInst", HandInst);
	len += WriteString(buff + len, size - len, "CustOrderHandlingInst", CustOrderHandlingInst);
	len += WriteString(buff + len, size - len, "OrderQty", OrderQty);
	len += WriteString(buff + len, size - len, "OrdType", OrdType);
	len += WriteString(buff + len, size - len, "Price", Price);
	len += WriteString(buff + len, size - len, "Side", Side);
	len += WriteString(buff + len, size - len, "Symbol", Symbol);
	len += WriteString(buff + len, size - len, "TimeInForce", TimeInForce);
	len += WriteString(buff + len, size - len, "TransactTime", TransactTime);
	len += WriteString(buff + len, size - len, "ManualOrderIndicator", ManualOrderIndicator);
	len += WriteString(buff + len, size - len, "NoAllocs", NoAllocs);
	len += WriteString(buff + len, size - len, "AllocAccount", AllocAccount);
	len += WriteString(buff + len, size - len, "StopPx", StopPx);
	len += WriteString(buff + len, size - len, "SecurityDesc", SecurityDesc);
	len += WriteString(buff + len, size - len, "MinQty", MinQty);
	len += WriteString(buff + len, size - len, "SecurityType", SecurityType);
	len += WriteString(buff + len, size - len, "CustomerOrFirm", CustomerOrFirm);
	len += WriteString(buff + len, size - len, "MaxShow", MaxShow);
	len += WriteString(buff + len, size - len, "ExpireDate", ExpireDate);
	len += WriteString(buff + len, size - len, "SelfMatchPreventionID", SelfMatchPreventionID);
	len += WriteString(buff + len, size - len, "SelfMatchPreventionInstruction", SelfMatchPreventionInstruction);
	len += WriteString(buff + len, size - len, "CtiCode", CtiCode);
	len += WriteString(buff + len, size - len, "AvgPxGroupID", AvgPxGroupID);
	len += WriteString(buff + len, size - len, "ClearingTradePriceType", ClearingTradePriceType);
	len += WriteString(buff + len, size - len, "AvgPXIndicator", AvgPXIndicator);
	len += WriteString(buff + len, size - len, "Memo", Memo);
	len += WriteString(buff + len, size - len, "GiveUpFirm", GiveUpFirm);
	len += WriteString(buff + len, size - len, "CmtaGiveupCD", CmtaGiveupCD);
	len += WriteString(buff + len, size - len, "CorrelationClOrdID", CorrelationClOrdID);

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int ReqNewOrderField::ToStream(char* buff)
{
	int len = 0;
	len += ReqHeader::ToStream(buff + len);

	len += WriteStream(buff + len, 1, Account);
	len += WriteStream(buff + len, 11, ClOrdID);
	len += WriteStream(buff + len, 21, HandInst);
	len += WriteStream(buff + len, 1031, CustOrderHandlingInst);
	len += WriteStream(buff + len, 38, OrderQty);
	len += WriteStream(buff + len, 40, OrdType);
	len += WriteStream(buff + len, 44, Price);
	len += WriteStream(buff + len, 54, Side);
	len += WriteStream(buff + len, 55, Symbol);
	len += WriteStream(buff + len, 59, TimeInForce);
	len += WriteStream(buff + len, 60, TransactTime);
	len += WriteStream(buff + len, 1028, ManualOrderIndicator);
	len += WriteStream(buff + len, 78, NoAllocs);
	len += WriteStream(buff + len, 79, AllocAccount);
	len += WriteStream(buff + len, 99, StopPx);
	len += WriteStream(buff + len, 107, SecurityDesc);
	len += WriteStream(buff + len, 110, MinQty);
	len += WriteStream(buff + len, 167, SecurityType);
	len += WriteStream(buff + len, 204, CustomerOrFirm);
	len += WriteStream(buff + len, 210, MaxShow);
	len += WriteStream(buff + len, 432, ExpireDate);
	len += WriteStream(buff + len, 7928, SelfMatchPreventionID);
	len += WriteStream(buff + len, 8000, SelfMatchPreventionInstruction);
	len += WriteStream(buff + len, 9702, CtiCode);
	len += WriteStream(buff + len, 1731, AvgPxGroupID);
	len += WriteStream(buff + len, 1598, ClearingTradePriceType);
	len += WriteStream(buff + len, 819, AvgPXIndicator);
	len += WriteStream(buff + len, 5149, Memo);
	len += WriteStream(buff + len, 9707, GiveUpFirm);
	len += WriteStream(buff + len, 9708, CmtaGiveupCD);
	len += WriteStream(buff + len, 9717, CorrelationClOrdID);

	return len;
}

