#pragma once

#include "t2sdk_interface.h"
#include "HsFutuSystemInfo.h"


class CUFXTraderApi
{
public:
	CUFXTraderApi();
	~CUFXTraderApi();
	//ע��ǰ�û������ַ
	void RegisterFront(const char* pszFrontAddress);
	//��ʼ�����Ӷ���
	int InitConfig(const char* pszLicFile, const char* pszSafeLevel = "", const char* pszPwd = "", const char* pszSslFile = "", const char* pszSslPwd = "");

	///331480 ��͸ʽ��֤����
	int ReqGetClientConnectionSessionID(const char* pszFundAccount, const char* pszPassword);
	///331481 �ͻ�����֤����
	int ReqClientAuth(const char* pszFundAccount, const char* pszAppId, const char* pszAuthCode);
	///331482 �ͻ���ϵͳ��Ϣ�ϱ�����
	int ReqClientSysInfoSubmit(const char* pszFundAccount, const char* pszAppId);
	//331100 ����
	int ReqClientLogin(const char* pszFundAccount, const char* pszPassword, char cEntrustWay);
	//338202�ڻ�ί��ȷ��
	int ReqOrderInsert(const char* pszExchangeType, const char* pszFutuCode, char cEntrustBs, char cFuturesDirection, int nEntrustAmount, double dFutuEntrustPrice);
	//338217�ڻ�����ί��
	int ReqOrderAction(int nEntrustNo);
	//338301�ڻ�ί�в�ѯ
	int ReqOrderQry(const char* pszPositionStr, int nRequestNum);
	//338302�ڻ��ɽ���ѯ
	int ReqTradeQry();
	//338303�ڻ��ֲֲ�ѯ
	int ReqInvestorPositionQry();

	//620001_33101�ڻ�����ί�гɽ��ر�����
	int SubscribeEntrustDeal(int nIssueType);

private:
	CConfigInterface* m_pConfig;
	CConnectionInterface* m_pConnection;

	char m_FrontAddress[64];

};



