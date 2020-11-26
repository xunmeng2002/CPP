#include "SocketInit.h"
#include <iostream>

static SocketInit _SOCKET_INIT;

SocketInit::SocketInit()
{
	WSADATA initData;
	initData.wVersion = 0;
	initData.wHighVersion = 2;
	strcpy(initData.szDescription, "");
	strcpy(initData.szSystemStatus, "");
	initData.iMaxSockets = 100;
	initData.lpVendorInfo = nullptr;
	if (WSAStartup(2, &initData) != 0)
	{
		std::cout << "SocketInit Failed!" << std::endl;
	}
}

SocketInit::~SocketInit()
{
	WSACleanup();
}

