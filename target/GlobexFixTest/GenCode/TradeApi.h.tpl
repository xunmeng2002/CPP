#pragma once
#include "TradeApiReqFields.h"
#include <string>

using namespace std;

class TradeApi
{
public:
	TradeApi();
	
	void OnSessionConnected(int sessionID);
	
	int SendResendRequest(ReqHeader* reqField);
	
!!entry ReqFields!!
!!travel!!
	virtual int !!@name!!(!!@name!!Field* reqField);
	
!!leave!!
!!leave!!

protected:
	int m_SessionID;
	char* m_SendBuff;
	char* m_LogBuff;
};

