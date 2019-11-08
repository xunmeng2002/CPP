#include "SocketInit.h"
#include <iostream>

SocketInit::SocketInit()
{
#ifdef WIN32
	WSADATA initData;
	initData.wVersion = 0;
	initData.wHighVersion = 2;
	strcpy(initData.szDescription, "");
	strcpy(initData.szSystemStatus, "");
	initData.iMaxSockets = 100;
	initData.lpVendorInfo = nullptr;
	WSAStartup(2, &initData);
	if (WSAStartup(2, &initData) != 0)
	{
		std::cout << "SocketInit Failed!" << std::endl;
	}
#endif
}

SocketInit::~SocketInit()
{
#ifdef WIN32
	WSACleanup();
#endif
}

static SocketInit _SOCKET_INIT;