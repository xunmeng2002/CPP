#pragma once
#include "SocketInit.h"
#include "ThreadBase.h"

class TcpServerSelect : public ThreadBase
{
public:
	TcpServerSelect(const char* name);

	bool Init(int port);

	bool Send();

protected:
	virtual void Run();

private:
	void OnAccept();
	void OnSend();
	void OnRecv();


};
