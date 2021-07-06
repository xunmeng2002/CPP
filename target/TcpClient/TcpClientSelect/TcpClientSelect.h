#pragma once
#include "SocketInit.h"
#include "ThreadBase.h"
#include "CacheList.h"
#include "ConnectData.h"
#include <map>
#include <list>



class TcpClientSelect : public ThreadBase
{
private:
	TcpClientSelect(const char* name = "TcpClientSelect");
	TcpClientSelect(const TcpClientSelect&) = delete;
	TcpClientSelect& operator=(const TcpClientSelect&) = delete;

public:
	static TcpClientSelect& GetInstance();

	void SetTcpInfo(long micro_seconds = 1000000, int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
	bool Init();

	int Connect(const char* ip, unsigned short port);
	void DisConnect(int sessionID);
	bool Send(int sessionID, const char* data, int length);

protected:
	virtual void Run();

private:
	void DisConnectSessions();
	void PrepareFds();
	void OnSend();
	void OnRecv();

	void ExecuteCommand(int sessionID);
	void AddConnect(int sessionID, SOCKET socketID, const char* ip, unsigned short port);
	void RemoveConnect(int sessionID);
	void ClearSessions();

private:
	static TcpClientSelect m_Instance;

	char m_ServerIP[32];
	int m_Port;
	int m_AF;
	int m_Type;
	int m_Protocol;
	sockaddr_in m_ServerAddress;
	int m_AddressLen;
	int m_MaxSessionID;
	char m_RecvBuffer[MAX_SINGLE_MESSAGE_LENGTH];

	fd_set m_RecvFds;
	fd_set m_SendFds;
	timeval m_TimeOut;

	std::map<SOCKET, int> m_SocketIndex;

	std::mutex m_ConnectDataMutex;
	std::map<int, ConnectData*> m_ConnectDatas;

	std::mutex m_DisConnectSessionMutex;
	std::list<int> m_DisConnectSessions;
};


void TcpClientSelectTest();