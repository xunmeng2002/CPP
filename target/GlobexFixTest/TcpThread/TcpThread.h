#pragma once
#include "SocketInit.h"
#include "ThreadBase.h"
#include "ConnectData.h"
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
	int Connect(const char* ip, unsigned short port);
	void DisConnect(int sessionID);
	bool Send(int sessionID, const char* data, int length);

	virtual void Run();
	void DisConnectSessions();
	void OnConncect();
	void PrepareFds();
	void OnSend();
	void OnRecv();

	void AddSessionData(ConnectData* connectData);
	void RemoveSessionData(ConnectData* connectData);
	ConnectData* GetSessionData(int sessionID);
	void ClearSessions();

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

	std::map<SOCKET, int> m_SocketIndex;

	std::list<ConnectData*> m_ConnectingSocket;
	std::mutex m_ConnectingSocketMutex;

	
	std::map<int, ConnectData*> m_ConnectDatas;
	std::mutex m_ConnectDataMutex;

	
	std::list<ConnectData*> m_DisConnectSessions;
	std::mutex m_DisConnectSessionMutex;
};