#include "ThostFtdcTraderSpiImpl.h"

void CThostFtdcTraderSpiImpl::OnFrontConnected()
{

}
void CThostFtdcTraderSpiImpl::OnFrontDisconnected(int nReason)
{

}
void CThostFtdcTraderSpiImpl::OnHeartBeatWarning(int nTimeLapse)
{

}

void CThostFtdcTraderSpiImpl::OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField* pUserPasswordUpdate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField* pTradingAccountPasswordUpdate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField* pRspUserAuthMethod, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField* pRspGenUserCaptcha, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspGenUserText(CThostFtdcRspGenUserTextField* pRspGenUserText, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspParkedOrderInsert(CThostFtdcParkedOrderField* pParkedOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField* pParkedOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspOrderAction(CThostFtdcInputOrderActionField* pInputOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField* pQueryMaxOrderVolume, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField* pRemoveParkedOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField* pRemoveParkedOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspExecOrderInsert(CThostFtdcInputExecOrderField* pInputExecOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField* pInputExecOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspForQuoteInsert(CThostFtdcInputForQuoteField* pInputForQuote, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQuoteInsert(CThostFtdcInputQuoteField* pInputQuote, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQuoteAction(CThostFtdcInputQuoteActionField* pInputQuoteAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField* pInputBatchOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField* pInputOptionSelfClose, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField* pInputOptionSelfCloseAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspCombActionInsert(CThostFtdcInputCombActionField* pInputCombAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryOrder(CThostFtdcOrderField* pOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryTrade(CThostFtdcTradeField* pTrade, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryInvestor(CThostFtdcInvestorField* pInvestor, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryTradingCode(CThostFtdcTradingCodeField* pTradingCode, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField* pInstrumentMarginRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField* pInstrumentCommissionRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryExchange(CThostFtdcExchangeField* pExchange, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryProduct(CThostFtdcProductField* pProduct, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField* pSettlementInfo, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryTransferBank(CThostFtdcTransferBankField* pTransferBank, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField* pInvestorPositionDetail, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryNotice(CThostFtdcNoticeField* pNotice, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField* pInvestorPositionCombineDetail, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField* pCFMMCTradingAccountKey, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField* pEWarrantOffset, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField* pInvestorProductGroupMargin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField* pExchangeMarginRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField* pExchangeMarginRateAdjust, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryExchangeRate(CThostFtdcExchangeRateField* pExchangeRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField* pSecAgentACIDMap, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryProductExchRate(CThostFtdcProductExchRateField* pProductExchRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryProductGroup(CThostFtdcProductGroupField* pProductGroup, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField* pMMInstrumentCommissionRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField* pMMOptionInstrCommRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField* pInstrumentOrderCommRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField* pSecAgentCheckMode, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField* pSecAgentTradeInfo, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField* pOptionInstrTradeCost, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField* pOptionInstrCommRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryExecOrder(CThostFtdcExecOrderField* pExecOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryForQuote(CThostFtdcForQuoteField* pForQuote, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryQuote(CThostFtdcQuoteField* pQuote, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField* pOptionSelfClose, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryInvestUnit(CThostFtdcInvestUnitField* pInvestUnit, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField* pCombInstrumentGuard, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryCombAction(CThostFtdcCombActionField* pCombAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryTransferSerial(CThostFtdcTransferSerialField* pTransferSerial, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryAccountregister(CThostFtdcAccountregisterField* pAccountregister, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRtnOrder(CThostFtdcOrderField* pOrder){}

void CThostFtdcTraderSpiImpl::OnRtnTrade(CThostFtdcTradeField* pTrade){}

void CThostFtdcTraderSpiImpl::OnErrRtnOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnErrRtnOrderAction(CThostFtdcOrderActionField* pOrderAction, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField* pInstrumentStatus){}

void CThostFtdcTraderSpiImpl::OnRtnBulletin(CThostFtdcBulletinField* pBulletin){}

void CThostFtdcTraderSpiImpl::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField* pTradingNoticeInfo){}

void CThostFtdcTraderSpiImpl::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField* pErrorConditionalOrder){}

void CThostFtdcTraderSpiImpl::OnRtnExecOrder(CThostFtdcExecOrderField* pExecOrder){}

void CThostFtdcTraderSpiImpl::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField* pInputExecOrder, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField* pExecOrderAction, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField* pInputForQuote, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnRtnQuote(CThostFtdcQuoteField* pQuote){}

void CThostFtdcTraderSpiImpl::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField* pInputQuote, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnErrRtnQuoteAction(CThostFtdcQuoteActionField* pQuoteAction, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField* pForQuoteRsp){}

void CThostFtdcTraderSpiImpl::OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField* pCFMMCTradingAccountToken){}

void CThostFtdcTraderSpiImpl::OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField* pBatchOrderAction, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField* pOptionSelfClose){}

void CThostFtdcTraderSpiImpl::OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField* pInputOptionSelfClose, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField* pOptionSelfCloseAction, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnRtnCombAction(CThostFtdcCombActionField* pCombAction){}

void CThostFtdcTraderSpiImpl::OnErrRtnCombActionInsert(CThostFtdcInputCombActionField* pInputCombAction, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnRspQryContractBank(CThostFtdcContractBankField* pContractBank, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryParkedOrder(CThostFtdcParkedOrderField* pParkedOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField* pParkedOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryTradingNotice(CThostFtdcTradingNoticeField* pTradingNotice, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField* pBrokerTradingParams, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField* pBrokerTradingAlgos, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField* pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField* pRspTransfer){}

void CThostFtdcTraderSpiImpl::OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField* pRspTransfer){}

void CThostFtdcTraderSpiImpl::OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField* pRspRepeal){}

void CThostFtdcTraderSpiImpl::OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField* pRspRepeal){}

void CThostFtdcTraderSpiImpl::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField* pRspTransfer){}

void CThostFtdcTraderSpiImpl::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField* pRspTransfer){}

void CThostFtdcTraderSpiImpl::OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField* pRspRepeal){}

void CThostFtdcTraderSpiImpl::OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField* pRspRepeal){}

void CThostFtdcTraderSpiImpl::OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField* pNotifyQueryAccount){}

void CThostFtdcTraderSpiImpl::OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField* pReqTransfer, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField* pReqTransfer, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField* pReqRepeal, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField* pReqRepeal, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField* pReqQueryAccount, CThostFtdcRspInfoField* pRspInfo){}

void CThostFtdcTraderSpiImpl::OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField* pRspRepeal){}

void CThostFtdcTraderSpiImpl::OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField* pRspRepeal){}

void CThostFtdcTraderSpiImpl::OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField* pReqTransfer, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField* pReqTransfer, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField* pReqQueryAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast){}

void CThostFtdcTraderSpiImpl::OnRtnOpenAccountByBank(CThostFtdcOpenAccountField* pOpenAccount){}

void CThostFtdcTraderSpiImpl::OnRtnCancelAccountByBank(CThostFtdcCancelAccountField* pCancelAccount){}

void CThostFtdcTraderSpiImpl::OnRtnChangeAccountByBank(CThostFtdcChangeAccountField* pChangeAccount){}
