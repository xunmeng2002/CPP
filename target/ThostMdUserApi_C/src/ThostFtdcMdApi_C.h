#ifndef __h_thost_ftdc_mdapi_h__
#define __h_thost_ftdc_mdapi_h__

#include "ThostFtdcMdSpi.h"
#ifdef PB_MD_API_IS_LIB
#define PB_API __declspec(dllexport)
#else
#define PB_API __declspec(dllimport)
#endif

extern "C"
{
	PB_API void CreateFtdcMdApi_C(const char *pszFlowPath = "", bool bIsUsingUdp = false, bool bIsMulticast = false, bool bIsLastQuot = true);

	PB_API void Release();

	PB_API void Init();

	PB_API int Join();

	PB_API const char *GetTradingDay();

	PB_API void RegisterFront(char *pszFrontAddress);

	PB_API void RegisterNameServer(char *pszNsAddress);

	PB_API void RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo);

	PB_API void RegisterSpi(ThostFtdcMdSpi_C* spi);

	PB_API int SubscribeMarketData(char *ppInstrumentID[], int nCount);

	PB_API int UnSubscribeMarketData(char *ppInstrumentID[], int nCount);

	PB_API int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID);

	PB_API int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID);

	PB_API int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID);
}

extern "C" 
{
	typedef PB_API void (*OnFrontConnected)();

	typedef PB_API void(*OnFrontDisconnected)(int nReason);

	typedef PB_API void(*OnHeartBeatWarning)(int nTimeLapse);

	typedef PB_API void(*OnRspUserLogin)(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	typedef PB_API void(*OnRspUserLogout)(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	typedef PB_API void(*OnRspError)(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	typedef PB_API void(*OnRspSubMarketData)(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	typedef PB_API void(*OnRspUnSubMarketData)(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	typedef PB_API void(*OnRspQryInstrument)(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	typedef PB_API void(*OnRtnDepthMarketData)(CThostFtdcDepthMarketDataField *pDepthMarketData);

	typedef PB_API void(*OnRtnExchangeStatus)(CThostFtdcExchangeStatusField *pExchangeStatus);

	typedef PB_API void(*OnRtnOptionsInfo)(CThostFtdcOptionsInfoField *pOptionsInfo);

	typedef PB_API void(*OnRtnTemplateMarketData)(int nTemplateID, void *pMarketData);

	struct ThostFtdcMdSpi_C
	{
		OnFrontConnected onFrontConnected;
		OnFrontDisconnected onFrontDisconnected;
		OnHeartBeatWarning onHeartBeatWarning;
		OnRspUserLogin onRspUserLogin;
		OnRspUserLogout onRspUserLogout;
		OnRspError onRspError;
		OnRspSubMarketData onRspSubMarketData;
		OnRspUnSubMarketData onRspUnSubMarketData;
		OnRspQryInstrument onRspQryInstrument;
		OnRtnDepthMarketData onRtnDepthMarketData;
		OnRtnExchangeStatus onRtnExchangeStatus;
		OnRtnOptionsInfo onRtnOptionsInfo;
		OnRtnTemplateMarketData onRtnTemplateMarketData;
	};
}

#endif //__H_THOST_FTDC_MD_API_C_H__