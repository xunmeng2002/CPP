#pragma once
#include "SocketInit.h"
#include "ThreadBase.h"
#include "CacheList.h"
#include "ConnectData.h"
#include <map>
#include <list>



class TcpServerSelect : public ThreadBase
{
private:
	TcpServerSelect(const char* name = "TcpServerSelect");
	TcpServerSelect(const TcpServerSelect&) = delete;
	TcpServerSelect& operator=(const TcpServerSelect&) = delete;

public:
	static TcpServerSelect& GetInstance();

	void SetTcpInfo(unsigned short port, long micro_seconds = 1000000, int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, int backlog = 5);
	bool Init();

	void DisConnect(int sessionID);
	bool Send(int sessionID, const char* data, int length);

protected:
	virtual void Run();

private:
	bool Listen();
	void DisConnectSessions();
	void PrepareFds();
	void OnAccept();
	void OnSend();
	void OnRecv();

	void AddConnect(int sessionID, SOCKET socketID, const char* ip, unsigned short port);
	void RemoveConnect(int sessionID);
	void ClearSessions();

private:
	static TcpServerSelect m_Instance;

	SOCKET m_ListenSocketID;
	int m_Port;
	int m_AF;
	int m_Type;
	int m_Protocol;
	int m_Backlog;
	sockaddr_in m_ServerAddress;
	sockaddr_in m_ClientAddress;
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


void TcpServerSelectTest();