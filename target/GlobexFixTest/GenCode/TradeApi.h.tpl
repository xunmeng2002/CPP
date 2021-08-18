#pragma once
#include "TradeApiReqFields.h"
#include "Event.h"
#include "Logger.h"
#include <string>

using namespace std;

class TradeApi
{
public:
	TradeApi();
	
	void OnSessionConnected(int sessionID);
	
	void SendResendRequest(ReqHeader* reqField);
	
	virtual void ReqSequenceReset(ReqSequenceResetField* reqField);
	
!!entry ReqFields!!
!!travel!!
!!if @name != "ReqSequenceReset":!!
!!inc indent!!
	virtual void !!@name!!(!!@name!!Field* reqField);

!!dec indent!!
!!leave!!
!!leave!!

protected:
	template<typename T>
	void SendRequest(T* reqField)
	{
		TcpEvent* tcpEvent = TcpEvent::Allocate();
		tcpEvent->EventID = EVENT_ON_TCP_SEND;
		tcpEvent->SessionID = m_SessionID;
		auto len = reqField->ToStream(tcpEvent->Buff);
		tcpEvent->Length = len;

		reqField->ToString(m_LogBuff, BUFF_SIZE);
		WRITE_LOG(LogLevel::Info, "%s", m_LogBuff);

		GlobalParam::GetInstance().IncreaseNextSendSeqNum();
		WorkThread::GetInstance().UpdateLastSendTime();
		TcpThread::GetInstance().Send(tcpEvent);
	}

protected:
	int m_SessionID;
	char* m_LogBuff;
};

