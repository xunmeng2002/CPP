#ifndef TCP_BASE_H
#define TCP_BASE_H

#include <WinSock2.h>
#include "Socket.h"

#define EVENT_SESSION_CONNECT 10000
#define EVENT_SESSION_CLOSE 10001
#define EVENT_REQUEST_DATA 10002
#define EVENT_RESPONSE_DATA 10003
#define EVENT_FRONT_DISCONNECTED 10004


#define MAX_SINGLE_RECV_BUFF_LEN 1024 * 64
class CacheList;

class TcpBase
{
public:
	TcpBase(int microSeconds);
	virtual ~TcpBase();

	virtual void PrepareFds() = 0;
	virtual bool Send(unsigned int sessionID, const char* data, int len);
	virtual bool SendEvent(unsigned int sessionID, int eventID) = 0;
	virtual void Run() = 0;

protected:
	virtual CacheList* GetSendCacheList(unsigned int sessionID) = 0;
	int Send(unsigned int sessionID, Socket* socket, CacheList* cacheList);
	int Recv(unsigned int sessionID, Socket* socket);

protected:
	timeval m_TimeOut;

	fd_set m_RecvFds;
	fd_set m_SendFds;

	char* m_RecvBuffer;
};


#endif