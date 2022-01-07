#pragma once
#include "ThostFtdcTraderApi.h"


class CThostFtdcTraderApiMiddle : public CThostFtdcTraderApi
{
public:
	static CThostFtdcTraderApi *CreateFtdcTraderApi(const char *pszFlowPath = "");
	
	static const char *GetApiVersion();
	
	virtual void Release();

	virtual void Init();

	virtual int Join();

	virtual const char * GetTradingDay();

	virtual void RegisterFront(, char * pszFrontAddress);

	virtual void RegisterNameServer(, char * pszNsAddress);

	virtual void RegisterFensUserInfo(, CThostFtdcFensUserInfoField *FensUserInfo);

	virtual void RegisterSpi(, CThostFtdcTraderSpi *TraderSp);

	virtual void SubscribePrivateTopic(, THOST_TE_RESUME_TYPE nResumeType);

	virtual void SubscribePublicTopic(, THOST_TE_RESUME_TYPE nResumeType);

	virtual int ReqAuthenticate(, CThostFtdcReqAuthenticateField *ReqAuthenticateint nRequestID);

	virtual int RegisterUserSystemInfo(, CThostFtdcUserSystemInfoField *UserSystemInfo);

	virtual int SubmitUserSystemInfo(, CThostFtdcUserSystemInfoField *UserSystemInfo);

	virtual int ReqUserLogin(, CThostFtdcReqUserLoginField *ReqUserLoginint nRequestID);

	virtual int ReqUserLogout(, CThostFtdcUserLogoutField *UserLogoutint nRequestID);

	virtual int ReqUserPasswordUpdate(, CThostFtdcUserPasswordUpdateField *UserPasswordUpdateint nRequestID);

	virtual int ReqTradingAccountPasswordUpdate(, CThostFtdcTradingAccountPasswordUpdateField *TradingAccountPasswordUpdateint nRequestID);

	virtual int ReqUserAuthMethod(, CThostFtdcReqUserAuthMethodField *ReqUserAuthMethodint nRequestID);

	virtual int ReqGenUserCaptcha(, CThostFtdcReqGenUserCaptchaField *ReqGenUserCaptchaint nRequestID);

	virtual int ReqGenUserText(, CThostFtdcReqGenUserTextField *ReqGenUserTextint nRequestID);

	virtual int ReqUserLoginWithCaptcha(, CThostFtdcReqUserLoginWithCaptchaField *ReqUserLoginWithCaptchaint nRequestID);

	virtual int ReqUserLoginWithText(, CThostFtdcReqUserLoginWithTextField *ReqUserLoginWithTextint nRequestID);

	virtual int ReqUserLoginWithOTP(, CThostFtdcReqUserLoginWithOTPField *ReqUserLoginWithOTPint nRequestID);

	virtual int ReqOrderInsert(, CThostFtdcInputOrderField *InputOrderint nRequestID);

	virtual int ReqParkedOrderInsert(, CThostFtdcParkedOrderField *ParkedOrderint nRequestID);

	virtual int ReqParkedOrderAction(, CThostFtdcParkedOrderActionField *ParkedOrderActionint nRequestID);

	virtual int ReqOrderAction(, CThostFtdcInputOrderActionField *InputOrderActionint nRequestID);

	virtual int ReqQryMaxOrderVolume(, CThostFtdcQryMaxOrderVolumeField *QryMaxOrderVolumeint nRequestID);

	virtual int ReqSettlementInfoConfirm(, CThostFtdcSettlementInfoConfirmField *SettlementInfoConfirmint nRequestID);

	virtual int ReqRemoveParkedOrder(, CThostFtdcRemoveParkedOrderField *RemoveParkedOrderint nRequestID);

	virtual int ReqRemoveParkedOrderAction(, CThostFtdcRemoveParkedOrderActionField *RemoveParkedOrderActionint nRequestID);

	virtual int ReqExecOrderInsert(, CThostFtdcInputExecOrderField *InputExecOrderint nRequestID);

	virtual int ReqExecOrderAction(, CThostFtdcInputExecOrderActionField *InputExecOrderActionint nRequestID);

	virtual int ReqForQuoteInsert(, CThostFtdcInputForQuoteField *InputForQuoteint nRequestID);

	virtual int ReqQuoteInsert(, CThostFtdcInputQuoteField *InputQuoteint nRequestID);

	virtual int ReqQuoteAction(, CThostFtdcInputQuoteActionField *InputQuoteActionint nRequestID);

	virtual int ReqBatchOrderAction(, CThostFtdcInputBatchOrderActionField *InputBatchOrderActionint nRequestID);

	virtual int ReqOptionSelfCloseInsert(, CThostFtdcInputOptionSelfCloseField *InputOptionSelfCloseint nRequestID);

	virtual int ReqOptionSelfCloseAction(, CThostFtdcInputOptionSelfCloseActionField *InputOptionSelfCloseActionint nRequestID);

	virtual int ReqCombActionInsert(, CThostFtdcInputCombActionField *InputCombActionint nRequestID);

	virtual int ReqQryOrder(, CThostFtdcQryOrderField *QryOrderint nRequestID);

	virtual int ReqQryTrade(, CThostFtdcQryTradeField *QryTradeint nRequestID);

	virtual int ReqQryInvestorPosition(, CThostFtdcQryInvestorPositionField *QryInvestorPositionint nRequestID);

	virtual int ReqQryTradingAccount(, CThostFtdcQryTradingAccountField *QryTradingAccountint nRequestID);

	virtual int ReqQryInvestor(, CThostFtdcQryInvestorField *QryInvestorint nRequestID);

	virtual int ReqQryTradingCode(, CThostFtdcQryTradingCodeField *QryTradingCodeint nRequestID);

	virtual int ReqQryInstrumentMarginRate(, CThostFtdcQryInstrumentMarginRateField *QryInstrumentMarginRateint nRequestID);

	virtual int ReqQryInstrumentCommissionRate(, CThostFtdcQryInstrumentCommissionRateField *QryInstrumentCommissionRateint nRequestID);

	virtual int ReqQryExchange(, CThostFtdcQryExchangeField *QryExchangeint nRequestID);

	virtual int ReqQryProduct(, CThostFtdcQryProductField *QryProductint nRequestID);

	virtual int ReqQryInstrument(, CThostFtdcQryInstrumentField *QryInstrumentint nRequestID);

	virtual int ReqQryDepthMarketData(, CThostFtdcQryDepthMarketDataField *QryDepthMarketDataint nRequestID);

	virtual int ReqQrySettlementInfo(, CThostFtdcQrySettlementInfoField *QrySettlementInfoint nRequestID);

	virtual int ReqQryTransferBank(, CThostFtdcQryTransferBankField *QryTransferBankint nRequestID);

	virtual int ReqQryInvestorPositionDetail(, CThostFtdcQryInvestorPositionDetailField *QryInvestorPositionDetailint nRequestID);

	virtual int ReqQryNotice(, CThostFtdcQryNoticeField *QryNoticeint nRequestID);

	virtual int ReqQrySettlementInfoConfirm(, CThostFtdcQrySettlementInfoConfirmField *QrySettlementInfoConfirmint nRequestID);

	virtual int ReqQryInvestorPositionCombineDetail(, CThostFtdcQryInvestorPositionCombineDetailField *QryInvestorPositionCombineDetailint nRequestID);

	virtual int ReqQryCFMMCTradingAccountKey(, CThostFtdcQryCFMMCTradingAccountKeyField *QryCFMMCTradingAccountKeyint nRequestID);

	virtual int ReqQryEWarrantOffset(, CThostFtdcQryEWarrantOffsetField *QryEWarrantOffsetint nRequestID);

	virtual int ReqQryInvestorProductGroupMargin(, CThostFtdcQryInvestorProductGroupMarginField *QryInvestorProductGroupMarginint nRequestID);

	virtual int ReqQryExchangeMarginRate(, CThostFtdcQryExchangeMarginRateField *QryExchangeMarginRateint nRequestID);

	virtual int ReqQryExchangeMarginRateAdjust(, CThostFtdcQryExchangeMarginRateAdjustField *QryExchangeMarginRateAdjustint nRequestID);

	virtual int ReqQryExchangeRate(, CThostFtdcQryExchangeRateField *QryExchangeRateint nRequestID);

	virtual int ReqQrySecAgentACIDMap(, CThostFtdcQrySecAgentACIDMapField *QrySecAgentACIDMapint nRequestID);

	virtual int ReqQryProductExchRate(, CThostFtdcQryProductExchRateField *QryProductExchRateint nRequestID);

	virtual int ReqQryProductGroup(, CThostFtdcQryProductGroupField *QryProductGroupint nRequestID);

	virtual int ReqQryMMInstrumentCommissionRate(, CThostFtdcQryMMInstrumentCommissionRateField *QryMMInstrumentCommissionRateint nRequestID);

	virtual int ReqQryMMOptionInstrCommRate(, CThostFtdcQryMMOptionInstrCommRateField *QryMMOptionInstrCommRateint nRequestID);

	virtual int ReqQryInstrumentOrderCommRate(, CThostFtdcQryInstrumentOrderCommRateField *QryInstrumentOrderCommRateint nRequestID);

	virtual int ReqQrySecAgentTradingAccount(, CThostFtdcQryTradingAccountField *QryTradingAccountint nRequestID);

	virtual int ReqQrySecAgentCheckMode(, CThostFtdcQrySecAgentCheckModeField *QrySecAgentCheckModeint nRequestID);

	virtual int ReqQrySecAgentTradeInfo(, CThostFtdcQrySecAgentTradeInfoField *QrySecAgentTradeInfoint nRequestID);

	virtual int ReqQryOptionInstrTradeCost(, CThostFtdcQryOptionInstrTradeCostField *QryOptionInstrTradeCostint nRequestID);

	virtual int ReqQryOptionInstrCommRate(, CThostFtdcQryOptionInstrCommRateField *QryOptionInstrCommRateint nRequestID);

	virtual int ReqQryExecOrder(, CThostFtdcQryExecOrderField *QryExecOrderint nRequestID);

	virtual int ReqQryForQuote(, CThostFtdcQryForQuoteField *QryForQuoteint nRequestID);

	virtual int ReqQryQuote(, CThostFtdcQryQuoteField *QryQuoteint nRequestID);

	virtual int ReqQryOptionSelfClose(, CThostFtdcQryOptionSelfCloseField *QryOptionSelfCloseint nRequestID);

	virtual int ReqQryInvestUnit(, CThostFtdcQryInvestUnitField *QryInvestUnitint nRequestID);

	virtual int ReqQryCombInstrumentGuard(, CThostFtdcQryCombInstrumentGuardField *QryCombInstrumentGuardint nRequestID);

	virtual int ReqQryCombAction(, CThostFtdcQryCombActionField *QryCombActionint nRequestID);

	virtual int ReqQryTransferSerial(, CThostFtdcQryTransferSerialField *QryTransferSerialint nRequestID);

	virtual int ReqQryAccountregister(, CThostFtdcQryAccountregisterField *QryAccountregisterint nRequestID);

	virtual int ReqQryContractBank(, CThostFtdcQryContractBankField *QryContractBankint nRequestID);

	virtual int ReqQryParkedOrder(, CThostFtdcQryParkedOrderField *QryParkedOrderint nRequestID);

	virtual int ReqQryParkedOrderAction(, CThostFtdcQryParkedOrderActionField *QryParkedOrderActionint nRequestID);

	virtual int ReqQryTradingNotice(, CThostFtdcQryTradingNoticeField *QryTradingNoticeint nRequestID);

	virtual int ReqQryBrokerTradingParams(, CThostFtdcQryBrokerTradingParamsField *QryBrokerTradingParamsint nRequestID);

	virtual int ReqQryBrokerTradingAlgos(, CThostFtdcQryBrokerTradingAlgosField *QryBrokerTradingAlgosint nRequestID);

	virtual int ReqQueryCFMMCTradingAccountToken(, CThostFtdcQueryCFMMCTradingAccountTokenField *QueryCFMMCTradingAccountTokenint nRequestID);

	virtual int ReqFromBankToFutureByFuture(, CThostFtdcReqTransferField *ReqTransferint nRequestID);

	virtual int ReqFromFutureToBankByFuture(, CThostFtdcReqTransferField *ReqTransferint nRequestID);

	virtual int ReqQueryBankAccountMoneyByFuture(, CThostFtdcReqQueryAccountField *ReqQueryAccountint nRequestID);

	virtual int ReqQryClassifiedInstrument(, CThostFtdcQryClassifiedInstrumentField *QryClassifiedInstrumentint nRequestID);

	virtual int ReqQryCombPromotionParam(, CThostFtdcQryCombPromotionParamField *QryCombPromotionParamint nRequestID);


private:
	CThostFtdcTraderApi* m_TraderApi;
};