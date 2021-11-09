#pragma once
#include "Event.h"

class TcpSubscriber
{
public:
	virtual void OnConnect(int sessionID, const char* ip, int port) {}
	virtual void OnDisConnect(int sessionID, const char* ip, int port) {}
	virtual void OnRecv(TcpEvent* tcpEvent) {}
};

class TcpPublisher
{
public:
	virtual void Connect(const char* ip, int port) {}
	virtual void DisConnect(int sessionID) {}
	virtual void Send(int sessionID, const char* data, int len) {}
	virtual void Send(TcpEvent* tcpEvent) {}
};
