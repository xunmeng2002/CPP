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
	int sendLen = 0;
	void* data = SendCache->GetData(sendLen);
	sendLen = min(sendLen, MAX_SINGLE_MESSAGE_LENGTH);
	int len = send(SocketID, (char*)data, sendLen, 0);
	if (len > 0)
	{
		SendCache->PopFront(nullptr, len);
	}
	return len;
}