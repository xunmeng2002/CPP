#ifndef __h_thost_ftdc_mdspi_h__
#define __h_thost_ftdc_mdspi_h__

#include "ThostFtdcMdApi.h"

struct ThostFtdcMdSpi_C;
class CThostFtdcMdSpiImpl : public CThostFtdcMdSpi
{
public:
	CThostFtdcMdSpiImpl();

	void RegisterSpi(ThostFtdcMdSpi_C* spi);

	virtual void OnFrontConnected();

	virtual void OnFrontDisconnected(int nReason);

	virtual void OnHeartBeatWarning(int nTimeLapse);

	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData);

	virtual void OnRtnExchangeStatus(CThostFtdcExchangeStatusField* pExchangeStatus);

	virtual void OnRtnOptionsInfo(CThostFtdcOptionsInfoField* pOptionsInfo);

	virtual void OnRtnTemplateMarketData(int nTemplateID, void* pMarketData);

private:
	ThostFtdcMdSpi_C* m_spi;
};


#endif