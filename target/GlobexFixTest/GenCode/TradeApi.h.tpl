#pragma once
#include "TradeApiReqFields.h"
#include <string>

using namespace std;

class TradeApi
{
public:
	TradeApi();
	
	void OnSessionConnected(int sessionID);
	
	void SendResendRequest(ReqHeader* reqField);
	
!!entry ReqFields!!
!!travel!!
	virtual void !!@name!!(!!@name!!Field* reqField);
	
!!leave!!
!!leave!!

protected:
	int m_SessionID;
	char* m_LogBuff;
};

