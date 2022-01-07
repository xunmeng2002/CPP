#include "ThostFtdcTraderSpiMiddle.h"
#include "Logger.h"
#include "StructWriteLogFunc.h"



void CThostFtdcTraderSpiMiddle::OnFrontConnected()
{
	WRITE_LOG(LogLevel::Info, "OnFrontConnected:");
}

void CThostFtdcTraderSpiMiddle::OnFrontDisconnected(, int nReason)
{
	WRITE_LOG(LogLevel::Info, "OnFrontDisconnected: nReason[%d]", nReason);
}

void CThostFtdcTraderSpiMiddle::OnHeartBeatWarning(, int nTimeLapse)
{
	WRITE_LOG(LogLevel::Info, "OnHeartBeatWarning: nTimeLapse[%d]", nTimeLapse);
}

void CThostFtdcTraderSpiMiddle::OnRspAuthenticate(, CThostFtdcRspAuthenticateField *RspAuthenticateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspAuthenticate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspAuthenticate(RspAuthenticate);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspUserLogin(, CThostFtdcRspUserLoginField *RspUserLoginCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspUserLogin: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspUserLogin(RspUserLogin);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspUserLogout(, CThostFtdcUserLogoutField *UserLogoutCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspUserLogout: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteUserLogout(UserLogout);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspUserPasswordUpdate(, CThostFtdcUserPasswordUpdateField *UserPasswordUpdateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspUserPasswordUpdate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteUserPasswordUpdate(UserPasswordUpdate);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspTradingAccountPasswordUpdate(, CThostFtdcTradingAccountPasswordUpdateField *TradingAccountPasswordUpdateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspTradingAccountPasswordUpdate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTradingAccountPasswordUpdate(TradingAccountPasswordUpdate);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspUserAuthMethod(, CThostFtdcRspUserAuthMethodField *RspUserAuthMethodCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspUserAuthMethod: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspUserAuthMethod(RspUserAuthMethod);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspGenUserCaptcha(, CThostFtdcRspGenUserCaptchaField *RspGenUserCaptchaCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspGenUserCaptcha: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspGenUserCaptcha(RspGenUserCaptcha);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspGenUserText(, CThostFtdcRspGenUserTextField *RspGenUserTextCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspGenUserText: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspGenUserText(RspGenUserText);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspOrderInsert(, CThostFtdcInputOrderField *InputOrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspOrderInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputOrder(InputOrder);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspParkedOrderInsert(, CThostFtdcParkedOrderField *ParkedOrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspParkedOrderInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteParkedOrder(ParkedOrder);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspParkedOrderAction(, CThostFtdcParkedOrderActionField *ParkedOrderActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspParkedOrderAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteParkedOrderAction(ParkedOrderAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspOrderAction(, CThostFtdcInputOrderActionField *InputOrderActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspOrderAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputOrderAction(InputOrderAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryMaxOrderVolume(, CThostFtdcQryMaxOrderVolumeField *QryMaxOrderVolumeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryMaxOrderVolume: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteQryMaxOrderVolume(QryMaxOrderVolume);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspSettlementInfoConfirm(, CThostFtdcSettlementInfoConfirmField *SettlementInfoConfirmCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspSettlementInfoConfirm: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSettlementInfoConfirm(SettlementInfoConfirm);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspRemoveParkedOrder(, CThostFtdcRemoveParkedOrderField *RemoveParkedOrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspRemoveParkedOrder: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRemoveParkedOrder(RemoveParkedOrder);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspRemoveParkedOrderAction(, CThostFtdcRemoveParkedOrderActionField *RemoveParkedOrderActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspRemoveParkedOrderAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRemoveParkedOrderAction(RemoveParkedOrderAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspExecOrderInsert(, CThostFtdcInputExecOrderField *InputExecOrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspExecOrderInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputExecOrder(InputExecOrder);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspExecOrderAction(, CThostFtdcInputExecOrderActionField *InputExecOrderActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspExecOrderAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputExecOrderAction(InputExecOrderAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspForQuoteInsert(, CThostFtdcInputForQuoteField *InputForQuoteCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspForQuoteInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputForQuote(InputForQuote);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQuoteInsert(, CThostFtdcInputQuoteField *InputQuoteCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQuoteInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputQuote(InputQuote);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQuoteAction(, CThostFtdcInputQuoteActionField *InputQuoteActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQuoteAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputQuoteAction(InputQuoteAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspBatchOrderAction(, CThostFtdcInputBatchOrderActionField *InputBatchOrderActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspBatchOrderAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputBatchOrderAction(InputBatchOrderAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspOptionSelfCloseInsert(, CThostFtdcInputOptionSelfCloseField *InputOptionSelfCloseCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspOptionSelfCloseInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputOptionSelfClose(InputOptionSelfClose);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspOptionSelfCloseAction(, CThostFtdcInputOptionSelfCloseActionField *InputOptionSelfCloseActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspOptionSelfCloseAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputOptionSelfCloseAction(InputOptionSelfCloseAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspCombActionInsert(, CThostFtdcInputCombActionField *InputCombActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspCombActionInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputCombAction(InputCombAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryOrder(, CThostFtdcOrderField *OrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryOrder: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteOrder(Order);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryTrade(, CThostFtdcTradeField *TradeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTrade: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTrade(Trade);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryInvestorPosition(, CThostFtdcInvestorPositionField *InvestorPositionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInvestorPosition: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorPosition(InvestorPosition);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryTradingAccount(, CThostFtdcTradingAccountField *TradingAccountCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTradingAccount: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTradingAccount(TradingAccount);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryInvestor(, CThostFtdcInvestorField *InvestorCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInvestor: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestor(Investor);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryTradingCode(, CThostFtdcTradingCodeField *TradingCodeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTradingCode: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTradingCode(TradingCode);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryInstrumentMarginRate(, CThostFtdcInstrumentMarginRateField *InstrumentMarginRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInstrumentMarginRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInstrumentMarginRate(InstrumentMarginRate);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryInstrumentCommissionRate(, CThostFtdcInstrumentCommissionRateField *InstrumentCommissionRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInstrumentCommissionRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInstrumentCommissionRate(InstrumentCommissionRate);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryExchange(, CThostFtdcExchangeField *ExchangeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryExchange: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteExchange(Exchange);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryProduct(, CThostFtdcProductField *ProductCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryProduct: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteProduct(Product);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryInstrument(, CThostFtdcInstrumentField *InstrumentCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInstrument: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInstrument(Instrument);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryDepthMarketData(, CThostFtdcDepthMarketDataField *DepthMarketDataCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryDepthMarketData: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteDepthMarketData(DepthMarketData);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQrySettlementInfo(, CThostFtdcSettlementInfoField *SettlementInfoCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySettlementInfo: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSettlementInfo(SettlementInfo);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryTransferBank(, CThostFtdcTransferBankField *TransferBankCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTransferBank: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTransferBank(TransferBank);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryInvestorPositionDetail(, CThostFtdcInvestorPositionDetailField *InvestorPositionDetailCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInvestorPositionDetail: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorPositionDetail(InvestorPositionDetail);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryNotice(, CThostFtdcNoticeField *NoticeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryNotice: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteNotice(Notice);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQrySettlementInfoConfirm(, CThostFtdcSettlementInfoConfirmField *SettlementInfoConfirmCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySettlementInfoConfirm: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSettlementInfoConfirm(SettlementInfoConfirm);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryInvestorPositionCombineDetail(, CThostFtdcInvestorPositionCombineDetailField *InvestorPositionCombineDetailCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInvestorPositionCombineDetail: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorPositionCombineDetail(InvestorPositionCombineDetail);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryCFMMCTradingAccountKey(, CThostFtdcCFMMCTradingAccountKeyField *CFMMCTradingAccountKeyCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryCFMMCTradingAccountKey: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteCFMMCTradingAccountKey(CFMMCTradingAccountKey);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryEWarrantOffset(, CThostFtdcEWarrantOffsetField *EWarrantOffsetCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryEWarrantOffset: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteEWarrantOffset(EWarrantOffset);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryInvestorProductGroupMargin(, CThostFtdcInvestorProductGroupMarginField *InvestorProductGroupMarginCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInvestorProductGroupMargin: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorProductGroupMargin(InvestorProductGroupMargin);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryExchangeMarginRate(, CThostFtdcExchangeMarginRateField *ExchangeMarginRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryExchangeMarginRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteExchangeMarginRate(ExchangeMarginRate);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryExchangeMarginRateAdjust(, CThostFtdcExchangeMarginRateAdjustField *ExchangeMarginRateAdjustCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryExchangeMarginRateAdjust: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteExchangeMarginRateAdjust(ExchangeMarginRateAdjust);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryExchangeRate(, CThostFtdcExchangeRateField *ExchangeRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryExchangeRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteExchangeRate(ExchangeRate);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQrySecAgentACIDMap(, CThostFtdcSecAgentACIDMapField *SecAgentACIDMapCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySecAgentACIDMap: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSecAgentACIDMap(SecAgentACIDMap);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryProductExchRate(, CThostFtdcProductExchRateField *ProductExchRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryProductExchRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteProductExchRate(ProductExchRate);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryProductGroup(, CThostFtdcProductGroupField *ProductGroupCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryProductGroup: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteProductGroup(ProductGroup);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryMMInstrumentCommissionRate(, CThostFtdcMMInstrumentCommissionRateField *MMInstrumentCommissionRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryMMInstrumentCommissionRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteMMInstrumentCommissionRate(MMInstrumentCommissionRate);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryMMOptionInstrCommRate(, CThostFtdcMMOptionInstrCommRateField *MMOptionInstrCommRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryMMOptionInstrCommRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteMMOptionInstrCommRate(MMOptionInstrCommRate);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryInstrumentOrderCommRate(, CThostFtdcInstrumentOrderCommRateField *InstrumentOrderCommRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInstrumentOrderCommRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInstrumentOrderCommRate(InstrumentOrderCommRate);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQrySecAgentTradingAccount(, CThostFtdcTradingAccountField *TradingAccountCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySecAgentTradingAccount: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTradingAccount(TradingAccount);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQrySecAgentCheckMode(, CThostFtdcSecAgentCheckModeField *SecAgentCheckModeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySecAgentCheckMode: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSecAgentCheckMode(SecAgentCheckMode);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQrySecAgentTradeInfo(, CThostFtdcSecAgentTradeInfoField *SecAgentTradeInfoCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQrySecAgentTradeInfo: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSecAgentTradeInfo(SecAgentTradeInfo);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryOptionInstrTradeCost(, CThostFtdcOptionInstrTradeCostField *OptionInstrTradeCostCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryOptionInstrTradeCost: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteOptionInstrTradeCost(OptionInstrTradeCost);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryOptionInstrCommRate(, CThostFtdcOptionInstrCommRateField *OptionInstrCommRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryOptionInstrCommRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteOptionInstrCommRate(OptionInstrCommRate);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryExecOrder(, CThostFtdcExecOrderField *ExecOrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryExecOrder: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteExecOrder(ExecOrder);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryForQuote(, CThostFtdcForQuoteField *ForQuoteCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryForQuote: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteForQuote(ForQuote);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryQuote(, CThostFtdcQuoteField *QuoteCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryQuote: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteQuote(Quote);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryOptionSelfClose(, CThostFtdcOptionSelfCloseField *OptionSelfCloseCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryOptionSelfClose: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteOptionSelfClose(OptionSelfClose);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryInvestUnit(, CThostFtdcInvestUnitField *InvestUnitCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryInvestUnit: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestUnit(InvestUnit);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryCombInstrumentGuard(, CThostFtdcCombInstrumentGuardField *CombInstrumentGuardCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryCombInstrumentGuard: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteCombInstrumentGuard(CombInstrumentGuard);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryCombAction(, CThostFtdcCombActionField *CombActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryCombAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteCombAction(CombAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryTransferSerial(, CThostFtdcTransferSerialField *TransferSerialCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTransferSerial: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTransferSerial(TransferSerial);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryAccountregister(, CThostFtdcAccountregisterField *AccountregisterCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryAccountregister: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteAccountregister(Accountregister);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspError(, CThostFtdcRspInfoField *RspInfoint nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspError: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRtnOrder(, CThostFtdcOrderField *Order)
{
	WRITE_LOG(LogLevel::Info, "OnRtnOrder:");
	WriteOrder(Order);
}

void CThostFtdcTraderSpiMiddle::OnRtnTrade(, CThostFtdcTradeField *Trade)
{
	WRITE_LOG(LogLevel::Info, "OnRtnTrade:");
	WriteTrade(Trade);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnOrderInsert(, CThostFtdcInputOrderField *InputOrderCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnOrderInsert:");
	WriteInputOrder(InputOrder);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnOrderAction(, CThostFtdcOrderActionField *OrderActionCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnOrderAction:");
	WriteOrderAction(OrderAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRtnInstrumentStatus(, CThostFtdcInstrumentStatusField *InstrumentStatus)
{
	WRITE_LOG(LogLevel::Info, "OnRtnInstrumentStatus:");
	WriteInstrumentStatus(InstrumentStatus);
}

void CThostFtdcTraderSpiMiddle::OnRtnBulletin(, CThostFtdcBulletinField *Bulletin)
{
	WRITE_LOG(LogLevel::Info, "OnRtnBulletin:");
	WriteBulletin(Bulletin);
}

void CThostFtdcTraderSpiMiddle::OnRtnTradingNotice(, CThostFtdcTradingNoticeInfoField *TradingNoticeInfo)
{
	WRITE_LOG(LogLevel::Info, "OnRtnTradingNotice:");
	WriteTradingNoticeInfo(TradingNoticeInfo);
}

void CThostFtdcTraderSpiMiddle::OnRtnErrorConditionalOrder(, CThostFtdcErrorConditionalOrderField *ErrorConditionalOrder)
{
	WRITE_LOG(LogLevel::Info, "OnRtnErrorConditionalOrder:");
	WriteErrorConditionalOrder(ErrorConditionalOrder);
}

void CThostFtdcTraderSpiMiddle::OnRtnExecOrder(, CThostFtdcExecOrderField *ExecOrder)
{
	WRITE_LOG(LogLevel::Info, "OnRtnExecOrder:");
	WriteExecOrder(ExecOrder);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnExecOrderInsert(, CThostFtdcInputExecOrderField *InputExecOrderCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnExecOrderInsert:");
	WriteInputExecOrder(InputExecOrder);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnExecOrderAction(, CThostFtdcExecOrderActionField *ExecOrderActionCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnExecOrderAction:");
	WriteExecOrderAction(ExecOrderAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnForQuoteInsert(, CThostFtdcInputForQuoteField *InputForQuoteCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnForQuoteInsert:");
	WriteInputForQuote(InputForQuote);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRtnQuote(, CThostFtdcQuoteField *Quote)
{
	WRITE_LOG(LogLevel::Info, "OnRtnQuote:");
	WriteQuote(Quote);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnQuoteInsert(, CThostFtdcInputQuoteField *InputQuoteCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnQuoteInsert:");
	WriteInputQuote(InputQuote);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnQuoteAction(, CThostFtdcQuoteActionField *QuoteActionCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnQuoteAction:");
	WriteQuoteAction(QuoteAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRtnForQuoteRsp(, CThostFtdcForQuoteRspField *ForQuoteRsp)
{
	WRITE_LOG(LogLevel::Info, "OnRtnForQuoteRsp:");
	WriteForQuoteRsp(ForQuoteRsp);
}

void CThostFtdcTraderSpiMiddle::OnRtnCFMMCTradingAccountToken(, CThostFtdcCFMMCTradingAccountTokenField *CFMMCTradingAccountToken)
{
	WRITE_LOG(LogLevel::Info, "OnRtnCFMMCTradingAccountToken:");
	WriteCFMMCTradingAccountToken(CFMMCTradingAccountToken);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnBatchOrderAction(, CThostFtdcBatchOrderActionField *BatchOrderActionCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnBatchOrderAction:");
	WriteBatchOrderAction(BatchOrderAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRtnOptionSelfClose(, CThostFtdcOptionSelfCloseField *OptionSelfClose)
{
	WRITE_LOG(LogLevel::Info, "OnRtnOptionSelfClose:");
	WriteOptionSelfClose(OptionSelfClose);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnOptionSelfCloseInsert(, CThostFtdcInputOptionSelfCloseField *InputOptionSelfCloseCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnOptionSelfCloseInsert:");
	WriteInputOptionSelfClose(InputOptionSelfClose);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnOptionSelfCloseAction(, CThostFtdcOptionSelfCloseActionField *OptionSelfCloseActionCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnOptionSelfCloseAction:");
	WriteOptionSelfCloseAction(OptionSelfCloseAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRtnCombAction(, CThostFtdcCombActionField *CombAction)
{
	WRITE_LOG(LogLevel::Info, "OnRtnCombAction:");
	WriteCombAction(CombAction);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnCombActionInsert(, CThostFtdcInputCombActionField *InputCombActionCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnCombActionInsert:");
	WriteInputCombAction(InputCombAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryContractBank(, CThostFtdcContractBankField *ContractBankCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryContractBank: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteContractBank(ContractBank);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryParkedOrder(, CThostFtdcParkedOrderField *ParkedOrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryParkedOrder: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteParkedOrder(ParkedOrder);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryParkedOrderAction(, CThostFtdcParkedOrderActionField *ParkedOrderActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryParkedOrderAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteParkedOrderAction(ParkedOrderAction);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryTradingNotice(, CThostFtdcTradingNoticeField *TradingNoticeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryTradingNotice: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTradingNotice(TradingNotice);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryBrokerTradingParams(, CThostFtdcBrokerTradingParamsField *BrokerTradingParamsCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryBrokerTradingParams: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteBrokerTradingParams(BrokerTradingParams);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryBrokerTradingAlgos(, CThostFtdcBrokerTradingAlgosField *BrokerTradingAlgosCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryBrokerTradingAlgos: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteBrokerTradingAlgos(BrokerTradingAlgos);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQueryCFMMCTradingAccountToken(, CThostFtdcQueryCFMMCTradingAccountTokenField *QueryCFMMCTradingAccountTokenCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQueryCFMMCTradingAccountToken: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteQueryCFMMCTradingAccountToken(QueryCFMMCTradingAccountToken);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRtnFromBankToFutureByBank(, CThostFtdcRspTransferField *RspTransfer)
{
	WRITE_LOG(LogLevel::Info, "OnRtnFromBankToFutureByBank:");
	WriteRspTransfer(RspTransfer);
}

void CThostFtdcTraderSpiMiddle::OnRtnFromFutureToBankByBank(, CThostFtdcRspTransferField *RspTransfer)
{
	WRITE_LOG(LogLevel::Info, "OnRtnFromFutureToBankByBank:");
	WriteRspTransfer(RspTransfer);
}

void CThostFtdcTraderSpiMiddle::OnRtnRepealFromBankToFutureByBank(, CThostFtdcRspRepealField *RspRepeal)
{
	WRITE_LOG(LogLevel::Info, "OnRtnRepealFromBankToFutureByBank:");
	WriteRspRepeal(RspRepeal);
}

void CThostFtdcTraderSpiMiddle::OnRtnRepealFromFutureToBankByBank(, CThostFtdcRspRepealField *RspRepeal)
{
	WRITE_LOG(LogLevel::Info, "OnRtnRepealFromFutureToBankByBank:");
	WriteRspRepeal(RspRepeal);
}

void CThostFtdcTraderSpiMiddle::OnRtnFromBankToFutureByFuture(, CThostFtdcRspTransferField *RspTransfer)
{
	WRITE_LOG(LogLevel::Info, "OnRtnFromBankToFutureByFuture:");
	WriteRspTransfer(RspTransfer);
}

void CThostFtdcTraderSpiMiddle::OnRtnFromFutureToBankByFuture(, CThostFtdcRspTransferField *RspTransfer)
{
	WRITE_LOG(LogLevel::Info, "OnRtnFromFutureToBankByFuture:");
	WriteRspTransfer(RspTransfer);
}

void CThostFtdcTraderSpiMiddle::OnRtnRepealFromBankToFutureByFutureManual(, CThostFtdcRspRepealField *RspRepeal)
{
	WRITE_LOG(LogLevel::Info, "OnRtnRepealFromBankToFutureByFutureManual:");
	WriteRspRepeal(RspRepeal);
}

void CThostFtdcTraderSpiMiddle::OnRtnRepealFromFutureToBankByFutureManual(, CThostFtdcRspRepealField *RspRepeal)
{
	WRITE_LOG(LogLevel::Info, "OnRtnRepealFromFutureToBankByFutureManual:");
	WriteRspRepeal(RspRepeal);
}

void CThostFtdcTraderSpiMiddle::OnRtnQueryBankBalanceByFuture(, CThostFtdcNotifyQueryAccountField *NotifyQueryAccount)
{
	WRITE_LOG(LogLevel::Info, "OnRtnQueryBankBalanceByFuture:");
	WriteNotifyQueryAccount(NotifyQueryAccount);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnBankToFutureByFuture(, CThostFtdcReqTransferField *ReqTransferCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnBankToFutureByFuture:");
	WriteReqTransfer(ReqTransfer);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnFutureToBankByFuture(, CThostFtdcReqTransferField *ReqTransferCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnFutureToBankByFuture:");
	WriteReqTransfer(ReqTransfer);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnRepealBankToFutureByFutureManual(, CThostFtdcReqRepealField *ReqRepealCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnRepealBankToFutureByFutureManual:");
	WriteReqRepeal(ReqRepeal);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnRepealFutureToBankByFutureManual(, CThostFtdcReqRepealField *ReqRepealCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnRepealFutureToBankByFutureManual:");
	WriteReqRepeal(ReqRepeal);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnErrRtnQueryBankBalanceByFuture(, CThostFtdcReqQueryAccountField *ReqQueryAccountCThostFtdcRspInfoField *RspInfo)
{
	WRITE_LOG(LogLevel::Info, "OnErrRtnQueryBankBalanceByFuture:");
	WriteReqQueryAccount(ReqQueryAccount);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRtnRepealFromBankToFutureByFuture(, CThostFtdcRspRepealField *RspRepeal)
{
	WRITE_LOG(LogLevel::Info, "OnRtnRepealFromBankToFutureByFuture:");
	WriteRspRepeal(RspRepeal);
}

void CThostFtdcTraderSpiMiddle::OnRtnRepealFromFutureToBankByFuture(, CThostFtdcRspRepealField *RspRepeal)
{
	WRITE_LOG(LogLevel::Info, "OnRtnRepealFromFutureToBankByFuture:");
	WriteRspRepeal(RspRepeal);
}

void CThostFtdcTraderSpiMiddle::OnRspFromBankToFutureByFuture(, CThostFtdcReqTransferField *ReqTransferCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspFromBankToFutureByFuture: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteReqTransfer(ReqTransfer);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspFromFutureToBankByFuture(, CThostFtdcReqTransferField *ReqTransferCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspFromFutureToBankByFuture: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteReqTransfer(ReqTransfer);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQueryBankAccountMoneyByFuture(, CThostFtdcReqQueryAccountField *ReqQueryAccountCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQueryBankAccountMoneyByFuture: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteReqQueryAccount(ReqQueryAccount);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRtnOpenAccountByBank(, CThostFtdcOpenAccountField *OpenAccount)
{
	WRITE_LOG(LogLevel::Info, "OnRtnOpenAccountByBank:");
	WriteOpenAccount(OpenAccount);
}

void CThostFtdcTraderSpiMiddle::OnRtnCancelAccountByBank(, CThostFtdcCancelAccountField *CancelAccount)
{
	WRITE_LOG(LogLevel::Info, "OnRtnCancelAccountByBank:");
	WriteCancelAccount(CancelAccount);
}

void CThostFtdcTraderSpiMiddle::OnRtnChangeAccountByBank(, CThostFtdcChangeAccountField *ChangeAccount)
{
	WRITE_LOG(LogLevel::Info, "OnRtnChangeAccountByBank:");
	WriteChangeAccount(ChangeAccount);
}

void CThostFtdcTraderSpiMiddle::OnRspQryClassifiedInstrument(, CThostFtdcInstrumentField *InstrumentCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryClassifiedInstrument: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInstrument(Instrument);
	WriteRspInfo(RspInfo);
}

void CThostFtdcTraderSpiMiddle::OnRspQryCombPromotionParam(, CThostFtdcCombPromotionParamField *CombPromotionParamCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "OnRspQryCombPromotionParam: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteCombPromotionParam(CombPromotionParam);
	WriteRspInfo(RspInfo);
}

