#include "ConnectData.h"
#include "Logger.h"

using namespace std;

ConnectData::ConnectData(int sessionID, const SOCKET& socketID, const char* clientIP, int clientPort)
	:SessionID(sessionID), SocketID(socketID), ClientPort(clientPort)
{
	memcpy(ClientIP, clientIP, sizeof(ClientIP));
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