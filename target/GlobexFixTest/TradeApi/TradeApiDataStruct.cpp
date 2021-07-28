#include "TradeApiDataStruct.h"
#include "Logger.h"
#include "Common.h"


void FixMessage::AddItem(int tag, string value)
{
	Items.insert(make_pair(tag, value));
}
string FixMessage::GetItem(int tag)
{
	if (Items.find(tag) == Items.end())
	{
		return "";
	}
	return Items[tag];
}
string FixMessage::GetMessageType()
{
	return GetItem(35);
}
string FixMessage::GetSeqNum()
{
	return GetItem(34);
}
int FixMessage::ToString(char* buff, int size)
{
	int len = 0;
	for (auto& it : Items)
	{
		if (size < len + 10)
		{
			_ASSERT(false);
			break;
		}
		len += sprintf(buff + len, "[%d]=[%s]", it.first, it.second.c_str());
	}
	return len;
}


Trailer::Trailer()
{

}
Trailer::Trailer(FixMessage* fixMessage)
{
	CheckSum = fixMessage->GetItem(10);
}
int Trailer::ToString(char* buff, int size)
{
	int len = 0;
	len += WriteString(buff + len, size - len, "CheckSum", CheckSum);
	return len;
}
int Trailer::AddTrailer(char* buff, int len)
{
	auto sum = CalculateSum((unsigned char*)buff, len);
	char temp[8];
	sprintf(temp, "%03d", sum);
	CheckSum = temp;

	_ASSERT(WriteStream(buff + len, 10, CheckSum) == TRAILER_LEN);
	return TRAILER_LEN;
}
