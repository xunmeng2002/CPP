#pragma once

#include <map>
#include "ThreadBase.h"
#include "SocketInit.h"
#include "TcpEvent.h"
#include "ConnectData.h"
#include "TcpSubscriber.h"
#include "TcpClient.h"
#include "TcpServer.h"


class TcpSelectBase : public ThreadBase, public TcpClient, public TcpServer
{
public:
	TcpSelectBase(const char* name, TcpSubscriber* subscriber);

	void SetTcpInfo(long timeOut = 1000000, int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
	virtual bool Init() = 0;
	virtual void Connect(const char* ip, int port) {}
	virtual void DisConnect(int sessionID) override;
	virtual void Send(int sessionID, const char* data, int length) override;
	virtual void Send(TcpEvent* tcpEvent) override;

protected:
	virtual void Run() override;
	virtual void HandleEvent();
	virtual void DoConnect(const string& ip, int port) {}
	virtual void DoDisConnect(int sessionID);
	virtual void PrepareFds();
	virtual void CheckConnect() {}
	virtual void DoAccept() {}
	virtual void DoSend();
	virtual void DoRecv();


	void AddConnect(ConnectData* connectData);
	void RemoveConnect(ConnectData* connectData);
	ConnectData* GetConnect(int sessionID);


	TcpEvent* GetSendEvent(int sessionID);
	void PushSendEvent(TcpEvent* tcpEvent);

protected:
	TcpSubscriber* m_Subscriber;

	int m_AF;
	int m_Type;
	int m_Protocol;
	sockaddr_in m_RemoteAddress;
	int m_AddressLen;

	int m_MaxSessionID;

	fd_set m_RecvFds;
	fd_set m_SendFds;
	timeval m_ConnectTimeOut;
	timeval m_TimeOut;

	std::map<int, ConnectData*> m_ConnectDatas;
	std::map<int, list<TcpEvent*>> m_SendEvents;
};
