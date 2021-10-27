#include "UdpServer.h"
#include "Logger.h"
#include "zip/zlib.h"
#include <stdio.h>
#include <iostream>

using namespace std;

UdpServer UdpServer::m_Instance;

UdpServer::UdpServer()
{
	m_Socket = INVALID_SOCKET;
	memset(&m_BindAddress, 0, sizeof(m_BindAddress));
	memset(&m_BroadAddress, 0, sizeof(m_BindAddress));
}
UdpServer& UdpServer::GetInstance()
{
	return m_Instance;
}
void UdpServer::SetBindAddress(const char* ip, int port)
{
	m_BindAddress.sin_family = AF_INET;
	m_BindAddress.sin_addr.S_un.S_addr = inet_addr(ip);
	m_BindAddress.sin_port = htons(port);

	WRITE_LOG(LogLevel::Info, "UdpServer SetBindAddress IP[%s], Port[%d]", ip, port);
}
void UdpServer::SetBroadAddress(const char* ip, int port)
{
	m_BroadAddress.sin_family = AF_INET;
	m_BroadAddress.sin_addr.S_un.S_addr = inet_addr(ip);
	m_BroadAddress.sin_port = htons(port);
	
	WRITE_LOG(LogLevel::Info, "UdpServer SetBroadAddress IP[%s], Port[%d]", ip, port);
}
bool UdpServer::Init()
{
	m_Socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_Socket == INVALID_SOCKET)
	{
		WRITE_LOG(LogLevel::Error, "Create Udp Socket Failed.");
		return false;
	}
	BOOL bBroadcast = TRUE;
	if (::setsockopt(m_Socket, SOL_SOCKET, SO_BROADCAST, (char*)&bBroadcast, sizeof(BOOL)) == SOCKET_ERROR)
	{
		WRITE_LOG(LogLevel::Error, "setsockopt SO_BROADCAST Failed.");
		return false;
	}
	int iSize = 1024 * 1024;
	if (::setsockopt(m_Socket, SOL_SOCKET, SO_SNDBUF, (char*)&iSize, sizeof(int)) == SOCKET_ERROR)
	{
		WRITE_LOG(LogLevel::Error, "setsockopt SO_SNDBUF Failed.");
		return false;
	}
	if (::bind(m_Socket, (sockaddr*)&m_BindAddress, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		WRITE_LOG(LogLevel::Error, "bind Failed.");
		return false;
	}
	WRITE_LOG(LogLevel::Info, "UdpServer Init Successed.");
	return true;
}

int UdpServer::Send(TcpEvent* tcpEvent)
{
	auto ret = ::sendto(m_Socket, tcpEvent->ReadPos, tcpEvent->Length, 0, (sockaddr*)&m_BroadAddress, sizeof(m_BroadAddress));
	WRITE_LOG(LogLevel::Info, "Udp Send: Len:[%d], Ret:[%d]", tcpEvent->Length, ret);
	return ret;
}
int UdpServer::ZipSend(TcpEvent* tcpEvent)
{
	WRITE_LOG(LogLevel::Info, "Udp ZipSend: Len:[%d], Buff:[%s]", tcpEvent->Length, tcpEvent->ReadPos);
	TcpEvent* tcpEvent2 = TcpEvent::Allocate();
	unsigned long len = BuffSize;
	auto ret = compress2((unsigned char*)tcpEvent2->Buff, &len, (unsigned char*)tcpEvent->Buff, tcpEvent->Length, Z_BEST_SPEED);
	if (ret == Z_OK)
	{
		tcpEvent2->Length = len;
		ret = Send(tcpEvent2);
	}
	else
	{
		WRITE_LOG(LogLevel::Error, "compress Failed. ret:[%d]", ret);
	}
	tcpEvent->Free();
	tcpEvent2->Free();
	return ret;
}

