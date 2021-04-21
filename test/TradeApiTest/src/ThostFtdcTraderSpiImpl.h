#pragma once

#include "ThostFtdcTraderSpiMiddle.h"
#include "UserData.h"

class CThostFtdcTraderSpiImpl : public CThostFtdcTraderSpiMiddle
{
public:
	CThostFtdcTraderSpiImpl(CThostFtdcTraderApi* traderApi);

	virtual void OnFrontConnected();

	virtual void OnFrontDisconnected(int nReason);

	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

public:
	void SetAccountInfo(AccountInfo* accountInfo);

private:
	void ReqAuthenticate();
	void ReqUserLogin();
	void ReqQryInstrument();

private:
	CThostFtdcTraderApi* m_TraderApi;
	int m_RequestID;

	AccountInfo* m_AccountInfo;
};
