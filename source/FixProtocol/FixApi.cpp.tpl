#include "FixApi.h"
#include "Logger.h"
#include "TcpEvent.h"


FixSpi::FixSpi()
{
	m_MdbPublisher = nullptr;
	m_FixLogBuff = new char[BuffSize];
}
FixSpi::~FixSpi()
{
	if (m_FixLogBuff)
	{
		delete m_FixLogBuff;
	}
	m_FixLogBuff = nullptr;
}
void FixSpi::OnFixConnected()
{
	WRITE_LOG(LogLevel::Info, "OnFixConnected");
}
void FixSpi::OnFixDisConnected()
{
	WRITE_LOG(LogLevel::Info, "OnFixDisConnected");
}
!!entry RspFields!!
!!travel!!
void FixSpi::OnFix!!@name!!(Fix!!@name!!Field* rspField)
{
	rspField->ToString(m_FixLogBuff, BuffSize);
	WRITE_LOG(LogLevel::Info, "OnFix!!@name!!: %s", m_FixLogBuff);
}
!!leave!!
!!leave!!


!!entry ReqFields!!
!!travel!!
void FixApi::!!@name!!(Fix!!@name!!Field* reqField)
{
	WRITE_LOG(LogLevel::Error, "!!@name!! was Not Implemented.");
}
!!leave!!
!!leave!!