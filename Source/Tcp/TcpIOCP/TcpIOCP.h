#include <map>
#include <mutex>
#include "SocketInit.h"
#include "OverlappedData.h"
#include "ThreadBase.h"
#include "TcpInterface.h"
#include "ConnectData.h"


class TcpIOCP : public ThreadBase, public TcpPublisher
{
public:
	TcpIOCP(const char* name);
	~TcpIOCP();

	void SetLocalAddress(const char* ip = "127.0.0.1", int port = 0);
	void RegisterSubscriber(TcpSubscriber* tcpSubscriber);
	virtual bool Init();
	virtual void Stop() override;

	virtual void DisConnect(int sessionID) override;
	virtual void Send(int sessionID, const char* data, int len) override;
	virtual void Send(TcpEvent* tcpEvent) override;

protected:
	virtual void Run() override;
	virtual void ThreadExit() override;
	virtual void HandleEvent() override;
	virtual void HandleCompletePortEvent();

	bool PostConnect(const char* ip, int port);
	bool PostDisConnect(int sessionID);
	bool PostAccept();
	bool PostSend(TcpEvent* tcpEvent);
	bool PostRecv(int sessionID, SOCKET sock);

	void ConnectComplete(OverlappedData* overlappedData, int len);
	void DisConnectComplete(OverlappedData* overlappedData, int len);
	void AcceptComplete(OverlappedData* overlappedData, int len);
	void SendComplete(OverlappedData* overlappedData, int len);
	void RecvComplete(OverlappedData* overlappedData, int len);
	
	void AddConnect(OverlappedData* overlappedData);
	void RemoveConnect(OverlappedData* overlappedData);
	ConnectData* GetConnect(int sessionID);

	SOCKET AllocateSocket();
	SOCKET PrepareSocket();
	void FreeSocket(SOCKET socket);

protected:
	TcpSubscriber* m_TcpSubscriber;
	int m_LastSessionID;
	std::map<int, ConnectData*> m_ConnectDatas;

	long long m_TotalSendLen;
	long long m_TotalRecvLen;

	SOCKET m_InitSocket;
	SOCKADDR_IN m_LocalAddress;
};

