#pragma once
#include "TradeApi.h"
#include "Logger.h"
#include "TcpThread.h"
#include "GlobalParam.h"
#include "WorkThread.h"


TradeApi::TradeApi()
	:m_SessionID(0)
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
	
	TcpThread::GetInstance().Send(tcpEvent);
}
	
!!entry ReqFields!!
!!travel!!
void TradeApi::!!@name!!(!!@name!!Field* reqField)
{
	TcpEvent* tcpEvent = TcpEvent::Allocate();
	tcpEvent->EventID = EVENT_ON_TCP_SEND;
	tcpEvent->SessionID = m_SessionID;
	auto len = reqField->ToStream(tcpEvent->Buff);
	tcpEvent->Length = len;
	
	reqField->ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "%s", m_LogBuff);

!!if @name != "ReqSequenceReset":!!
!!inc indent!!
	GlobalParam::GetInstance().IncreaseNextSendSeqNum();
!!dec indent!!
	WorkThread::GetInstance().UpdateLastSendTime();
	TcpThread::GetInstance().Send(tcpEvent);
}

!!leave!!
!!leave!!
