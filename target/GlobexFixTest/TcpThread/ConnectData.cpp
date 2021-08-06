#include "ConnectData.h"
#include "Logger.h"
#include "MemCacheTemplateSingleton.h"

using namespace std;

ConnectData::ConnectData()
{
	SendCache = new CacheList();
}
ConnectData::~ConnectData()
{
	if (SendCache != nullptr)
	{
		delete SendCache;
	}
	SendCache = nullptr;
}

void ConnectData::Set(int sessionID, const SOCKET& socketID, const string& clientIP, int clientPort)
{
	SessionID = sessionID;
	SocketID = socketID;
	ClientIP = clientIP;
	ClientPort = clientPort;
}
void ConnectData::Reset()
{
	lock_guard<mutex> guard(SendMutex);
	SendCache->Clear();
	closesocket(SocketID);
}
bool ConnectData::Send(const char* data, int length)
{
	lock_guard<mutex> guard(SendMutex);
	SendCache->PushBack(data, length);
	return true;
}
int ConnectData::OnSend()
{
	lock_guard<mutex> guard(SendMutex);
	int len = 0;
	void* data = SendCache->GetData(len);
	len = min(len, MAX_SINGLE_MESSAGE_LENGTH);
	int sendLen = send(SocketID, (char*)data, len, 0);
	*((char*)data + len) = 0;
	WRITE_LOG(LogLevel::Debug, "OnSend: SessionID[%d] data[%s], len[%d], sendLen[%d]", SessionID, data, len, sendLen);
	if (sendLen > 0)
	{
		SendCache->PopFront(nullptr, sendLen);
	}
	return sendLen;
}

ConnectData* ConnectData::Allocate(int sessionID, const SOCKET& socketID, const string& clientIP, int clientPort)
{
	ConnectData* connectData = MemCacheTemplateSingleton<ConnectData>::GetInstance().Allocate();
	connectData->Set(sessionID, socketID, clientIP, clientPort);
	return connectData;
}
void ConnectData::Free(ConnectData* connectData)
{
	connectData->Reset();
	MemCacheTemplateSingleton<ConnectData>::GetInstance().Free(connectData);
}