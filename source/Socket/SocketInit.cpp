#include "SocketInit.h"
#include <iostream>


SocketInit SocketInit::m_SocketInit;

SocketInit::SocketInit()
{
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
}