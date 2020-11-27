#pragma once

#include "SocketInit.h"
#include "SocketMemCache.h"
#include "SocketDataStruct.h"
#include "TcpIOCP.h"


class TcpClient :public TcpIOCP
{
private:
	TcpClient();
	~TcpClient();
	TcpClient(const TcpClient&) = delete;
	TcpClient& operator=(const TcpClient&) = delete;
public:
	static TcpClient& GetInstance();
	bool Init();
	void Stop() override;
	void SetServerAddress(const char* address, int port, int family = AF_INET);

	bool Connect();
protected:
	virtual void ThreadInit();
	virtual void Run();
	virtual void ThreadExit();

private:
	bool Create(int maxConcurrency = 0);
	bool PostConnect();
	void OnConnectComplete(SocketData* socketData, int len);


private:
	static TcpClient m_Instance;
	SOCKET m_InitSocket;
	int m_Family;
	std::string m_ServerIP;
	int m_ServerPort;
	SOCKADDR_IN m_ServerAddress;
	SOCKADDR_IN m_LocalAddress;
};