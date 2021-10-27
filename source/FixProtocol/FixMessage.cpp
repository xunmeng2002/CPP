#include "FixMessage.h"
#include "Logger.h"
#include "Utility.h"
#include "MemCacheTemplateSingleton.h"


FixMessage* FixMessage::Allocate()
{
	return MemCacheTemplateSingleton<FixMessage>::GetInstance().Allocate();
}
void FixMessage::Free()
{
	Clear();
	MemCacheTemplateSingleton<FixMessage>::GetInstance().Free(this);
}
void FixMessage::SetItem(int tag, string value)
{
	Items[tag] = value;
}
void FixMessage::Clear()
{
	Items.clear();
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
string FixMessage::GetMsgSeqNum()
{
	return GetItem(34);
}
string FixMessage::GetPossDupFlag()
{
	return GetItem(43);
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
