#pragma once
#include "ThreadBase.h"
#include "TcpInterface.h"
#include "ConnectData.h"
#include <set>
#include <map>
#pragma once

using namespace std;

class WorkThread : public ThreadBase, public TcpSubscriber
{
	WorkThread();
	~WorkThread();
public:
	static WorkThread& GetInstance();
	void RegisterTcp(TcpPublisher* tcpPublisher);

	virtual void OnConnect(int sessionID, const char* ip, int port) override;
	virtual void OnDisConnect(int sessionID, const char* ip, int port) override;
	virtual void OnRecv(TcpEvent* tcpEvent) override;

	void CloseConnects();
	void Send(const char* data, int len);
protected:
	virtual void HandleEvent() override;

	void AddConnect(int sessionID, const char* ip, int port);
	void RemoveConnect(int sessionID, const char* ip, int port);
	void HandleRecvData(TcpEvent* tcpEvent);
	void HandleDisConnects();
	void HandleSendData(TcpEvent* tcpEvent);


private:
	static WorkThread m_Instance;

	TcpPublisher* m_TcpPublisher;
	map<int, ConnectData*> m_ConnectDatas;
};

