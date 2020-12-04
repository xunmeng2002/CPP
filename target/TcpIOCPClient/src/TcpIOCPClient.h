#pragma once

#include "SocketInit.h"
#include "SocketMemCache.h"
#include "SocketDataStruct.h"
#include "TcpIOCP.h"


class TcpIOCPClient :public TcpIOCP
{
private:
	TcpIOCPClient();
	~TcpIOCPClient();
	TcpIOCPClient(const TcpIOCPClient&) = delete;
	TcpIOCPClient& operator=(const TcpIOCPClient&) = delete;
public:
	static TcpIOCPClient& GetInstance();
	bool Init();
	void Stop() override;
	void SetServerAddress(const char* address, int port, int family = AF_INET);

	bool Connect();
protected:
	virtual void Run() override;

private:
	bool Create(int maxConcurrency = 0);
	bool PostConnect();
	void OnConnectComplete(SocketData* socketData, int len);


private:
	static TcpIOCPClient m_Instance;
	SOCKET m_InitSocket;
	int m_Family;
	std::string m_ServerIP;
	int m_ServerPort;
	SOCKADDR_IN m_ServerAddress;
	SOCKADDR_IN m_LocalAddress;
};