#pragma once
#include "FixUtility.h"

class FixMessage
{
public:
	static FixMessage* Allocate();
	void Free();

	void SetItem(int tag, string value);
	void Clear();
	string GetItem(int tag);
	string GetMessageType();
	string GetMsgSeqNum();
	string GetPossDupFlag();
	int ToString(char* buff, int size);


	unordered_map<int, string> Items;
};
