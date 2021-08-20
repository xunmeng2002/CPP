#pragma once
#include "TcpEvent.h"

class TcpSubscriber
{
public:
	virtual void OnConnect(int sessionID, const char* ip, int port) = 0;
	virtual void OnDisConnect(int sessionID, const char* ip, int port) = 0;
	virtual void OnRecv(TcpEvent* tcpEvent) = 0;
};
