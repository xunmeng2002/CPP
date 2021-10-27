#pragma once
#include "SocketInit.h"
#include "TcpEvent.h"

class UdpServer
{
	UdpServer();
public:
	static UdpServer& GetInstance();
	void SetBindAddress(const char* ip, int port = 0);
	void SetBroadAddress(const char* ip, int port);
	bool Init();
	int Send(TcpEvent* tcpEvent);
	int ZipSend(TcpEvent* tcpEvent);



private:
	static UdpServer m_Instance;
	SOCKET  m_Socket;
	sockaddr_in m_BindAddress;
	sockaddr_in m_BroadAddress;
};

