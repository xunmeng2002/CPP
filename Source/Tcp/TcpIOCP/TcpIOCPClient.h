#pragma once

#include "TcpIOCP.h"


class TcpIOCPClient :public TcpIOCP
{
private:
	TcpIOCPClient();
	~TcpIOCPClient();
	TcpIOCPClient(const TcpIOCPClient&) = delete;
	TcpIOCPClient& operator=(const TcpIOCPClient&) = delete;
public:
	static TcpIOCPClient& GetInstance();

	virtual void Connect(const char* ip, int port) override;


private:
	static TcpIOCPClient m_Instance;
};