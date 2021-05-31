#pragma once

#include "ThostFtdcTraderSpiMiddle.h"
#include <set>
#include <string>


typedef char TThostFtdcAccountTypeType[10];

struct AccountInfo
{
	TThostFtdcAccountTypeType AccountType;
	TThostFtdcBrokerIDType	BrokerID;
	TThostFtdcUserIDType	UserID;
	TThostFtdcPasswordType	Password;
	TThostFtdcProductInfoType	UserProductInfo;
	TThostFtdcAuthCodeType	AuthCode;
	TThostFtdcAppIDType	AppID;
	std::set<std::string> FrontAddrs;
};

class CThostFtdcTraderSpiImpl : public CThostFtdcTraderSpiMiddle
{
public:
	CThostFtdcTraderSpiImpl(CThostFtdcTraderApi* traderApi);

	virtual void OnFrontConnected();

	virtual void OnFrontDisconnected(int nReason);

	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField* TradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
	
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* InvestorPosition, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryOrder(CThostFtdcOrderField* Order, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryTrade(CThostFtdcTradeField* Trade, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

public:
	void SetAccountInfo(AccountInfo* accountInfo);

private:
	void ReqAuthenticate();
	void ReqUserLogin();
	void ReqQryInstrument();
	void ReqQryTradingAccount();
	void ReqQryInvestorPosition();
	void ReqQryOrder();
	void ReqQryTrade();

private:
	CThostFtdcTraderApi* m_TraderApi;
	int m_RequestID;

	AccountInfo* m_AccountInfo;
};
