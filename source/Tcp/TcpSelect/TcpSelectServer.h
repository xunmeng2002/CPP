#pragma once
#include "TcpSelectBase.h"


class TcpSelectServer : public TcpSelectBase
{
public:
	TcpSelectServer();

	void SetBindAddress(const char* ip, int port, int backLog = 5);
	virtual bool Init() override;

protected:
	int Bind();
	int Listen();
	virtual void PrepareFds() override;
	virtual void DoAccept() override;


private:
	SOCKET m_ListenSocket;
	sockaddr_in m_ListenAddress;
	int m_Backlog;
};