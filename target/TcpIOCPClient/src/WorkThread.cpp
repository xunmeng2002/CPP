#include "WorkThread.h"
#include "Logger.h"
#include "TcpIOCPClient.h"

using namespace std;

WorkThread::WorkThread(int workThreadID)
	:WorkThreadBase(workThreadID), m_MessageBuffer("")
{

}
WorkThread::~WorkThread()
{

}

void WorkThread::CloseConnects()
{
	lock_guard<mutex> guard(m_SessionIDMutex);
	for (auto it : m_SessionIDs)
	{
		TcpIOCPClient::GetInstance().CloseConnect(it.first);
	}
}
void WorkThread::SendTestMessage(const std::string& message)
{
	for (auto& it : m_SessionIDs)
	{
		SendTestMessage(it.first, message);
	}
}

void WorkThread::HandleNewConnect(SocketData* socketData)
{
	WorkThreadBase::HandleNewConnect(socketData);

	SendTestMessage(socketData->SessionID, "First Connect.");
}
void WorkThread::HandleRecvMessage(SocketData* socketData)
{
	socketData->FormatBuffer();
	WRITE_LOG(LogLevel::Debug, "RecvMessage  WorkThread:[%d] SessionID:[%d] Socket:[%lld] Len:[%d] Data:[%s].",
		m_WorkThreadID, socketData->SessionID, socketData->ConnectSocket, socketData->WsaBuffer.len, socketData->WsaBuffer.buf);
}

void WorkThread::SendTestMessage(int sessionID, const std::string& message)
{
	sprintf(m_MessageBuffer, "Message From TcpIOCPClient, On WorkThread:[%d], SessionID:[%d] Message:[%s]", m_WorkThreadID, sessionID, message.c_str());
	if (!TcpIOCPClient::GetInstance().Send(sessionID, m_MessageBuffer, strlen(m_MessageBuffer)))
	{
		WRITE_LOG(LogLevel::Warning, "Tcp Send Failed. On WorkThread:[%d], SessionID:[%d]", m_WorkThreadID, sessionID);
		TcpIOCPClient::GetInstance().CloseConnect(sessionID);
	}
}