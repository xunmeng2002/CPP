#include "WorkThread.h"
#include "Logger.h"
#include "TcpIOCPServer.h"

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
		TcpIOCPServer::GetInstance().CloseConnect(it.first);
	}
}
void WorkThread::SendTestMessage(const std::string& message)
{
	for (auto it : m_SessionIDs)
	{
		SendTestMessage(it.first, message);
	}
}


void WorkThread::HandleRecvMessage(SocketData* socketData)
{
	socketData->FormatBuffer();
	WRITE_LOG(LogLayer::Normal, LogLevel::Info, "WorkThread:[%d] RecvMessage SessionID:[%d] Socket:[%lld], Len:[%d], Data:[%s].",
		m_WorkThreadID, socketData->SessionID, socketData->ConnectSocket, socketData->WsaBuffer.len, socketData->WsaBuffer.buf);

	char responseMessage[256] = { 0 };
	sprintf(responseMessage, "Server Recv Message Len:[%d].", socketData->WsaBuffer.len);
	if (!TcpIOCPServer::GetInstance().Send(socketData->SessionID, responseMessage, strlen(responseMessage)))
	{
		TcpIOCPServer::GetInstance().CloseConnect(socketData->SessionID);
	}
}

void WorkThread::SendTestMessage(int sessionID, const std::string& message)
{
	sprintf(m_MessageBuffer, "Message From TcpIOCPServer Data:[%s]", message.c_str());
	WRITE_LOG(LogLayer::Normal, LogLevel::Info, "SendTestMessage, Len:[%d].", strlen(m_MessageBuffer));
	if (!TcpIOCPServer::GetInstance().Send(sessionID, m_MessageBuffer, strlen(m_MessageBuffer)))
	{
		WRITE_LOG(LogLayer::Normal, LogLevel::Info, "Tcp Send Failed. On WorkThread:[%d], SessionID:[%d]", m_WorkThreadID, sessionID);
		TcpIOCPServer::GetInstance().CloseConnect(sessionID);
	}
}