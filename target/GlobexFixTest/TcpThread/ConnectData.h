#pragma once
#include "SocketInit.h"
#include "CacheList.h"
#include <mutex>
#include <string>

#define MAX_SINGLE_MESSAGE_LENGTH 1024 * 64

class ConnectData
{
public:
	ConnectData();
	~ConnectData();

	void Set(int sessionID, const SOCKET& socketID, const std::string& clientIP, int clientPort);
	void Reset();

	bool Send(const char* data, int length);
	int OnSend();

	static ConnectData* Allocate(int sessionID, const SOCKET& socketID, const std::string& clientIP, int clientPort);
	static void Free(ConnectData* connectData);

	int SessionID;
	SOCKET SocketID;
	std::string ClientIP;
	int ClientPort;
	std::mutex SendMutex;
	CacheList* SendCache;
};