#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <WinSock2.h>
#include "TcpBase.h"
#include "Socket.h"
#include "CacheList.h"

class Package;
class TcpConnection;

class TcpClient : public TcpBase
{
public:
	TcpClient(int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, int microSeconds = 1000000);
	virtual ~TcpClient();

	int Connect(const char* ipAddress, unsigned int port);
	void Close();

	virtual void PrepareFds();
	virtual bool SendEvent(unsigned int sessionID, int eventID);
	virtual void Run();

protected:
	virtual CacheList* GetSendCacheList(unsigned int sessionID);

private:
	void HandleEvents();
	void Send();
	void Recv();
protected:
	Socket* m_Socket;
	unsigned int m_SessionID;

	CacheList* m_SendCacheList;
	unsigned int m_MaxSessionID;
	bool m_Connected;
};


#endif