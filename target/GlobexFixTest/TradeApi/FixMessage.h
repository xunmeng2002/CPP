#pragma once
#include "TradeApiCommon.h"

enum class ConnectStatus
{
	NotConnected = 0,
	Connecting = 1,
	Connected = 2,
};

enum class LogonStatus
{
	NotLogged = 0,
	Logging = 1,
	Logged = 2,
	Logout = 3,
};


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
