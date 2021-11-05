#include "Udp.h"
#include "Logger.h"
#include "zip/zlib.h"
#include <stdio.h>
#include <iostream>

using namespace std;

Udp Udp::m_Instance;

Udp::Udp()
{
	m_Socket = INVALID_SOCKET;
	memset(&m_BindAddress, 0, sizeof(m_BindAddress));
	memset(&m_RemoteAddress, 0, sizeof(m_BindAddress));
	m_RemoteAddressLen = sizeof(SOCKADDR);
}
Udp::~Udp()
{
	closesocket(m_Socket);
}
Udp& Udp::GetInstance()
{
	return m_Instance;
}
void Udp::SetBindAddress(const char* ip, int port)
{
	m_BindAddress.sin_family = AF_INET;
	m_BindAddress.sin_addr.S_un.S_addr = inet_addr(ip);
	m_BindAddress.sin_port = htons(port);

	WRITE_LOG(LogLevel::Info, "Udp SetBindAddress IP[%s], Port[%d]", ip, port);
}
void Udp::SetRemoteAddress(const char* ip, int port)
{
	m_RemoteAddress.sin_family = AF_INET;
	m_RemoteAddress.sin_addr.S_un.S_addr = inet_addr(ip);
	m_RemoteAddress.sin_port = htons(port);

	m_RemoteAddressLen = sizeof(m_RemoteAddress);
	
	WRITE_LOG(LogLevel::Info, "Udp SetRemoteAddress IP[%s], Port[%d]", ip, port);
}
bool Udp::Init(bool setBroadCast)
{
	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_Socket == INVALID_SOCKET)
	{
		WRITE_LOG(LogLevel::Error, "Create Udp Socket Failed.");
		Close();
		return false;
	}
	if (setBroadCast)
	{
		BOOL bBroadcast = TRUE;
		if (::setsockopt(m_Socket, SOL_SOCKET, SO_BROADCAST, (char*)&bBroadcast, sizeof(BOOL)) == SOCKET_ERROR)
		{
			WRITE_LOG(LogLevel::Error, "setsockopt SO_BROADCAST Failed.");
			Close();
			return false;
		}
	}
	auto ret = bind(m_Socket, (sockaddr*)&m_BindAddress, sizeof(SOCKADDR));
	if (ret == SOCKET_ERROR)
	{
		WRITE_LOG(LogLevel::Error, "bind Failed. ret[%d]", ret);
		Close();
		return false;
	}
	WRITE_LOG(LogLevel::Info, "Udp Init Successed.");
	return true;
}
void Udp::Close()
{
	closesocket(m_Socket);
	m_Socket = INVALID_SOCKET;
}

int Udp::SendTo(TcpEvent* tcpEvent)
{
	auto sendLen = ::sendto(m_Socket, tcpEvent->ReadPos, tcpEvent->Length, 0, (sockaddr*)&m_RemoteAddress, sizeof(m_RemoteAddress));
	WRITE_LOG(LogLevel::Info, "Udp SendTo:[%s:%u], Len:[%d], Ret:[%d]", inet_ntoa(m_RemoteAddress.sin_addr), ntohs(m_RemoteAddress.sin_port), tcpEvent->Length, sendLen);
	return sendLen;
}
int Udp::RecvFrom(TcpEvent* tcpEvent)
{
	int recvLen = recvfrom(m_Socket, tcpEvent->Buff, BuffSize - 1, 0, (SOCKADDR*)&m_RemoteAddress, &m_RemoteAddressLen);
	WRITE_LOG(LogLevel::Info, "Udp RecvFrom:[%s:%u], recvLen:[%d]", inet_ntoa(m_RemoteAddress.sin_addr), ntohs(m_RemoteAddress.sin_port), recvLen);
	tcpEvent->Length = recvLen;
	return recvLen;
}
bool Udp::ZipSendTo(TcpEvent* tcpEvent)
{
	WRITE_LOG(LogLevel::Info, "Udp ZipSendTo: Len:[%d], Buff:[%s]", tcpEvent->Length, tcpEvent->ReadPos);
	TcpEvent* tcpEvent2 = TcpEvent::Allocate();
	unsigned long destLen = BuffSize;
	auto ret = compress2((unsigned char*)tcpEvent2->Buff, &destLen, (unsigned char*)tcpEvent->Buff, tcpEvent->Length, Z_BEST_SPEED);
	auto result = true;
	if (ret != Z_OK)
	{
		WRITE_LOG(LogLevel::Error, "compress Failed. ret:[%d]", ret);
		result = false;
	}
	else
	{
		tcpEvent2->Length = destLen;
		result = SendTo(tcpEvent2) > 0;
	}
	tcpEvent2->Free();
	return result;
}
bool Udp::ZipRecvFrom(TcpEvent* tcpEvent)
{
	TcpEvent* tcpEvent2 = TcpEvent::Allocate();
	auto result = true;
	int len = RecvFrom(tcpEvent2);
	if (len <= 0)
	{
		tcpEvent2->Free();
		return false;
	}
	unsigned long sourceLen = len;
	unsigned long destLen = BuffSize - 1;
	auto ret = uncompress2((unsigned char*)tcpEvent->Buff, &destLen, (const unsigned char*)tcpEvent2->Buff, &sourceLen);
	if (ret != Z_OK)
	{
		WRITE_LOG(LogLevel::Error, "compress Failed. ret:[%d]", ret);
		result = false;
	}
	else
	{
		tcpEvent->Length += destLen;
		tcpEvent->Buff[tcpEvent->Length] = '\0';
		WRITE_LOG(LogLevel::Info, "Udp ZipRecvFrom: Len:[%d], Buff:[%s]", tcpEvent->Length, tcpEvent->ReadPos);
	}
	tcpEvent2->Free();
	return ret;
}

