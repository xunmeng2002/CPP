#include "FixFields.h"
#include "FixMdb.h"
#include "FixItems.h"

!!items = {}!!
!!entry items!!
!!travel!!
!!items[@name] = @key!!
!!leave!!
!!leave!!

!!entry Headers!!
!!travel!!
Fix!!@name!!::Fix!!@name!!(const string& fieldName, const string& msgType, const string& msgClass, FixMessage* fixMessage)
	:FieldName(fieldName), MsgType(msgType), MsgClass(msgClass), m_FixMessage(fixMessage)
{
	memset(HeadBuff, 0, sizeof(HeadBuff));
	if (!fixMessage)
		return;
!!travel!!
!!if @name != "MsgType":!!
!!inc indent!!
!!key = items[@name]!!
	!!@name!! = fixMessage->GetItem(!!$key!!);
!!dec indent!!
!!leave!!
}
Fix!!@name!!::Fix!!@name!!(Fix!!@name!!&& other) noexcept
{
	m_FixMessage = other.m_FixMessage;
	other.m_FixMessage = nullptr;
	FieldName = std::move(other.FieldName);
	MsgClass = other.MsgClass;
	Items = std::move(other.Items);
	
!!travel!!
	!!@name!! = std::move(other.!!@name!!);
!!leave!!
}
Fix!!@name!!& Fix!!@name!!::operator=(Fix!!@name!!&& other) noexcept
{
	Items.clear();
	if (m_FixMessage)
		m_FixMessage->Free();
	m_FixMessage = other.m_FixMessage;
	other.m_FixMessage = nullptr;
	FieldName = std::move(other.FieldName);
	MsgClass = other.MsgClass;
	Items = std::move(other.Items);
	
!!travel!!
	!!@name!! = std::move(other.!!@name!!);
!!leave!!
	
	return *this;
}
Fix!!@name!!::~Fix!!@name!!()
{
	if (m_FixMessage)
		m_FixMessage->Free();
	m_FixMessage = nullptr;
}

int Fix!!@name!!::ToString(char* buff, int size)
{
	int len = 0;
	len += sprintf(buff, "%s:", FieldName.c_str());
	
!!travel!!
	len += WriteString(buff + len, size - len, "!!@name!!", !!@name!!);
!!leave!!
	return len;
}
int Fix!!@name!!::ToStream(char* buff)
{
	int len = 0;
!!travel!!
!!if @name != "BeginString" and @name != "BodyLength":!!
!!inc indent!!
!!key = items[@name]!!
	len += WriteStream(buff + len, !!$key!!, !!@name!!);
!!dec indent!!
!!leave!!
	return len;
}
FixMessage* Fix!!@name!!::GetFixMessage()
{
!!travel!!
!!key = items[@name]!!
	m_FixMessage->SetItem(!!$key!!, !!@name!!);
!!leave!!
	return m_FixMessage;
}
string Fix!!@name!!::CreateSql()
{
	return "!!travel!!!!if @name != "MsgSeqNum":!!!!inc indent!!!!@name!! char(32), !!dec indent!!!!else:!!!!inc indent!!!!@name!! char(!!@len!!) PRIMARY KEY NOT NULL, !!dec indent!!!!leave!!";
}
string Fix!!@name!!::InsertSql()
{
	return !!travel!!!!if pumpid > 0:!!!!inc indent!! + "\", \"" + !!dec indent!!!!@name!!!!leave!!;
}
int Fix!!@name!!::AddHeader(char* buff, int bodyLen)
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
void Fix!!@name!!::SetHeader(const string& senderCompID, const string& senderSubID, const string& targetCompID, const string& targetSubID)
{
	SenderCompID = senderCompID;
	SenderSubID = senderSubID;
	TargetCompID = targetCompID;
	TargetSubID = targetSubID;
}

!!leave!!
!!leave!!

!!entry Trailers!!
!!travel!!
Fix!!@name!!::Fix!!@name!!(FixMessage* fixMessage)
{
	if (!fixMessage)
		return;
!!travel!!
!!key = items[@name]!!
	!!@name!! = fixMessage->GetItem(!!$key!!);
!!leave!!
}
int Fix!!@name!!::ToString(char* buff, int size)
{
	int len = 0;
!!travel!!
	len += WriteString(buff + len, size - len, "!!@name!!", !!@name!!);
!!leave!!
	return len;
}
void Fix!!@name!!::GetFixMessage(FixMessage* fixMessage)
{
!!travel!!
!!key = items[@name]!!
	fixMessage->SetItem(!!$key!!, !!@name!!);
!!leave!!
}
int Fix!!@name!!::AddTrailer(char* buff, int len)
{
	auto sum = CalculateSum((unsigned char*)buff, len);
	char temp[8];
	sprintf(temp, "%03d", sum);
	CheckSum = temp;

	_ASSERT(WriteStream(buff + len, 10, CheckSum) == TRAILER_LEN);
	return TRAILER_LEN;
}
!!leave!!
!!leave!!

!!entry ReqFields!!
!!travel!!
Fix!!@name!!Field::Fix!!@name!!Field(FixMessage* fixMessage)
	:FixReqHeader("Fix!!@name!!Field", "!!@msgtype!!", "!!@msgClass!!", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
!!travel!!
!!key = items[@name]!!
	!!@name!! = fixMessage->GetItem(!!$key!!);
!!leave!!
}
Fix!!@name!!Field::Fix!!@name!!Field(Fix!!@name!!Field&& other) noexcept
	:FixReqHeader(std::move(other)), FixTrailer(other)
{
!!travel!!
	!!@name!! = std::move(other.!!@name!!);
!!leave!!
}
Fix!!@name!!Field& Fix!!@name!!Field::operator=(Fix!!@name!!Field&& other) noexcept
{
	FixReqHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
!!travel!!
	!!@name!! = std::move(other.!!@name!!);
!!leave!!

	return *this;
}
Fix!!@name!!Field::~Fix!!@name!!Field()
{
	
}
int Fix!!@name!!Field::ToString(char* buff, int size)
{
	int len = 0;
	len += FixReqHeader::ToString(buff + len, size - len);
	
!!travel!!
	len += WriteString(buff + len, size - len, "!!@name!!", !!@name!!);
!!leave!!

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int Fix!!@name!!Field::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixReqHeader::ToStream(buff + len);
	
!!travel!!
!!key = items[@name]!!
	len += WriteStream(buff + len, !!$key!!, !!@name!!);
!!leave!!

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* Fix!!@name!!Field::GetFixMessage()
{
	FixReqHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
!!travel!!
!!key = items[@name]!!
	m_FixMessage->SetItem(!!$key!!, !!@name!!);
!!leave!!
	return m_FixMessage;
}
string Fix!!@name!!Field::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_Fix!!@name!!(" + FixReqHeader::CreateSql() + "!!travel!!!!if pumpid > 0:!!!!inc indent!!, !!dec indent!!!!@name!! char(!!@len!!)!!leave!!);";
}
string Fix!!@name!!Field::InsertSql()
{
	return "REPLACE INTO t_Fix!!@name!! VALUES(\"" + FixReqHeader::InsertSql()!!travel!! + "\", \"" + !!@name!!!!leave!! + "\");";
}
int Fix!!@name!!Field::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
!!if @msgClass == "app":!!
!!inc indent!!
	FixMessage* fixMessage = FixMessage::Allocate();
	for (auto i = 0; i < colCount; i++)
	{
		fixMessage->SetItem(FixItems::GetInstance().GetItemKey(colNames[i]), colValues[i]);
	}
	((FixTableCallback*)callback)->InitReqMessage(new Fix!!@name!!Field(fixMessage));
!!dec indent!!
	return 0;
}

!!leave!!
!!leave!!

!!entry RspFields!!
!!travel!!
Fix!!@name!!Field::Fix!!@name!!Field(FixMessage* fixMessage)
	:FixRspHeader("Fix!!@name!!Field", "!!@msgtype!!", "!!@msgClass!!", fixMessage), FixTrailer(fixMessage)
{
	if (!fixMessage)
		return;
!!travel!!
!!key = items[@name]!!
	!!@name!! = fixMessage->GetItem(!!$key!!);
!!leave!!
}
Fix!!@name!!Field::Fix!!@name!!Field(Fix!!@name!!Field&& other) noexcept
	:FixRspHeader(std::move(other)), FixTrailer(other)
{
!!travel!!
	!!@name!! = std::move(other.!!@name!!);
!!leave!!
}
Fix!!@name!!Field& Fix!!@name!!Field::operator=(Fix!!@name!!Field&& other) noexcept
{
	FixRspHeader::operator=(std::move(other));
	FixTrailer::operator=(other);
	
!!travel!!
	!!@name!! = std::move(other.!!@name!!);
!!leave!!

	return *this;
}
Fix!!@name!!Field::~Fix!!@name!!Field()
{
	
}
int Fix!!@name!!Field::ToString(char* buff, int size)
{
	int len = 0;
	len += FixRspHeader::ToString(buff + len, size - len);
	
!!travel!!
	len += WriteString(buff + len, size - len, "!!@name!!", !!@name!!);
!!leave!!

	len += FixTrailer::ToString(buff + len, size - len);
	return len;
}
int Fix!!@name!!Field::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += FixRspHeader::ToStream(buff + len);
	
!!travel!!
!!key = items[@name]!!
	len += WriteStream(buff + len, !!$key!!, !!@name!!);
!!leave!!

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
FixMessage* Fix!!@name!!Field::GetFixMessage()
{
	FixRspHeader::GetFixMessage();
	FixTrailer::GetFixMessage(m_FixMessage);
!!travel!!
!!key = items[@name]!!
	m_FixMessage->SetItem(!!$key!!, !!@name!!);
!!leave!!
	return m_FixMessage;
}
string Fix!!@name!!Field::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_Fix!!@name!!(" + FixRspHeader::CreateSql() + "!!travel!!!!if pumpid > 0:!!!!inc indent!!, !!dec indent!!!!@name!! char(!!@len!!)!!leave!!);";
}
string Fix!!@name!!Field::InsertSql()
{
	return "REPLACE INTO t_Fix!!@name!! VALUES(\"" + FixRspHeader::InsertSql()!!travel!! + "\", \"" + !!@name!!!!leave!! + "\");";
}
int Fix!!@name!!Field::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
!!if @msgClass == "app":!!
!!inc indent!!
	FixMessage* fixMessage = FixMessage::Allocate();
	for (auto i = 0; i < colCount; i++)
	{
		fixMessage->SetItem(FixItems::GetInstance().GetItemKey(colNames[i]), colValues[i]);
	}
	((FixTableCallback*)callback)->InitRspMessage(new Fix!!@name!!Field(fixMessage));
!!dec indent!!
	return 0;
}

!!leave!!
!!leave!!

!!entry InnerTables!!
!!travel!!
int Fix!!@name!!::ToString(char* buff, int size)
{
	return snprintf(buff, size, "Fix!!@name!!: !!entry items!!!!travel!!!!if pumpid > 0:!!!!inc indent!!, !!dec indent!!!!@name!!:[%s]!!leave!!"!!travel!!, !!@name!!.c_str()!!leave!!!!leave!!);
}
int Fix!!@name!!::ToStream(char* buff, int size)
{
	return snprintf(buff, size, "!!entry items!!!!travel!!!!if pumpid > 0:!!!!inc indent!!, !!dec indent!!'%s'!!leave!!"!!travel!!, !!@name!!.c_str()!!leave!!!!leave!!);
}
string Fix!!@name!!::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_Fix!!@name!!(!!entry items!!!!travel!!!!@name!! char(!!@len!!), !!leave!!!!leave!!!!entry primarykey!!PRIMARY KEY(!!travel!!!!if pumpid > 0:!!!!inc indent!!, !!dec indent!!!!@name!!!!leave!!!!leave!!));";
}
string Fix!!@name!!::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	ToStream(m_Buff, 4096);
	return "REPLACE INTO t_Fix!!@name!! VALUES(" + string(m_Buff) + ");";
}
int Fix!!@name!!::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new Fix!!@name!!();
!!entry items!!
!!travel!!
	field->!!@name!! = colValues[!!$pumpid!!];
!!leave!!
!!leave!!

	((FixTableCallback*)callback)->SelectFix!!@name!!Callback(field);
	return 0;
}

!!leave!!
!!leave!!
