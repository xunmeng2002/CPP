#pragma once
#include "SocketInit.h"
#include "CacheList.h"
#include <mutex>
#include <string>

class ConnectData
{
public:
	static ConnectData* Allocate(int sessionID, const SOCKET& socketID, const std::string& clientIP, int clientPort);
	void Free();

	void Set(int sessionID, const SOCKET& socketID, const std::string& clientIP, int clientPort);

	int SessionID;
	SOCKET SocketID;
	std::string ClientIP;
	int ClientPort;
};