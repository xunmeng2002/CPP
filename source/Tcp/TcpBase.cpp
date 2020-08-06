#include "TcpBase.h"
#include "CacheList.h"

using namespace std;


TcpBase::TcpBase(int microSeconds)
{
	m_TimeOut.tv_sec = microSeconds / 1000000;
	m_TimeOut.tv_usec = microSeconds % 1000000;

	m_RecvBuffer = new char[MAX_SINGLE_RECV_BUFF_LEN];
}
TcpBase::~TcpBase()
{
	delete[] m_RecvBuffer;
}
bool TcpBase::Send(unsigned int sessionID, const char* data, int len)
{
	auto cacheList = GetSendCacheList(sessionID);
	if (cacheList == nullptr)
	{
		return false;
	}
	cacheList->PushBack(data, len);
	return true;
}

int TcpBase::Send(unsigned int sessionID, Socket* socket, CacheList* cacheList)
{
	int sendLen = 0;
	void* data = cacheList->GetData(sendLen);
	int len = socket->Send((char*)data, sendLen, 0);
	if (len > 0)
	{
		cacheList->PopFront(nullptr, len);
	}
	else
	{
		SendEvent(sessionID, EVENT_SESSION_CLOSE);
	}
	return len;
}
int TcpBase::Recv(unsigned int sessionID, Socket* socket)
{
	int len = socket->Recv(m_RecvBuffer, MAX_SINGLE_RECV_BUFF_LEN, 0);
	if (len > 0)
	{
		//TODO
	}
	else
	{
		SendEvent(sessionID, EVENT_SESSION_CLOSE);
	}
	return len;
}