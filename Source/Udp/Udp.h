#pragma once
#include "SocketInit.h"
#include "Event.h"

class Udp
{
	Udp();
	~Udp();
public:
	static Udp& GetInstance();
	void SetBindAddress(const char* ip = "127.0.0.1", int port = 0);
	void SetRemoteAddress(const char* ip, int port);
	bool Init(bool setBroadCast);
	void Close();
	int SendTo(TcpEvent* tcpEvent);
	int RecvFrom(TcpEvent* tcpEvent);
	bool ZipSendTo(TcpEvent* tcpEvent);
	bool ZipRecvFrom(TcpEvent* tcpEvent);



private:
	static Udp m_Instance;
	SOCKET  m_Socket;
	sockaddr_in m_BindAddress;
	sockaddr_in m_RemoteAddress;
	int m_RemoteAddressLen;
};

