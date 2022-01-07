#pragma once
#include "ThostFtdcTraderApi.h"


class CThostFtdcTraderSpiMiddle : public CThostFtdcTraderSpi
{
public:
	virtual void OnFrontConnected();

	virtual void OnFrontDisconnected(, int nReason);

	virtual void OnHeartBeatWarning(, int nTimeLapse);

	virtual void OnRspAuthenticate(, CThostFtdcRspAuthenticateField *RspAuthenticateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspUserLogin(, CThostFtdcRspUserLoginField *RspUserLoginCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspUserLogout(, CThostFtdcUserLogoutField *UserLogoutCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspUserPasswordUpdate(, CThostFtdcUserPasswordUpdateField *UserPasswordUpdateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspTradingAccountPasswordUpdate(, CThostFtdcTradingAccountPasswordUpdateField *TradingAccountPasswordUpdateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspUserAuthMethod(, CThostFtdcRspUserAuthMethodField *RspUserAuthMethodCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspGenUserCaptcha(, CThostFtdcRspGenUserCaptchaField *RspGenUserCaptchaCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspGenUserText(, CThostFtdcRspGenUserTextField *RspGenUserTextCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspOrderInsert(, CThostFtdcInputOrderField *InputOrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspParkedOrderInsert(, CThostFtdcParkedOrderField *ParkedOrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspParkedOrderAction(, CThostFtdcParkedOrderActionField *ParkedOrderActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspOrderAction(, CThostFtdcInputOrderActionField *InputOrderActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryMaxOrderVolume(, CThostFtdcQryMaxOrderVolumeField *QryMaxOrderVolumeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspSettlementInfoConfirm(, CThostFtdcSettlementInfoConfirmField *SettlementInfoConfirmCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspRemoveParkedOrder(, CThostFtdcRemoveParkedOrderField *RemoveParkedOrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspRemoveParkedOrderAction(, CThostFtdcRemoveParkedOrderActionField *RemoveParkedOrderActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspExecOrderInsert(, CThostFtdcInputExecOrderField *InputExecOrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspExecOrderAction(, CThostFtdcInputExecOrderActionField *InputExecOrderActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspForQuoteInsert(, CThostFtdcInputForQuoteField *InputForQuoteCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQuoteInsert(, CThostFtdcInputQuoteField *InputQuoteCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQuoteAction(, CThostFtdcInputQuoteActionField *InputQuoteActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspBatchOrderAction(, CThostFtdcInputBatchOrderActionField *InputBatchOrderActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspOptionSelfCloseInsert(, CThostFtdcInputOptionSelfCloseField *InputOptionSelfCloseCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspOptionSelfCloseAction(, CThostFtdcInputOptionSelfCloseActionField *InputOptionSelfCloseActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspCombActionInsert(, CThostFtdcInputCombActionField *InputCombActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryOrder(, CThostFtdcOrderField *OrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryTrade(, CThostFtdcTradeField *TradeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryInvestorPosition(, CThostFtdcInvestorPositionField *InvestorPositionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryTradingAccount(, CThostFtdcTradingAccountField *TradingAccountCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryInvestor(, CThostFtdcInvestorField *InvestorCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryTradingCode(, CThostFtdcTradingCodeField *TradingCodeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryInstrumentMarginRate(, CThostFtdcInstrumentMarginRateField *InstrumentMarginRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryInstrumentCommissionRate(, CThostFtdcInstrumentCommissionRateField *InstrumentCommissionRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryExchange(, CThostFtdcExchangeField *ExchangeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryProduct(, CThostFtdcProductField *ProductCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryInstrument(, CThostFtdcInstrumentField *InstrumentCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryDepthMarketData(, CThostFtdcDepthMarketDataField *DepthMarketDataCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQrySettlementInfo(, CThostFtdcSettlementInfoField *SettlementInfoCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryTransferBank(, CThostFtdcTransferBankField *TransferBankCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryInvestorPositionDetail(, CThostFtdcInvestorPositionDetailField *InvestorPositionDetailCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryNotice(, CThostFtdcNoticeField *NoticeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQrySettlementInfoConfirm(, CThostFtdcSettlementInfoConfirmField *SettlementInfoConfirmCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryInvestorPositionCombineDetail(, CThostFtdcInvestorPositionCombineDetailField *InvestorPositionCombineDetailCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryCFMMCTradingAccountKey(, CThostFtdcCFMMCTradingAccountKeyField *CFMMCTradingAccountKeyCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryEWarrantOffset(, CThostFtdcEWarrantOffsetField *EWarrantOffsetCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryInvestorProductGroupMargin(, CThostFtdcInvestorProductGroupMarginField *InvestorProductGroupMarginCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryExchangeMarginRate(, CThostFtdcExchangeMarginRateField *ExchangeMarginRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryExchangeMarginRateAdjust(, CThostFtdcExchangeMarginRateAdjustField *ExchangeMarginRateAdjustCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryExchangeRate(, CThostFtdcExchangeRateField *ExchangeRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQrySecAgentACIDMap(, CThostFtdcSecAgentACIDMapField *SecAgentACIDMapCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryProductExchRate(, CThostFtdcProductExchRateField *ProductExchRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryProductGroup(, CThostFtdcProductGroupField *ProductGroupCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryMMInstrumentCommissionRate(, CThostFtdcMMInstrumentCommissionRateField *MMInstrumentCommissionRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryMMOptionInstrCommRate(, CThostFtdcMMOptionInstrCommRateField *MMOptionInstrCommRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryInstrumentOrderCommRate(, CThostFtdcInstrumentOrderCommRateField *InstrumentOrderCommRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQrySecAgentTradingAccount(, CThostFtdcTradingAccountField *TradingAccountCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQrySecAgentCheckMode(, CThostFtdcSecAgentCheckModeField *SecAgentCheckModeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQrySecAgentTradeInfo(, CThostFtdcSecAgentTradeInfoField *SecAgentTradeInfoCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryOptionInstrTradeCost(, CThostFtdcOptionInstrTradeCostField *OptionInstrTradeCostCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryOptionInstrCommRate(, CThostFtdcOptionInstrCommRateField *OptionInstrCommRateCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryExecOrder(, CThostFtdcExecOrderField *ExecOrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryForQuote(, CThostFtdcForQuoteField *ForQuoteCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryQuote(, CThostFtdcQuoteField *QuoteCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryOptionSelfClose(, CThostFtdcOptionSelfCloseField *OptionSelfCloseCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryInvestUnit(, CThostFtdcInvestUnitField *InvestUnitCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryCombInstrumentGuard(, CThostFtdcCombInstrumentGuardField *CombInstrumentGuardCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryCombAction(, CThostFtdcCombActionField *CombActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryTransferSerial(, CThostFtdcTransferSerialField *TransferSerialCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryAccountregister(, CThostFtdcAccountregisterField *AccountregisterCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspError(, CThostFtdcRspInfoField *RspInfoint nRequestID, bool bIsLast);

	virtual void OnRtnOrder(, CThostFtdcOrderField *Order);

	virtual void OnRtnTrade(, CThostFtdcTradeField *Trade);

	virtual void OnErrRtnOrderInsert(, CThostFtdcInputOrderField *InputOrderCThostFtdcRspInfoField *RspInfo);

	virtual void OnErrRtnOrderAction(, CThostFtdcOrderActionField *OrderActionCThostFtdcRspInfoField *RspInfo);

	virtual void OnRtnInstrumentStatus(, CThostFtdcInstrumentStatusField *InstrumentStatus);

	virtual void OnRtnBulletin(, CThostFtdcBulletinField *Bulletin);

	virtual void OnRtnTradingNotice(, CThostFtdcTradingNoticeInfoField *TradingNoticeInfo);

	virtual void OnRtnErrorConditionalOrder(, CThostFtdcErrorConditionalOrderField *ErrorConditionalOrder);

	virtual void OnRtnExecOrder(, CThostFtdcExecOrderField *ExecOrder);

	virtual void OnErrRtnExecOrderInsert(, CThostFtdcInputExecOrderField *InputExecOrderCThostFtdcRspInfoField *RspInfo);

	virtual void OnErrRtnExecOrderAction(, CThostFtdcExecOrderActionField *ExecOrderActionCThostFtdcRspInfoField *RspInfo);

	virtual void OnErrRtnForQuoteInsert(, CThostFtdcInputForQuoteField *InputForQuoteCThostFtdcRspInfoField *RspInfo);

	virtual void OnRtnQuote(, CThostFtdcQuoteField *Quote);

	virtual void OnErrRtnQuoteInsert(, CThostFtdcInputQuoteField *InputQuoteCThostFtdcRspInfoField *RspInfo);

	virtual void OnErrRtnQuoteAction(, CThostFtdcQuoteActionField *QuoteActionCThostFtdcRspInfoField *RspInfo);

	virtual void OnRtnForQuoteRsp(, CThostFtdcForQuoteRspField *ForQuoteRsp);

	virtual void OnRtnCFMMCTradingAccountToken(, CThostFtdcCFMMCTradingAccountTokenField *CFMMCTradingAccountToken);

	virtual void OnErrRtnBatchOrderAction(, CThostFtdcBatchOrderActionField *BatchOrderActionCThostFtdcRspInfoField *RspInfo);

	virtual void OnRtnOptionSelfClose(, CThostFtdcOptionSelfCloseField *OptionSelfClose);

	virtual void OnErrRtnOptionSelfCloseInsert(, CThostFtdcInputOptionSelfCloseField *InputOptionSelfCloseCThostFtdcRspInfoField *RspInfo);

	virtual void OnErrRtnOptionSelfCloseAction(, CThostFtdcOptionSelfCloseActionField *OptionSelfCloseActionCThostFtdcRspInfoField *RspInfo);

	virtual void OnRtnCombAction(, CThostFtdcCombActionField *CombAction);

	virtual void OnErrRtnCombActionInsert(, CThostFtdcInputCombActionField *InputCombActionCThostFtdcRspInfoField *RspInfo);

	virtual void OnRspQryContractBank(, CThostFtdcContractBankField *ContractBankCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryParkedOrder(, CThostFtdcParkedOrderField *ParkedOrderCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryParkedOrderAction(, CThostFtdcParkedOrderActionField *ParkedOrderActionCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryTradingNotice(, CThostFtdcTradingNoticeField *TradingNoticeCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryBrokerTradingParams(, CThostFtdcBrokerTradingParamsField *BrokerTradingParamsCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryBrokerTradingAlgos(, CThostFtdcBrokerTradingAlgosField *BrokerTradingAlgosCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQueryCFMMCTradingAccountToken(, CThostFtdcQueryCFMMCTradingAccountTokenField *QueryCFMMCTradingAccountTokenCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRtnFromBankToFutureByBank(, CThostFtdcRspTransferField *RspTransfer);

	virtual void OnRtnFromFutureToBankByBank(, CThostFtdcRspTransferField *RspTransfer);

	virtual void OnRtnRepealFromBankToFutureByBank(, CThostFtdcRspRepealField *RspRepeal);

	virtual void OnRtnRepealFromFutureToBankByBank(, CThostFtdcRspRepealField *RspRepeal);

	virtual void OnRtnFromBankToFutureByFuture(, CThostFtdcRspTransferField *RspTransfer);

	virtual void OnRtnFromFutureToBankByFuture(, CThostFtdcRspTransferField *RspTransfer);

	virtual void OnRtnRepealFromBankToFutureByFutureManual(, CThostFtdcRspRepealField *RspRepeal);

	virtual void OnRtnRepealFromFutureToBankByFutureManual(, CThostFtdcRspRepealField *RspRepeal);

	virtual void OnRtnQueryBankBalanceByFuture(, CThostFtdcNotifyQueryAccountField *NotifyQueryAccount);

	virtual void OnErrRtnBankToFutureByFuture(, CThostFtdcReqTransferField *ReqTransferCThostFtdcRspInfoField *RspInfo);

	virtual void OnErrRtnFutureToBankByFuture(, CThostFtdcReqTransferField *ReqTransferCThostFtdcRspInfoField *RspInfo);

	virtual void OnErrRtnRepealBankToFutureByFutureManual(, CThostFtdcReqRepealField *ReqRepealCThostFtdcRspInfoField *RspInfo);

	virtual void OnErrRtnRepealFutureToBankByFutureManual(, CThostFtdcReqRepealField *ReqRepealCThostFtdcRspInfoField *RspInfo);

	virtual void OnErrRtnQueryBankBalanceByFuture(, CThostFtdcReqQueryAccountField *ReqQueryAccountCThostFtdcRspInfoField *RspInfo);

	virtual void OnRtnRepealFromBankToFutureByFuture(, CThostFtdcRspRepealField *RspRepeal);

	virtual void OnRtnRepealFromFutureToBankByFuture(, CThostFtdcRspRepealField *RspRepeal);

	virtual void OnRspFromBankToFutureByFuture(, CThostFtdcReqTransferField *ReqTransferCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspFromFutureToBankByFuture(, CThostFtdcReqTransferField *ReqTransferCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQueryBankAccountMoneyByFuture(, CThostFtdcReqQueryAccountField *ReqQueryAccountCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRtnOpenAccountByBank(, CThostFtdcOpenAccountField *OpenAccount);

	virtual void OnRtnCancelAccountByBank(, CThostFtdcCancelAccountField *CancelAccount);

	virtual void OnRtnChangeAccountByBank(, CThostFtdcChangeAccountField *ChangeAccount);

	virtual void OnRspQryClassifiedInstrument(, CThostFtdcInstrumentField *InstrumentCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

	virtual void OnRspQryCombPromotionParam(, CThostFtdcCombPromotionParamField *CombPromotionParamCThostFtdcRspInfoField *RspInfo, int nRequestID, bool bIsLast);

};