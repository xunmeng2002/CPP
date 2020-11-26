#pragma once
#include <WinSock2.h>
#include <MSWSock.h>
#pragma comment(lib,"ws2_32.lib")



class SocketInit
{
public:
	SocketInit();
	virtual ~SocketInit();
};

