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

	bool Send(const string& funcName, ReqFieldBase* reqField);



	int ReqLogon();

	int ReqLogout();

	int ReqHeartBeat(const string& testReqID = "");

	int ReqTestRequest();

	int ReqResendRequest(int startSeqNum, int endSeqNum);

	int ReqSequenceReset(string msgSeqNum);

	int ReqNewOrder();



	void OnRspLogon(RspFieldBase* rspField);

	void OnRspLogout(RspFieldBase* rspField);

	void OnRspHeartBeat(RspFieldBase* rspField);

	void OnRspTestRequest(RspFieldBase* rspField);

	void OnSessionLevelReject(RspFieldBase* rspField);

	void OnResendRequest(RspFieldBase* rspField);

	void OnRspSequenceReset(RspFieldBase* rspField);

private:
	void SetHead(ReqFieldBase* reqField);

	void CheckAndUpdateRecvSeqNum(string seqNum);

	RspFieldBase* ParseRspField();

	void ResetMarks();

private:
	int m_SessionID;
	ConnectStatus m_ConnectStatus;
	AccountInfo* m_AccountInfo;
	LogonStatus m_AccountLogonStatus;
	bool m_IsOnResendRequest;
	int m_ResendSendSeqNum;
	int m_ResendStartSeqNum;
	int m_ResendEndSeqNum;

	string m_SenderCompID;
	

	char* m_SendBuff;
	char* m_ParseBuff;
	int m_ParseBuffDataLen;
	CacheList* m_CacheList;
	FixMessage* m_FixMessage;
	char* m_LogBuff;


	map<int, ReqFieldBase*> m_ReqFields;
	map<int, RspFieldBase*> m_RspFields;
};