#pragma once

#include "t2sdk_interface.h"
#include "HsFutuSystemInfo.h"


class CUFXTraderApi
{
public:
	CUFXTraderApi();
	~CUFXTraderApi();
	//注册前置机网络地址
	void RegisterFront(const char* pszFrontAddress);
	//初始化连接对象
	int InitConfig(const char* pszLicFile, const char* pszSafeLevel = "", const char* pszPwd = "", const char* pszSslFile = "", const char* pszSslPwd = "");

	///331480 穿透式认证请求
	int ReqGetClientConnectionSessionID(const char* pszFundAccount, const char* pszPassword);
	///331481 客户端认证请求
	int ReqClientAuth(const char* pszFundAccount, const char* pszAppId, const char* pszAuthCode);
	///331482 客户端系统信息上报请求
	int ReqClientSysInfoSubmit(const char* pszFundAccount, const char* pszAppId);
	//331100 登入
	int ReqClientLogin(const char* pszFundAccount, const char* pszPassword, char cEntrustWay);
	//338202期货委托确认
	int ReqOrderInsert(const char* pszExchangeType, const char* pszFutuCode, char cEntrustBs, char cFuturesDirection, int nEntrustAmount, double dFutuEntrustPrice);
	//338217期货撤单委托
	int ReqOrderAction(int nEntrustNo);
	//338301期货委托查询
	int ReqOrderQry(const char* pszPositionStr, int nRequestNum);
	//338302期货成交查询
	int ReqTradeQry();
	//338303期货持仓查询
	int ReqInvestorPositionQry();

	//620001_33101期货订阅委托成交回报功能
	int SubscribeEntrustDeal(int nIssueType);

private:
	CConfigInterface* m_pConfig;
	CConnectionInterface* m_pConnection;

	char m_FrontAddress[64];

};



