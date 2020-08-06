#ifndef SOCKET_INIT_H
#define SOCKET_INIT_H

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

class SocketInit
{
public:
	SocketInit();

private:
	static SocketInit m_SocketInit;
};

#endif
