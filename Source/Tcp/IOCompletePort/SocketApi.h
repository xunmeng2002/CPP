#pragma once

#include "SocketInit.h"

class SocketApi
{
private:
	SocketApi();
	~SocketApi();
	SocketApi(const SocketApi&) = delete;
	SocketApi& operator=(const SocketApi&) = delete;

public:
	static SocketApi& GetInstance();
	bool Init(SOCKET sock);

	LPFN_ACCEPTEX AcceptEx;
	LPFN_GETACCEPTEXSOCKADDRS GetAcceptExSockAddrs;
	LPFN_CONNECTEX ConnectEx;
	LPFN_DISCONNECTEX DisconnectEx;


private:
	static SocketApi m_Instance;
};