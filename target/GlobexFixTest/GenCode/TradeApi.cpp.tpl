#pragma once
#include "TradeApi.h"
#include "GlobalParam.h"
#include "WorkThread.h"


TradeApi::TradeApi(TcpClient* tcpClient)
	:m_TcpClient(tcpClient), m_SessionID(0)
{
	m_LogBuff = new char[BUFF_SIZE];
}

void TradeApi::OnSessionConnected(int sessionID)
{
	m_SessionID = sessionID;
}

void TradeApi::SendResendRequest(ReqHeader* reqField)
{
	TcpEvent* tcpEvent = TcpEvent::Allocate();
	tcpEvent->EventID = EVENT_ON_TCP_SEND;
	tcpEvent->SessionID = m_SessionID;
	auto len = reqField->ToStream(tcpEvent->Buff);
	tcpEvent->Length = len;
	
	reqField->ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "%s", m_LogBuff);
	
	WorkThread::GetInstance().UpdateLastSendTime();
	m_TcpClient->Send(tcpEvent);
}

void TradeApi::ReqSequenceReset(ReqSequenceResetField* reqField)
{
	TcpEvent* tcpEvent = TcpEvent::Allocate();
	tcpEvent->EventID = EVENT_ON_TCP_SEND;
	tcpEvent->SessionID = m_SessionID;
	auto len = reqField->ToStream(tcpEvent->Buff);
	tcpEvent->Length = len;
	
	reqField->ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "%s", m_LogBuff);

	WorkThread::GetInstance().UpdateLastSendTime();
	m_TcpClient->Send(tcpEvent);
}
	
!!entry ReqFields!!
!!travel!!
!!if @name != "ReqSequenceReset":!!
!!inc indent!!
void TradeApi::!!@name!!(!!@name!!Field* reqField)
{
	SendRequest(reqField);
}

!!dec indent!!
!!leave!!
!!leave!!
