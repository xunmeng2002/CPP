#pragma once

#include "TcpIOCP.h"


class TcpIOCPServer : public TcpIOCP
{
private:
	TcpIOCPServer();
	~TcpIOCPServer();
	TcpIOCPServer(const TcpIOCPServer&) = delete;
	TcpIOCPServer& operator=(const TcpIOCPServer&) = delete;
public:
	static TcpIOCPServer& GetInstance();
	virtual bool Init() override;

protected:
	virtual void ThreadInit();
	virtual void ThreadExit();
private:
	bool Bind();
	bool Listen(int backLog = 5);
	
private:
	static TcpIOCPServer m_Instance;
};

