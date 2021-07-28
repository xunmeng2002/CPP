#pragma once
#include "TradeApiCommon.h"

#define HEAD_LEN 18
#define TRAILER_LEN 7

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
};


class FixMessage
{
public:
	void AddItem(int tag, string value);
	string GetItem(int tag);
	string GetMessageType();
	string GetSeqNum();
	int ToString(char* buff, int size);


	unordered_map<int, string> Items;
};


class Trailer
{
public:
	Trailer();
	Trailer(FixMessage* fixMessage);

	virtual int ToString(char* buff, int size);
	int AddTrailer(char* buff, int len);
	

public:
	string CheckSum;
};
