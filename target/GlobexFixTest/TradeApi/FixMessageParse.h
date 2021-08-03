#pragma once
#include "TradeApiRspFields.h"
#include "TradeSpi.h"
#include "CacheList.h"
#include <string>

using namespace std;

class FixMessageParse
{
public:
	FixMessageParse(TradeSpi* tradeSpi);
	~FixMessageParse();
	
	void OnSessionDisConnected();
	
	void OnRecv(char* buff, int len);
	
	void Parse();
	
private:
	CacheList* m_CacheList;
	FixMessage* m_FixMessage;
	char* m_LogBuff;
	char* m_ParseBuff;
	int m_ParseBuffDataLen;
	
	TradeSpi* m_TradeSpi;
};

