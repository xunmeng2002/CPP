#pragma once
#include "TradeSpi.h"
#include "Logger.h"


TradeSpi::TradeSpi()
{
	m_LogBuff = new char[BUFF_SIZE];
}
TradeSpi::~TradeSpi()
{
	if (m_LogBuff)
	{
		delete m_LogBuff;
	}
	m_LogBuff = nullptr;
}

!!entry RspFields!!
!!travel!!
void TradeSpi::On!!@name!!(FixMessage* fixMessage)
{
	!!@name!!Field rspField(fixMessage);
	rspField.ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "%s", m_LogBuff);
}
void TradeSpi::On!!@name!!(!!@name!!Field* rspField)
{
	rspField->ToString(m_LogBuff, BUFF_SIZE);
	WRITE_LOG(LogLevel::Info, "%s", m_LogBuff);
}

!!leave!!
!!leave!!
