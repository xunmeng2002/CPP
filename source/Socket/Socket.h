#ifndef SOCKET_H
#define SOCKET_H

#include <WinSock2.h>
#include <string>

class Socket
{
public:
	Socket(int af, int type, int protocol);
	Socket(const SOCKET& socketID, bool blocking, int af, int type, int protocol);
	Socket(const Socket&) = delete;
	Socket& operator=(const Socket&) = delete;
	Socket(Socket&& socket);
	Socket& operator=(Socket&& socket);
	~Socket();

	Socket* Accept();
	int Bind(const char* ipAddress, int port);
	int Close();
	int Connect(const char* ipAddress, unsigned int port);
	bool GetBlocking();
	sockaddr_in GetPeerName();
	sockaddr_in GetSockName();
	int GetSockOpt(int level, int optName, char* optValue, int* optLen);
	SOCKET GetSocketID();
	int GetTimeOut();
	int Ioctl(long cmd, unsigned long* argp);
	int Listen(int backLog = 5);
	
	int Recv(char* data, int len, int flags);
	int RecvFrom(char* data, int len, int flags, sockaddr* from, int* fromLen);
	int Send(const char* data, int len, int flags);
	int SendTo(const char* data, int len, int flags, const sockaddr* toAddr, int toLen);
	int SetBlocking(bool blocking);
	void SetPeerAddress(const sockaddr_in& peerAddr);
	int SetSockOpt(int level, int optName, const char* optValue, int optLen);
	int SetTimeOut(int timeOut);
	int ShutDown(int how);
	

private:
	SOCKET m_SocketID;
	bool m_Blocking;
	int m_AF;
	int m_Type;
	int m_Protocol;
	sockaddr_in m_ListenAddress;
	sockaddr_in m_PeerAddress;
	int m_TimeOut;
};


#endif
