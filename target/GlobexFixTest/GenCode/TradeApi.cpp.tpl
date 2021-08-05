#pragma once
#include "TradeApi.h"
#include "Logger.h"
#include "TcpThread.h"
#include "GlobalParam.h"


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

int TradeApi::SendResendRequest(ReqHeader* reqField)
{
	auto len = reqField->ToStream(m_SendBuff);
	
	reqField->ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "%s", m_LogBuff);
	
	return TcpThread::GetInstance().Send(m_SessionID, m_SendBuff, len);
}
	
!!entry ReqFields!!
!!travel!!
int TradeApi::!!@name!!(!!@name!!Field* reqField)
{
	auto len = reqField->ToStream(m_SendBuff);
	
	reqField->ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "%s", m_LogBuff);

!!if @name != "ReqSequenceReset":!!
!!inc indent!!
	GlobalParam::GetInstance().IncreaseNextSendSeqNum();
!!dec indent!!
	return TcpThread::GetInstance().Send(m_SessionID, m_SendBuff, len);
}

!!leave!!
!!leave!!
