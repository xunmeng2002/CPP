#include "ThostFtdcTraderSpiImpl.h"
#include "Logger.h"


CThostFtdcTraderSpiImpl::CThostFtdcTraderSpiImpl(CThostFtdcTraderApi* traderApi)
	:m_TraderApi(traderApi), m_RequestID(0), m_AccountInfo(nullptr)
{
}
void CThostFtdcTraderSpiImpl::OnFrontConnected()
{
	WRITE_LOG(LogLevel::Info, "OnFrontConnected");

	ReqAuthenticate();
}
void CThostFtdcTraderSpiImpl::OnFrontDisconnected(int nReason)
{
	WRITE_LOG(LogLevel::Info, "OnFrontDisconnected, nReason[%d]", nReason);
}
void CThostFtdcTraderSpiImpl::OnHeartBeatWarning(int nTimeLapse)
{
	WRITE_LOG(LogLevel::Info, "OnHeartBeatWarning, nTimeLapse[%d]", nTimeLapse);
}
void CThostFtdcTraderSpiImpl::OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspAuthenticate, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
	WriteAuthenticate(pRspAuthenticateField);
	ReqUserLogin();
}
void CThostFtdcTraderSpiImpl::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspUserLogin, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
	WriteRspInfo(pRspInfo);
	WriteUserLoginField(pRspUserLogin);
	ReqQryInstrument();
}
void CThostFtdcTraderSpiImpl::OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspUserLogout, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField* pUserPasswordUpdate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspUserPasswordUpdate, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField* pTradingAccountPasswordUpdate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspTradingAccountPasswordUpdate, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField* pRspUserAuthMethod, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspUserAuthMethod, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField* pRspGenUserCaptcha, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspGenUserCaptcha, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspGenUserText(CThostFtdcRspGenUserTextField* pRspGenUserText, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspGenUserText, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspOrderInsert, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspParkedOrderInsert(CThostFtdcParkedOrderField* pParkedOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspParkedOrderInsert, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField* pParkedOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspParkedOrderAction, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspOrderAction(CThostFtdcInputOrderActionField* pInputOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspOrderAction, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField* pQueryMaxOrderVolume, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQueryMaxOrderVolume, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspSettlementInfoConfirm, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField* pRemoveParkedOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspRemoveParkedOrder, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField* pRemoveParkedOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspRemoveParkedOrderAction, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspExecOrderInsert(CThostFtdcInputExecOrderField* pInputExecOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspExecOrderInsert, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField* pInputExecOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspExecOrderAction, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspForQuoteInsert(CThostFtdcInputForQuoteField* pInputForQuote, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspForQuoteInsert, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQuoteInsert(CThostFtdcInputQuoteField* pInputQuote, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQuoteInsert, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQuoteAction(CThostFtdcInputQuoteActionField* pInputQuoteAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQuoteAction, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField* pInputBatchOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspBatchOrderAction, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField* pInputOptionSelfClose, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspOptionSelfCloseInsert, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField* pInputOptionSelfCloseAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspOptionSelfCloseAction, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspCombActionInsert(CThostFtdcInputCombActionField* pInputCombAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspCombActionInsert, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryOrder(CThostFtdcOrderField* pOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryOrder, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryTrade(CThostFtdcTradeField* pTrade, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTrade, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInvestorPosition, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTradingAccount, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryInvestor(CThostFtdcInvestorField* pInvestor, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInvestor, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryTradingCode(CThostFtdcTradingCodeField* pTradingCode, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTradingCode, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField* pInstrumentMarginRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInstrumentMarginRate, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField* pInstrumentCommissionRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInstrumentCommissionRate, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryExchange(CThostFtdcExchangeField* pExchange, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryExchange, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryProduct(CThostFtdcProductField* pProduct, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryProduct, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInstrument, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
	WriteRspInfo(pRspInfo);
	WriteInstrumentField(pInstrument);
}
void CThostFtdcTraderSpiImpl::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryDepthMarketData, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField* pSettlementInfo, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySettlementInfo, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryTransferBank(CThostFtdcTransferBankField* pTransferBank, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTransferBank, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField* pInvestorPositionDetail, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInvestorPositionDetail, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryNotice(CThostFtdcNoticeField* pNotice, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryNotice, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySettlementInfoConfirm, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField* pInvestorPositionCombineDetail, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInvestorPositionCombineDetail, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField* pCFMMCTradingAccountKey, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryCFMMCTradingAccountKey, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField* pEWarrantOffset, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryEWarrantOffset, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField* pInvestorProductGroupMargin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInvestorProductGroupMargin, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField* pExchangeMarginRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryExchangeMarginRate, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField* pExchangeMarginRateAdjust, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryExchangeMarginRateAdjust, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryExchangeRate(CThostFtdcExchangeRateField* pExchangeRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryExchangeRate, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField* pSecAgentACIDMap, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySecAgentACIDMap, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryProductExchRate(CThostFtdcProductExchRateField* pProductExchRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryProductExchRate, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryProductGroup(CThostFtdcProductGroupField* pProductGroup, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryProductGroup, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField* pMMInstrumentCommissionRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryMMInstrumentCommissionRate, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField* pMMOptionInstrCommRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryMMOptionInstrCommRate, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField* pInstrumentOrderCommRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInstrumentOrderCommRate, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySecAgentTradingAccount, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField* pSecAgentCheckMode, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySecAgentCheckMode, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField* pSecAgentTradeInfo, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySecAgentTradeInfo, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField* pOptionInstrTradeCost, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryOptionInstrTradeCost, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField* pOptionInstrCommRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryOptionInstrCommRate, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryExecOrder(CThostFtdcExecOrderField* pExecOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryExecOrder, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryForQuote(CThostFtdcForQuoteField* pForQuote, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryForQuote, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryQuote(CThostFtdcQuoteField* pQuote, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryQuote, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField* pOptionSelfClose, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryOptionSelfClose, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryInvestUnit(CThostFtdcInvestUnitField* pInvestUnit, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInvestUnit, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField* pCombInstrumentGuard, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryCombInstrumentGuard, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryCombAction(CThostFtdcCombActionField* pCombAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryCombAction, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryTransferSerial(CThostFtdcTransferSerialField* pTransferSerial, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTransferSerial, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspQryAccountregister(CThostFtdcAccountregisterField* pAccountregister, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryAccountregister, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspError, nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
}
void CThostFtdcTraderSpiImpl::OnRtnOrder(CThostFtdcOrderField* pOrder)
{
	WRITE_LOG(LogLevel::Info, "OnRtnOrder");
}
void CThostFtdcTraderSpiImpl::OnRtnTrade(CThostFtdcTradeField* pTrade)
{
	WRITE_LOG(LogLevel::Info, "OnRtnTrade");
}
void CThostFtdcTraderSpiImpl::OnErrRtnOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnOrderInsert");
}
void CThostFtdcTraderSpiImpl::OnErrRtnOrderAction(CThostFtdcOrderActionField* pOrderAction, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnOrderAction");
}
void CThostFtdcTraderSpiImpl::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField* pInstrumentStatus)
{
	WRITE_LOG(LogLevel::Info, "OnRtnInstrumentStatus");
	WriteInstrumentStatus(pInstrumentStatus);
}
void CThostFtdcTraderSpiImpl::OnRtnBulletin(CThostFtdcBulletinField* pBulletin)
{
	WRITE_LOG(LogLevel::Info, "OnRtnBulletin");
}
void CThostFtdcTraderSpiImpl::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField* pTradingNoticeInfo)
{
	WRITE_LOG(LogLevel::Info, "OnRtnTradingNotice");
}
void CThostFtdcTraderSpiImpl::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField* pErrorConditionalOrder)
{
	WRITE_LOG(LogLevel::Info, "OnRtnErrorConditionalOrder");
}
void CThostFtdcTraderSpiImpl::OnRtnExecOrder(CThostFtdcExecOrderField* pExecOrder)
{
	WRITE_LOG(LogLevel::Info, "OnRtnExecOrder");
}
void CThostFtdcTraderSpiImpl::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField* pInputExecOrder, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnExecOrderInsert");
}
void CThostFtdcTraderSpiImpl::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField* pExecOrderAction, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnExecOrderAction");
}
void CThostFtdcTraderSpiImpl::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField* pInputForQuote, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnForQuoteInsert");
}
void CThostFtdcTraderSpiImpl::OnRtnQuote(CThostFtdcQuoteField* pQuote)
{
	WRITE_LOG(LogLevel::Info, "OnRtnQuote");
}
void CThostFtdcTraderSpiImpl::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField* pInputQuote, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnQuoteInsert");
}
void CThostFtdcTraderSpiImpl::OnErrRtnQuoteAction(CThostFtdcQuoteActionField* pQuoteAction, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnQuoteAction");
}
void CThostFtdcTraderSpiImpl::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField* pForQuoteRsp)
{
	WRITE_LOG(LogLevel::Info, "OnRtnForQuoteRsp");
}
void CThostFtdcTraderSpiImpl::OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField* pCFMMCTradingAccountToken)
{
	WRITE_LOG(LogLevel::Info, "OnRtnCFMMCTradingAccountToken");
}
void CThostFtdcTraderSpiImpl::OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField* pBatchOrderAction, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnBatchOrderAction");
}
void CThostFtdcTraderSpiImpl::OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField* pOptionSelfClose)
{
	WRITE_LOG(LogLevel::Info, "OnRtnOptionSelfClose");
}
void CThostFtdcTraderSpiImpl::OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField* pInputOptionSelfClose, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnOptionSelfCloseInsert");
}
void CThostFtdcTraderSpiImpl::OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField* pOptionSelfCloseAction, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnOptionSelfCloseAction");
}
void CThostFtdcTraderSpiImpl::OnRtnCombAction(CThostFtdcCombActionField* pCombAction)
{
	WRITE_LOG(LogLevel::Info, "OnRtnCombAction");
}
void CThostFtdcTraderSpiImpl::OnErrRtnCombActionInsert(CThostFtdcInputCombActionField* pInputCombAction, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnCombActionInsert");
}
void CThostFtdcTraderSpiImpl::OnRspQryContractBank(CThostFtdcContractBankField* pContractBank, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryContractBank");
}
void CThostFtdcTraderSpiImpl::OnRspQryParkedOrder(CThostFtdcParkedOrderField* pParkedOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryParkedOrder");
}
void CThostFtdcTraderSpiImpl::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField* pParkedOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryParkedOrderAction");
}
void CThostFtdcTraderSpiImpl::OnRspQryTradingNotice(CThostFtdcTradingNoticeField* pTradingNotice, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTradingNotice");
}
void CThostFtdcTraderSpiImpl::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField* pBrokerTradingParams, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryBrokerTradingParams");
}
void CThostFtdcTraderSpiImpl::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField* pBrokerTradingAlgos, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryBrokerTradingAlgos");
}
void CThostFtdcTraderSpiImpl::OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField* pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQueryCFMMCTradingAccountToken");
}
void CThostFtdcTraderSpiImpl::OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField* pRspTransfer)
{
	WRITE_LOG(LogLevel::Info, "OnRtnFromBankToFutureByBank");
}
void CThostFtdcTraderSpiImpl::OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField* pRspTransfer)
{
	WRITE_LOG(LogLevel::Info, "OnRtnFromFutureToBankByBank");
}
void CThostFtdcTraderSpiImpl::OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField* pRspRepeal)
{
	WRITE_LOG(LogLevel::Info, "OnRtnRepealFromBankToFutureByBank");
}
void CThostFtdcTraderSpiImpl::OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField* pRspRepeal)
{
	WRITE_LOG(LogLevel::Info, "OnRtnRepealFromFutureToBankByBank");
}
void CThostFtdcTraderSpiImpl::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField* pRspTransfer)
{
	WRITE_LOG(LogLevel::Info, "OnRtnFromBankToFutureByFuture");
}
void CThostFtdcTraderSpiImpl::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField* pRspTransfer)
{
	WRITE_LOG(LogLevel::Info, "OnRtnFromFutureToBankByFuture");
}
void CThostFtdcTraderSpiImpl::OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField* pRspRepeal)
{
	WRITE_LOG(LogLevel::Info, "OnRtnRepealFromBankToFutureByFutureManual");
}
void CThostFtdcTraderSpiImpl::OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField* pRspRepeal)
{
	WRITE_LOG(LogLevel::Info, "OnRtnRepealFromFutureToBankByFutureManual");
}
void CThostFtdcTraderSpiImpl::OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField* pNotifyQueryAccount)
{
	WRITE_LOG(LogLevel::Info, "OnRtnQueryBankBalanceByFuture");
}
void CThostFtdcTraderSpiImpl::OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField* pReqTransfer, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnBankToFutureByFuture");
}
void CThostFtdcTraderSpiImpl::OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField* pReqTransfer, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnFutureToBankByFuture");
}
void CThostFtdcTraderSpiImpl::OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField* pReqRepeal, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnRepealBankToFutureByFutureManual");
}
void CThostFtdcTraderSpiImpl::OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField* pReqRepeal, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnRepealFutureToBankByFutureManual");
}
void CThostFtdcTraderSpiImpl::OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField* pReqQueryAccount, CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnQueryBankBalanceByFuture");
}
void CThostFtdcTraderSpiImpl::OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField* pRspRepeal)
{
	WRITE_LOG(LogLevel::Info, "OnRtnRepealFromBankToFutureByFuture");
}
void CThostFtdcTraderSpiImpl::OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField* pRspRepeal)
{
	WRITE_LOG(LogLevel::Info, "OnRtnRepealFromFutureToBankByFuture");
}
void CThostFtdcTraderSpiImpl::OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField* pReqTransfer, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspFromBankToFutureByFuture");
}
void CThostFtdcTraderSpiImpl::OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField* pReqTransfer, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspFromFutureToBankByFuture");
}
void CThostFtdcTraderSpiImpl::OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField* pReqQueryAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQueryBankAccountMoneyByFuture");
}
void CThostFtdcTraderSpiImpl::OnRtnOpenAccountByBank(CThostFtdcOpenAccountField* pOpenAccount)
{
	WRITE_LOG(LogLevel::Info, "OnRtnOpenAccountByBank");
}
void CThostFtdcTraderSpiImpl::OnRtnCancelAccountByBank(CThostFtdcCancelAccountField* pCancelAccount)
{
	WRITE_LOG(LogLevel::Info, "OnRtnCancelAccountByBank");
}
void CThostFtdcTraderSpiImpl::OnRtnChangeAccountByBank(CThostFtdcChangeAccountField* pChangeAccount)
{
	WRITE_LOG(LogLevel::Info, "OnRtnChangeAccountByBank");
}


void CThostFtdcTraderSpiImpl::SetAccountInfo(AccountInfo* accountInfo)
{
	m_AccountInfo = accountInfo;
}

void CThostFtdcTraderSpiImpl::WriteRspInfo(CThostFtdcRspInfoField* pRspInfo)
{
	if (pRspInfo)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspInfoField: ErrorID[%d], ErrorMsg[%s]", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
	}
}
void CThostFtdcTraderSpiImpl::WriteAuthenticate(CThostFtdcRspAuthenticateField* authenticate)
{
	if (authenticate)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspAuthenticateField: BrokerID[%s], UserID[%s], UserProductInfo[%s], AppID[%s], AppType[%c]", 
			authenticate->BrokerID, authenticate->UserID, authenticate->UserProductInfo, authenticate->AppID, authenticate->AppType);
	}
}
void CThostFtdcTraderSpiImpl::WriteUserLoginField(CThostFtdcRspUserLoginField* userLogin)
{
	if (userLogin)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcRspUserLoginField: "
			"TradingDay[%s], LoginTime[%s], BrokerID[%s], UserID[%s], SystemName[%s], FrontID[%d], "
			"SessionID[%d], MaxOrderRef[%s], SHFETime[%s], DCETime[%s], CZCETime[%s], FFEXTime[%s], INETime[%s]",
			userLogin->TradingDay, userLogin->LoginTime, userLogin->BrokerID, userLogin->UserID, userLogin->SystemName, userLogin->FrontID,
			userLogin->SessionID, userLogin->MaxOrderRef, userLogin->SHFETime, userLogin->DCETime, userLogin->CZCETime, userLogin->FFEXTime, userLogin->INETime);
	}
}
void CThostFtdcTraderSpiImpl::WriteInstrumentStatus(CThostFtdcInstrumentStatusField* instrumentStatus)
{
	if (instrumentStatus)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInstrumentStatusField: ExchangeID[%s], ExchangeInstID[%s], SettlementGroupID[%s], InstrumentID[%s], InstrumentStatus[%c], "
			"TradingSegmentSN[%d], EnterTime[%s], EnterReason[%c]",
			instrumentStatus->ExchangeID, instrumentStatus->ExchangeInstID, instrumentStatus->SettlementGroupID, instrumentStatus->InstrumentID, instrumentStatus->InstrumentStatus,
			instrumentStatus->TradingSegmentSN, instrumentStatus->EnterTime, instrumentStatus->EnterReason);
	}
}
void CThostFtdcTraderSpiImpl::WriteInstrumentField(CThostFtdcInstrumentField* instrument)
{
	if (instrument)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdcInstrumentField: "
			"InstrumentID[%s], ExchangeID[%s], InstrumentName[%s], ExchangeInstID[%s], ProductID[%s], ProductClass[%c], "
			"DeliveryYear[%d], DeliveryMonth[%d], MaxMarketOrderVolume[%d], MinMarketOrderVolume[%d], MaxLimitOrderVolume[%d], MinLimitOrderVolume[%d], "
			"VolumeMultiple[%d], PriceTick[%f], CreateDate[%s], OpenDate[%s], ExpireDate[%s], StartDelivDate[%s], "
			"EndDelivDate[%s], InstLifePhase[%C], IsTrading[%d], PositionType[%c], PositionDateType[%c], LongMarginRatio[%f], "
			"ShortMarginRatio[%f], MaxMarginSideAlgorithm[%c], UnderlyingInstrID[%s], StrikePrice[%d], OptionsType[%c], UnderlyingMultiple[%d], "
			"CombinationType[%c]",
			instrument->InstrumentID, instrument->ExchangeID, instrument->InstrumentName, instrument->ExchangeInstID, instrument->ProductID, instrument->ProductClass,
			instrument->DeliveryYear, instrument->DeliveryMonth, instrument->MaxMarketOrderVolume, instrument->MinMarketOrderVolume, instrument->MaxLimitOrderVolume, instrument->MinLimitOrderVolume,
			instrument->VolumeMultiple, instrument->PriceTick, instrument->CreateDate, instrument->OpenDate, instrument->ExpireDate, instrument->StartDelivDate,
			instrument->EndDelivDate, instrument->InstLifePhase, instrument->IsTrading, instrument->PositionType, instrument->PositionDateType, instrument->LongMarginRatio,
			instrument->ShortMarginRatio, instrument->MaxMarginSideAlgorithm, instrument->UnderlyingInstrID, instrument->StrikePrice, instrument->OptionsType, instrument->UnderlyingMultiple,
			instrument->CombinationType);
	}
}

void CThostFtdcTraderSpiImpl::ReqAuthenticate()
{
	CThostFtdcReqAuthenticateField authenticate;
	::memset(&authenticate, 0, sizeof(authenticate));
	strcpy(authenticate.BrokerID, m_AccountInfo->BrokerID);
	strcpy(authenticate.UserID, m_AccountInfo->UserID);
	strcpy(authenticate.UserProductInfo, m_AccountInfo->UserProductInfo);
	strcpy(authenticate.AuthCode, m_AccountInfo->AuthCode);
	strcpy(authenticate.AppID, m_AccountInfo->AppID);

	int ret = m_TraderApi->ReqAuthenticate(&authenticate, m_RequestID++);
	WRITE_LOG(LogLevel::Info, "ReqAuthenticate: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqUserLogin()
{
	CThostFtdcReqUserLoginField userLogin;
	::memset(&userLogin, 0, sizeof(userLogin));
	strcpy(userLogin.TradingDay, "");
	strcpy(userLogin.BrokerID, m_AccountInfo->BrokerID);
	strcpy(userLogin.UserID, m_AccountInfo->UserID);
	strcpy(userLogin.Password, m_AccountInfo->Password);
	strcpy(userLogin.UserProductInfo, m_AccountInfo->UserProductInfo);

	int ret = m_TraderApi->ReqUserLogin(&userLogin, m_RequestID++);
	WRITE_LOG(LogLevel::Info, "ReqUserLogin: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqQryInstrument()
{
	CThostFtdcQryInstrumentField qryInstrument;
	::memset(&qryInstrument, 0, sizeof(qryInstrument));
	int ret = m_TraderApi->ReqQryInstrument(&qryInstrument, m_RequestID++);
	WRITE_LOG(LogLevel::Info, "ReqQryInstrument: ret[%d]", ret);
}