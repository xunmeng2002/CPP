#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "TcpBase.h"
#include <map>

class CacheList;

class TcpServer : public TcpBase
{
public:
	TcpServer(int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, int microSeconds = 1000000);
	virtual ~TcpServer();

	int Bind(const char* ipAddress, int port);
	int Listen(int backLog = 5);
	void Accept();
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
	Socket* m_ListenSocket;
	std::map<unsigned int, Socket*> m_Sockets;
	std::map<unsigned int, CacheList*> m_SendCacheLists;

	int m_BackLog;
	unsigned int m_MaxSessionID;
};

#endif