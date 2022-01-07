#pragma once

#include "PBApiDataStruct.h"
#include "StepApi.h"

#define PBSTEP_ERROR_DISCONNECT -3
#define PBSTEP_ERROR_NOT_LOGIN -8

class PBStepSpi;
class PBStepApi
{
public:
	PBStepApi();
	~PBStepApi();
	
	bool Init(PBStepSpi* stepSpi, const char* address, const char* fileName);
	
	//设置用户数据请求
	int ReqSetUserInfo(PBStepReqSetUserInfoField& ReqSetUserInfo, int& reqNo);
	//客户端校验请求
	int ReqSecurityVerity(PBStepReqSecurityVerityField& ReqSecurityVerity, int& reqNo);
	//登录请求
	int ReqLogin(PBStepReqLoginField& ReqLogin, int& reqNo);
	//确认结算单请求
	int ReqConfirmSettlement(PBStepReqConfirmSettlementField& ReqConfirmSettlement, int& reqNo);
	//委托请求
	int ReqInsertOrder(PBStepReqInsertOrderField& ReqInsertOrder, int& reqNo);
	//委托撤单请求
	int ReqCancelOrder(PBStepReqCancelOrderField& ReqCancelOrder, int& reqNo);
	//查询持仓请求
	int ReqQryPosition(PBStepQryPositionField& QryPosition, int& reqNo);
	//查询持仓明细请求
	int ReqQryPositionDetail(PBStepQryPositionDetailField& QryPositionDetail, int& reqNo);
	//查询当日委托
	int ReqQryTodayOrder(PBStepQryTodayOrderField& QryTodayOrder, int& reqNo);
	//查询单笔委托
	int ReqQryOneOrder(PBStepQryTodayOrderField& QryTodayOrder, int& reqNo);
	//查询当日成交请求
	int ReqQryTodayTrade(PBStepQryTodayTradeField& QryTodayTrade, int& reqNo);
	//查询资金请求
	int ReqQryCapital(PBStepQryCapitalField& QryCapital, int& reqNo);
	//查询席位请求
	int ReqQryHolderAccount(PBStepQryHolderAccountField& QryHolderAccount, int& reqNo);
	//查询合约请求
	int ReqQryInstrument(PBStepQryInstrumentField& QryInstrument, int& reqNo);
	//查询期货交易所状态请求
	int ReqQrySystemStatus(PBStepQrySystemStatusField& QrySystemStatus, int& reqNo);
	//查询结算单请求
	int ReqQrySettlement(PBStepQrySettlementField& QrySettlement, int& reqNo);
	//查询行权请求
	int ReqQryTodayExecOrder(PBStepQryTodayExecOrderField& QryTodayExecOrder, int& reqNo);
	//行权请求
	int ReqExecOrder(PBStepReqExecOrderField& ReqExecOrder, int& reqNo);
	//行权撤单请求
	int ReqCancelExecOrder(PBStepReqCancelExecOrderField& ReqCancelExecOrder, int& reqNo);
	//询价请求
	int ReqInquiry(PBStepReqInquiryField& ReqInquiry, int& reqNo);
	//查询期货手续费率请求
	int ReqQryFutureCommissionRate(PBStepQryFutureCommissionRateField& QryFutureCommissionRate, int& reqNo);
	//查询期货保证金率请求
	int ReqQryFutureMarginRate(PBStepQryFutureMarginRateField& QryFutureMarginRate, int& reqNo);
	//查询银证转账流水请求
	int ReqQryTransferMoney(PBStepQryTransferMoneyField& QryTransferMoney, int& reqNo);
	//查询成交增量请求
	int ReqQryIncTrade(PBStepQryIncTradeField& QryIncTrade, int& reqNo);
	//查询委托增量请求
	int ReqQryIncOrder(PBStepQryIncOrderField& QryIncOrder, int& reqNo);
	//查询备兑证券锁定或解锁数量请求
	int ReqQryLockAvailable(PBStepQryLockAvailableField& QryLockAvailable, int& reqNo);
	//备兑证券锁定或解锁请求
	int ReqLockSecurityOrder(PBStepReqLockSecurityOrderField& ReqLockSecurityOrder, int& reqNo);

private:
	void SetBaseInfo(HANDLE_REQUEST request, PBStepBaseInfoField& baseInfo);

private:
	HANDLE_USER m_User;
};
