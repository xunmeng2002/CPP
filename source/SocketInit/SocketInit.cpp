#include "SocketInit.h"
#include <iostream>

static SocketInit _SOCKET_INIT;

using namespace std;

SocketInit::SocketInit()
{
#ifdef WINDOWS
	cout << "ON WINDOWS" << endl;
	WSADATA initData;
	initData.wVersion = 0;
	initData.wHighVersion = 2;
	memset(initData.szDescription, 0, sizeof(initData.szDescription));
	memset(initData.szSystemStatus, 0, sizeof(initData.szSystemStatus));
	initData.iMaxSockets = 100;
	initData.lpVendorInfo = nullptr;
	if (WSAStartup(2, &initData) != 0)
	{
		std::cout << "SocketInit Failed!" << std::endl;
	}
#endif
#ifdef LINUX
	cout << "ON LINUX" << endl;
#endif
}

SocketInit::~SocketInit()
{
#ifdef WINDOWS
	WSACleanup();
#endif
}

