#pragma once
#include "TcpEvent.h"


class TcpServer
{
public:
	virtual void DisConnect(int sessionID) = 0;
	virtual void Send(int sessionID, const char* data, int length) = 0;
	virtual void Send(TcpEvent* tcpEvent) = 0;
};