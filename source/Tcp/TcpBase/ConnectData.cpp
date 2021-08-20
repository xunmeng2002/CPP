#include "ConnectData.h"
#include "Logger.h"
#include "MemCacheTemplateSingleton.h"

using namespace std;

ConnectData* ConnectData::Allocate(int sessionID, const SOCKET& socketID, const string& remoteIP, int remotePort)
{
	ConnectData* connectData = MemCacheTemplateSingleton<ConnectData>::GetInstance().Allocate();
	connectData->Set(sessionID, socketID, remoteIP, remotePort);
	return connectData;
}
void ConnectData::Free()
{
	closesocket(SocketID);
	MemCacheTemplateSingleton<ConnectData>::GetInstance().Free(this);
}

void ConnectData::Set(int sessionID, const SOCKET& socketID, const string& remoteIP, int remotePort)
{
	SessionID = sessionID;
	SocketID = socketID;
	RemoteIP = remoteIP;
	RemotePort = remotePort;
}