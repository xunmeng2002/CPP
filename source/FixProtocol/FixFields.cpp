#include "FixFields.h"
#include "FixMdb.h"
#include "FixItems.h"


FixReqHeader::FixReqHeader(const string& fieldName, const string& msgType, const string& msgClass, FixMessage* fixMessage)
	:FieldName(fieldName), MsgType(msgType), MsgClass(msgClass), m_FixMessage(fixMessage)
{
	memset(HeadBuff, 0, sizeof(HeadBuff));
	if (!fixMessage)
		return;
	BeginString = fixMessage->GetItem(8);
	BodyLength = fixMessage->GetItem(9);
	MsgSeqNum = fixMessage->GetItem(34);
	PossDupFlag = fixMessage->GetItem(43);
	SenderCompID = fixMessage->GetItem(49);
	SenderSubID = fixMessage->GetItem(50);
	SendingTime = fixMessage->GetItem(52);
	TargetCompID = fixMessage->GetItem(56);
	TargetSubID = fixMessage->GetItem(57);
	OrigSendingTime = fixMessage->GetItem(122);
	SenderLocationID = fixMessage->GetItem(142);
	LastMsgSeqNumProcessed = fixMessage->GetItem(369);
}
FixReqHeader::FixReqHeader(FixReqHeader&& other) noexcept
{
	m_FixMessage = other.m_FixMessage;
	other.m_FixMessage = nullptr;
	FieldName = std::move(other.FieldName);
	MsgClass = other.MsgClass;
	Items = std::move(other.Items);
	
	BeginString = std::move(other.BeginString);
	BodyLength = std::move(other.BodyLength);
	MsgType = std::move(other.MsgType);
	MsgSeqNum = std::move(other.MsgSeqNum);
	PossDupFlag = std::move(other.PossDupFlag);
	SenderCompID = std::move(other.SenderCompID);
	SenderSubID = std::move(other.SenderSubID);
	SendingTime = std::move(other.SendingTime);
	TargetCompID = std::move(other.TargetCompID);
	TargetSubID = std::move(other.TargetSubID);
	OrigSendingTime = std::move(other.OrigSendingTime);
	SenderLocationID = std::move(other.SenderLocationID);
	LastMsgSeqNumProcessed = std::move(other.LastMsgSeqNumProcessed);
}
FixReqHeader& FixReqHeader::operator=(FixReqHeader&& other) noexcept
{
	Items.clear();
	if (m_FixMessage)
		m_FixMessage->Free();
	m_FixMessage = other.m_FixMessage;
	other.m_FixMessage = nullptr;
	FieldName = std::move(other.FieldName);
	MsgClass = other.MsgClass;
	Items = std::move(other.Items);
	
	BeginString = std::move(other.BeginString);
	BodyLength = std::move(other.BodyLength);
	MsgType = std::move(other.MsgType);
	MsgSeqNum = std::move(other.MsgSeqNum);
	PossDupFlag = std::move(other.PossDupFlag);
	SenderCompID = std::move(other.SenderCompID);
	SenderSubID = std::move(other.SenderSubID);
	SendingTime = std::move(other.SendingTime);
	TargetCompID = std::move(other.TargetCompID);
	TargetSubID = std::move(other.TargetSubID);
	OrigSendingTime = std::move(other.OrigSendingTime);
	SenderLocationID = std::move(other.SenderLocationID);
	LastMsgSeqNumProcessed = std::move(other.LastMsgSeqNumProcessed);
	
	return *this;
}
FixReqHeader::~FixReqHeader()
{
	if (m_FixMessage)
		m_FixMessage->Free();
	m_FixMessage = nullptr;
}

int FixReqHeader::ToString(char* buff, int size)
{
	int len = 0;
	len += sprintf(buff, "%s:", FieldName.c_str());
	
	len += WriteString(buff + len, size - len, "BeginString", BeginString);
	len += WriteString(buff + len, size - len, "BodyLength", BodyLength);
	len += WriteString(buff + len, size - len, "MsgType", MsgType);
	len += WriteString(buff + len, size - len, "MsgSeqNum", MsgSeqNum);
	len += WriteString(buff + len, size - len, "PossDupFlag", PossDupFlag);
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
int FixReqHeader::ToStream(char* buff)
{
	int len = 0;
	len += WriteStream(buff + len, 35, MsgType);
	len += WriteStream(buff + len, 34, MsgSeqNum);
	len += WriteStream(buff + len, 43, PossDupFlag);
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
FixMessage* FixReqHeader::GetFixMessage()
{
	m_FixMessage->SetItem(8, BeginString);
	m_FixMessage->SetItem(9, BodyLength);
	m_FixMessage->SetItem(35, MsgType);
	m_FixMessage->SetItem(34, MsgSeqNum);
	m_FixMessage->SetItem(43, PossDupFlag);
	m_FixMessage->SetItem(49, SenderCompID);
	m_FixMessage->SetItem(50, SenderSubID);
	m_FixMessage->SetItem(52, SendingTime);
	m_FixMessage->SetItem(56, TargetCompID);
	m_FixMessage->SetItem(57, TargetSubID);
	m_FixMessage->SetItem(122, OrigSendingTime);
	m_FixMessage->SetItem(142, SenderLocationID);
	m_FixMessage->SetItem(369, LastMsgSeqNumProcessed);
	return m_FixMessage;
}
string FixReqHeader::CreateSql()
{
	return "BeginString char(32), BodyLength char(32), MsgType char(32), MsgSeqNum char(32) PRIMARY KEY NOT NULL, PossDupFlag char(32), SenderCompID char(32), SenderSubID char(32), SendingTime char(32), TargetCompID char(32), TargetSubID char(32), OrigSendingTime char(32), SenderLocationID char(32), LastMsgSeqNumProcessed char(32), ";
}
string FixReqHeader::InsertSql()
{
	return BeginString + "\", \"" + BodyLength + "\", \"" + MsgType + "\", \"" + MsgSeqNum + "\", \"" + PossDupFlag + "\", \"" + SenderCompID + "\", \"" + SenderSubID + "\", \"" + SendingTime + "\", \"" + TargetCompID + "\", \"" + TargetSubID + "\", \"" + OrigSendingTime + "\", \"" + SenderLocationID + "\", \"" + LastMsgSeqNumProcessed;
}
int FixReqHeader::AddHeader(char* buff, int bodyLen)
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
void FixReqHeader::SetHeader(const string& senderCompID, const string& senderSubID, const string& targetCompID, const string& targetSubID)
{
	SenderCompID = senderCompID;
	SenderSubID = senderSubID;
	TargetCompID = targetCompID;
	TargetSubID = targetSubID;
}

FixRspHeader::FixRspHeader(const string& fieldName, const string& msgType, const string& msgClass, FixMessage* fixMessage)
	:FieldName(fieldName), MsgType(msgType), MsgClass(msgClass), m_FixMessage(fixMessage)
{
	memset(HeadBuff, 0, sizeof(HeadBuff));
	if (!fixMessage)
		return;
	BeginString = fixMessage->GetItem(8);
	BodyLength = fixMessage->GetItem(9);
	MsgSeqNum = fixMessage->GetItem(34);
	PossDupFlag = fixMessage->GetItem(43);
	SenderCompID = fixMessage->GetItem(49);
	SenderSubID = fixMessage->GetItem(50);
	SendingTime = fixMessage->GetItem(52);
	TargetCompID = fixMessage->GetItem(56);
	TargetSubID = fixMessage->GetItem(57);
	OrigSendingTime = fixMessage->GetItem(122);
	TargetLocationID = fixMessage->GetItem(143);
	LastMsgSeqNumProcessed = fixMessage->GetItem(369);
}
FixRspHeader::FixRspHeader(FixRspHeader&& other) noexcept
{
	m_FixMessage = other.m_FixMessage;
	other.m_FixMessage = nullptr;
	FieldName = std::move(other.FieldName);
	MsgClass = other.MsgClass;
	Items = std::move(other.Items);
	
	BeginString = std::move(other.BeginString);
	BodyLength = std::move(other.BodyLength);
	MsgType = std::move(other.MsgType);
	MsgSeqNum = std::move(other.MsgSeqNum);
	PossDupFlag = std::move(other.PossDupFlag);
	SenderCompID = std::move(other.SenderCompID);
	SenderSubID = std::move(other.SenderSubID);
	SendingTime = std::move(other.SendingTime);
	TargetCompID = std::move(other.TargetCompID);
	TargetSubID = std::move(other.TargetSubID);
	OrigSendingTime = std::move(other.OrigSendingTime);
	TargetLocationID = std::move(other.TargetLocationID);
	LastMsgSeqNumProcessed = std::move(other.LastMsgSeqNumProcessed);
}
FixRspHeader& FixRspHeader::operator=(FixRspHeader&& other) noexcept
{
	Items.clear();
	if (m_FixMessage)
		m_FixMessage->Free();
	m_FixMessage = other.m_FixMessage;
	other.m_FixMessage = nullptr;
	FieldName = std::move(other.FieldName);
	MsgClass = other.MsgClass;
	Items = std::move(other.Items);
	
	BeginString = std::move(other.BeginString);
	BodyLength = std::move(other.BodyLength);
	MsgType = std::move(other.MsgType);
	MsgSeqNum = std::move(other.MsgSeqNum);
	PossDupFlag = std::move(other.PossDupFlag);
	SenderCompID = std::move(other.SenderCompID);
	SenderSubID = std::move(other.SenderSubID);
	SendingTime = std::move(other.SendingTime);
	TargetCompID = std::move(other.TargetCompID);
	TargetSubID = std::move(other.TargetSubID);
	OrigSendingTime = std::move(other.OrigSendingTime);
	TargetLocationID = std::move(other.TargetLocationID);
	LastMsgSeqNumProcessed = std::move(other.LastMsgSeqNumProcessed);
	
	return *this;
}
FixRspHeader::~FixRspHeader()
{
	if (m_FixMessage)
		m_FixMessage->Free();
	m_FixMessage = nullptr;
}

int FixRspHeader::ToString(char* buff, int size)
{
	int len = 0;
	len += sprintf(buff, "%s:", FieldName.c_str());
	
	len += WriteString(buff + len, size - len, "BeginString", BeginString);
	len += WriteString(buff + len, size - len, "BodyLength", BodyLength);
	len += WriteString(buff + len, size - len, "MsgType", MsgType);
	len += WriteString(buff + len, size - len, "MsgSeqNum", MsgSeqNum);
	len += WriteString(buff + len, size - len, "PossDupFlag", PossDupFlag);
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
int FixRspHeader::ToStream(char* buff)
{
	int len = 0;
	len += WriteStream(buff + len, 35, MsgType);
	len += WriteStream(buff + len, 34, MsgSeqNum);
	len += WriteStream(buff + len, 43, PossDupFlag);
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
FixMessage* FixRspHeader::GetFixMessage()
{
	m_FixMessage->SetItem(8, BeginString);
	m_FixMessage->SetItem(9, BodyLength);
	m_FixMessage->SetItem(35, MsgType);
	m_FixMessage->SetItem(34, MsgSeqNum);
	m_FixMessage->SetItem(43, PossDupFlag);
	m_FixMessage->SetItem(49, SenderCompID);
	m_FixMessage->SetItem(50, SenderSubID);
	m_FixMessage->SetItem(52, SendingTime);
	m_FixMessage->SetItem(56, TargetCompID);
	m_FixMessage->SetItem(57, TargetSubID);
	m_FixMessage->SetItem(122, OrigSendingTime);
	m_FixMessage->SetItem(143, TargetLocationID);
	m_FixMessage->SetItem(369, LastMsgSeqNumProcessed);
	return m_FixMessage;
}
string FixRspHeader::CreateSql()
{
	return "BeginString char(32), BodyLength char(32), MsgType char(32), MsgSeqNum char(32) PRIMARY KEY NOT NULL, PossDupFlag char(32), SenderCompID char(32), SenderSubID char(32), SendingTime char(32), TargetCompID char(32), TargetSubID char(32), OrigSendingTime char(32), TargetLocationID char(32), LastMsgSeqNumProcessed char(32), ";
}
string FixRspHeader::InsertSql()
{
	return BeginString + "\", \"" + BodyLength + "\", \"" + MsgType + "\", \"" + MsgSeqNum + "\", \"" + PossDupFlag + "\", \"" + SenderCompID + "\", \"" + SenderSubID + "\", \"" + SendingTime + "\", \"" + TargetCompID + "\", \"" + TargetSubID + "\", \"" + OrigSendingTime + "\", \"" + TargetLocationID + "\", \"" + LastMsgSeqNumProcessed;
}
int FixRspHeader::AddHeader(char* buff, int bodyLen)
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
void FixRspHeader::SetHeader(const string& senderCompID, const string& senderSubID, const string& targetCompID, const string& targetSubID)
{
	SenderCompID = senderCompID;
	SenderSubID = senderSubID;
	TargetCompID = targetCompID;
	TargetSubID = targetSubID;
}


FixTrailer::FixTrailer(FixMessage* fixMessage)
{
	if (!fixMessage)
		return;
	CheckSum = fixMessage->GetItem(10);
}
int FixTrailer::ToString(char* buff, int size)
{
	int len = 0;
	len += WriteString(buff + len, size - len, "CheckSum", CheckSum);
	return len;
}
void FixTrailer::GetFixMessage(FixMessage* fixMessage)
{
	fixMessage->SetItem(10, CheckSum);
}
int FixTrailer::AddTrailer(char* buff, int len)
{
	auto sum = CalculateSum((unsigned char*)buff, len);
	char temp[8];
	sprintf(temp, "%03d", sum);
	CheckSum = temp;

	_ASSERT(WriteStream(buff + len, 10, CheckSum) == TRAILER_LEN);
	return TRAILER_LEN;
}

FixReqLogonField::FixReqLogonField(FixMessage* fixMessage)
	:FixReqHeader("FixReqLogonField", "A", "admin", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
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
FixReqLogonField::FixReqLogonField(FixReqLogonField&& other) noexcept
	:FixReqHeader(std::move(other)), FixTrailer(other)
{
	HeartBtInt = std::move(other.HeartBtInt);
	ResetSeqNumFlag = std::move(other.ResetSeqNumFlag);
	ApplicationSystemName = std::move(other.ApplicationSystemName);
	ApplicationSystemVersion = std::move(other.ApplicationSystemVersion);
	ApplicationSystemVendor = std::move(other.ApplicationSystemVendor);
	EncodedTextLen = std::move(other.EncodedTextLen);
	EncodedText = std::move(other.EncodedText);
	EncryptedPasswordMethod = std::move(other.EncryptedPasswordMethod);
	EncryptedPasswordLen = std::move(other.EncryptedPasswordLen);
	EncryptedPassword = std::move(other.EncryptedPassword);
}
FixReqLogonField& FixReqLogonField::operator=(FixReqLogonField&& other) noexcept
{
	FixReqHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	HeartBtInt = std::move(other.HeartBtInt);
	ResetSeqNumFlag = std::move(other.ResetSeqNumFlag);
	ApplicationSystemName = std::move(other.ApplicationSystemName);
	ApplicationSystemVersion = std::move(other.ApplicationSystemVersion);
	ApplicationSystemVendor = std::move(other.ApplicationSystemVendor);
	EncodedTextLen = std::move(other.EncodedTextLen);
	EncodedText = std::move(other.EncodedText);
	EncryptedPasswordMethod = std::move(other.EncryptedPasswordMethod);
	EncryptedPasswordLen = std::move(other.EncryptedPasswordLen);
	EncryptedPassword = std::move(other.EncryptedPassword);

	return *this;
}
FixReqLogonField::~FixReqLogonField()
{
	
}
int FixReqLogonField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixReqHeader::ToString(buff + len, size - len);
	
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

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixReqLogonField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixReqHeader::ToStream(buff + len);
	
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

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixReqLogonField::GetFixMessage()
{
	FixReqHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(108, HeartBtInt);
	m_FixMessage->SetItem(141, ResetSeqNumFlag);
	m_FixMessage->SetItem(1603, ApplicationSystemName);
	m_FixMessage->SetItem(1604, ApplicationSystemVersion);
	m_FixMessage->SetItem(1605, ApplicationSystemVendor);
	m_FixMessage->SetItem(354, EncodedTextLen);
	m_FixMessage->SetItem(355, EncodedText);
	m_FixMessage->SetItem(1400, EncryptedPasswordMethod);
	m_FixMessage->SetItem(1401, EncryptedPasswordLen);
	m_FixMessage->SetItem(1402, EncryptedPassword);
	return m_FixMessage;
}
string FixReqLogonField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixReqLogon(" + FixReqHeader::CreateSql() + "HeartBtInt char(32), ResetSeqNumFlag char(32), ApplicationSystemName char(32), ApplicationSystemVersion char(32), ApplicationSystemVendor char(32), EncodedTextLen char(32), EncodedText char(128), EncryptedPasswordMethod char(32), EncryptedPasswordLen char(32), EncryptedPassword char(128));";
}
string FixReqLogonField::InsertSql()
{
	return "REPLACE INTO t_FixReqLogon VALUES(\"" + FixReqHeader::InsertSql() + "\", \"" + HeartBtInt + "\", \"" + ResetSeqNumFlag + "\", \"" + ApplicationSystemName + "\", \"" + ApplicationSystemVersion + "\", \"" + ApplicationSystemVendor + "\", \"" + EncodedTextLen + "\", \"" + EncodedText + "\", \"" + EncryptedPasswordMethod + "\", \"" + EncryptedPasswordLen + "\", \"" + EncryptedPassword + "\");";
}
int FixReqLogonField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	return 0;
}

FixReqLogoutField::FixReqLogoutField(FixMessage* fixMessage)
	:FixReqHeader("FixReqLogoutField", "5", "admin", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	Text = fixMessage->GetItem(58);
	NextExpectedMsgSeqNum = fixMessage->GetItem(789);
	SplitMsg = fixMessage->GetItem(9553);
}
FixReqLogoutField::FixReqLogoutField(FixReqLogoutField&& other) noexcept
	:FixReqHeader(std::move(other)), FixTrailer(other)
{
	Text = std::move(other.Text);
	NextExpectedMsgSeqNum = std::move(other.NextExpectedMsgSeqNum);
	SplitMsg = std::move(other.SplitMsg);
}
FixReqLogoutField& FixReqLogoutField::operator=(FixReqLogoutField&& other) noexcept
{
	FixReqHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	Text = std::move(other.Text);
	NextExpectedMsgSeqNum = std::move(other.NextExpectedMsgSeqNum);
	SplitMsg = std::move(other.SplitMsg);

	return *this;
}
FixReqLogoutField::~FixReqLogoutField()
{
	
}
int FixReqLogoutField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixReqHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "Text", Text);
	len += WriteString(buff + len, size - len, "NextExpectedMsgSeqNum", NextExpectedMsgSeqNum);
	len += WriteString(buff + len, size - len, "SplitMsg", SplitMsg);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixReqLogoutField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixReqHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 58, Text);
	len += WriteStream(buff + len, 789, NextExpectedMsgSeqNum);
	len += WriteStream(buff + len, 9553, SplitMsg);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixReqLogoutField::GetFixMessage()
{
	FixReqHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(58, Text);
	m_FixMessage->SetItem(789, NextExpectedMsgSeqNum);
	m_FixMessage->SetItem(9553, SplitMsg);
	return m_FixMessage;
}
string FixReqLogoutField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixReqLogout(" + FixReqHeader::CreateSql() + "Text char(255), NextExpectedMsgSeqNum char(32), SplitMsg char(32));";
}
string FixReqLogoutField::InsertSql()
{
	return "REPLACE INTO t_FixReqLogout VALUES(\"" + FixReqHeader::InsertSql() + "\", \"" + Text + "\", \"" + NextExpectedMsgSeqNum + "\", \"" + SplitMsg + "\");";
}
int FixReqLogoutField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	return 0;
}

FixReqHeartBeatField::FixReqHeartBeatField(FixMessage* fixMessage)
	:FixReqHeader("FixReqHeartBeatField", "0", "admin", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	TestReqID = fixMessage->GetItem(112);
	SplitMsg = fixMessage->GetItem(9553);
}
FixReqHeartBeatField::FixReqHeartBeatField(FixReqHeartBeatField&& other) noexcept
	:FixReqHeader(std::move(other)), FixTrailer(other)
{
	TestReqID = std::move(other.TestReqID);
	SplitMsg = std::move(other.SplitMsg);
}
FixReqHeartBeatField& FixReqHeartBeatField::operator=(FixReqHeartBeatField&& other) noexcept
{
	FixReqHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	TestReqID = std::move(other.TestReqID);
	SplitMsg = std::move(other.SplitMsg);

	return *this;
}
FixReqHeartBeatField::~FixReqHeartBeatField()
{
	
}
int FixReqHeartBeatField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixReqHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "TestReqID", TestReqID);
	len += WriteString(buff + len, size - len, "SplitMsg", SplitMsg);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixReqHeartBeatField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixReqHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 112, TestReqID);
	len += WriteStream(buff + len, 9553, SplitMsg);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixReqHeartBeatField::GetFixMessage()
{
	FixReqHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(112, TestReqID);
	m_FixMessage->SetItem(9553, SplitMsg);
	return m_FixMessage;
}
string FixReqHeartBeatField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixReqHeartBeat(" + FixReqHeader::CreateSql() + "TestReqID char(32), SplitMsg char(32));";
}
string FixReqHeartBeatField::InsertSql()
{
	return "REPLACE INTO t_FixReqHeartBeat VALUES(\"" + FixReqHeader::InsertSql() + "\", \"" + TestReqID + "\", \"" + SplitMsg + "\");";
}
int FixReqHeartBeatField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	return 0;
}

FixReqTestRequestField::FixReqTestRequestField(FixMessage* fixMessage)
	:FixReqHeader("FixReqTestRequestField", "1", "admin", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	TestReqID = fixMessage->GetItem(112);
}
FixReqTestRequestField::FixReqTestRequestField(FixReqTestRequestField&& other) noexcept
	:FixReqHeader(std::move(other)), FixTrailer(other)
{
	TestReqID = std::move(other.TestReqID);
}
FixReqTestRequestField& FixReqTestRequestField::operator=(FixReqTestRequestField&& other) noexcept
{
	FixReqHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	TestReqID = std::move(other.TestReqID);

	return *this;
}
FixReqTestRequestField::~FixReqTestRequestField()
{
	
}
int FixReqTestRequestField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixReqHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "TestReqID", TestReqID);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixReqTestRequestField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixReqHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 112, TestReqID);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixReqTestRequestField::GetFixMessage()
{
	FixReqHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(112, TestReqID);
	return m_FixMessage;
}
string FixReqTestRequestField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixReqTestRequest(" + FixReqHeader::CreateSql() + "TestReqID char(32));";
}
string FixReqTestRequestField::InsertSql()
{
	return "REPLACE INTO t_FixReqTestRequest VALUES(\"" + FixReqHeader::InsertSql() + "\", \"" + TestReqID + "\");";
}
int FixReqTestRequestField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	return 0;
}

FixReqResendRequestField::FixReqResendRequestField(FixMessage* fixMessage)
	:FixReqHeader("FixReqResendRequestField", "2", "admin", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	BeginSeqNo = fixMessage->GetItem(7);
	EndSeqNo = fixMessage->GetItem(16);
}
FixReqResendRequestField::FixReqResendRequestField(FixReqResendRequestField&& other) noexcept
	:FixReqHeader(std::move(other)), FixTrailer(other)
{
	BeginSeqNo = std::move(other.BeginSeqNo);
	EndSeqNo = std::move(other.EndSeqNo);
}
FixReqResendRequestField& FixReqResendRequestField::operator=(FixReqResendRequestField&& other) noexcept
{
	FixReqHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	BeginSeqNo = std::move(other.BeginSeqNo);
	EndSeqNo = std::move(other.EndSeqNo);

	return *this;
}
FixReqResendRequestField::~FixReqResendRequestField()
{
	
}
int FixReqResendRequestField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixReqHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "BeginSeqNo", BeginSeqNo);
	len += WriteString(buff + len, size - len, "EndSeqNo", EndSeqNo);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixReqResendRequestField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixReqHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 7, BeginSeqNo);
	len += WriteStream(buff + len, 16, EndSeqNo);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixReqResendRequestField::GetFixMessage()
{
	FixReqHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(7, BeginSeqNo);
	m_FixMessage->SetItem(16, EndSeqNo);
	return m_FixMessage;
}
string FixReqResendRequestField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixReqResendRequest(" + FixReqHeader::CreateSql() + "BeginSeqNo char(32), EndSeqNo char(32));";
}
string FixReqResendRequestField::InsertSql()
{
	return "REPLACE INTO t_FixReqResendRequest VALUES(\"" + FixReqHeader::InsertSql() + "\", \"" + BeginSeqNo + "\", \"" + EndSeqNo + "\");";
}
int FixReqResendRequestField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	return 0;
}

FixReqSequenceResetField::FixReqSequenceResetField(FixMessage* fixMessage)
	:FixReqHeader("FixReqSequenceResetField", "4", "admin", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	NewSeqNo = fixMessage->GetItem(36);
	GapFillFlag = fixMessage->GetItem(123);
}
FixReqSequenceResetField::FixReqSequenceResetField(FixReqSequenceResetField&& other) noexcept
	:FixReqHeader(std::move(other)), FixTrailer(other)
{
	NewSeqNo = std::move(other.NewSeqNo);
	GapFillFlag = std::move(other.GapFillFlag);
}
FixReqSequenceResetField& FixReqSequenceResetField::operator=(FixReqSequenceResetField&& other) noexcept
{
	FixReqHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	NewSeqNo = std::move(other.NewSeqNo);
	GapFillFlag = std::move(other.GapFillFlag);

	return *this;
}
FixReqSequenceResetField::~FixReqSequenceResetField()
{
	
}
int FixReqSequenceResetField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixReqHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "NewSeqNo", NewSeqNo);
	len += WriteString(buff + len, size - len, "GapFillFlag", GapFillFlag);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixReqSequenceResetField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixReqHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 36, NewSeqNo);
	len += WriteStream(buff + len, 123, GapFillFlag);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixReqSequenceResetField::GetFixMessage()
{
	FixReqHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(36, NewSeqNo);
	m_FixMessage->SetItem(123, GapFillFlag);
	return m_FixMessage;
}
string FixReqSequenceResetField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixReqSequenceReset(" + FixReqHeader::CreateSql() + "NewSeqNo char(32), GapFillFlag char(32));";
}
string FixReqSequenceResetField::InsertSql()
{
	return "REPLACE INTO t_FixReqSequenceReset VALUES(\"" + FixReqHeader::InsertSql() + "\", \"" + NewSeqNo + "\", \"" + GapFillFlag + "\");";
}
int FixReqSequenceResetField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	return 0;
}

FixReqNewOrderField::FixReqNewOrderField(FixMessage* fixMessage)
	:FixReqHeader("FixReqNewOrderField", "D", "app", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
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
FixReqNewOrderField::FixReqNewOrderField(FixReqNewOrderField&& other) noexcept
	:FixReqHeader(std::move(other)), FixTrailer(other)
{
	Account = std::move(other.Account);
	ClOrdID = std::move(other.ClOrdID);
	HandInst = std::move(other.HandInst);
	CustOrderHandlingInst = std::move(other.CustOrderHandlingInst);
	OrderQty = std::move(other.OrderQty);
	OrdType = std::move(other.OrdType);
	Price = std::move(other.Price);
	Side = std::move(other.Side);
	Symbol = std::move(other.Symbol);
	TimeInForce = std::move(other.TimeInForce);
	TransactTime = std::move(other.TransactTime);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	NoAllocs = std::move(other.NoAllocs);
	AllocAccount = std::move(other.AllocAccount);
	StopPx = std::move(other.StopPx);
	SecurityDesc = std::move(other.SecurityDesc);
	MinQty = std::move(other.MinQty);
	SecurityType = std::move(other.SecurityType);
	CustomerOrFirm = std::move(other.CustomerOrFirm);
	MaxShow = std::move(other.MaxShow);
	ExpireDate = std::move(other.ExpireDate);
	SelfMatchPreventionID = std::move(other.SelfMatchPreventionID);
	SelfMatchPreventionInstruction = std::move(other.SelfMatchPreventionInstruction);
	CtiCode = std::move(other.CtiCode);
	AvgPxGroupID = std::move(other.AvgPxGroupID);
	ClearingTradePriceType = std::move(other.ClearingTradePriceType);
	AvgPXIndicator = std::move(other.AvgPXIndicator);
	Memo = std::move(other.Memo);
	GiveUpFirm = std::move(other.GiveUpFirm);
	CmtaGiveupCD = std::move(other.CmtaGiveupCD);
	CorrelationClOrdID = std::move(other.CorrelationClOrdID);
}
FixReqNewOrderField& FixReqNewOrderField::operator=(FixReqNewOrderField&& other) noexcept
{
	FixReqHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	Account = std::move(other.Account);
	ClOrdID = std::move(other.ClOrdID);
	HandInst = std::move(other.HandInst);
	CustOrderHandlingInst = std::move(other.CustOrderHandlingInst);
	OrderQty = std::move(other.OrderQty);
	OrdType = std::move(other.OrdType);
	Price = std::move(other.Price);
	Side = std::move(other.Side);
	Symbol = std::move(other.Symbol);
	TimeInForce = std::move(other.TimeInForce);
	TransactTime = std::move(other.TransactTime);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	NoAllocs = std::move(other.NoAllocs);
	AllocAccount = std::move(other.AllocAccount);
	StopPx = std::move(other.StopPx);
	SecurityDesc = std::move(other.SecurityDesc);
	MinQty = std::move(other.MinQty);
	SecurityType = std::move(other.SecurityType);
	CustomerOrFirm = std::move(other.CustomerOrFirm);
	MaxShow = std::move(other.MaxShow);
	ExpireDate = std::move(other.ExpireDate);
	SelfMatchPreventionID = std::move(other.SelfMatchPreventionID);
	SelfMatchPreventionInstruction = std::move(other.SelfMatchPreventionInstruction);
	CtiCode = std::move(other.CtiCode);
	AvgPxGroupID = std::move(other.AvgPxGroupID);
	ClearingTradePriceType = std::move(other.ClearingTradePriceType);
	AvgPXIndicator = std::move(other.AvgPXIndicator);
	Memo = std::move(other.Memo);
	GiveUpFirm = std::move(other.GiveUpFirm);
	CmtaGiveupCD = std::move(other.CmtaGiveupCD);
	CorrelationClOrdID = std::move(other.CorrelationClOrdID);

	return *this;
}
FixReqNewOrderField::~FixReqNewOrderField()
{
	
}
int FixReqNewOrderField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixReqHeader::ToString(buff + len, size - len);
	
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

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixReqNewOrderField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixReqHeader::ToStream(buff + len);
	
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

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixReqNewOrderField::GetFixMessage()
{
	FixReqHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(1, Account);
	m_FixMessage->SetItem(11, ClOrdID);
	m_FixMessage->SetItem(21, HandInst);
	m_FixMessage->SetItem(1031, CustOrderHandlingInst);
	m_FixMessage->SetItem(38, OrderQty);
	m_FixMessage->SetItem(40, OrdType);
	m_FixMessage->SetItem(44, Price);
	m_FixMessage->SetItem(54, Side);
	m_FixMessage->SetItem(55, Symbol);
	m_FixMessage->SetItem(59, TimeInForce);
	m_FixMessage->SetItem(60, TransactTime);
	m_FixMessage->SetItem(1028, ManualOrderIndicator);
	m_FixMessage->SetItem(78, NoAllocs);
	m_FixMessage->SetItem(79, AllocAccount);
	m_FixMessage->SetItem(99, StopPx);
	m_FixMessage->SetItem(107, SecurityDesc);
	m_FixMessage->SetItem(110, MinQty);
	m_FixMessage->SetItem(167, SecurityType);
	m_FixMessage->SetItem(204, CustomerOrFirm);
	m_FixMessage->SetItem(210, MaxShow);
	m_FixMessage->SetItem(432, ExpireDate);
	m_FixMessage->SetItem(7928, SelfMatchPreventionID);
	m_FixMessage->SetItem(8000, SelfMatchPreventionInstruction);
	m_FixMessage->SetItem(9702, CtiCode);
	m_FixMessage->SetItem(1731, AvgPxGroupID);
	m_FixMessage->SetItem(1598, ClearingTradePriceType);
	m_FixMessage->SetItem(819, AvgPXIndicator);
	m_FixMessage->SetItem(5149, Memo);
	m_FixMessage->SetItem(9707, GiveUpFirm);
	m_FixMessage->SetItem(9708, CmtaGiveupCD);
	m_FixMessage->SetItem(9717, CorrelationClOrdID);
	return m_FixMessage;
}
string FixReqNewOrderField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixReqNewOrder(" + FixReqHeader::CreateSql() + "Account char(32), ClOrdID char(32), HandInst char(32), CustOrderHandlingInst char(32), OrderQty char(32), OrdType char(32), Price char(32), Side char(32), Symbol char(32), TimeInForce char(32), TransactTime char(32), ManualOrderIndicator char(32), NoAllocs char(32), AllocAccount char(32), StopPx char(32), SecurityDesc char(32), MinQty char(32), SecurityType char(32), CustomerOrFirm char(32), MaxShow char(32), ExpireDate char(32), SelfMatchPreventionID char(32), SelfMatchPreventionInstruction char(32), CtiCode char(32), AvgPxGroupID char(32), ClearingTradePriceType char(32), AvgPXIndicator char(32), Memo char(32), GiveUpFirm char(32), CmtaGiveupCD char(32), CorrelationClOrdID char(32));";
}
string FixReqNewOrderField::InsertSql()
{
	return "REPLACE INTO t_FixReqNewOrder VALUES(\"" + FixReqHeader::InsertSql() + "\", \"" + Account + "\", \"" + ClOrdID + "\", \"" + HandInst + "\", \"" + CustOrderHandlingInst + "\", \"" + OrderQty + "\", \"" + OrdType + "\", \"" + Price + "\", \"" + Side + "\", \"" + Symbol + "\", \"" + TimeInForce + "\", \"" + TransactTime + "\", \"" + ManualOrderIndicator + "\", \"" + NoAllocs + "\", \"" + AllocAccount + "\", \"" + StopPx + "\", \"" + SecurityDesc + "\", \"" + MinQty + "\", \"" + SecurityType + "\", \"" + CustomerOrFirm + "\", \"" + MaxShow + "\", \"" + ExpireDate + "\", \"" + SelfMatchPreventionID + "\", \"" + SelfMatchPreventionInstruction + "\", \"" + CtiCode + "\", \"" + AvgPxGroupID + "\", \"" + ClearingTradePriceType + "\", \"" + AvgPXIndicator + "\", \"" + Memo + "\", \"" + GiveUpFirm + "\", \"" + CmtaGiveupCD + "\", \"" + CorrelationClOrdID + "\");";
}
int FixReqNewOrderField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	FixMessage* fixMessage = FixMessage::Allocate();
	for (auto i = 0; i < colCount; i++)
	{
		fixMessage->SetItem(FixItems::GetInstance().GetItemKey(colNames[i]), colValues[i]);
	}
	((FixTableCallback*)callback)->InitReqMessage(new FixReqNewOrderField(fixMessage));
	return 0;
}

FixReqOrderCancelRequestField::FixReqOrderCancelRequestField(FixMessage* fixMessage)
	:FixReqHeader("FixReqOrderCancelRequestField", "F", "app", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	Account = fixMessage->GetItem(1);
	ClOrdID = fixMessage->GetItem(11);
	OrderID = fixMessage->GetItem(37);
	OrigClOrdID = fixMessage->GetItem(41);
	Side = fixMessage->GetItem(54);
	Symbol = fixMessage->GetItem(55);
	TransactTime = fixMessage->GetItem(60);
	ManualOrderIndicator = fixMessage->GetItem(1028);
	Memo = fixMessage->GetItem(5149);
	SecurityDesc = fixMessage->GetItem(107);
	SecurityType = fixMessage->GetItem(167);
	CorrelationClOrdID = fixMessage->GetItem(9717);
}
FixReqOrderCancelRequestField::FixReqOrderCancelRequestField(FixReqOrderCancelRequestField&& other) noexcept
	:FixReqHeader(std::move(other)), FixTrailer(other)
{
	Account = std::move(other.Account);
	ClOrdID = std::move(other.ClOrdID);
	OrderID = std::move(other.OrderID);
	OrigClOrdID = std::move(other.OrigClOrdID);
	Side = std::move(other.Side);
	Symbol = std::move(other.Symbol);
	TransactTime = std::move(other.TransactTime);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	Memo = std::move(other.Memo);
	SecurityDesc = std::move(other.SecurityDesc);
	SecurityType = std::move(other.SecurityType);
	CorrelationClOrdID = std::move(other.CorrelationClOrdID);
}
FixReqOrderCancelRequestField& FixReqOrderCancelRequestField::operator=(FixReqOrderCancelRequestField&& other) noexcept
{
	FixReqHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	Account = std::move(other.Account);
	ClOrdID = std::move(other.ClOrdID);
	OrderID = std::move(other.OrderID);
	OrigClOrdID = std::move(other.OrigClOrdID);
	Side = std::move(other.Side);
	Symbol = std::move(other.Symbol);
	TransactTime = std::move(other.TransactTime);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	Memo = std::move(other.Memo);
	SecurityDesc = std::move(other.SecurityDesc);
	SecurityType = std::move(other.SecurityType);
	CorrelationClOrdID = std::move(other.CorrelationClOrdID);

	return *this;
}
FixReqOrderCancelRequestField::~FixReqOrderCancelRequestField()
{
	
}
int FixReqOrderCancelRequestField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixReqHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "Account", Account);
	len += WriteString(buff + len, size - len, "ClOrdID", ClOrdID);
	len += WriteString(buff + len, size - len, "OrderID", OrderID);
	len += WriteString(buff + len, size - len, "OrigClOrdID", OrigClOrdID);
	len += WriteString(buff + len, size - len, "Side", Side);
	len += WriteString(buff + len, size - len, "Symbol", Symbol);
	len += WriteString(buff + len, size - len, "TransactTime", TransactTime);
	len += WriteString(buff + len, size - len, "ManualOrderIndicator", ManualOrderIndicator);
	len += WriteString(buff + len, size - len, "Memo", Memo);
	len += WriteString(buff + len, size - len, "SecurityDesc", SecurityDesc);
	len += WriteString(buff + len, size - len, "SecurityType", SecurityType);
	len += WriteString(buff + len, size - len, "CorrelationClOrdID", CorrelationClOrdID);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixReqOrderCancelRequestField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixReqHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 1, Account);
	len += WriteStream(buff + len, 11, ClOrdID);
	len += WriteStream(buff + len, 37, OrderID);
	len += WriteStream(buff + len, 41, OrigClOrdID);
	len += WriteStream(buff + len, 54, Side);
	len += WriteStream(buff + len, 55, Symbol);
	len += WriteStream(buff + len, 60, TransactTime);
	len += WriteStream(buff + len, 1028, ManualOrderIndicator);
	len += WriteStream(buff + len, 5149, Memo);
	len += WriteStream(buff + len, 107, SecurityDesc);
	len += WriteStream(buff + len, 167, SecurityType);
	len += WriteStream(buff + len, 9717, CorrelationClOrdID);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixReqOrderCancelRequestField::GetFixMessage()
{
	FixReqHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(1, Account);
	m_FixMessage->SetItem(11, ClOrdID);
	m_FixMessage->SetItem(37, OrderID);
	m_FixMessage->SetItem(41, OrigClOrdID);
	m_FixMessage->SetItem(54, Side);
	m_FixMessage->SetItem(55, Symbol);
	m_FixMessage->SetItem(60, TransactTime);
	m_FixMessage->SetItem(1028, ManualOrderIndicator);
	m_FixMessage->SetItem(5149, Memo);
	m_FixMessage->SetItem(107, SecurityDesc);
	m_FixMessage->SetItem(167, SecurityType);
	m_FixMessage->SetItem(9717, CorrelationClOrdID);
	return m_FixMessage;
}
string FixReqOrderCancelRequestField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixReqOrderCancelRequest(" + FixReqHeader::CreateSql() + "Account char(32), ClOrdID char(32), OrderID char(32), OrigClOrdID char(32), Side char(32), Symbol char(32), TransactTime char(32), ManualOrderIndicator char(32), Memo char(32), SecurityDesc char(32), SecurityType char(32), CorrelationClOrdID char(32));";
}
string FixReqOrderCancelRequestField::InsertSql()
{
	return "REPLACE INTO t_FixReqOrderCancelRequest VALUES(\"" + FixReqHeader::InsertSql() + "\", \"" + Account + "\", \"" + ClOrdID + "\", \"" + OrderID + "\", \"" + OrigClOrdID + "\", \"" + Side + "\", \"" + Symbol + "\", \"" + TransactTime + "\", \"" + ManualOrderIndicator + "\", \"" + Memo + "\", \"" + SecurityDesc + "\", \"" + SecurityType + "\", \"" + CorrelationClOrdID + "\");";
}
int FixReqOrderCancelRequestField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	FixMessage* fixMessage = FixMessage::Allocate();
	for (auto i = 0; i < colCount; i++)
	{
		fixMessage->SetItem(FixItems::GetInstance().GetItemKey(colNames[i]), colValues[i]);
	}
	((FixTableCallback*)callback)->InitReqMessage(new FixReqOrderCancelRequestField(fixMessage));
	return 0;
}

FixReqOrderCancelReplaceRequestField::FixReqOrderCancelReplaceRequestField(FixMessage* fixMessage)
	:FixReqHeader("FixReqOrderCancelReplaceRequestField", "G", "app", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	Account = fixMessage->GetItem(1);
	ClOrdID = fixMessage->GetItem(11);
	OrderID = fixMessage->GetItem(37);
	HandInst = fixMessage->GetItem(21);
	OrderQty = fixMessage->GetItem(38);
	CustOrderHandlingInst = fixMessage->GetItem(1031);
	OrdType = fixMessage->GetItem(40);
	OrigClOrdID = fixMessage->GetItem(41);
	Price = fixMessage->GetItem(44);
	Side = fixMessage->GetItem(54);
	Symbol = fixMessage->GetItem(55);
	Text = fixMessage->GetItem(58);
	TimeInForce = fixMessage->GetItem(59);
	ManualOrderIndicator = fixMessage->GetItem(1028);
	TransactTime = fixMessage->GetItem(60);
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
	CorrelationClOrdID = fixMessage->GetItem(9717);
	OFMOverride = fixMessage->GetItem(9768);
}
FixReqOrderCancelReplaceRequestField::FixReqOrderCancelReplaceRequestField(FixReqOrderCancelReplaceRequestField&& other) noexcept
	:FixReqHeader(std::move(other)), FixTrailer(other)
{
	Account = std::move(other.Account);
	ClOrdID = std::move(other.ClOrdID);
	OrderID = std::move(other.OrderID);
	HandInst = std::move(other.HandInst);
	OrderQty = std::move(other.OrderQty);
	CustOrderHandlingInst = std::move(other.CustOrderHandlingInst);
	OrdType = std::move(other.OrdType);
	OrigClOrdID = std::move(other.OrigClOrdID);
	Price = std::move(other.Price);
	Side = std::move(other.Side);
	Symbol = std::move(other.Symbol);
	Text = std::move(other.Text);
	TimeInForce = std::move(other.TimeInForce);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	TransactTime = std::move(other.TransactTime);
	NoAllocs = std::move(other.NoAllocs);
	AllocAccount = std::move(other.AllocAccount);
	StopPx = std::move(other.StopPx);
	SecurityDesc = std::move(other.SecurityDesc);
	MinQty = std::move(other.MinQty);
	SecurityType = std::move(other.SecurityType);
	CustomerOrFirm = std::move(other.CustomerOrFirm);
	MaxShow = std::move(other.MaxShow);
	ExpireDate = std::move(other.ExpireDate);
	SelfMatchPreventionID = std::move(other.SelfMatchPreventionID);
	SelfMatchPreventionInstruction = std::move(other.SelfMatchPreventionInstruction);
	CtiCode = std::move(other.CtiCode);
	AvgPxGroupID = std::move(other.AvgPxGroupID);
	ClearingTradePriceType = std::move(other.ClearingTradePriceType);
	AvgPXIndicator = std::move(other.AvgPXIndicator);
	Memo = std::move(other.Memo);
	CorrelationClOrdID = std::move(other.CorrelationClOrdID);
	OFMOverride = std::move(other.OFMOverride);
}
FixReqOrderCancelReplaceRequestField& FixReqOrderCancelReplaceRequestField::operator=(FixReqOrderCancelReplaceRequestField&& other) noexcept
{
	FixReqHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	Account = std::move(other.Account);
	ClOrdID = std::move(other.ClOrdID);
	OrderID = std::move(other.OrderID);
	HandInst = std::move(other.HandInst);
	OrderQty = std::move(other.OrderQty);
	CustOrderHandlingInst = std::move(other.CustOrderHandlingInst);
	OrdType = std::move(other.OrdType);
	OrigClOrdID = std::move(other.OrigClOrdID);
	Price = std::move(other.Price);
	Side = std::move(other.Side);
	Symbol = std::move(other.Symbol);
	Text = std::move(other.Text);
	TimeInForce = std::move(other.TimeInForce);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	TransactTime = std::move(other.TransactTime);
	NoAllocs = std::move(other.NoAllocs);
	AllocAccount = std::move(other.AllocAccount);
	StopPx = std::move(other.StopPx);
	SecurityDesc = std::move(other.SecurityDesc);
	MinQty = std::move(other.MinQty);
	SecurityType = std::move(other.SecurityType);
	CustomerOrFirm = std::move(other.CustomerOrFirm);
	MaxShow = std::move(other.MaxShow);
	ExpireDate = std::move(other.ExpireDate);
	SelfMatchPreventionID = std::move(other.SelfMatchPreventionID);
	SelfMatchPreventionInstruction = std::move(other.SelfMatchPreventionInstruction);
	CtiCode = std::move(other.CtiCode);
	AvgPxGroupID = std::move(other.AvgPxGroupID);
	ClearingTradePriceType = std::move(other.ClearingTradePriceType);
	AvgPXIndicator = std::move(other.AvgPXIndicator);
	Memo = std::move(other.Memo);
	CorrelationClOrdID = std::move(other.CorrelationClOrdID);
	OFMOverride = std::move(other.OFMOverride);

	return *this;
}
FixReqOrderCancelReplaceRequestField::~FixReqOrderCancelReplaceRequestField()
{
	
}
int FixReqOrderCancelReplaceRequestField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixReqHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "Account", Account);
	len += WriteString(buff + len, size - len, "ClOrdID", ClOrdID);
	len += WriteString(buff + len, size - len, "OrderID", OrderID);
	len += WriteString(buff + len, size - len, "HandInst", HandInst);
	len += WriteString(buff + len, size - len, "OrderQty", OrderQty);
	len += WriteString(buff + len, size - len, "CustOrderHandlingInst", CustOrderHandlingInst);
	len += WriteString(buff + len, size - len, "OrdType", OrdType);
	len += WriteString(buff + len, size - len, "OrigClOrdID", OrigClOrdID);
	len += WriteString(buff + len, size - len, "Price", Price);
	len += WriteString(buff + len, size - len, "Side", Side);
	len += WriteString(buff + len, size - len, "Symbol", Symbol);
	len += WriteString(buff + len, size - len, "Text", Text);
	len += WriteString(buff + len, size - len, "TimeInForce", TimeInForce);
	len += WriteString(buff + len, size - len, "ManualOrderIndicator", ManualOrderIndicator);
	len += WriteString(buff + len, size - len, "TransactTime", TransactTime);
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
	len += WriteString(buff + len, size - len, "CorrelationClOrdID", CorrelationClOrdID);
	len += WriteString(buff + len, size - len, "OFMOverride", OFMOverride);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixReqOrderCancelReplaceRequestField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixReqHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 1, Account);
	len += WriteStream(buff + len, 11, ClOrdID);
	len += WriteStream(buff + len, 37, OrderID);
	len += WriteStream(buff + len, 21, HandInst);
	len += WriteStream(buff + len, 38, OrderQty);
	len += WriteStream(buff + len, 1031, CustOrderHandlingInst);
	len += WriteStream(buff + len, 40, OrdType);
	len += WriteStream(buff + len, 41, OrigClOrdID);
	len += WriteStream(buff + len, 44, Price);
	len += WriteStream(buff + len, 54, Side);
	len += WriteStream(buff + len, 55, Symbol);
	len += WriteStream(buff + len, 58, Text);
	len += WriteStream(buff + len, 59, TimeInForce);
	len += WriteStream(buff + len, 1028, ManualOrderIndicator);
	len += WriteStream(buff + len, 60, TransactTime);
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
	len += WriteStream(buff + len, 9717, CorrelationClOrdID);
	len += WriteStream(buff + len, 9768, OFMOverride);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixReqOrderCancelReplaceRequestField::GetFixMessage()
{
	FixReqHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(1, Account);
	m_FixMessage->SetItem(11, ClOrdID);
	m_FixMessage->SetItem(37, OrderID);
	m_FixMessage->SetItem(21, HandInst);
	m_FixMessage->SetItem(38, OrderQty);
	m_FixMessage->SetItem(1031, CustOrderHandlingInst);
	m_FixMessage->SetItem(40, OrdType);
	m_FixMessage->SetItem(41, OrigClOrdID);
	m_FixMessage->SetItem(44, Price);
	m_FixMessage->SetItem(54, Side);
	m_FixMessage->SetItem(55, Symbol);
	m_FixMessage->SetItem(58, Text);
	m_FixMessage->SetItem(59, TimeInForce);
	m_FixMessage->SetItem(1028, ManualOrderIndicator);
	m_FixMessage->SetItem(60, TransactTime);
	m_FixMessage->SetItem(78, NoAllocs);
	m_FixMessage->SetItem(79, AllocAccount);
	m_FixMessage->SetItem(99, StopPx);
	m_FixMessage->SetItem(107, SecurityDesc);
	m_FixMessage->SetItem(110, MinQty);
	m_FixMessage->SetItem(167, SecurityType);
	m_FixMessage->SetItem(204, CustomerOrFirm);
	m_FixMessage->SetItem(210, MaxShow);
	m_FixMessage->SetItem(432, ExpireDate);
	m_FixMessage->SetItem(7928, SelfMatchPreventionID);
	m_FixMessage->SetItem(8000, SelfMatchPreventionInstruction);
	m_FixMessage->SetItem(9702, CtiCode);
	m_FixMessage->SetItem(1731, AvgPxGroupID);
	m_FixMessage->SetItem(1598, ClearingTradePriceType);
	m_FixMessage->SetItem(819, AvgPXIndicator);
	m_FixMessage->SetItem(5149, Memo);
	m_FixMessage->SetItem(9717, CorrelationClOrdID);
	m_FixMessage->SetItem(9768, OFMOverride);
	return m_FixMessage;
}
string FixReqOrderCancelReplaceRequestField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixReqOrderCancelReplaceRequest(" + FixReqHeader::CreateSql() + "Account char(32), ClOrdID char(32), OrderID char(32), HandInst char(32), OrderQty char(32), CustOrderHandlingInst char(32), OrdType char(32), OrigClOrdID char(32), Price char(32), Side char(32), Symbol char(32), Text char(255), TimeInForce char(32), ManualOrderIndicator char(32), TransactTime char(32), NoAllocs char(32), AllocAccount char(32), StopPx char(32), SecurityDesc char(32), MinQty char(32), SecurityType char(32), CustomerOrFirm char(32), MaxShow char(32), ExpireDate char(32), SelfMatchPreventionID char(32), SelfMatchPreventionInstruction char(32), CtiCode char(32), AvgPxGroupID char(32), ClearingTradePriceType char(32), AvgPXIndicator char(32), Memo char(32), CorrelationClOrdID char(32), OFMOverride char(32));";
}
string FixReqOrderCancelReplaceRequestField::InsertSql()
{
	return "REPLACE INTO t_FixReqOrderCancelReplaceRequest VALUES(\"" + FixReqHeader::InsertSql() + "\", \"" + Account + "\", \"" + ClOrdID + "\", \"" + OrderID + "\", \"" + HandInst + "\", \"" + OrderQty + "\", \"" + CustOrderHandlingInst + "\", \"" + OrdType + "\", \"" + OrigClOrdID + "\", \"" + Price + "\", \"" + Side + "\", \"" + Symbol + "\", \"" + Text + "\", \"" + TimeInForce + "\", \"" + ManualOrderIndicator + "\", \"" + TransactTime + "\", \"" + NoAllocs + "\", \"" + AllocAccount + "\", \"" + StopPx + "\", \"" + SecurityDesc + "\", \"" + MinQty + "\", \"" + SecurityType + "\", \"" + CustomerOrFirm + "\", \"" + MaxShow + "\", \"" + ExpireDate + "\", \"" + SelfMatchPreventionID + "\", \"" + SelfMatchPreventionInstruction + "\", \"" + CtiCode + "\", \"" + AvgPxGroupID + "\", \"" + ClearingTradePriceType + "\", \"" + AvgPXIndicator + "\", \"" + Memo + "\", \"" + CorrelationClOrdID + "\", \"" + OFMOverride + "\");";
}
int FixReqOrderCancelReplaceRequestField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	FixMessage* fixMessage = FixMessage::Allocate();
	for (auto i = 0; i < colCount; i++)
	{
		fixMessage->SetItem(FixItems::GetInstance().GetItemKey(colNames[i]), colValues[i]);
	}
	((FixTableCallback*)callback)->InitReqMessage(new FixReqOrderCancelReplaceRequestField(fixMessage));
	return 0;
}

FixReqOrderStatusRequestField::FixReqOrderStatusRequestField(FixMessage* fixMessage)
	:FixReqHeader("FixReqOrderStatusRequestField", "H", "app", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	ClOrdID = fixMessage->GetItem(11);
	OrderID = fixMessage->GetItem(37);
	Side = fixMessage->GetItem(54);
	Symbol = fixMessage->GetItem(55);
	TransactTime = fixMessage->GetItem(60);
	ManualOrderIndicator = fixMessage->GetItem(1028);
	SecurityDesc = fixMessage->GetItem(107);
	SecurityType = fixMessage->GetItem(167);
	CorrelationClOrdID = fixMessage->GetItem(9717);
}
FixReqOrderStatusRequestField::FixReqOrderStatusRequestField(FixReqOrderStatusRequestField&& other) noexcept
	:FixReqHeader(std::move(other)), FixTrailer(other)
{
	ClOrdID = std::move(other.ClOrdID);
	OrderID = std::move(other.OrderID);
	Side = std::move(other.Side);
	Symbol = std::move(other.Symbol);
	TransactTime = std::move(other.TransactTime);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	SecurityDesc = std::move(other.SecurityDesc);
	SecurityType = std::move(other.SecurityType);
	CorrelationClOrdID = std::move(other.CorrelationClOrdID);
}
FixReqOrderStatusRequestField& FixReqOrderStatusRequestField::operator=(FixReqOrderStatusRequestField&& other) noexcept
{
	FixReqHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	ClOrdID = std::move(other.ClOrdID);
	OrderID = std::move(other.OrderID);
	Side = std::move(other.Side);
	Symbol = std::move(other.Symbol);
	TransactTime = std::move(other.TransactTime);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	SecurityDesc = std::move(other.SecurityDesc);
	SecurityType = std::move(other.SecurityType);
	CorrelationClOrdID = std::move(other.CorrelationClOrdID);

	return *this;
}
FixReqOrderStatusRequestField::~FixReqOrderStatusRequestField()
{
	
}
int FixReqOrderStatusRequestField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixReqHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "ClOrdID", ClOrdID);
	len += WriteString(buff + len, size - len, "OrderID", OrderID);
	len += WriteString(buff + len, size - len, "Side", Side);
	len += WriteString(buff + len, size - len, "Symbol", Symbol);
	len += WriteString(buff + len, size - len, "TransactTime", TransactTime);
	len += WriteString(buff + len, size - len, "ManualOrderIndicator", ManualOrderIndicator);
	len += WriteString(buff + len, size - len, "SecurityDesc", SecurityDesc);
	len += WriteString(buff + len, size - len, "SecurityType", SecurityType);
	len += WriteString(buff + len, size - len, "CorrelationClOrdID", CorrelationClOrdID);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixReqOrderStatusRequestField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixReqHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 11, ClOrdID);
	len += WriteStream(buff + len, 37, OrderID);
	len += WriteStream(buff + len, 54, Side);
	len += WriteStream(buff + len, 55, Symbol);
	len += WriteStream(buff + len, 60, TransactTime);
	len += WriteStream(buff + len, 1028, ManualOrderIndicator);
	len += WriteStream(buff + len, 107, SecurityDesc);
	len += WriteStream(buff + len, 167, SecurityType);
	len += WriteStream(buff + len, 9717, CorrelationClOrdID);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixReqOrderStatusRequestField::GetFixMessage()
{
	FixReqHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(11, ClOrdID);
	m_FixMessage->SetItem(37, OrderID);
	m_FixMessage->SetItem(54, Side);
	m_FixMessage->SetItem(55, Symbol);
	m_FixMessage->SetItem(60, TransactTime);
	m_FixMessage->SetItem(1028, ManualOrderIndicator);
	m_FixMessage->SetItem(107, SecurityDesc);
	m_FixMessage->SetItem(167, SecurityType);
	m_FixMessage->SetItem(9717, CorrelationClOrdID);
	return m_FixMessage;
}
string FixReqOrderStatusRequestField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixReqOrderStatusRequest(" + FixReqHeader::CreateSql() + "ClOrdID char(32), OrderID char(32), Side char(32), Symbol char(32), TransactTime char(32), ManualOrderIndicator char(32), SecurityDesc char(32), SecurityType char(32), CorrelationClOrdID char(32));";
}
string FixReqOrderStatusRequestField::InsertSql()
{
	return "REPLACE INTO t_FixReqOrderStatusRequest VALUES(\"" + FixReqHeader::InsertSql() + "\", \"" + ClOrdID + "\", \"" + OrderID + "\", \"" + Side + "\", \"" + Symbol + "\", \"" + TransactTime + "\", \"" + ManualOrderIndicator + "\", \"" + SecurityDesc + "\", \"" + SecurityType + "\", \"" + CorrelationClOrdID + "\");";
}
int FixReqOrderStatusRequestField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	FixMessage* fixMessage = FixMessage::Allocate();
	for (auto i = 0; i < colCount; i++)
	{
		fixMessage->SetItem(FixItems::GetInstance().GetItemKey(colNames[i]), colValues[i]);
	}
	((FixTableCallback*)callback)->InitReqMessage(new FixReqOrderStatusRequestField(fixMessage));
	return 0;
}


FixRspLogonField::FixRspLogonField(FixMessage* fixMessage)
	:FixRspHeader("FixRspLogonField", "A", "admin", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	HeartBtInt = fixMessage->GetItem(108);
	ResetSeqNumFlag = fixMessage->GetItem(141);
	ApplicationSystemName = fixMessage->GetItem(1603);
	ApplicationSystemVersion = fixMessage->GetItem(1604);
	ApplicationSystemVendor = fixMessage->GetItem(1605);
	SplitMsg = fixMessage->GetItem(9553);
}
FixRspLogonField::FixRspLogonField(FixRspLogonField&& other) noexcept
	:FixRspHeader(std::move(other)), FixTrailer(other)
{
	HeartBtInt = std::move(other.HeartBtInt);
	ResetSeqNumFlag = std::move(other.ResetSeqNumFlag);
	ApplicationSystemName = std::move(other.ApplicationSystemName);
	ApplicationSystemVersion = std::move(other.ApplicationSystemVersion);
	ApplicationSystemVendor = std::move(other.ApplicationSystemVendor);
	SplitMsg = std::move(other.SplitMsg);
}
FixRspLogonField& FixRspLogonField::operator=(FixRspLogonField&& other) noexcept
{
	FixRspHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	
	HeartBtInt = std::move(other.HeartBtInt);
	ResetSeqNumFlag = std::move(other.ResetSeqNumFlag);
	ApplicationSystemName = std::move(other.ApplicationSystemName);
	ApplicationSystemVersion = std::move(other.ApplicationSystemVersion);
	ApplicationSystemVendor = std::move(other.ApplicationSystemVendor);
	SplitMsg = std::move(other.SplitMsg);

	return *this;
}
FixRspLogonField::~FixRspLogonField()
{
	
}
int FixRspLogonField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixRspHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "HeartBtInt", HeartBtInt);
	len += WriteString(buff + len, size - len, "ResetSeqNumFlag", ResetSeqNumFlag);
	len += WriteString(buff + len, size - len, "ApplicationSystemName", ApplicationSystemName);
	len += WriteString(buff + len, size - len, "ApplicationSystemVersion", ApplicationSystemVersion);
	len += WriteString(buff + len, size - len, "ApplicationSystemVendor", ApplicationSystemVendor);
	len += WriteString(buff + len, size - len, "SplitMsg", SplitMsg);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixRspLogonField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixRspHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 108, HeartBtInt);
	len += WriteStream(buff + len, 141, ResetSeqNumFlag);
	len += WriteStream(buff + len, 1603, ApplicationSystemName);
	len += WriteStream(buff + len, 1604, ApplicationSystemVersion);
	len += WriteStream(buff + len, 1605, ApplicationSystemVendor);
	len += WriteStream(buff + len, 9553, SplitMsg);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixRspLogonField::GetFixMessage()
{
	FixRspHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(108, HeartBtInt);
	m_FixMessage->SetItem(141, ResetSeqNumFlag);
	m_FixMessage->SetItem(1603, ApplicationSystemName);
	m_FixMessage->SetItem(1604, ApplicationSystemVersion);
	m_FixMessage->SetItem(1605, ApplicationSystemVendor);
	m_FixMessage->SetItem(9553, SplitMsg);
	return m_FixMessage;
}
string FixRspLogonField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixRspLogon(" + FixRspHeader::CreateSql() + "HeartBtInt char(32), ResetSeqNumFlag char(32), ApplicationSystemName char(32), ApplicationSystemVersion char(32), ApplicationSystemVendor char(32), SplitMsg char(32));";
}
string FixRspLogonField::InsertSql()
{
	return "REPLACE INTO t_FixRspLogon VALUES(\"" + FixRspHeader::InsertSql() + "\", \"" + HeartBtInt + "\", \"" + ResetSeqNumFlag + "\", \"" + ApplicationSystemName + "\", \"" + ApplicationSystemVersion + "\", \"" + ApplicationSystemVendor + "\", \"" + SplitMsg + "\");";
}
int FixRspLogonField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	return 0;
}

FixRspLogoutField::FixRspLogoutField(FixMessage* fixMessage)
	:FixRspHeader("FixRspLogoutField", "5", "admin", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	Text = fixMessage->GetItem(58);
	NextExpectedMsgSeqNum = fixMessage->GetItem(789);
	SplitMsg = fixMessage->GetItem(9553);
}
FixRspLogoutField::FixRspLogoutField(FixRspLogoutField&& other) noexcept
	:FixRspHeader(std::move(other)), FixTrailer(other)
{
	Text = std::move(other.Text);
	NextExpectedMsgSeqNum = std::move(other.NextExpectedMsgSeqNum);
	SplitMsg = std::move(other.SplitMsg);
}
FixRspLogoutField& FixRspLogoutField::operator=(FixRspLogoutField&& other) noexcept
{
	FixRspHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	
	Text = std::move(other.Text);
	NextExpectedMsgSeqNum = std::move(other.NextExpectedMsgSeqNum);
	SplitMsg = std::move(other.SplitMsg);

	return *this;
}
FixRspLogoutField::~FixRspLogoutField()
{
	
}
int FixRspLogoutField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixRspHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "Text", Text);
	len += WriteString(buff + len, size - len, "NextExpectedMsgSeqNum", NextExpectedMsgSeqNum);
	len += WriteString(buff + len, size - len, "SplitMsg", SplitMsg);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixRspLogoutField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixRspHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 58, Text);
	len += WriteStream(buff + len, 789, NextExpectedMsgSeqNum);
	len += WriteStream(buff + len, 9553, SplitMsg);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixRspLogoutField::GetFixMessage()
{
	FixRspHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(58, Text);
	m_FixMessage->SetItem(789, NextExpectedMsgSeqNum);
	m_FixMessage->SetItem(9553, SplitMsg);
	return m_FixMessage;
}
string FixRspLogoutField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixRspLogout(" + FixRspHeader::CreateSql() + "Text char(255), NextExpectedMsgSeqNum char(32), SplitMsg char(32));";
}
string FixRspLogoutField::InsertSql()
{
	return "REPLACE INTO t_FixRspLogout VALUES(\"" + FixRspHeader::InsertSql() + "\", \"" + Text + "\", \"" + NextExpectedMsgSeqNum + "\", \"" + SplitMsg + "\");";
}
int FixRspLogoutField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	return 0;
}

FixRspHeartBeatField::FixRspHeartBeatField(FixMessage* fixMessage)
	:FixRspHeader("FixRspHeartBeatField", "0", "admin", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	TestReqID = fixMessage->GetItem(112);
	SplitMsg = fixMessage->GetItem(9553);
}
FixRspHeartBeatField::FixRspHeartBeatField(FixRspHeartBeatField&& other) noexcept
	:FixRspHeader(std::move(other)), FixTrailer(other)
{
	TestReqID = std::move(other.TestReqID);
	SplitMsg = std::move(other.SplitMsg);
}
FixRspHeartBeatField& FixRspHeartBeatField::operator=(FixRspHeartBeatField&& other) noexcept
{
	FixRspHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	
	TestReqID = std::move(other.TestReqID);
	SplitMsg = std::move(other.SplitMsg);

	return *this;
}
FixRspHeartBeatField::~FixRspHeartBeatField()
{
	
}
int FixRspHeartBeatField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixRspHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "TestReqID", TestReqID);
	len += WriteString(buff + len, size - len, "SplitMsg", SplitMsg);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixRspHeartBeatField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixRspHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 112, TestReqID);
	len += WriteStream(buff + len, 9553, SplitMsg);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixRspHeartBeatField::GetFixMessage()
{
	FixRspHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(112, TestReqID);
	m_FixMessage->SetItem(9553, SplitMsg);
	return m_FixMessage;
}
string FixRspHeartBeatField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixRspHeartBeat(" + FixRspHeader::CreateSql() + "TestReqID char(32), SplitMsg char(32));";
}
string FixRspHeartBeatField::InsertSql()
{
	return "REPLACE INTO t_FixRspHeartBeat VALUES(\"" + FixRspHeader::InsertSql() + "\", \"" + TestReqID + "\", \"" + SplitMsg + "\");";
}
int FixRspHeartBeatField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	return 0;
}

FixRspTestRequestField::FixRspTestRequestField(FixMessage* fixMessage)
	:FixRspHeader("FixRspTestRequestField", "1", "admin", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	TestReqID = fixMessage->GetItem(112);
}
FixRspTestRequestField::FixRspTestRequestField(FixRspTestRequestField&& other) noexcept
	:FixRspHeader(std::move(other)), FixTrailer(other)
{
	TestReqID = std::move(other.TestReqID);
}
FixRspTestRequestField& FixRspTestRequestField::operator=(FixRspTestRequestField&& other) noexcept
{
	FixRspHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	
	TestReqID = std::move(other.TestReqID);

	return *this;
}
FixRspTestRequestField::~FixRspTestRequestField()
{
	
}
int FixRspTestRequestField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixRspHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "TestReqID", TestReqID);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixRspTestRequestField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixRspHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 112, TestReqID);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixRspTestRequestField::GetFixMessage()
{
	FixRspHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(112, TestReqID);
	return m_FixMessage;
}
string FixRspTestRequestField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixRspTestRequest(" + FixRspHeader::CreateSql() + "TestReqID char(32));";
}
string FixRspTestRequestField::InsertSql()
{
	return "REPLACE INTO t_FixRspTestRequest VALUES(\"" + FixRspHeader::InsertSql() + "\", \"" + TestReqID + "\");";
}
int FixRspTestRequestField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	return 0;
}

FixRspResendRequestField::FixRspResendRequestField(FixMessage* fixMessage)
	:FixRspHeader("FixRspResendRequestField", "2", "admin", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	BeginSeqNo = fixMessage->GetItem(7);
	EndSeqNo = fixMessage->GetItem(16);
}
FixRspResendRequestField::FixRspResendRequestField(FixRspResendRequestField&& other) noexcept
	:FixRspHeader(std::move(other)), FixTrailer(other)
{
	BeginSeqNo = std::move(other.BeginSeqNo);
	EndSeqNo = std::move(other.EndSeqNo);
}
FixRspResendRequestField& FixRspResendRequestField::operator=(FixRspResendRequestField&& other) noexcept
{
	FixRspHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	
	BeginSeqNo = std::move(other.BeginSeqNo);
	EndSeqNo = std::move(other.EndSeqNo);

	return *this;
}
FixRspResendRequestField::~FixRspResendRequestField()
{
	
}
int FixRspResendRequestField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixRspHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "BeginSeqNo", BeginSeqNo);
	len += WriteString(buff + len, size - len, "EndSeqNo", EndSeqNo);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixRspResendRequestField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixRspHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 7, BeginSeqNo);
	len += WriteStream(buff + len, 16, EndSeqNo);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixRspResendRequestField::GetFixMessage()
{
	FixRspHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(7, BeginSeqNo);
	m_FixMessage->SetItem(16, EndSeqNo);
	return m_FixMessage;
}
string FixRspResendRequestField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixRspResendRequest(" + FixRspHeader::CreateSql() + "BeginSeqNo char(32), EndSeqNo char(32));";
}
string FixRspResendRequestField::InsertSql()
{
	return "REPLACE INTO t_FixRspResendRequest VALUES(\"" + FixRspHeader::InsertSql() + "\", \"" + BeginSeqNo + "\", \"" + EndSeqNo + "\");";
}
int FixRspResendRequestField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	return 0;
}

FixRspSessionLevelRejectField::FixRspSessionLevelRejectField(FixMessage* fixMessage)
	:FixRspHeader("FixRspSessionLevelRejectField", "3", "admin", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	RefSeqNum = fixMessage->GetItem(45);
	Text = fixMessage->GetItem(58);
	RefTagID = fixMessage->GetItem(371);
	SessionRejectReason = fixMessage->GetItem(373);
	ManualOrderIndicator = fixMessage->GetItem(1028);
	SplitMsg = fixMessage->GetItem(9553);
}
FixRspSessionLevelRejectField::FixRspSessionLevelRejectField(FixRspSessionLevelRejectField&& other) noexcept
	:FixRspHeader(std::move(other)), FixTrailer(other)
{
	RefSeqNum = std::move(other.RefSeqNum);
	Text = std::move(other.Text);
	RefTagID = std::move(other.RefTagID);
	SessionRejectReason = std::move(other.SessionRejectReason);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	SplitMsg = std::move(other.SplitMsg);
}
FixRspSessionLevelRejectField& FixRspSessionLevelRejectField::operator=(FixRspSessionLevelRejectField&& other) noexcept
{
	FixRspHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	
	RefSeqNum = std::move(other.RefSeqNum);
	Text = std::move(other.Text);
	RefTagID = std::move(other.RefTagID);
	SessionRejectReason = std::move(other.SessionRejectReason);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	SplitMsg = std::move(other.SplitMsg);

	return *this;
}
FixRspSessionLevelRejectField::~FixRspSessionLevelRejectField()
{
	
}
int FixRspSessionLevelRejectField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixRspHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "RefSeqNum", RefSeqNum);
	len += WriteString(buff + len, size - len, "Text", Text);
	len += WriteString(buff + len, size - len, "RefTagID", RefTagID);
	len += WriteString(buff + len, size - len, "SessionRejectReason", SessionRejectReason);
	len += WriteString(buff + len, size - len, "ManualOrderIndicator", ManualOrderIndicator);
	len += WriteString(buff + len, size - len, "SplitMsg", SplitMsg);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixRspSessionLevelRejectField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixRspHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 45, RefSeqNum);
	len += WriteStream(buff + len, 58, Text);
	len += WriteStream(buff + len, 371, RefTagID);
	len += WriteStream(buff + len, 373, SessionRejectReason);
	len += WriteStream(buff + len, 1028, ManualOrderIndicator);
	len += WriteStream(buff + len, 9553, SplitMsg);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixRspSessionLevelRejectField::GetFixMessage()
{
	FixRspHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(45, RefSeqNum);
	m_FixMessage->SetItem(58, Text);
	m_FixMessage->SetItem(371, RefTagID);
	m_FixMessage->SetItem(373, SessionRejectReason);
	m_FixMessage->SetItem(1028, ManualOrderIndicator);
	m_FixMessage->SetItem(9553, SplitMsg);
	return m_FixMessage;
}
string FixRspSessionLevelRejectField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixRspSessionLevelReject(" + FixRspHeader::CreateSql() + "RefSeqNum char(32), Text char(255), RefTagID char(32), SessionRejectReason char(32), ManualOrderIndicator char(32), SplitMsg char(32));";
}
string FixRspSessionLevelRejectField::InsertSql()
{
	return "REPLACE INTO t_FixRspSessionLevelReject VALUES(\"" + FixRspHeader::InsertSql() + "\", \"" + RefSeqNum + "\", \"" + Text + "\", \"" + RefTagID + "\", \"" + SessionRejectReason + "\", \"" + ManualOrderIndicator + "\", \"" + SplitMsg + "\");";
}
int FixRspSessionLevelRejectField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	return 0;
}

FixRspSequenceResetField::FixRspSequenceResetField(FixMessage* fixMessage)
	:FixRspHeader("FixRspSequenceResetField", "4", "admin", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	NewSeqNo = fixMessage->GetItem(36);
	GapFillFlag = fixMessage->GetItem(123);
}
FixRspSequenceResetField::FixRspSequenceResetField(FixRspSequenceResetField&& other) noexcept
	:FixRspHeader(std::move(other)), FixTrailer(other)
{
	NewSeqNo = std::move(other.NewSeqNo);
	GapFillFlag = std::move(other.GapFillFlag);
}
FixRspSequenceResetField& FixRspSequenceResetField::operator=(FixRspSequenceResetField&& other) noexcept
{
	FixRspHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	
	NewSeqNo = std::move(other.NewSeqNo);
	GapFillFlag = std::move(other.GapFillFlag);

	return *this;
}
FixRspSequenceResetField::~FixRspSequenceResetField()
{
	
}
int FixRspSequenceResetField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixRspHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "NewSeqNo", NewSeqNo);
	len += WriteString(buff + len, size - len, "GapFillFlag", GapFillFlag);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixRspSequenceResetField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixRspHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 36, NewSeqNo);
	len += WriteStream(buff + len, 123, GapFillFlag);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixRspSequenceResetField::GetFixMessage()
{
	FixRspHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(36, NewSeqNo);
	m_FixMessage->SetItem(123, GapFillFlag);
	return m_FixMessage;
}
string FixRspSequenceResetField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixRspSequenceReset(" + FixRspHeader::CreateSql() + "NewSeqNo char(32), GapFillFlag char(32));";
}
string FixRspSequenceResetField::InsertSql()
{
	return "REPLACE INTO t_FixRspSequenceReset VALUES(\"" + FixRspHeader::InsertSql() + "\", \"" + NewSeqNo + "\", \"" + GapFillFlag + "\");";
}
int FixRspSequenceResetField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	return 0;
}

FixExecutionReportField::FixExecutionReportField(FixMessage* fixMessage)
	:FixRspHeader("FixExecutionReportField", "8", "app", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	Account = fixMessage->GetItem(1);
	AvgPx = fixMessage->GetItem(6);
	ClOrdID = fixMessage->GetItem(11);
	CumQty = fixMessage->GetItem(14);
	ExecID = fixMessage->GetItem(17);
	ExecRefID = fixMessage->GetItem(19);
	ExecTransType = fixMessage->GetItem(20);
	LastPx = fixMessage->GetItem(31);
	LastQty = fixMessage->GetItem(32);
	OrderID = fixMessage->GetItem(37);
	OrderQty = fixMessage->GetItem(38);
	OrderStatus = fixMessage->GetItem(39);
	OrdType = fixMessage->GetItem(40);
	OrigClOrdID = fixMessage->GetItem(41);
	Price = fixMessage->GetItem(44);
	SecurityID = fixMessage->GetItem(48);
	Side = fixMessage->GetItem(54);
	Symbol = fixMessage->GetItem(55);
	Text = fixMessage->GetItem(58);
	TimeInForce = fixMessage->GetItem(59);
	TransactTime = fixMessage->GetItem(60);
	SettlDate = fixMessage->GetItem(64);
	TradeDate = fixMessage->GetItem(75);
	NoAllocs = fixMessage->GetItem(78);
	AllocAccount = fixMessage->GetItem(79);
	StopPx = fixMessage->GetItem(99);
	OrdRejReason = fixMessage->GetItem(103);
	SecurityDesc = fixMessage->GetItem(107);
	MinQty = fixMessage->GetItem(110);
	ExecType = fixMessage->GetItem(150);
	LeavesQty = fixMessage->GetItem(151);
	SecurityType = fixMessage->GetItem(167);
	MaxShow = fixMessage->GetItem(210);
	ContraTrader = fixMessage->GetItem(337);
	RefMsgType = fixMessage->GetItem(372);
	ContraBroker = fixMessage->GetItem(375);
	ExecRestatementReason = fixMessage->GetItem(378);
	BusinessRejectReason = fixMessage->GetItem(380);
	TotalNumSecurities = fixMessage->GetItem(393);
	ExpireDate = fixMessage->GetItem(432);
	MultiLegReportingType = fixMessage->GetItem(442);
	SecondaryExecID = fixMessage->GetItem(527);
	CrossID = fixMessage->GetItem(548);
	CrossType = fixMessage->GetItem(549);
	MassStatusReqID = fixMessage->GetItem(584);
	UnderlyingPx = fixMessage->GetItem(810);
	OptionDelta = fixMessage->GetItem(811);
	AvgPXIndicator = fixMessage->GetItem(819);
	LastRptRequest = fixMessage->GetItem(912);
	HostCrossID = fixMessage->GetItem(961);
	ManualOrderIndicator = fixMessage->GetItem(1028);
	CustOrderHandlingInst = fixMessage->GetItem(1031);
	Volatility = fixMessage->GetItem(1188);
	ExpirationTimeValue = fixMessage->GetItem(1189);
	RiskFreeRate = fixMessage->GetItem(1190);
	NoFills = fixMessage->GetItem(1362);
	FillExecID = fixMessage->GetItem(1363);
	FillPx = fixMessage->GetItem(1364);
	FillQty = fixMessage->GetItem(1365);
	ClearingTradePriceType = fixMessage->GetItem(1598);
	FillYieldType = fixMessage->GetItem(1622);
	AvgPxGroupID = fixMessage->GetItem(1731);
	Memo = fixMessage->GetItem(5149);
	DelayDuration = fixMessage->GetItem(5904);
	RequestTime = fixMessage->GetItem(5979);
	SelfMatchPreventionID = fixMessage->GetItem(7928);
	SelfMatchPreventionInstruction = fixMessage->GetItem(8000);
	SplitMsg = fixMessage->GetItem(9553);
	OriginalSecondaryExecID = fixMessage->GetItem(9703);
	CorrelationClOrdID = fixMessage->GetItem(9717);
	MDTradeEntryID = fixMessage->GetItem(37711);
	MarketSegmentID = fixMessage->GetItem(1300);
}
FixExecutionReportField::FixExecutionReportField(FixExecutionReportField&& other) noexcept
	:FixRspHeader(std::move(other)), FixTrailer(other)
{
	Account = std::move(other.Account);
	AvgPx = std::move(other.AvgPx);
	ClOrdID = std::move(other.ClOrdID);
	CumQty = std::move(other.CumQty);
	ExecID = std::move(other.ExecID);
	ExecRefID = std::move(other.ExecRefID);
	ExecTransType = std::move(other.ExecTransType);
	LastPx = std::move(other.LastPx);
	LastQty = std::move(other.LastQty);
	OrderID = std::move(other.OrderID);
	OrderQty = std::move(other.OrderQty);
	OrderStatus = std::move(other.OrderStatus);
	OrdType = std::move(other.OrdType);
	OrigClOrdID = std::move(other.OrigClOrdID);
	Price = std::move(other.Price);
	SecurityID = std::move(other.SecurityID);
	Side = std::move(other.Side);
	Symbol = std::move(other.Symbol);
	Text = std::move(other.Text);
	TimeInForce = std::move(other.TimeInForce);
	TransactTime = std::move(other.TransactTime);
	SettlDate = std::move(other.SettlDate);
	TradeDate = std::move(other.TradeDate);
	NoAllocs = std::move(other.NoAllocs);
	AllocAccount = std::move(other.AllocAccount);
	StopPx = std::move(other.StopPx);
	OrdRejReason = std::move(other.OrdRejReason);
	SecurityDesc = std::move(other.SecurityDesc);
	MinQty = std::move(other.MinQty);
	ExecType = std::move(other.ExecType);
	LeavesQty = std::move(other.LeavesQty);
	SecurityType = std::move(other.SecurityType);
	MaxShow = std::move(other.MaxShow);
	ContraTrader = std::move(other.ContraTrader);
	RefMsgType = std::move(other.RefMsgType);
	ContraBroker = std::move(other.ContraBroker);
	ExecRestatementReason = std::move(other.ExecRestatementReason);
	BusinessRejectReason = std::move(other.BusinessRejectReason);
	TotalNumSecurities = std::move(other.TotalNumSecurities);
	ExpireDate = std::move(other.ExpireDate);
	MultiLegReportingType = std::move(other.MultiLegReportingType);
	SecondaryExecID = std::move(other.SecondaryExecID);
	CrossID = std::move(other.CrossID);
	CrossType = std::move(other.CrossType);
	MassStatusReqID = std::move(other.MassStatusReqID);
	UnderlyingPx = std::move(other.UnderlyingPx);
	OptionDelta = std::move(other.OptionDelta);
	AvgPXIndicator = std::move(other.AvgPXIndicator);
	LastRptRequest = std::move(other.LastRptRequest);
	HostCrossID = std::move(other.HostCrossID);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	CustOrderHandlingInst = std::move(other.CustOrderHandlingInst);
	Volatility = std::move(other.Volatility);
	ExpirationTimeValue = std::move(other.ExpirationTimeValue);
	RiskFreeRate = std::move(other.RiskFreeRate);
	NoFills = std::move(other.NoFills);
	FillExecID = std::move(other.FillExecID);
	FillPx = std::move(other.FillPx);
	FillQty = std::move(other.FillQty);
	ClearingTradePriceType = std::move(other.ClearingTradePriceType);
	FillYieldType = std::move(other.FillYieldType);
	AvgPxGroupID = std::move(other.AvgPxGroupID);
	Memo = std::move(other.Memo);
	DelayDuration = std::move(other.DelayDuration);
	RequestTime = std::move(other.RequestTime);
	SelfMatchPreventionID = std::move(other.SelfMatchPreventionID);
	SelfMatchPreventionInstruction = std::move(other.SelfMatchPreventionInstruction);
	SplitMsg = std::move(other.SplitMsg);
	OriginalSecondaryExecID = std::move(other.OriginalSecondaryExecID);
	CorrelationClOrdID = std::move(other.CorrelationClOrdID);
	MDTradeEntryID = std::move(other.MDTradeEntryID);
	MarketSegmentID = std::move(other.MarketSegmentID);
}
FixExecutionReportField& FixExecutionReportField::operator=(FixExecutionReportField&& other) noexcept
{
	FixRspHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	
	Account = std::move(other.Account);
	AvgPx = std::move(other.AvgPx);
	ClOrdID = std::move(other.ClOrdID);
	CumQty = std::move(other.CumQty);
	ExecID = std::move(other.ExecID);
	ExecRefID = std::move(other.ExecRefID);
	ExecTransType = std::move(other.ExecTransType);
	LastPx = std::move(other.LastPx);
	LastQty = std::move(other.LastQty);
	OrderID = std::move(other.OrderID);
	OrderQty = std::move(other.OrderQty);
	OrderStatus = std::move(other.OrderStatus);
	OrdType = std::move(other.OrdType);
	OrigClOrdID = std::move(other.OrigClOrdID);
	Price = std::move(other.Price);
	SecurityID = std::move(other.SecurityID);
	Side = std::move(other.Side);
	Symbol = std::move(other.Symbol);
	Text = std::move(other.Text);
	TimeInForce = std::move(other.TimeInForce);
	TransactTime = std::move(other.TransactTime);
	SettlDate = std::move(other.SettlDate);
	TradeDate = std::move(other.TradeDate);
	NoAllocs = std::move(other.NoAllocs);
	AllocAccount = std::move(other.AllocAccount);
	StopPx = std::move(other.StopPx);
	OrdRejReason = std::move(other.OrdRejReason);
	SecurityDesc = std::move(other.SecurityDesc);
	MinQty = std::move(other.MinQty);
	ExecType = std::move(other.ExecType);
	LeavesQty = std::move(other.LeavesQty);
	SecurityType = std::move(other.SecurityType);
	MaxShow = std::move(other.MaxShow);
	ContraTrader = std::move(other.ContraTrader);
	RefMsgType = std::move(other.RefMsgType);
	ContraBroker = std::move(other.ContraBroker);
	ExecRestatementReason = std::move(other.ExecRestatementReason);
	BusinessRejectReason = std::move(other.BusinessRejectReason);
	TotalNumSecurities = std::move(other.TotalNumSecurities);
	ExpireDate = std::move(other.ExpireDate);
	MultiLegReportingType = std::move(other.MultiLegReportingType);
	SecondaryExecID = std::move(other.SecondaryExecID);
	CrossID = std::move(other.CrossID);
	CrossType = std::move(other.CrossType);
	MassStatusReqID = std::move(other.MassStatusReqID);
	UnderlyingPx = std::move(other.UnderlyingPx);
	OptionDelta = std::move(other.OptionDelta);
	AvgPXIndicator = std::move(other.AvgPXIndicator);
	LastRptRequest = std::move(other.LastRptRequest);
	HostCrossID = std::move(other.HostCrossID);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	CustOrderHandlingInst = std::move(other.CustOrderHandlingInst);
	Volatility = std::move(other.Volatility);
	ExpirationTimeValue = std::move(other.ExpirationTimeValue);
	RiskFreeRate = std::move(other.RiskFreeRate);
	NoFills = std::move(other.NoFills);
	FillExecID = std::move(other.FillExecID);
	FillPx = std::move(other.FillPx);
	FillQty = std::move(other.FillQty);
	ClearingTradePriceType = std::move(other.ClearingTradePriceType);
	FillYieldType = std::move(other.FillYieldType);
	AvgPxGroupID = std::move(other.AvgPxGroupID);
	Memo = std::move(other.Memo);
	DelayDuration = std::move(other.DelayDuration);
	RequestTime = std::move(other.RequestTime);
	SelfMatchPreventionID = std::move(other.SelfMatchPreventionID);
	SelfMatchPreventionInstruction = std::move(other.SelfMatchPreventionInstruction);
	SplitMsg = std::move(other.SplitMsg);
	OriginalSecondaryExecID = std::move(other.OriginalSecondaryExecID);
	CorrelationClOrdID = std::move(other.CorrelationClOrdID);
	MDTradeEntryID = std::move(other.MDTradeEntryID);
	MarketSegmentID = std::move(other.MarketSegmentID);

	return *this;
}
FixExecutionReportField::~FixExecutionReportField()
{
	
}
int FixExecutionReportField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixRspHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "Account", Account);
	len += WriteString(buff + len, size - len, "AvgPx", AvgPx);
	len += WriteString(buff + len, size - len, "ClOrdID", ClOrdID);
	len += WriteString(buff + len, size - len, "CumQty", CumQty);
	len += WriteString(buff + len, size - len, "ExecID", ExecID);
	len += WriteString(buff + len, size - len, "ExecRefID", ExecRefID);
	len += WriteString(buff + len, size - len, "ExecTransType", ExecTransType);
	len += WriteString(buff + len, size - len, "LastPx", LastPx);
	len += WriteString(buff + len, size - len, "LastQty", LastQty);
	len += WriteString(buff + len, size - len, "OrderID", OrderID);
	len += WriteString(buff + len, size - len, "OrderQty", OrderQty);
	len += WriteString(buff + len, size - len, "OrderStatus", OrderStatus);
	len += WriteString(buff + len, size - len, "OrdType", OrdType);
	len += WriteString(buff + len, size - len, "OrigClOrdID", OrigClOrdID);
	len += WriteString(buff + len, size - len, "Price", Price);
	len += WriteString(buff + len, size - len, "SecurityID", SecurityID);
	len += WriteString(buff + len, size - len, "Side", Side);
	len += WriteString(buff + len, size - len, "Symbol", Symbol);
	len += WriteString(buff + len, size - len, "Text", Text);
	len += WriteString(buff + len, size - len, "TimeInForce", TimeInForce);
	len += WriteString(buff + len, size - len, "TransactTime", TransactTime);
	len += WriteString(buff + len, size - len, "SettlDate", SettlDate);
	len += WriteString(buff + len, size - len, "TradeDate", TradeDate);
	len += WriteString(buff + len, size - len, "NoAllocs", NoAllocs);
	len += WriteString(buff + len, size - len, "AllocAccount", AllocAccount);
	len += WriteString(buff + len, size - len, "StopPx", StopPx);
	len += WriteString(buff + len, size - len, "OrdRejReason", OrdRejReason);
	len += WriteString(buff + len, size - len, "SecurityDesc", SecurityDesc);
	len += WriteString(buff + len, size - len, "MinQty", MinQty);
	len += WriteString(buff + len, size - len, "ExecType", ExecType);
	len += WriteString(buff + len, size - len, "LeavesQty", LeavesQty);
	len += WriteString(buff + len, size - len, "SecurityType", SecurityType);
	len += WriteString(buff + len, size - len, "MaxShow", MaxShow);
	len += WriteString(buff + len, size - len, "ContraTrader", ContraTrader);
	len += WriteString(buff + len, size - len, "RefMsgType", RefMsgType);
	len += WriteString(buff + len, size - len, "ContraBroker", ContraBroker);
	len += WriteString(buff + len, size - len, "ExecRestatementReason", ExecRestatementReason);
	len += WriteString(buff + len, size - len, "BusinessRejectReason", BusinessRejectReason);
	len += WriteString(buff + len, size - len, "TotalNumSecurities", TotalNumSecurities);
	len += WriteString(buff + len, size - len, "ExpireDate", ExpireDate);
	len += WriteString(buff + len, size - len, "MultiLegReportingType", MultiLegReportingType);
	len += WriteString(buff + len, size - len, "SecondaryExecID", SecondaryExecID);
	len += WriteString(buff + len, size - len, "CrossID", CrossID);
	len += WriteString(buff + len, size - len, "CrossType", CrossType);
	len += WriteString(buff + len, size - len, "MassStatusReqID", MassStatusReqID);
	len += WriteString(buff + len, size - len, "UnderlyingPx", UnderlyingPx);
	len += WriteString(buff + len, size - len, "OptionDelta", OptionDelta);
	len += WriteString(buff + len, size - len, "AvgPXIndicator", AvgPXIndicator);
	len += WriteString(buff + len, size - len, "LastRptRequest", LastRptRequest);
	len += WriteString(buff + len, size - len, "HostCrossID", HostCrossID);
	len += WriteString(buff + len, size - len, "ManualOrderIndicator", ManualOrderIndicator);
	len += WriteString(buff + len, size - len, "CustOrderHandlingInst", CustOrderHandlingInst);
	len += WriteString(buff + len, size - len, "Volatility", Volatility);
	len += WriteString(buff + len, size - len, "ExpirationTimeValue", ExpirationTimeValue);
	len += WriteString(buff + len, size - len, "RiskFreeRate", RiskFreeRate);
	len += WriteString(buff + len, size - len, "NoFills", NoFills);
	len += WriteString(buff + len, size - len, "FillExecID", FillExecID);
	len += WriteString(buff + len, size - len, "FillPx", FillPx);
	len += WriteString(buff + len, size - len, "FillQty", FillQty);
	len += WriteString(buff + len, size - len, "ClearingTradePriceType", ClearingTradePriceType);
	len += WriteString(buff + len, size - len, "FillYieldType", FillYieldType);
	len += WriteString(buff + len, size - len, "AvgPxGroupID", AvgPxGroupID);
	len += WriteString(buff + len, size - len, "Memo", Memo);
	len += WriteString(buff + len, size - len, "DelayDuration", DelayDuration);
	len += WriteString(buff + len, size - len, "RequestTime", RequestTime);
	len += WriteString(buff + len, size - len, "SelfMatchPreventionID", SelfMatchPreventionID);
	len += WriteString(buff + len, size - len, "SelfMatchPreventionInstruction", SelfMatchPreventionInstruction);
	len += WriteString(buff + len, size - len, "SplitMsg", SplitMsg);
	len += WriteString(buff + len, size - len, "OriginalSecondaryExecID", OriginalSecondaryExecID);
	len += WriteString(buff + len, size - len, "CorrelationClOrdID", CorrelationClOrdID);
	len += WriteString(buff + len, size - len, "MDTradeEntryID", MDTradeEntryID);
	len += WriteString(buff + len, size - len, "MarketSegmentID", MarketSegmentID);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixExecutionReportField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixRspHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 1, Account);
	len += WriteStream(buff + len, 6, AvgPx);
	len += WriteStream(buff + len, 11, ClOrdID);
	len += WriteStream(buff + len, 14, CumQty);
	len += WriteStream(buff + len, 17, ExecID);
	len += WriteStream(buff + len, 19, ExecRefID);
	len += WriteStream(buff + len, 20, ExecTransType);
	len += WriteStream(buff + len, 31, LastPx);
	len += WriteStream(buff + len, 32, LastQty);
	len += WriteStream(buff + len, 37, OrderID);
	len += WriteStream(buff + len, 38, OrderQty);
	len += WriteStream(buff + len, 39, OrderStatus);
	len += WriteStream(buff + len, 40, OrdType);
	len += WriteStream(buff + len, 41, OrigClOrdID);
	len += WriteStream(buff + len, 44, Price);
	len += WriteStream(buff + len, 48, SecurityID);
	len += WriteStream(buff + len, 54, Side);
	len += WriteStream(buff + len, 55, Symbol);
	len += WriteStream(buff + len, 58, Text);
	len += WriteStream(buff + len, 59, TimeInForce);
	len += WriteStream(buff + len, 60, TransactTime);
	len += WriteStream(buff + len, 64, SettlDate);
	len += WriteStream(buff + len, 75, TradeDate);
	len += WriteStream(buff + len, 78, NoAllocs);
	len += WriteStream(buff + len, 79, AllocAccount);
	len += WriteStream(buff + len, 99, StopPx);
	len += WriteStream(buff + len, 103, OrdRejReason);
	len += WriteStream(buff + len, 107, SecurityDesc);
	len += WriteStream(buff + len, 110, MinQty);
	len += WriteStream(buff + len, 150, ExecType);
	len += WriteStream(buff + len, 151, LeavesQty);
	len += WriteStream(buff + len, 167, SecurityType);
	len += WriteStream(buff + len, 210, MaxShow);
	len += WriteStream(buff + len, 337, ContraTrader);
	len += WriteStream(buff + len, 372, RefMsgType);
	len += WriteStream(buff + len, 375, ContraBroker);
	len += WriteStream(buff + len, 378, ExecRestatementReason);
	len += WriteStream(buff + len, 380, BusinessRejectReason);
	len += WriteStream(buff + len, 393, TotalNumSecurities);
	len += WriteStream(buff + len, 432, ExpireDate);
	len += WriteStream(buff + len, 442, MultiLegReportingType);
	len += WriteStream(buff + len, 527, SecondaryExecID);
	len += WriteStream(buff + len, 548, CrossID);
	len += WriteStream(buff + len, 549, CrossType);
	len += WriteStream(buff + len, 584, MassStatusReqID);
	len += WriteStream(buff + len, 810, UnderlyingPx);
	len += WriteStream(buff + len, 811, OptionDelta);
	len += WriteStream(buff + len, 819, AvgPXIndicator);
	len += WriteStream(buff + len, 912, LastRptRequest);
	len += WriteStream(buff + len, 961, HostCrossID);
	len += WriteStream(buff + len, 1028, ManualOrderIndicator);
	len += WriteStream(buff + len, 1031, CustOrderHandlingInst);
	len += WriteStream(buff + len, 1188, Volatility);
	len += WriteStream(buff + len, 1189, ExpirationTimeValue);
	len += WriteStream(buff + len, 1190, RiskFreeRate);
	len += WriteStream(buff + len, 1362, NoFills);
	len += WriteStream(buff + len, 1363, FillExecID);
	len += WriteStream(buff + len, 1364, FillPx);
	len += WriteStream(buff + len, 1365, FillQty);
	len += WriteStream(buff + len, 1598, ClearingTradePriceType);
	len += WriteStream(buff + len, 1622, FillYieldType);
	len += WriteStream(buff + len, 1731, AvgPxGroupID);
	len += WriteStream(buff + len, 5149, Memo);
	len += WriteStream(buff + len, 5904, DelayDuration);
	len += WriteStream(buff + len, 5979, RequestTime);
	len += WriteStream(buff + len, 7928, SelfMatchPreventionID);
	len += WriteStream(buff + len, 8000, SelfMatchPreventionInstruction);
	len += WriteStream(buff + len, 9553, SplitMsg);
	len += WriteStream(buff + len, 9703, OriginalSecondaryExecID);
	len += WriteStream(buff + len, 9717, CorrelationClOrdID);
	len += WriteStream(buff + len, 37711, MDTradeEntryID);
	len += WriteStream(buff + len, 1300, MarketSegmentID);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixExecutionReportField::GetFixMessage()
{
	FixRspHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(1, Account);
	m_FixMessage->SetItem(6, AvgPx);
	m_FixMessage->SetItem(11, ClOrdID);
	m_FixMessage->SetItem(14, CumQty);
	m_FixMessage->SetItem(17, ExecID);
	m_FixMessage->SetItem(19, ExecRefID);
	m_FixMessage->SetItem(20, ExecTransType);
	m_FixMessage->SetItem(31, LastPx);
	m_FixMessage->SetItem(32, LastQty);
	m_FixMessage->SetItem(37, OrderID);
	m_FixMessage->SetItem(38, OrderQty);
	m_FixMessage->SetItem(39, OrderStatus);
	m_FixMessage->SetItem(40, OrdType);
	m_FixMessage->SetItem(41, OrigClOrdID);
	m_FixMessage->SetItem(44, Price);
	m_FixMessage->SetItem(48, SecurityID);
	m_FixMessage->SetItem(54, Side);
	m_FixMessage->SetItem(55, Symbol);
	m_FixMessage->SetItem(58, Text);
	m_FixMessage->SetItem(59, TimeInForce);
	m_FixMessage->SetItem(60, TransactTime);
	m_FixMessage->SetItem(64, SettlDate);
	m_FixMessage->SetItem(75, TradeDate);
	m_FixMessage->SetItem(78, NoAllocs);
	m_FixMessage->SetItem(79, AllocAccount);
	m_FixMessage->SetItem(99, StopPx);
	m_FixMessage->SetItem(103, OrdRejReason);
	m_FixMessage->SetItem(107, SecurityDesc);
	m_FixMessage->SetItem(110, MinQty);
	m_FixMessage->SetItem(150, ExecType);
	m_FixMessage->SetItem(151, LeavesQty);
	m_FixMessage->SetItem(167, SecurityType);
	m_FixMessage->SetItem(210, MaxShow);
	m_FixMessage->SetItem(337, ContraTrader);
	m_FixMessage->SetItem(372, RefMsgType);
	m_FixMessage->SetItem(375, ContraBroker);
	m_FixMessage->SetItem(378, ExecRestatementReason);
	m_FixMessage->SetItem(380, BusinessRejectReason);
	m_FixMessage->SetItem(393, TotalNumSecurities);
	m_FixMessage->SetItem(432, ExpireDate);
	m_FixMessage->SetItem(442, MultiLegReportingType);
	m_FixMessage->SetItem(527, SecondaryExecID);
	m_FixMessage->SetItem(548, CrossID);
	m_FixMessage->SetItem(549, CrossType);
	m_FixMessage->SetItem(584, MassStatusReqID);
	m_FixMessage->SetItem(810, UnderlyingPx);
	m_FixMessage->SetItem(811, OptionDelta);
	m_FixMessage->SetItem(819, AvgPXIndicator);
	m_FixMessage->SetItem(912, LastRptRequest);
	m_FixMessage->SetItem(961, HostCrossID);
	m_FixMessage->SetItem(1028, ManualOrderIndicator);
	m_FixMessage->SetItem(1031, CustOrderHandlingInst);
	m_FixMessage->SetItem(1188, Volatility);
	m_FixMessage->SetItem(1189, ExpirationTimeValue);
	m_FixMessage->SetItem(1190, RiskFreeRate);
	m_FixMessage->SetItem(1362, NoFills);
	m_FixMessage->SetItem(1363, FillExecID);
	m_FixMessage->SetItem(1364, FillPx);
	m_FixMessage->SetItem(1365, FillQty);
	m_FixMessage->SetItem(1598, ClearingTradePriceType);
	m_FixMessage->SetItem(1622, FillYieldType);
	m_FixMessage->SetItem(1731, AvgPxGroupID);
	m_FixMessage->SetItem(5149, Memo);
	m_FixMessage->SetItem(5904, DelayDuration);
	m_FixMessage->SetItem(5979, RequestTime);
	m_FixMessage->SetItem(7928, SelfMatchPreventionID);
	m_FixMessage->SetItem(8000, SelfMatchPreventionInstruction);
	m_FixMessage->SetItem(9553, SplitMsg);
	m_FixMessage->SetItem(9703, OriginalSecondaryExecID);
	m_FixMessage->SetItem(9717, CorrelationClOrdID);
	m_FixMessage->SetItem(37711, MDTradeEntryID);
	m_FixMessage->SetItem(1300, MarketSegmentID);
	return m_FixMessage;
}
string FixExecutionReportField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixExecutionReport(" + FixRspHeader::CreateSql() + "Account char(32), AvgPx char(32), ClOrdID char(32), CumQty char(32), ExecID char(32), ExecRefID char(32), ExecTransType char(32), LastPx char(32), LastQty char(32), OrderID char(32), OrderQty char(32), OrderStatus char(32), OrdType char(32), OrigClOrdID char(32), Price char(32), SecurityID char(32), Side char(32), Symbol char(32), Text char(255), TimeInForce char(32), TransactTime char(32), SettlDate char(32), TradeDate char(32), NoAllocs char(32), AllocAccount char(32), StopPx char(32), OrdRejReason char(32), SecurityDesc char(32), MinQty char(32), ExecType char(32), LeavesQty char(32), SecurityType char(32), MaxShow char(32), ContraTrader char(32), RefMsgType char(32), ContraBroker char(32), ExecRestatementReason char(32), BusinessRejectReason char(32), TotalNumSecurities char(32), ExpireDate char(32), MultiLegReportingType char(32), SecondaryExecID char(32), CrossID char(32), CrossType char(32), MassStatusReqID char(32), UnderlyingPx char(32), OptionDelta char(32), AvgPXIndicator char(32), LastRptRequest char(32), HostCrossID char(32), ManualOrderIndicator char(32), CustOrderHandlingInst char(32), Volatility char(32), ExpirationTimeValue char(32), RiskFreeRate char(32), NoFills char(32), FillExecID char(32), FillPx char(32), FillQty char(32), ClearingTradePriceType char(32), FillYieldType char(32), AvgPxGroupID char(32), Memo char(32), DelayDuration char(32), RequestTime char(32), SelfMatchPreventionID char(32), SelfMatchPreventionInstruction char(32), SplitMsg char(32), OriginalSecondaryExecID char(32), CorrelationClOrdID char(32), MDTradeEntryID char(32), MarketSegmentID char(32));";
}
string FixExecutionReportField::InsertSql()
{
	return "REPLACE INTO t_FixExecutionReport VALUES(\"" + FixRspHeader::InsertSql() + "\", \"" + Account + "\", \"" + AvgPx + "\", \"" + ClOrdID + "\", \"" + CumQty + "\", \"" + ExecID + "\", \"" + ExecRefID + "\", \"" + ExecTransType + "\", \"" + LastPx + "\", \"" + LastQty + "\", \"" + OrderID + "\", \"" + OrderQty + "\", \"" + OrderStatus + "\", \"" + OrdType + "\", \"" + OrigClOrdID + "\", \"" + Price + "\", \"" + SecurityID + "\", \"" + Side + "\", \"" + Symbol + "\", \"" + Text + "\", \"" + TimeInForce + "\", \"" + TransactTime + "\", \"" + SettlDate + "\", \"" + TradeDate + "\", \"" + NoAllocs + "\", \"" + AllocAccount + "\", \"" + StopPx + "\", \"" + OrdRejReason + "\", \"" + SecurityDesc + "\", \"" + MinQty + "\", \"" + ExecType + "\", \"" + LeavesQty + "\", \"" + SecurityType + "\", \"" + MaxShow + "\", \"" + ContraTrader + "\", \"" + RefMsgType + "\", \"" + ContraBroker + "\", \"" + ExecRestatementReason + "\", \"" + BusinessRejectReason + "\", \"" + TotalNumSecurities + "\", \"" + ExpireDate + "\", \"" + MultiLegReportingType + "\", \"" + SecondaryExecID + "\", \"" + CrossID + "\", \"" + CrossType + "\", \"" + MassStatusReqID + "\", \"" + UnderlyingPx + "\", \"" + OptionDelta + "\", \"" + AvgPXIndicator + "\", \"" + LastRptRequest + "\", \"" + HostCrossID + "\", \"" + ManualOrderIndicator + "\", \"" + CustOrderHandlingInst + "\", \"" + Volatility + "\", \"" + ExpirationTimeValue + "\", \"" + RiskFreeRate + "\", \"" + NoFills + "\", \"" + FillExecID + "\", \"" + FillPx + "\", \"" + FillQty + "\", \"" + ClearingTradePriceType + "\", \"" + FillYieldType + "\", \"" + AvgPxGroupID + "\", \"" + Memo + "\", \"" + DelayDuration + "\", \"" + RequestTime + "\", \"" + SelfMatchPreventionID + "\", \"" + SelfMatchPreventionInstruction + "\", \"" + SplitMsg + "\", \"" + OriginalSecondaryExecID + "\", \"" + CorrelationClOrdID + "\", \"" + MDTradeEntryID + "\", \"" + MarketSegmentID + "\");";
}
int FixExecutionReportField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	FixMessage* fixMessage = FixMessage::Allocate();
	for (auto i = 0; i < colCount; i++)
	{
		fixMessage->SetItem(FixItems::GetInstance().GetItemKey(colNames[i]), colValues[i]);
	}
	((FixTableCallback*)callback)->InitRspMessage(new FixExecutionReportField(fixMessage));
	return 0;
}

FixRspOrderCancelRejectField::FixRspOrderCancelRejectField(FixMessage* fixMessage)
	:FixRspHeader("FixRspOrderCancelRejectField", "9", "app", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
	Account = fixMessage->GetItem(1);
	ClOrdID = fixMessage->GetItem(11);
	ExecID = fixMessage->GetItem(17);
	OrderID = fixMessage->GetItem(37);
	OrderStatus = fixMessage->GetItem(39);
	OrigClOrdID = fixMessage->GetItem(41);
	SecurityID = fixMessage->GetItem(48);
	Text = fixMessage->GetItem(58);
	TransactTime = fixMessage->GetItem(60);
	CxlRejReason = fixMessage->GetItem(102);
	SecurityDesc = fixMessage->GetItem(107);
	CancelRejResponseTo = fixMessage->GetItem(434);
	ManualOrderIndicator = fixMessage->GetItem(1028);
	CustOrderHandlingInst = fixMessage->GetItem(1031);
	Memo = fixMessage->GetItem(5149);
	SelfMatchPreventionID = fixMessage->GetItem(7928);
	CorrelationClOrdID = fixMessage->GetItem(9717);
	RequestTime = fixMessage->GetItem(5979);
	DelayDuration = fixMessage->GetItem(5904);
	SplitMsg = fixMessage->GetItem(9553);
}
FixRspOrderCancelRejectField::FixRspOrderCancelRejectField(FixRspOrderCancelRejectField&& other) noexcept
	:FixRspHeader(std::move(other)), FixTrailer(other)
{
	Account = std::move(other.Account);
	ClOrdID = std::move(other.ClOrdID);
	ExecID = std::move(other.ExecID);
	OrderID = std::move(other.OrderID);
	OrderStatus = std::move(other.OrderStatus);
	OrigClOrdID = std::move(other.OrigClOrdID);
	SecurityID = std::move(other.SecurityID);
	Text = std::move(other.Text);
	TransactTime = std::move(other.TransactTime);
	CxlRejReason = std::move(other.CxlRejReason);
	SecurityDesc = std::move(other.SecurityDesc);
	CancelRejResponseTo = std::move(other.CancelRejResponseTo);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	CustOrderHandlingInst = std::move(other.CustOrderHandlingInst);
	Memo = std::move(other.Memo);
	SelfMatchPreventionID = std::move(other.SelfMatchPreventionID);
	CorrelationClOrdID = std::move(other.CorrelationClOrdID);
	RequestTime = std::move(other.RequestTime);
	DelayDuration = std::move(other.DelayDuration);
	SplitMsg = std::move(other.SplitMsg);
}
FixRspOrderCancelRejectField& FixRspOrderCancelRejectField::operator=(FixRspOrderCancelRejectField&& other) noexcept
{
	FixRspHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	
	Account = std::move(other.Account);
	ClOrdID = std::move(other.ClOrdID);
	ExecID = std::move(other.ExecID);
	OrderID = std::move(other.OrderID);
	OrderStatus = std::move(other.OrderStatus);
	OrigClOrdID = std::move(other.OrigClOrdID);
	SecurityID = std::move(other.SecurityID);
	Text = std::move(other.Text);
	TransactTime = std::move(other.TransactTime);
	CxlRejReason = std::move(other.CxlRejReason);
	SecurityDesc = std::move(other.SecurityDesc);
	CancelRejResponseTo = std::move(other.CancelRejResponseTo);
	ManualOrderIndicator = std::move(other.ManualOrderIndicator);
	CustOrderHandlingInst = std::move(other.CustOrderHandlingInst);
	Memo = std::move(other.Memo);
	SelfMatchPreventionID = std::move(other.SelfMatchPreventionID);
	CorrelationClOrdID = std::move(other.CorrelationClOrdID);
	RequestTime = std::move(other.RequestTime);
	DelayDuration = std::move(other.DelayDuration);
	SplitMsg = std::move(other.SplitMsg);

	return *this;
}
FixRspOrderCancelRejectField::~FixRspOrderCancelRejectField()
{
	
}
int FixRspOrderCancelRejectField::ToString(char* buff, int size)
{
	int len = 0;
	len += FixRspHeader::ToString(buff + len, size - len);
	
	len += WriteString(buff + len, size - len, "Account", Account);
	len += WriteString(buff + len, size - len, "ClOrdID", ClOrdID);
	len += WriteString(buff + len, size - len, "ExecID", ExecID);
	len += WriteString(buff + len, size - len, "OrderID", OrderID);
	len += WriteString(buff + len, size - len, "OrderStatus", OrderStatus);
	len += WriteString(buff + len, size - len, "OrigClOrdID", OrigClOrdID);
	len += WriteString(buff + len, size - len, "SecurityID", SecurityID);
	len += WriteString(buff + len, size - len, "Text", Text);
	len += WriteString(buff + len, size - len, "TransactTime", TransactTime);
	len += WriteString(buff + len, size - len, "CxlRejReason", CxlRejReason);
	len += WriteString(buff + len, size - len, "SecurityDesc", SecurityDesc);
	len += WriteString(buff + len, size - len, "CancelRejResponseTo", CancelRejResponseTo);
	len += WriteString(buff + len, size - len, "ManualOrderIndicator", ManualOrderIndicator);
	len += WriteString(buff + len, size - len, "CustOrderHandlingInst", CustOrderHandlingInst);
	len += WriteString(buff + len, size - len, "Memo", Memo);
	len += WriteString(buff + len, size - len, "SelfMatchPreventionID", SelfMatchPreventionID);
	len += WriteString(buff + len, size - len, "CorrelationClOrdID", CorrelationClOrdID);
	len += WriteString(buff + len, size - len, "RequestTime", RequestTime);
	len += WriteString(buff + len, size - len, "DelayDuration", DelayDuration);
	len += WriteString(buff + len, size - len, "SplitMsg", SplitMsg);

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int FixRspOrderCancelRejectField::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixRspHeader::ToStream(buff + len);
	
	len += WriteStream(buff + len, 1, Account);
	len += WriteStream(buff + len, 11, ClOrdID);
	len += WriteStream(buff + len, 17, ExecID);
	len += WriteStream(buff + len, 37, OrderID);
	len += WriteStream(buff + len, 39, OrderStatus);
	len += WriteStream(buff + len, 41, OrigClOrdID);
	len += WriteStream(buff + len, 48, SecurityID);
	len += WriteStream(buff + len, 58, Text);
	len += WriteStream(buff + len, 60, TransactTime);
	len += WriteStream(buff + len, 102, CxlRejReason);
	len += WriteStream(buff + len, 107, SecurityDesc);
	len += WriteStream(buff + len, 434, CancelRejResponseTo);
	len += WriteStream(buff + len, 1028, ManualOrderIndicator);
	len += WriteStream(buff + len, 1031, CustOrderHandlingInst);
	len += WriteStream(buff + len, 5149, Memo);
	len += WriteStream(buff + len, 7928, SelfMatchPreventionID);
	len += WriteStream(buff + len, 9717, CorrelationClOrdID);
	len += WriteStream(buff + len, 5979, RequestTime);
	len += WriteStream(buff + len, 5904, DelayDuration);
	len += WriteStream(buff + len, 9553, SplitMsg);

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* FixRspOrderCancelRejectField::GetFixMessage()
{
	FixRspHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
	m_FixMessage->SetItem(1, Account);
	m_FixMessage->SetItem(11, ClOrdID);
	m_FixMessage->SetItem(17, ExecID);
	m_FixMessage->SetItem(37, OrderID);
	m_FixMessage->SetItem(39, OrderStatus);
	m_FixMessage->SetItem(41, OrigClOrdID);
	m_FixMessage->SetItem(48, SecurityID);
	m_FixMessage->SetItem(58, Text);
	m_FixMessage->SetItem(60, TransactTime);
	m_FixMessage->SetItem(102, CxlRejReason);
	m_FixMessage->SetItem(107, SecurityDesc);
	m_FixMessage->SetItem(434, CancelRejResponseTo);
	m_FixMessage->SetItem(1028, ManualOrderIndicator);
	m_FixMessage->SetItem(1031, CustOrderHandlingInst);
	m_FixMessage->SetItem(5149, Memo);
	m_FixMessage->SetItem(7928, SelfMatchPreventionID);
	m_FixMessage->SetItem(9717, CorrelationClOrdID);
	m_FixMessage->SetItem(5979, RequestTime);
	m_FixMessage->SetItem(5904, DelayDuration);
	m_FixMessage->SetItem(9553, SplitMsg);
	return m_FixMessage;
}
string FixRspOrderCancelRejectField::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixRspOrderCancelReject(" + FixRspHeader::CreateSql() + "Account char(32), ClOrdID char(32), ExecID char(32), OrderID char(32), OrderStatus char(32), OrigClOrdID char(32), SecurityID char(32), Text char(255), TransactTime char(32), CxlRejReason char(32), SecurityDesc char(32), CancelRejResponseTo char(32), ManualOrderIndicator char(32), CustOrderHandlingInst char(32), Memo char(32), SelfMatchPreventionID char(32), CorrelationClOrdID char(32), RequestTime char(32), DelayDuration char(32), SplitMsg char(32));";
}
string FixRspOrderCancelRejectField::InsertSql()
{
	return "REPLACE INTO t_FixRspOrderCancelReject VALUES(\"" + FixRspHeader::InsertSql() + "\", \"" + Account + "\", \"" + ClOrdID + "\", \"" + ExecID + "\", \"" + OrderID + "\", \"" + OrderStatus + "\", \"" + OrigClOrdID + "\", \"" + SecurityID + "\", \"" + Text + "\", \"" + TransactTime + "\", \"" + CxlRejReason + "\", \"" + SecurityDesc + "\", \"" + CancelRejResponseTo + "\", \"" + ManualOrderIndicator + "\", \"" + CustOrderHandlingInst + "\", \"" + Memo + "\", \"" + SelfMatchPreventionID + "\", \"" + CorrelationClOrdID + "\", \"" + RequestTime + "\", \"" + DelayDuration + "\", \"" + SplitMsg + "\");";
}
int FixRspOrderCancelRejectField::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	FixMessage* fixMessage = FixMessage::Allocate();
	for (auto i = 0; i < colCount; i++)
	{
		fixMessage->SetItem(FixItems::GetInstance().GetItemKey(colNames[i]), colValues[i]);
	}
	((FixTableCallback*)callback)->InitRspMessage(new FixRspOrderCancelRejectField(fixMessage));
	return 0;
}


int FixProduct::ToString(char* buff, int size)
{
	return snprintf(buff, size, "FixProduct: ExchangeID:[%s], ProductID:[%s], MarketSegmentID:[%s]", ExchangeID.c_str(), ProductID.c_str(), MarketSegmentID.c_str());
}
int FixProduct::ToStream(char* buff, int size)
{
	return snprintf(buff, size, "'%s', '%s', '%s'", ExchangeID.c_str(), ProductID.c_str(), MarketSegmentID.c_str());
}
string FixProduct::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixProduct(ExchangeID char(32), ProductID char(32), MarketSegmentID char(32), PRIMARY KEY(ExchangeID, ProductID));";
}
string FixProduct::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	ToStream(m_Buff, 4096);
	return "REPLACE INTO t_FixProduct VALUES(" + string(m_Buff) + ");";
}
int FixProduct::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new FixProduct();
	field->ExchangeID = colValues[0];
	field->ProductID = colValues[1];
	field->MarketSegmentID = colValues[2];

	((FixTableCallback*)callback)->SelectFixProductCallback(field);
	return 0;
}

int FixInstrument::ToString(char* buff, int size)
{
	return snprintf(buff, size, "FixInstrument: ExchangeID:[%s], ProductID:[%s], InstrumentID:[%s], ITCAlias:[%s], GenCode:[%s], MarketSegmentID:[%s]", ExchangeID.c_str(), ProductID.c_str(), InstrumentID.c_str(), ITCAlias.c_str(), GenCode.c_str(), MarketSegmentID.c_str());
}
int FixInstrument::ToStream(char* buff, int size)
{
	return snprintf(buff, size, "'%s', '%s', '%s', '%s', '%s', '%s'", ExchangeID.c_str(), ProductID.c_str(), InstrumentID.c_str(), ITCAlias.c_str(), GenCode.c_str(), MarketSegmentID.c_str());
}
string FixInstrument::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_FixInstrument(ExchangeID char(32), ProductID char(32), InstrumentID char(32), ITCAlias char(32), GenCode char(32), MarketSegmentID char(32), PRIMARY KEY(ExchangeID, InstrumentID));";
}
string FixInstrument::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	ToStream(m_Buff, 4096);
	return "REPLACE INTO t_FixInstrument VALUES(" + string(m_Buff) + ");";
}
int FixInstrument::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new FixInstrument();
	field->ExchangeID = colValues[0];
	field->ProductID = colValues[1];
	field->InstrumentID = colValues[2];
	field->ITCAlias = colValues[3];
	field->GenCode = colValues[4];
	field->MarketSegmentID = colValues[5];

	((FixTableCallback*)callback)->SelectFixInstrumentCallback(field);
	return 0;
}

