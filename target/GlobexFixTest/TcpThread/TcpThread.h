#pragma once
#include "SocketInit.h"
#include "ThreadBase.h"
#include "ConnectData.h"
#include "MyEvent.h"
#include <mutex>
#include <map>
#include <list>

#define MAX_SINGLE_MESSAGE_LENGTH 1024 * 64

class TcpThread : public ThreadBase
{
	TcpThread(const char* name = "TcpThread");
	TcpThread(const TcpThread&) = delete;
	TcpThread& operator=(const TcpThread&) = delete;
public:
	static TcpThread& GetInstance();

	void SetTcpInfo(long micro_seconds = 1000000, int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
	bool Init();
	void Connect(const char* ip, unsigned short port);
	void DisConnect(int sessionID);
	bool Send(int sessionID, const char* data, int length);

	virtual void Run();
	void HandleEvent();
	void DoConnect(const string& ip, int port);
	void DoDisConnect(int sessionID);
	void OnConncect();
	void PrepareFds();
	void OnSend();
	void OnRecv();

	void NotifyConnectStatus(const string& ip, int port, int sessionID, int eventID);
	void AddSessionData(ConnectData* connectData);
	void RemoveSessionData(ConnectData* connectData);
	ConnectData* GetSessionData(int sessionID);

private:
	static TcpThread m_Instance;

	int m_Port;
	int m_AF;
	int m_Type;
	int m_Protocol;
	sockaddr_in m_ServerAddress;
	int m_AddressLen;

	int m_MaxSessionID;
	char m_RecvBuffer[MAX_SINGLE_MESSAGE_LENGTH];

	fd_set m_ConnectFds;
	fd_set m_RecvFds;
	fd_set m_SendFds;
	timeval m_ConnectTimeOut;
	timeval m_TimeOut;

	std::list<ConnectData*> m_ConnectingSocket;
	
	std::map<int, ConnectData*> m_ConnectDatas;
	std::mutex m_ConnectDataMutex;
};