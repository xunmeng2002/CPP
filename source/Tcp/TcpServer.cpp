#include "TcpServer.h"
#include "CacheList.h"

using namespace std;


TcpServer::TcpServer(int af, int type, int protocol, int microSeconds)
	:TcpBase(microSeconds), m_MaxSessionID(0)
{
	m_ListenSocket = new Socket(af, type, protocol);
}
TcpServer::~TcpServer()
{
	delete m_ListenSocket;

	for (auto& it : m_Sockets)
	{
		delete  it.second;
	}
	for (auto& it : m_SendCacheLists)
	{
		delete  it.second;
	}

	m_Sockets.clear();
	m_SendCacheLists.clear();
}

int TcpServer::Bind(const char* ipAddress, int port)
{
	return m_ListenSocket->Bind(ipAddress, port);
}
int TcpServer::Listen(int backLog)
{
	m_BackLog = backLog;
	return m_ListenSocket->Listen(backLog);
}
void TcpServer::Accept()
{
	for (auto i = 0; i < m_BackLog; i++)
	{
		Socket* socket = m_ListenSocket->Accept();
		if (socket == nullptr)
		{
			break;
		}
		auto sessionID = m_MaxSessionID++;
		m_Sockets.insert(make_pair(sessionID, socket));
		m_SendCacheLists.insert(make_pair(sessionID, new CacheList()));
	}
}
void TcpServer::Close()
{
	m_ListenSocket->Close();
}

void TcpServer::PrepareFds()
{
	FD_ZERO(&m_RecvFds);
	FD_ZERO(&m_SendFds);
	FD_SET(m_ListenSocket->GetSocketID(), &m_RecvFds);

	for (auto& it : m_SendCacheLists)
	{
		auto socketID = m_Sockets[it.first]->GetSocketID();
		FD_SET(socketID, &m_RecvFds);
		if (!it.second->IsEmpty())
		{
			FD_SET(socketID, &m_SendFds);
		}
	}
}
bool TcpServer::SendEvent(unsigned int sessionID, int eventID)
{
	return true;
}
void TcpServer::Run()
{
	HandleEvents();
	PrepareFds();
	::select(0, &m_RecvFds, &m_SendFds, nullptr, &m_TimeOut);
	Accept();
	Send();
	Recv();
}

CacheList* TcpServer::GetSendCacheList(unsigned int sessionID)
{
	if (m_SendCacheLists.find(sessionID) == m_SendCacheLists.end())
	{
		return nullptr;
	}
	return m_SendCacheLists[sessionID];
}


void TcpServer::HandleEvents()
{

}
void TcpServer::Send()
{
	for (auto& it : m_SendCacheLists)
	{
		auto socket = m_Sockets[it.first];
		if (FD_ISSET(socket->GetSocketID(), &m_SendFds))
		{
			TcpBase::Send(it.first, socket, it.second);
		}
	}
}
void TcpServer::Recv()
{
	for (auto& it : m_Sockets)
	{
		auto socket = it.second;
		if (FD_ISSET(socket->GetSocketID(), &m_RecvFds))
		{
			TcpBase::Recv(it.first, socket);
		}
	}
}