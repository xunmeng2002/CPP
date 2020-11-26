#include "WorkThread.h"
#include "Logger.h"
#include "TcpClient.h"

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
	for (auto sessionID : m_SessionIDs)
	{
		TcpClient::GetInstance().CloseConnect(sessionID);
	}
}
void WorkThread::SendTestMessage(const std::string& message)
{
	for (auto sessionID : m_SessionIDs)
	{
		SendTestMessage(sessionID, message);
	}
}

void WorkThread::HandleNewConnect(SocketData* socketData)
{
	{
		lock_guard<mutex> guard(m_SessionIDMutex);
		m_SessionIDs.insert(socketData->SessionID);
	}
	WRITE_LOG(LogLayer::Normal, LogLevel::Info, "WorkThread:[%d] NewConnect SessionID:%d", m_WorkThreadID, socketData->SessionID);

	SendTestMessage(socketData->SessionID, "First Connect.");
}
void WorkThread::HandleRecvMessage(SocketData* socketData)
{
	socketData->FormatBuffer();
	WRITE_LOG(LogLayer::Normal, LogLevel::Info, "RecvMessage WorkThread:[%d] SessionID:[%d] Socket:[%lld], Len:[%d], Data:[%s].",
		m_WorkThreadID, socketData->SessionID, socketData->ConnectSocket, socketData->WsaBuffer.len, socketData->WsaBuffer.buf);
}

void WorkThread::SendTestMessage(int sessionID, const std::string& message)
{
	sprintf(m_MessageBuffer, "Message From TcpClient, On WorkThread:[%d], SessionID:[%d] Message:[%s]", m_WorkThreadID, sessionID, message.c_str());
	WRITE_LOG(LogLayer::Normal, LogLevel::Info, "SendTestMessage, Len:[%d].", strlen(m_MessageBuffer));
	if (!TcpClient::GetInstance().Send(sessionID, m_MessageBuffer, strlen(m_MessageBuffer)))
	{
		WRITE_LOG(LogLayer::Normal, LogLevel::Info, "Tcp Send Failed. On WorkThread:[%d], SessionID:[%d]", m_WorkThreadID, sessionID);
		TcpClient::GetInstance().CloseConnect(sessionID);
	}
}