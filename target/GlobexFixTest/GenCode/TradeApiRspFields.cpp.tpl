#include "TradeApiRspFields.h"

!!entry RspFields!!
!!travel!!
!!@name!!::!!@name!!(const string& fieldName, FixMessage* fixMessage)
	:RspHeader("!!@name!!", fixMessage)
{
!!travel!!
	!!@name!! = fixMessage->GetItem(!!@key!!);
!!leave!!
}
int !!@name!!::ToString(char* buff, int size)
{
	int len = 0;
	len += RspHeader::ToString(buff + len, size - len);
	
!!travel!!
	len += WriteString(buff + len, size - len, "!!@name!!", !!@name!!);
!!leave!!

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int !!@name!!::ToStream(char* buff)
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
