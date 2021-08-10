#include "ConnectData.h"
#include "Logger.h"
#include "MemCacheTemplateSingleton.h"

using namespace std;

ConnectData* ConnectData::Allocate(int sessionID, const SOCKET& socketID, const string& clientIP, int clientPort)
{
	ConnectData* connectData = MemCacheTemplateSingleton<ConnectData>::GetInstance().Allocate();
	connectData->Set(sessionID, socketID, clientIP, clientPort);
	return connectData;
}
void ConnectData::Free()
{
	closesocket(SocketID);
	MemCacheTemplateSingleton<ConnectData>::GetInstance().Free(this);
}

void ConnectData::Set(int sessionID, const SOCKET& socketID, const string& clientIP, int clientPort)
{
	SessionID = sessionID;
	SocketID = socketID;
	ClientIP = clientIP;
	ClientPort = clientPort;
}