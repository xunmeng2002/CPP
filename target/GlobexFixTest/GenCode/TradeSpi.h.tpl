#pragma once
#include "TradeApiRspFields.h"


class TradeSpi
{
public:
	TradeSpi();
	virtual ~TradeSpi();
	
	virtual void OnFixMessage(FixMessage* fixMessage) = 0;
	
!!entry RspFields!!
!!travel!!
	virtual void On!!@name!!(FixMessage* fixMessage);
	virtual void On!!@name!!(!!@name!!Field* rspField);
	
!!leave!!
!!leave!!
protected:
	char* m_LogBuff;
};
