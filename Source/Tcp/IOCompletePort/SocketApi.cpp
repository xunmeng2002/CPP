#include "SocketApi.h"
#include "Logger.h"

SocketApi SocketApi::m_Instance;

SocketApi::SocketApi()
{
	AcceptEx = nullptr;
	GetAcceptExSockAddrs = nullptr;
	ConnectEx = nullptr;
	DisconnectEx = nullptr;
}
SocketApi::~SocketApi()
{

}

SocketApi& SocketApi::GetInstance()
{
	return m_Instance;
}
bool SocketApi::Init(SOCKET sock)
{
	GUID guidAcceptEx = WSAID_ACCEPTEX;
	GUID guidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
	GUID guidConnectEx = WSAID_CONNECTEX;
	GUID guidDisconnectEx = WSAID_DISCONNECTEX;

	DWORD dwBytes = 0;
	if (SOCKET_ERROR == WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptEx, sizeof(guidAcceptEx),
		&AcceptEx, sizeof(AcceptEx), &dwBytes, NULL, NULL))
	{
		WRITE_ERROR_LOG(WSAGetLastError(), "Get AcceptEx Func Failed.");
		return false;
	}

	if (SOCKET_ERROR == WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidGetAcceptExSockAddrs, sizeof(guidGetAcceptExSockAddrs),
		&GetAcceptExSockAddrs, sizeof(GetAcceptExSockAddrs), &dwBytes, NULL, NULL))
	{
		WRITE_ERROR_LOG(WSAGetLastError(), "Get GetAcceptExSockAddrs Func Failed.");
		return false;
	}

	if (SOCKET_ERROR == WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidConnectEx, sizeof(guidConnectEx),
		&ConnectEx, sizeof(ConnectEx), &dwBytes, NULL, NULL))
	{
		WRITE_ERROR_LOG(WSAGetLastError(), "Get ConnectEx Func Failed.");
		return false;
	}

	if (SOCKET_ERROR == WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidDisconnectEx, sizeof(guidDisconnectEx),
		&DisconnectEx, sizeof(DisconnectEx), &dwBytes, NULL, NULL))
	{
		WRITE_ERROR_LOG(WSAGetLastError(), "Get DisconnectEx Func Failed.");
		return false;
	}
	return true;
}