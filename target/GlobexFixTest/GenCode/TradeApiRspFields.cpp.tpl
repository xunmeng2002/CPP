#include "TradeApiRspFields.h"

!!entry RspFields!!
!!travel!!
!!@name!!Field::!!@name!!Field(FixMessage* fixMessage)
	:RspHeader("!!@name!!Field", "!!@msgtype!!", fixMessage), Trailer(fixMessage), m_FixMessage(fixMessage)
{
!!travel!!
	!!@name!! = fixMessage->GetItem(!!@key!!);
!!leave!!
}
!!@name!!Field::~!!@name!!Field()
{
	FixMessage::Free(m_FixMessage);
}
int !!@name!!Field::ToString(char* buff, int size)
{
	int len = 0;
	len += RspHeader::ToString(buff + len, size - len);
	
!!travel!!
	len += WriteString(buff + len, size - len, "!!@name!!", !!@name!!);
!!leave!!

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int !!@name!!Field::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += RspHeader::ToStream(buff + len);
	
!!travel!!
	len += WriteStream(buff + len, !!@key!!, !!@name!!);
!!leave!!

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}

!!leave!!
!!leave!!
