#pragma once
#include "TcpSelectBase.h"
#include <list>


class TcpSelectClient : public TcpSelectBase
{
public:
	TcpSelectClient();

	virtual bool Init() override;
	virtual void Connect(const char* ip, int port) override;

protected:
	virtual void DoConnect(const string& ip, int port) override;
	void CheckConnect();

private:
	fd_set m_ConnectFds;
	std::list<ConnectData*> m_ConnectingSocket;
};