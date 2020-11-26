#include <map>
#include "SocketInit.h"
#include "SocketDataStruct.h"
#include "ThreadBase.h"


class TcpBase : public ThreadBase
{
public:
	TcpBase(const char* name);
	~TcpBase();

	virtual bool Init() = 0;

	bool Send(int sessionID, const char* data, int len);
	void CloseConnect(int sessionID);

protected:
	bool PostSend(int sessionID, SOCKET sock, const char* data, int len, int& sendLen);
	bool PostRecv(int sessionID, SOCKET sock);
	bool PostDisConnect(SocketData* socketData);

	void OnSendComplete(SocketData* socketData, int len);
	void OnRecvComplete(SocketData* socketData, int len);

	void AddConnect(SocketData* socketData);
	void RemoveConnect(SocketData* socketData);

protected:
	int m_LastSessionID;
	std::map<int, ConnectInfo> m_ConnectInfos;
};

