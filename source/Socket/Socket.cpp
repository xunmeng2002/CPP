#include "Socket.h"
#include <string>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

Socket::Socket(int af, int type, int protocol)
	:m_AF(af), m_Type(type), m_Protocol(protocol), m_Blocking(true)
{
	m_SocketID = socket(af, type, protocol);
}
Socket::Socket(const SOCKET& socketID, bool blocking, int af, int type, int protocol)
	:m_SocketID(socketID), m_Blocking(blocking), m_AF(af), m_Type(type), m_Protocol(protocol)
{

}
Socket::Socket(Socket&& socket)
{
	m_SocketID = socket.m_SocketID;
	m_Blocking = socket.m_Blocking;
	m_AF = socket.m_AF;
	m_Type = socket.m_Type;
	m_Protocol = socket.m_Protocol;
	m_ListenAddress = socket.m_ListenAddress;
	m_PeerAddress = socket.m_PeerAddress;
	m_TimeOut = socket.m_Blocking;
	
	socket.m_SocketID = INVALID_SOCKET;
}
Socket& Socket::operator=(Socket&& socket)
{
	m_SocketID = socket.m_SocketID;
	m_Blocking = socket.m_Blocking;
	m_AF = socket.m_AF;
	m_Type = socket.m_Type;
	m_Protocol = socket.m_Protocol;
	m_ListenAddress = socket.m_ListenAddress;
	m_PeerAddress = socket.m_PeerAddress;
	m_TimeOut = socket.m_Blocking;

	socket.m_SocketID = INVALID_SOCKET;
	return *this;
}
Socket::~Socket()
{
	::closesocket(m_SocketID);
}

Socket* Socket::Accept()
{
	sockaddr_in clientAddr;
	int addrLen = sizeof(clientAddr);
	SOCKET clientSocket = ::accept(m_SocketID, (sockaddr*)&clientAddr, &addrLen);
	if (clientSocket == INVALID_SOCKET)
	{
		return nullptr;
	}

	Socket* socket = new Socket(clientSocket, m_Blocking, m_AF, m_Type, m_Protocol);
	socket->SetPeerAddress(clientAddr);

	printf("accept addr:[%s], port[%d]\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	return socket;
}
int Socket::Bind(const char* ipAddress, int port)
{
	memset(&m_ListenAddress, 0, sizeof(m_ListenAddress));
	m_ListenAddress.sin_family = m_AF;
	m_ListenAddress.sin_addr.s_addr = inet_addr(ipAddress);
	m_ListenAddress.sin_port = htons(port);
	return ::bind(m_SocketID, (sockaddr*)&m_ListenAddress, sizeof(m_ListenAddress));
}
int Socket::Close()
{
	return ::closesocket(m_SocketID);
}
int Socket::Connect(const char* ipAddress, unsigned int port)
{
	::memset(&m_PeerAddress, 0, sizeof(m_PeerAddress));
	m_PeerAddress.sin_family = m_AF;
	m_PeerAddress.sin_addr.s_addr = inet_addr(ipAddress);
	m_PeerAddress.sin_port = htons(port);

	return ::connect(m_SocketID, (sockaddr*)&m_PeerAddress, sizeof(m_PeerAddress));
}
bool Socket::GetBlocking()
{
	return m_Blocking;
}
sockaddr_in Socket::GetPeerName()
{
	return m_PeerAddress;
}
sockaddr_in Socket::GetSockName()
{
	return m_ListenAddress;
}
int Socket::GetSockOpt(int level, int optName, char* optValue, int* optLen)
{
	return ::getsockopt(m_SocketID, level, optName, optValue, optLen);
}
SOCKET Socket::GetSocketID()
{
	return m_SocketID;
}
int Socket::GetTimeOut()
{
	return m_TimeOut;
}
int Socket::Ioctl(long cmd, unsigned long* argp)
{
	return ::ioctlsocket(m_SocketID, cmd, argp);
}
int Socket::Listen(int backLog)
{
	return ::listen(m_SocketID, backLog);
}
int Socket::Recv(char* data, int len, int flags)
{
	return ::recv(m_SocketID, data, len, flags);
}
int Socket::RecvFrom(char* data, int len, int flags, sockaddr* from, int* fromLen)
{
	return ::recvfrom(m_SocketID, data, len, flags, from, fromLen);
}
int Socket::Send(const char* data, int len, int flags)
{
	return ::send(m_SocketID, data, len, flags);
}
int Socket::SendTo(const char* data, int len, int flags, const sockaddr* toAddr, int toLen)
{
	return ::sendto(m_SocketID, data, len, flags, toAddr, toLen);
}
int Socket::SetBlocking(bool blocking)
{
	unsigned long flag = !blocking;
	int ret = ::ioctlsocket(m_SocketID, FIONBIO, &flag);
	if (ret == 0)
	{
		m_Blocking = blocking;
	}
	return ret;
}
void Socket::SetPeerAddress(const sockaddr_in& peerAddr)
{
	m_PeerAddress = peerAddr;
}
int Socket::SetSockOpt(int level, int optName, const char* optValue, int optLen)
{
	return ::setsockopt(m_SocketID, level, optName, optValue, optLen);
}
int Socket::SetTimeOut(int timeOut)
{
	int ret = ::setsockopt(m_SocketID, SOL_SOCKET, SO_SNDTIMEO, (char*)&m_TimeOut, sizeof(m_TimeOut));
	if (ret == 0)
	{
		m_TimeOut = timeOut;
	}
	return ret;
}
int Socket::ShutDown(int how)
{
	return ::shutdown(m_SocketID, how);
}