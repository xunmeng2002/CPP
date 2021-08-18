#include "TradeApiReqFields.h"

!!items = {}!!
!!entry items!!
!!travel!!
!!items[@name] = @key!!
!!leave!!
!!leave!!

!!entry ReqFields!!
!!travel!!
!!@name!!Field::!!@name!!Field(FixMessage* fixMessage)
	:ReqHeader("!!@name!!Field", "!!@msgtype!!", fixMessage), Trailer(fixMessage), m_FixMessage(fixMessage)
{
	if (!fixMessage)
		return;
!!travel!!
!!key = items[@name]!!
	!!@name!! = fixMessage->GetItem(!!$key!!);
!!leave!!
}
!!@name!!Field::!!@name!!Field(!!@name!!Field&& other) noexcept
	:ReqHeader(std::move(other)), Trailer(other)
{
	m_FixMessage = other.m_FixMessage;
	other.m_FixMessage = nullptr;
	
!!travel!!
	!!@name!! = std::move(other.!!@name!!);
!!leave!!
}
!!@name!!Field& !!@name!!Field::operator=(!!@name!!Field&& other) noexcept
{
	ReqHeader::operator=(std::move(other));
	Trailer::operator=(other);
	
	if (m_FixMessage)
		m_FixMessage->Free();
	m_FixMessage = other.m_FixMessage;
	other.m_FixMessage = nullptr;

!!travel!!
	!!@name!! = std::move(other.!!@name!!);
!!leave!!

	return *this;
}
!!@name!!Field::~!!@name!!Field()
{
	if (m_FixMessage)
		m_FixMessage->Free();
}

int !!@name!!Field::ToString(char* buff, int size)
{
	int len = 0;
	len += ReqHeader::ToString(buff + len, size - len);
	
!!travel!!
	len += WriteString(buff + len, size - len, "!!@name!!", !!@name!!);
!!leave!!

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int !!@name!!Field::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += ReqHeader::ToStream(buff + len);
	
!!travel!!
!!key = items[@name]!!
	len += WriteStream(buff + len, !!$key!!, !!@name!!);
!!leave!!

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}
string !!@name!!Field::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS !!@name!!(" + ReqHeader::CreateSql() + "!!travel!!!!if $pumpid > "1":!!!!inc indent!!, !!dec indent!!!!@name!! char (32)!!leave!!);";
}
string !!@name!!Field::InsertSql()
{
	return "REPLACE INTO !!@name!! VALUES(" + ReqHeader::InsertSql()!!travel!! + ", " + !!@name!!!!leave!! + ");";
}

!!leave!!
!!leave!!
