#include "TradeApiReqFields.h"


!!entry ReqFields!!
!!travel!!
!!@name!!::!!@name!!(const string& fieldName, FixMessage* fixMessage)
	:ReqHeader("!!@name!!", fixMessage)
{
!!travel!!
	!!@name!! = fixMessage->GetItem(!!@key!!);
!!leave!!
}
int !!@name!!::ToString(char* buff, int size)
{
	int len = 0;
	len += ReqHeader::ToString(buff + len, size - len);
	
!!travel!!
	len += WriteString(buff + len, size - len, "!!@name!!", !!@name!!);
!!leave!!

	len += Trailer::ToString(buff + len, size - len);
	return len;
}
int !!@name!!::ToStream(char* buff)
{
	int len = HEAD_LEN;
	len += ReqHeader::ToStream(buff + len);
	
!!travel!!
	len += WriteStream(buff + len, !!@key!!, !!@name!!);
!!leave!!

	AddHeader(buff, len - HEAD_LEN);
	len += AddTrailer(buff, len);

	return len;
}

!!leave!!
!!leave!!
