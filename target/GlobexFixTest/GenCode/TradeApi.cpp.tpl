#pragma once
#include "TradeApi.h"
#include "Logger.h"
#include "TcpThread.h"


TradeApi::TradeApi()
	:m_SessionID(0)
{
	m_SendBuff = new char[BUFF_SIZE];
	m_LogBuff = new char[BUFF_SIZE];
}

void TradeApi::OnSessionConnected(int sessionID)
{
	m_SessionID = sessionID;
}
	
!!entry ReqFields!!
!!travel!!
int TradeApi::!!@name!!(!!@name!!Field* reqField)
{
	auto len = reqField->ToStream(m_SendBuff);
	
	reqField->ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "%s", m_LogBuff);
	return TcpThread::GetInstance().Send(m_SessionID, m_SendBuff, len);
}

!!leave!!
!!leave!!
