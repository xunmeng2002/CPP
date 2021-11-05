#pragma once

#include "SocketInit.h"
#include "SocketMemCache.h"
#include "SocketDataStruct.h"
#include "TcpIOCP.h"


class TcpIOCPServer : public TcpIOCP
{
private:
	TcpIOCPServer();
	~TcpIOCPServer();
	TcpIOCPServer(const TcpIOCPServer&) = delete;
	TcpIOCPServer& operator=(const TcpIOCPServer&) = delete;
public:
	static TcpIOCPServer& GetInstance();
	bool Init();
	void Stop() override;
	void SetSocketInfo(int port, const char* ip = "127.0.0.1", int family = AF_INET);

protected:
	virtual void ThreadInit();
	virtual void Run();
	virtual void ThreadExit();
private:
	bool Create(int maxConcurrency = 0);
	bool TryBind();
	bool Listen(int backLog = 5);
	
	bool PostAccept();
	void OnAcceptComplete(SocketData* socketData, int len);



private:
	static TcpIOCPServer m_Instance;
	int m_Family;
	std::string m_IP;
	int m_Port;
	SOCKADDR_IN m_ServerAddress;
	SOCKET m_ServerSocket;
};

