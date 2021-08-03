#include "TradeApiHeaderFields.h"


!!entry Headers!!
!!travel!!
!!@name!!::!!@name!!(const string& fieldName, const string& msgType, FixMessage* fixMessage)
	:FieldName(fieldName), MsgType(msgType)
{
!!travel!!
!!if @name != "MsgType":!!
!!inc indent!!
	!!@name!! = fixMessage->GetItem(!!@key!!);
!!dec indent!!
!!leave!!
}
int !!@name!!::ToString(char* buff, int size)
{
	int len = 0;
	len += sprintf(buff, "%s:", FieldName.c_str());
	
!!travel!!
	len += WriteString(buff + len, size - len, "!!@name!!", !!@name!!);
!!leave!!
	return len;
}
int !!@name!!::ToStream(char* buff)
{
	int len = 0;
!!travel!!
!!if @name != "BeginString" and @name != "BodyLength":!!
!!inc indent!!
	len += WriteStream(buff + len, !!@key!!, !!@name!!);
!!dec indent!!
!!leave!!
	return len;
}
int !!@name!!::AddHeader(char* buff, int bodyLen)
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
void !!@name!!::SetHeader(const string& senderCompID, const string& senderSubID, const string& targetCompID, const string& targetSubID)
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
!!@name!!::!!@name!!(FixMessage* fixMessage)
{
!!travel!!
	!!@name!! = fixMessage->GetItem(!!@key!!);
!!leave!!
}
int !!@name!!::ToString(char* buff, int size)
{
	int len = 0;
!!travel!!
	len += WriteString(buff + len, size - len, "!!@name!!", !!@name!!);
!!leave!!
	return len;
}
int !!@name!!::AddTrailer(char* buff, int len)
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
