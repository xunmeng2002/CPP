#pragma once
#include "SocketInit.h"
#include "CacheList.h"
#include <mutex>

#define MAX_SINGLE_MESSAGE_LENGTH 1024 * 64

class ConnectData
{
public:
	ConnectData(int sessionID, const SOCKET& socketID, const char* clientIP, int clientPort);
	~ConnectData();

	bool Send(const char* data, int length);
	int OnSend();

	int SessionID;
	SOCKET SocketID;
	char ClientIP[32];
	int ClientPort;
	std::mutex SendMutex;
	CacheList* SendCache;
};