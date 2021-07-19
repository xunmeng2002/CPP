#pragma once
#include "TradeApiDataStruct.h"
#include "TradeApiReqFields.h"
#include "TradeApiRspFields.h"
#include "AccountInfo.h"
#include "CacheList.h"
#include <map>

using namespace std;

class TradeApi
{
public:
	TradeApi(AccountInfo* accountInfo);

	void OnRecv(char* buff, int len);

	void Parse();

	void OnSessionConnected(int sessionID);

	void OnSessionDisConnected(int sessionID);

	void OnFixMessage();

	void CheckLogonStatus();


	int ReqLogon();

	int ReqHeartBeat(const string& testReqID);

	int ReqNewOrder();



	void OnRspLogon();

	void OnRspLogout();

	void OnRspHeartBeat();

	void OnRspTestRequest();

	void OnSessionLevelReject();

private:
	int m_SessionID;
	ConnectStatus m_ConnectStatus;
	AccountInfo* m_AccountInfo;
	LogonStatus m_AccountLogonStatus;


	string m_SenderCompID;
	bool m_SendOrderMark;

	char* m_SendBuff;
	char* m_ParseBuff;
	int m_ParseBuffDataLen;
	CacheList* m_CacheList;
	FixMessage* m_FixMessage;
	char* m_LogBuff;
};