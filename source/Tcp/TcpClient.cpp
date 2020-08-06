#include "TcpClient.h"

using namespace std;

TcpClient::TcpClient(int af, int type, int protocol, int microSeconds)
	:TcpBase(microSeconds), m_SessionID(0), m_MaxSessionID(0), m_Connected(false)
{
	m_SessionID = 0;
	m_Socket = new Socket(af, type, protocol);
	m_SendCacheList = new CacheList();
	m_RecvBuffer = new char[MAX_SINGLE_RECV_BUFF_LEN];
}
TcpClient::~TcpClient()
{
	delete m_Socket;
	delete m_SendCacheList;
}

int TcpClient::Connect(const char* ipAddress, unsigned int port)
{
	int ret = m_Socket->Connect(ipAddress, port);
	if (ret < 0)
	{
		return ret;
	}
	m_SessionID = m_MaxSessionID++;
	m_Connected = true;
	return ret;
}
void TcpClient::Close()
{
	m_Socket->Close();
}

void TcpClient::PrepareFds()
{
	FD_ZERO(&m_RecvFds);
	FD_ZERO(&m_SendFds);
	
	auto socketID = m_Socket->GetSocketID();
	FD_SET(socketID, &m_RecvFds);
	if (!m_SendCacheList->IsEmpty())
	{
		FD_SET(socketID, &m_SendFds);
	}
}
bool TcpClient::SendEvent(unsigned int sessionID, int eventID)
{
	return true;
}
void TcpClient::Run()
{
	HandleEvents();
	PrepareFds();
	::select(0, &m_RecvFds, &m_SendFds, nullptr, &m_TimeOut);
	Send();
	Recv();
}

CacheList* TcpClient::GetSendCacheList(unsigned int sessionID)
{
	if (m_Connected)
	{
		return m_SendCacheList;
	}
	return nullptr;
}


void TcpClient::HandleEvents()
{

}
void TcpClient::Send()
{
	auto socketID = m_Socket->GetSocketID();
	if (FD_ISSET(socketID, &m_SendFds))
	{
		TcpBase::Send(m_SessionID, m_Socket, m_SendCacheList);
	}
}
void TcpClient::Recv()
{
	if (FD_ISSET(m_Socket->GetSocketID(), &m_RecvFds))
	{
		TcpBase::Recv(m_SessionID, m_Socket);
	}
}
