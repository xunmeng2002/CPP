#include "ThostFtdcMdApi_C.h"

static CThostFtdcMdSpiImpl* md_spi = nullptr;
static CThostFtdcMdApi* md_api = nullptr;

void CreateFtdcMdApi_C(const char* pszFlowPath, bool bIsUsingUdp, bool bIsMulticast, bool bIsLastQuot)
{
	if (md_api == nullptr)
	{
		md_api = CreateFtdcMdApi(pszFlowPath, bIsUsingUdp, bIsMulticast, bIsLastQuot);
	}
	if (md_spi == nullptr)
	{
		md_spi = new CThostFtdcMdSpiImpl();
	}
}
void Release()
{
	if (md_api)
	{
		md_api->Release();
	}
	md_api = nullptr;
	if (md_spi)
	{
		delete md_spi;
	}
	md_spi = nullptr;
}
void Init()
{
	md_api->Init();
}
int Join()
{
	return md_api->Join();
}
const char* GetTradingDay()
{
	return md_api->GetTradingDay();
}
void RegisterFront(char* pszFrontAddress)
{
	md_api->RegisterFront(pszFrontAddress);
}
void RegisterNameServer(char* pszNsAddress)
{
	md_api->RegisterNameServer(pszNsAddress);
}
void RegisterFensUserInfo(CThostFtdcFensUserInfoField* pFensUserInfo)
{
	md_api->RegisterFensUserInfo(pFensUserInfo);
}
void RegisterSpi(ThostFtdcMdSpi_C* spi)
{
	md_spi->RegisterSpi(spi);
	md_api->RegisterSpi(md_spi);
}
int SubscribeMarketData(char* ppInstrumentID[], int nCount)
{
	return md_api->SubscribeMarketData(ppInstrumentID, nCount);
}
int UnSubscribeMarketData(char* ppInstrumentID[], int nCount)
{
	return md_api->UnSubscribeMarketData(ppInstrumentID, nCount);
}
int ReqUserLogin(CThostFtdcReqUserLoginField* pReqUserLogin, int nRequestID)
{
	return md_api->ReqUserLogin(pReqUserLogin, nRequestID);
}
int ReqUserLogout(CThostFtdcUserLogoutField* pUserLogout, int nRequestID)
{
	return md_api->ReqUserLogout(pUserLogout, nRequestID);
}
int ReqQryInstrument(CThostFtdcQryInstrumentField* pQryInstrument, int nRequestID)
{
	return md_api->ReqQryInstrument(pQryInstrument, nRequestID);
}