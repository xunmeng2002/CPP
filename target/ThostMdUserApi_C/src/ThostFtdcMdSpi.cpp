#include "ThostFtdcMdSpi.h"
#include "ThostFtdcMdApi_C.h"

CThostFtdcMdSpiImpl::CThostFtdcMdSpiImpl()
	:m_spi(nullptr)
{
}
void CThostFtdcMdSpiImpl::RegisterSpi(ThostFtdcMdSpi_C* spi)
{
	m_spi = spi;
}

void CThostFtdcMdSpiImpl::OnFrontConnected()
{
	if (m_spi)
	{
		m_spi->onFrontConnected();
	}
}
void CThostFtdcMdSpiImpl::OnFrontDisconnected(int nReason)
{
	if (m_spi)
	{
		m_spi->onFrontDisconnected(nReason);
	}
}
void CThostFtdcMdSpiImpl::OnHeartBeatWarning(int nTimeLapse)
{
	if (m_spi)
	{
		m_spi->onHeartBeatWarning(nTimeLapse);
	}
}
void CThostFtdcMdSpiImpl::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_spi)
	{
		m_spi->onRspUserLogin(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
	}
}
void CThostFtdcMdSpiImpl::OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_spi)
	{
		m_spi->onRspUserLogout(pUserLogout, pRspInfo, nRequestID, bIsLast);
	}
}
void CThostFtdcMdSpiImpl::OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_spi)
	{
		m_spi->onRspError(pRspInfo, nRequestID, bIsLast);
	}
}
void CThostFtdcMdSpiImpl::OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_spi)
	{
		m_spi->onRspSubMarketData(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
	}
}
void CThostFtdcMdSpiImpl::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_spi)
	{
		m_spi->onRspUnSubMarketData(pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
	}
}
void CThostFtdcMdSpiImpl::OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (m_spi)
	{
		m_spi->onRspQryInstrument(pInstrument, pRspInfo, nRequestID, bIsLast);
	}
}
void CThostFtdcMdSpiImpl::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	if (m_spi)
	{
		m_spi->onRtnDepthMarketData(pDepthMarketData);
	}
}
void CThostFtdcMdSpiImpl::OnRtnExchangeStatus(CThostFtdcExchangeStatusField* pExchangeStatus)
{
	if (m_spi)
	{
		m_spi->onRtnExchangeStatus(pExchangeStatus);
	}
}
void CThostFtdcMdSpiImpl::OnRtnOptionsInfo(CThostFtdcOptionsInfoField* pOptionsInfo)
{
	if (m_spi)
	{
		m_spi->onRtnOptionsInfo(pOptionsInfo);
	}
}
void CThostFtdcMdSpiImpl::OnRtnTemplateMarketData(int nTemplateID, void* pMarketData)
{
	if (m_spi)
	{
		m_spi->onRtnTemplateMarketData(nTemplateID, pMarketData);
	}
}