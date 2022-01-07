#include "ThostFtdcTraderApiMiddle.h"
#include "Logger.h"
#include "StructWriteLogFunc.h"



CThostFtdcTraderApi *CThostFtdcTraderApiMiddle::CreateFtdcTraderApi(const char *pszFlowPath)
{
	WRITE_LOG(LogLevel::Info, "CreateFtdcTraderApi: pszFlowPath[%s]", pszFlowPath);
	
	auto traderApi = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);
	auto apiMiddle = new CThostFtdcTraderApiMiddle();
	apiMiddle->m_TraderApi = traderApi;
	
	return apiMiddle;
}

const char *CThostFtdcTraderApiMiddle::GetApiVersion()
{
	WRITE_LOG(LogLevel::Info, "GetApiVersion:");
	
	return CThostFtdcTraderApi::GetApiVersion();
}

void CThostFtdcTraderApiMiddle::Release()
{
	WRITE_LOG(LogLevel::Info, "Release:");

	return m_TraderApi->Release();
}

void CThostFtdcTraderApiMiddle::Init()
{
	WRITE_LOG(LogLevel::Info, "Init:");

	return m_TraderApi->Init();
}

int CThostFtdcTraderApiMiddle::Join()
{
	WRITE_LOG(LogLevel::Info, "Join:");

	return m_TraderApi->Join();
}

const char * CThostFtdcTraderApiMiddle::GetTradingDay()
{
	WRITE_LOG(LogLevel::Info, "GetTradingDay:");

	return m_TraderApi->GetTradingDay();
}

void CThostFtdcTraderApiMiddle::RegisterFront(, char * pszFrontAddress)
{
	WRITE_LOG(LogLevel::Info, "RegisterFront: pszFrontAddress[%s]", pszFrontAddress);

	return m_TraderApi->RegisterFront(, pszFrontAddress);
}

void CThostFtdcTraderApiMiddle::RegisterNameServer(, char * pszNsAddress)
{
	WRITE_LOG(LogLevel::Info, "RegisterNameServer: pszNsAddress[%s]", pszNsAddress);

	return m_TraderApi->RegisterNameServer(, pszNsAddress);
}

void CThostFtdcTraderApiMiddle::RegisterFensUserInfo(, CThostFtdcFensUserInfoField *FensUserInfo)
{
	WRITE_LOG(LogLevel::Info, "RegisterFensUserInfo:");
	WriteFensUserInfo(FensUserInfo);

	return m_TraderApi->RegisterFensUserInfo(, FensUserInfo);
}

void CThostFtdcTraderApiMiddle::RegisterSpi(, CThostFtdcTraderSpi *TraderSp)
{
	WRITE_LOG(LogLevel::Info, "RegisterSpi:");

	return m_TraderApi->RegisterSpi(, TraderSp);
}

void CThostFtdcTraderApiMiddle::SubscribePrivateTopic(, THOST_TE_RESUME_TYPE nResumeType)
{
	WRITE_LOG(LogLevel::Info, "SubscribePrivateTopic: nResumeType[%d]", nResumeType);

	return m_TraderApi->SubscribePrivateTopic(, nResumeType);
}

void CThostFtdcTraderApiMiddle::SubscribePublicTopic(, THOST_TE_RESUME_TYPE nResumeType)
{
	WRITE_LOG(LogLevel::Info, "SubscribePublicTopic: nResumeType[%d]", nResumeType);

	return m_TraderApi->SubscribePublicTopic(, nResumeType);
}

int CThostFtdcTraderApiMiddle::ReqAuthenticate(, CThostFtdcReqAuthenticateField *ReqAuthenticateint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqAuthenticate: nRequestID[%d]", nRequestID);
	WriteReqAuthenticate(ReqAuthenticate);

	return m_TraderApi->ReqAuthenticate(, ReqAuthenticatenRequestID);
}

int CThostFtdcTraderApiMiddle::RegisterUserSystemInfo(, CThostFtdcUserSystemInfoField *UserSystemInfo)
{
	WRITE_LOG(LogLevel::Info, "RegisterUserSystemInfo:");
	WriteUserSystemInfo(UserSystemInfo);

	return m_TraderApi->RegisterUserSystemInfo(, UserSystemInfo);
}

int CThostFtdcTraderApiMiddle::SubmitUserSystemInfo(, CThostFtdcUserSystemInfoField *UserSystemInfo)
{
	WRITE_LOG(LogLevel::Info, "SubmitUserSystemInfo:");
	WriteUserSystemInfo(UserSystemInfo);

	return m_TraderApi->SubmitUserSystemInfo(, UserSystemInfo);
}

int CThostFtdcTraderApiMiddle::ReqUserLogin(, CThostFtdcReqUserLoginField *ReqUserLoginint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqUserLogin: nRequestID[%d]", nRequestID);
	WriteReqUserLogin(ReqUserLogin);

	return m_TraderApi->ReqUserLogin(, ReqUserLoginnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqUserLogout(, CThostFtdcUserLogoutField *UserLogoutint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqUserLogout: nRequestID[%d]", nRequestID);
	WriteUserLogout(UserLogout);

	return m_TraderApi->ReqUserLogout(, UserLogoutnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqUserPasswordUpdate(, CThostFtdcUserPasswordUpdateField *UserPasswordUpdateint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqUserPasswordUpdate: nRequestID[%d]", nRequestID);
	WriteUserPasswordUpdate(UserPasswordUpdate);

	return m_TraderApi->ReqUserPasswordUpdate(, UserPasswordUpdatenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqTradingAccountPasswordUpdate(, CThostFtdcTradingAccountPasswordUpdateField *TradingAccountPasswordUpdateint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqTradingAccountPasswordUpdate: nRequestID[%d]", nRequestID);
	WriteTradingAccountPasswordUpdate(TradingAccountPasswordUpdate);

	return m_TraderApi->ReqTradingAccountPasswordUpdate(, TradingAccountPasswordUpdatenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqUserAuthMethod(, CThostFtdcReqUserAuthMethodField *ReqUserAuthMethodint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqUserAuthMethod: nRequestID[%d]", nRequestID);
	WriteReqUserAuthMethod(ReqUserAuthMethod);

	return m_TraderApi->ReqUserAuthMethod(, ReqUserAuthMethodnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqGenUserCaptcha(, CThostFtdcReqGenUserCaptchaField *ReqGenUserCaptchaint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqGenUserCaptcha: nRequestID[%d]", nRequestID);
	WriteReqGenUserCaptcha(ReqGenUserCaptcha);

	return m_TraderApi->ReqGenUserCaptcha(, ReqGenUserCaptchanRequestID);
}

int CThostFtdcTraderApiMiddle::ReqGenUserText(, CThostFtdcReqGenUserTextField *ReqGenUserTextint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqGenUserText: nRequestID[%d]", nRequestID);
	WriteReqGenUserText(ReqGenUserText);

	return m_TraderApi->ReqGenUserText(, ReqGenUserTextnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqUserLoginWithCaptcha(, CThostFtdcReqUserLoginWithCaptchaField *ReqUserLoginWithCaptchaint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqUserLoginWithCaptcha: nRequestID[%d]", nRequestID);
	WriteReqUserLoginWithCaptcha(ReqUserLoginWithCaptcha);

	return m_TraderApi->ReqUserLoginWithCaptcha(, ReqUserLoginWithCaptchanRequestID);
}

int CThostFtdcTraderApiMiddle::ReqUserLoginWithText(, CThostFtdcReqUserLoginWithTextField *ReqUserLoginWithTextint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqUserLoginWithText: nRequestID[%d]", nRequestID);
	WriteReqUserLoginWithText(ReqUserLoginWithText);

	return m_TraderApi->ReqUserLoginWithText(, ReqUserLoginWithTextnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqUserLoginWithOTP(, CThostFtdcReqUserLoginWithOTPField *ReqUserLoginWithOTPint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqUserLoginWithOTP: nRequestID[%d]", nRequestID);
	WriteReqUserLoginWithOTP(ReqUserLoginWithOTP);

	return m_TraderApi->ReqUserLoginWithOTP(, ReqUserLoginWithOTPnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqOrderInsert(, CThostFtdcInputOrderField *InputOrderint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqOrderInsert: nRequestID[%d]", nRequestID);
	WriteInputOrder(InputOrder);

	return m_TraderApi->ReqOrderInsert(, InputOrdernRequestID);
}

int CThostFtdcTraderApiMiddle::ReqParkedOrderInsert(, CThostFtdcParkedOrderField *ParkedOrderint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqParkedOrderInsert: nRequestID[%d]", nRequestID);
	WriteParkedOrder(ParkedOrder);

	return m_TraderApi->ReqParkedOrderInsert(, ParkedOrdernRequestID);
}

int CThostFtdcTraderApiMiddle::ReqParkedOrderAction(, CThostFtdcParkedOrderActionField *ParkedOrderActionint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqParkedOrderAction: nRequestID[%d]", nRequestID);
	WriteParkedOrderAction(ParkedOrderAction);

	return m_TraderApi->ReqParkedOrderAction(, ParkedOrderActionnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqOrderAction(, CThostFtdcInputOrderActionField *InputOrderActionint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqOrderAction: nRequestID[%d]", nRequestID);
	WriteInputOrderAction(InputOrderAction);

	return m_TraderApi->ReqOrderAction(, InputOrderActionnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQueryMaxOrderVolume(, CThostFtdcQueryMaxOrderVolumeField *QueryMaxOrderVolumeint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQueryMaxOrderVolume: nRequestID[%d]", nRequestID);
	WriteQueryMaxOrderVolume(QueryMaxOrderVolume);

	return m_TraderApi->ReqQueryMaxOrderVolume(, QueryMaxOrderVolumenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqSettlementInfoConfirm(, CThostFtdcSettlementInfoConfirmField *SettlementInfoConfirmint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqSettlementInfoConfirm: nRequestID[%d]", nRequestID);
	WriteSettlementInfoConfirm(SettlementInfoConfirm);

	return m_TraderApi->ReqSettlementInfoConfirm(, SettlementInfoConfirmnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqRemoveParkedOrder(, CThostFtdcRemoveParkedOrderField *RemoveParkedOrderint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqRemoveParkedOrder: nRequestID[%d]", nRequestID);
	WriteRemoveParkedOrder(RemoveParkedOrder);

	return m_TraderApi->ReqRemoveParkedOrder(, RemoveParkedOrdernRequestID);
}

int CThostFtdcTraderApiMiddle::ReqRemoveParkedOrderAction(, CThostFtdcRemoveParkedOrderActionField *RemoveParkedOrderActionint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqRemoveParkedOrderAction: nRequestID[%d]", nRequestID);
	WriteRemoveParkedOrderAction(RemoveParkedOrderAction);

	return m_TraderApi->ReqRemoveParkedOrderAction(, RemoveParkedOrderActionnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqExecOrderInsert(, CThostFtdcInputExecOrderField *InputExecOrderint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqExecOrderInsert: nRequestID[%d]", nRequestID);
	WriteInputExecOrder(InputExecOrder);

	return m_TraderApi->ReqExecOrderInsert(, InputExecOrdernRequestID);
}

int CThostFtdcTraderApiMiddle::ReqExecOrderAction(, CThostFtdcInputExecOrderActionField *InputExecOrderActionint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqExecOrderAction: nRequestID[%d]", nRequestID);
	WriteInputExecOrderAction(InputExecOrderAction);

	return m_TraderApi->ReqExecOrderAction(, InputExecOrderActionnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqForQuoteInsert(, CThostFtdcInputForQuoteField *InputForQuoteint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqForQuoteInsert: nRequestID[%d]", nRequestID);
	WriteInputForQuote(InputForQuote);

	return m_TraderApi->ReqForQuoteInsert(, InputForQuotenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQuoteInsert(, CThostFtdcInputQuoteField *InputQuoteint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQuoteInsert: nRequestID[%d]", nRequestID);
	WriteInputQuote(InputQuote);

	return m_TraderApi->ReqQuoteInsert(, InputQuotenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQuoteAction(, CThostFtdcInputQuoteActionField *InputQuoteActionint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQuoteAction: nRequestID[%d]", nRequestID);
	WriteInputQuoteAction(InputQuoteAction);

	return m_TraderApi->ReqQuoteAction(, InputQuoteActionnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqBatchOrderAction(, CThostFtdcInputBatchOrderActionField *InputBatchOrderActionint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqBatchOrderAction: nRequestID[%d]", nRequestID);
	WriteInputBatchOrderAction(InputBatchOrderAction);

	return m_TraderApi->ReqBatchOrderAction(, InputBatchOrderActionnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqOptionSelfCloseInsert(, CThostFtdcInputOptionSelfCloseField *InputOptionSelfCloseint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqOptionSelfCloseInsert: nRequestID[%d]", nRequestID);
	WriteInputOptionSelfClose(InputOptionSelfClose);

	return m_TraderApi->ReqOptionSelfCloseInsert(, InputOptionSelfClosenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqOptionSelfCloseAction(, CThostFtdcInputOptionSelfCloseActionField *InputOptionSelfCloseActionint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqOptionSelfCloseAction: nRequestID[%d]", nRequestID);
	WriteInputOptionSelfCloseAction(InputOptionSelfCloseAction);

	return m_TraderApi->ReqOptionSelfCloseAction(, InputOptionSelfCloseActionnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqCombActionInsert(, CThostFtdcInputCombActionField *InputCombActionint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqCombActionInsert: nRequestID[%d]", nRequestID);
	WriteInputCombAction(InputCombAction);

	return m_TraderApi->ReqCombActionInsert(, InputCombActionnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryOrder(, CThostFtdcQryOrderField *QryOrderint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryOrder: nRequestID[%d]", nRequestID);
	WriteQryOrder(QryOrder);

	return m_TraderApi->ReqQryOrder(, QryOrdernRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryTrade(, CThostFtdcQryTradeField *QryTradeint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryTrade: nRequestID[%d]", nRequestID);
	WriteQryTrade(QryTrade);

	return m_TraderApi->ReqQryTrade(, QryTradenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryInvestorPosition(, CThostFtdcQryInvestorPositionField *QryInvestorPositionint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryInvestorPosition: nRequestID[%d]", nRequestID);
	WriteQryInvestorPosition(QryInvestorPosition);

	return m_TraderApi->ReqQryInvestorPosition(, QryInvestorPositionnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryTradingAccount(, CThostFtdcQryTradingAccountField *QryTradingAccountint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryTradingAccount: nRequestID[%d]", nRequestID);
	WriteQryTradingAccount(QryTradingAccount);

	return m_TraderApi->ReqQryTradingAccount(, QryTradingAccountnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryInvestor(, CThostFtdcQryInvestorField *QryInvestorint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryInvestor: nRequestID[%d]", nRequestID);
	WriteQryInvestor(QryInvestor);

	return m_TraderApi->ReqQryInvestor(, QryInvestornRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryTradingCode(, CThostFtdcQryTradingCodeField *QryTradingCodeint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryTradingCode: nRequestID[%d]", nRequestID);
	WriteQryTradingCode(QryTradingCode);

	return m_TraderApi->ReqQryTradingCode(, QryTradingCodenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryInstrumentMarginRate(, CThostFtdcQryInstrumentMarginRateField *QryInstrumentMarginRateint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryInstrumentMarginRate: nRequestID[%d]", nRequestID);
	WriteQryInstrumentMarginRate(QryInstrumentMarginRate);

	return m_TraderApi->ReqQryInstrumentMarginRate(, QryInstrumentMarginRatenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryInstrumentCommissionRate(, CThostFtdcQryInstrumentCommissionRateField *QryInstrumentCommissionRateint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryInstrumentCommissionRate: nRequestID[%d]", nRequestID);
	WriteQryInstrumentCommissionRate(QryInstrumentCommissionRate);

	return m_TraderApi->ReqQryInstrumentCommissionRate(, QryInstrumentCommissionRatenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryExchange(, CThostFtdcQryExchangeField *QryExchangeint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryExchange: nRequestID[%d]", nRequestID);
	WriteQryExchange(QryExchange);

	return m_TraderApi->ReqQryExchange(, QryExchangenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryProduct(, CThostFtdcQryProductField *QryProductint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryProduct: nRequestID[%d]", nRequestID);
	WriteQryProduct(QryProduct);

	return m_TraderApi->ReqQryProduct(, QryProductnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryInstrument(, CThostFtdcQryInstrumentField *QryInstrumentint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryInstrument: nRequestID[%d]", nRequestID);
	WriteQryInstrument(QryInstrument);

	return m_TraderApi->ReqQryInstrument(, QryInstrumentnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryDepthMarketData(, CThostFtdcQryDepthMarketDataField *QryDepthMarketDataint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryDepthMarketData: nRequestID[%d]", nRequestID);
	WriteQryDepthMarketData(QryDepthMarketData);

	return m_TraderApi->ReqQryDepthMarketData(, QryDepthMarketDatanRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQrySettlementInfo(, CThostFtdcQrySettlementInfoField *QrySettlementInfoint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQrySettlementInfo: nRequestID[%d]", nRequestID);
	WriteQrySettlementInfo(QrySettlementInfo);

	return m_TraderApi->ReqQrySettlementInfo(, QrySettlementInfonRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryTransferBank(, CThostFtdcQryTransferBankField *QryTransferBankint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryTransferBank: nRequestID[%d]", nRequestID);
	WriteQryTransferBank(QryTransferBank);

	return m_TraderApi->ReqQryTransferBank(, QryTransferBanknRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryInvestorPositionDetail(, CThostFtdcQryInvestorPositionDetailField *QryInvestorPositionDetailint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryInvestorPositionDetail: nRequestID[%d]", nRequestID);
	WriteQryInvestorPositionDetail(QryInvestorPositionDetail);

	return m_TraderApi->ReqQryInvestorPositionDetail(, QryInvestorPositionDetailnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryNotice(, CThostFtdcQryNoticeField *QryNoticeint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryNotice: nRequestID[%d]", nRequestID);
	WriteQryNotice(QryNotice);

	return m_TraderApi->ReqQryNotice(, QryNoticenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQrySettlementInfoConfirm(, CThostFtdcQrySettlementInfoConfirmField *QrySettlementInfoConfirmint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQrySettlementInfoConfirm: nRequestID[%d]", nRequestID);
	WriteQrySettlementInfoConfirm(QrySettlementInfoConfirm);

	return m_TraderApi->ReqQrySettlementInfoConfirm(, QrySettlementInfoConfirmnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryInvestorPositionCombineDetail(, CThostFtdcQryInvestorPositionCombineDetailField *QryInvestorPositionCombineDetailint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryInvestorPositionCombineDetail: nRequestID[%d]", nRequestID);
	WriteQryInvestorPositionCombineDetail(QryInvestorPositionCombineDetail);

	return m_TraderApi->ReqQryInvestorPositionCombineDetail(, QryInvestorPositionCombineDetailnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryCFMMCTradingAccountKey(, CThostFtdcQryCFMMCTradingAccountKeyField *QryCFMMCTradingAccountKeyint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryCFMMCTradingAccountKey: nRequestID[%d]", nRequestID);
	WriteQryCFMMCTradingAccountKey(QryCFMMCTradingAccountKey);

	return m_TraderApi->ReqQryCFMMCTradingAccountKey(, QryCFMMCTradingAccountKeynRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryEWarrantOffset(, CThostFtdcQryEWarrantOffsetField *QryEWarrantOffsetint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryEWarrantOffset: nRequestID[%d]", nRequestID);
	WriteQryEWarrantOffset(QryEWarrantOffset);

	return m_TraderApi->ReqQryEWarrantOffset(, QryEWarrantOffsetnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryInvestorProductGroupMargin(, CThostFtdcQryInvestorProductGroupMarginField *QryInvestorProductGroupMarginint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryInvestorProductGroupMargin: nRequestID[%d]", nRequestID);
	WriteQryInvestorProductGroupMargin(QryInvestorProductGroupMargin);

	return m_TraderApi->ReqQryInvestorProductGroupMargin(, QryInvestorProductGroupMarginnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryExchangeMarginRate(, CThostFtdcQryExchangeMarginRateField *QryExchangeMarginRateint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryExchangeMarginRate: nRequestID[%d]", nRequestID);
	WriteQryExchangeMarginRate(QryExchangeMarginRate);

	return m_TraderApi->ReqQryExchangeMarginRate(, QryExchangeMarginRatenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryExchangeMarginRateAdjust(, CThostFtdcQryExchangeMarginRateAdjustField *QryExchangeMarginRateAdjustint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryExchangeMarginRateAdjust: nRequestID[%d]", nRequestID);
	WriteQryExchangeMarginRateAdjust(QryExchangeMarginRateAdjust);

	return m_TraderApi->ReqQryExchangeMarginRateAdjust(, QryExchangeMarginRateAdjustnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryExchangeRate(, CThostFtdcQryExchangeRateField *QryExchangeRateint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryExchangeRate: nRequestID[%d]", nRequestID);
	WriteQryExchangeRate(QryExchangeRate);

	return m_TraderApi->ReqQryExchangeRate(, QryExchangeRatenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQrySecAgentACIDMap(, CThostFtdcQrySecAgentACIDMapField *QrySecAgentACIDMapint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQrySecAgentACIDMap: nRequestID[%d]", nRequestID);
	WriteQrySecAgentACIDMap(QrySecAgentACIDMap);

	return m_TraderApi->ReqQrySecAgentACIDMap(, QrySecAgentACIDMapnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryProductExchRate(, CThostFtdcQryProductExchRateField *QryProductExchRateint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryProductExchRate: nRequestID[%d]", nRequestID);
	WriteQryProductExchRate(QryProductExchRate);

	return m_TraderApi->ReqQryProductExchRate(, QryProductExchRatenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryProductGroup(, CThostFtdcQryProductGroupField *QryProductGroupint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryProductGroup: nRequestID[%d]", nRequestID);
	WriteQryProductGroup(QryProductGroup);

	return m_TraderApi->ReqQryProductGroup(, QryProductGroupnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryMMInstrumentCommissionRate(, CThostFtdcQryMMInstrumentCommissionRateField *QryMMInstrumentCommissionRateint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryMMInstrumentCommissionRate: nRequestID[%d]", nRequestID);
	WriteQryMMInstrumentCommissionRate(QryMMInstrumentCommissionRate);

	return m_TraderApi->ReqQryMMInstrumentCommissionRate(, QryMMInstrumentCommissionRatenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryMMOptionInstrCommRate(, CThostFtdcQryMMOptionInstrCommRateField *QryMMOptionInstrCommRateint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryMMOptionInstrCommRate: nRequestID[%d]", nRequestID);
	WriteQryMMOptionInstrCommRate(QryMMOptionInstrCommRate);

	return m_TraderApi->ReqQryMMOptionInstrCommRate(, QryMMOptionInstrCommRatenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryInstrumentOrderCommRate(, CThostFtdcQryInstrumentOrderCommRateField *QryInstrumentOrderCommRateint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryInstrumentOrderCommRate: nRequestID[%d]", nRequestID);
	WriteQryInstrumentOrderCommRate(QryInstrumentOrderCommRate);

	return m_TraderApi->ReqQryInstrumentOrderCommRate(, QryInstrumentOrderCommRatenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQrySecAgentTradingAccount(, CThostFtdcQryTradingAccountField *QryTradingAccountint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQrySecAgentTradingAccount: nRequestID[%d]", nRequestID);
	WriteQryTradingAccount(QryTradingAccount);

	return m_TraderApi->ReqQrySecAgentTradingAccount(, QryTradingAccountnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQrySecAgentCheckMode(, CThostFtdcQrySecAgentCheckModeField *QrySecAgentCheckModeint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQrySecAgentCheckMode: nRequestID[%d]", nRequestID);
	WriteQrySecAgentCheckMode(QrySecAgentCheckMode);

	return m_TraderApi->ReqQrySecAgentCheckMode(, QrySecAgentCheckModenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQrySecAgentTradeInfo(, CThostFtdcQrySecAgentTradeInfoField *QrySecAgentTradeInfoint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQrySecAgentTradeInfo: nRequestID[%d]", nRequestID);
	WriteQrySecAgentTradeInfo(QrySecAgentTradeInfo);

	return m_TraderApi->ReqQrySecAgentTradeInfo(, QrySecAgentTradeInfonRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryOptionInstrTradeCost(, CThostFtdcQryOptionInstrTradeCostField *QryOptionInstrTradeCostint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryOptionInstrTradeCost: nRequestID[%d]", nRequestID);
	WriteQryOptionInstrTradeCost(QryOptionInstrTradeCost);

	return m_TraderApi->ReqQryOptionInstrTradeCost(, QryOptionInstrTradeCostnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryOptionInstrCommRate(, CThostFtdcQryOptionInstrCommRateField *QryOptionInstrCommRateint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryOptionInstrCommRate: nRequestID[%d]", nRequestID);
	WriteQryOptionInstrCommRate(QryOptionInstrCommRate);

	return m_TraderApi->ReqQryOptionInstrCommRate(, QryOptionInstrCommRatenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryExecOrder(, CThostFtdcQryExecOrderField *QryExecOrderint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryExecOrder: nRequestID[%d]", nRequestID);
	WriteQryExecOrder(QryExecOrder);

	return m_TraderApi->ReqQryExecOrder(, QryExecOrdernRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryForQuote(, CThostFtdcQryForQuoteField *QryForQuoteint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryForQuote: nRequestID[%d]", nRequestID);
	WriteQryForQuote(QryForQuote);

	return m_TraderApi->ReqQryForQuote(, QryForQuotenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryQuote(, CThostFtdcQryQuoteField *QryQuoteint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryQuote: nRequestID[%d]", nRequestID);
	WriteQryQuote(QryQuote);

	return m_TraderApi->ReqQryQuote(, QryQuotenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryOptionSelfClose(, CThostFtdcQryOptionSelfCloseField *QryOptionSelfCloseint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryOptionSelfClose: nRequestID[%d]", nRequestID);
	WriteQryOptionSelfClose(QryOptionSelfClose);

	return m_TraderApi->ReqQryOptionSelfClose(, QryOptionSelfClosenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryInvestUnit(, CThostFtdcQryInvestUnitField *QryInvestUnitint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryInvestUnit: nRequestID[%d]", nRequestID);
	WriteQryInvestUnit(QryInvestUnit);

	return m_TraderApi->ReqQryInvestUnit(, QryInvestUnitnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryCombInstrumentGuard(, CThostFtdcQryCombInstrumentGuardField *QryCombInstrumentGuardint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryCombInstrumentGuard: nRequestID[%d]", nRequestID);
	WriteQryCombInstrumentGuard(QryCombInstrumentGuard);

	return m_TraderApi->ReqQryCombInstrumentGuard(, QryCombInstrumentGuardnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryCombAction(, CThostFtdcQryCombActionField *QryCombActionint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryCombAction: nRequestID[%d]", nRequestID);
	WriteQryCombAction(QryCombAction);

	return m_TraderApi->ReqQryCombAction(, QryCombActionnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryTransferSerial(, CThostFtdcQryTransferSerialField *QryTransferSerialint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryTransferSerial: nRequestID[%d]", nRequestID);
	WriteQryTransferSerial(QryTransferSerial);

	return m_TraderApi->ReqQryTransferSerial(, QryTransferSerialnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryAccountregister(, CThostFtdcQryAccountregisterField *QryAccountregisterint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryAccountregister: nRequestID[%d]", nRequestID);
	WriteQryAccountregister(QryAccountregister);

	return m_TraderApi->ReqQryAccountregister(, QryAccountregisternRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryContractBank(, CThostFtdcQryContractBankField *QryContractBankint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryContractBank: nRequestID[%d]", nRequestID);
	WriteQryContractBank(QryContractBank);

	return m_TraderApi->ReqQryContractBank(, QryContractBanknRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryParkedOrder(, CThostFtdcQryParkedOrderField *QryParkedOrderint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryParkedOrder: nRequestID[%d]", nRequestID);
	WriteQryParkedOrder(QryParkedOrder);

	return m_TraderApi->ReqQryParkedOrder(, QryParkedOrdernRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryParkedOrderAction(, CThostFtdcQryParkedOrderActionField *QryParkedOrderActionint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryParkedOrderAction: nRequestID[%d]", nRequestID);
	WriteQryParkedOrderAction(QryParkedOrderAction);

	return m_TraderApi->ReqQryParkedOrderAction(, QryParkedOrderActionnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryTradingNotice(, CThostFtdcQryTradingNoticeField *QryTradingNoticeint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryTradingNotice: nRequestID[%d]", nRequestID);
	WriteQryTradingNotice(QryTradingNotice);

	return m_TraderApi->ReqQryTradingNotice(, QryTradingNoticenRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryBrokerTradingParams(, CThostFtdcQryBrokerTradingParamsField *QryBrokerTradingParamsint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryBrokerTradingParams: nRequestID[%d]", nRequestID);
	WriteQryBrokerTradingParams(QryBrokerTradingParams);

	return m_TraderApi->ReqQryBrokerTradingParams(, QryBrokerTradingParamsnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQryBrokerTradingAlgos(, CThostFtdcQryBrokerTradingAlgosField *QryBrokerTradingAlgosint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQryBrokerTradingAlgos: nRequestID[%d]", nRequestID);
	WriteQryBrokerTradingAlgos(QryBrokerTradingAlgos);

	return m_TraderApi->ReqQryBrokerTradingAlgos(, QryBrokerTradingAlgosnRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQueryCFMMCTradingAccountToken(, CThostFtdcQueryCFMMCTradingAccountTokenField *QueryCFMMCTradingAccountTokenint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQueryCFMMCTradingAccountToken: nRequestID[%d]", nRequestID);
	WriteQueryCFMMCTradingAccountToken(QueryCFMMCTradingAccountToken);

	return m_TraderApi->ReqQueryCFMMCTradingAccountToken(, QueryCFMMCTradingAccountTokennRequestID);
}

int CThostFtdcTraderApiMiddle::ReqFromBankToFutureByFuture(, CThostFtdcReqTransferField *ReqTransferint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqFromBankToFutureByFuture: nRequestID[%d]", nRequestID);
	WriteReqTransfer(ReqTransfer);

	return m_TraderApi->ReqFromBankToFutureByFuture(, ReqTransfernRequestID);
}

int CThostFtdcTraderApiMiddle::ReqFromFutureToBankByFuture(, CThostFtdcReqTransferField *ReqTransferint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqFromFutureToBankByFuture: nRequestID[%d]", nRequestID);
	WriteReqTransfer(ReqTransfer);

	return m_TraderApi->ReqFromFutureToBankByFuture(, ReqTransfernRequestID);
}

int CThostFtdcTraderApiMiddle::ReqQueryBankAccountMoneyByFuture(, CThostFtdcReqQueryAccountField *ReqQueryAccountint nRequestID)
{
	WRITE_LOG(LogLevel::Info, "ReqQueryBankAccountMoneyByFuture: nRequestID[%d]", nRequestID);
	WriteReqQueryAccount(ReqQueryAccount);

	return m_TraderApi->ReqQueryBankAccountMoneyByFuture(, ReqQueryAccountnRequestID);
}

