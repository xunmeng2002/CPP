#pragma once

#include "PBStepApi.h"

class PBStepSpi
{
public:
	virtual void OnDisConnected();
	
	//设置用户数据应答
	virtual void OnRspSetUserInfo(PBStepRspSetUserInfoField* RspSetUserInfo, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//客户端校验回报
	virtual void OnRspSecurityVerity(PBStepRspSecurityVerityField* RspSecurityVerity, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//登录回报
	virtual void OnRspLogin(PBStepRspLoginField* RspLogin, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//确认结算单应答
	virtual void OnRspConfirmSettlement(PBStepRspConfirmSettlementField* RspConfirmSettlement, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//委托应答
	virtual void OnRspInsertOrder(PBStepRspInsertOrderField* RspInsertOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//委托撤单应答
	virtual void OnRspCancelOrder(PBStepRspCancelOrderField* RspCancelOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询持仓回报
	virtual void OnRspQryPosition(PBStepPositionField* Position, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询持仓明细应答
	virtual void OnRspQryPositionDetail(PBStepPositionDetailField* PositionDetail, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询当日委托应答
	virtual void OnRspQryTodayOrder(PBStepTodayOrderField* TodayOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询单笔委托回报
	virtual void OnRspQryOneOrder(PBStepTodayOrderField* TodayOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询当日成交回报
	virtual void OnRspQryTodayTrade(PBStepTodayTradeField* TodayTrade, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询资金回报
	virtual void OnRspQryCapital(PBStepCapitalField* Capital, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询席位应答
	virtual void OnRspQryHolderAccount(PBStepHolderAccountField* HolderAccount, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询合约回报
	virtual void OnRspQryInstrument(PBStepInstrumentField* Instrument, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询期货交易所状态回报
	virtual void OnRspQrySystemStatus(PBStepSystemStatusField* SystemStatus, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询结算单应答
	virtual void OnRspQrySettlement(PBStepSettlementField* Settlement, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询行权应答
	virtual void OnRspQryTodayExecOrder(PBStepTodayExecOrderField* TodayExecOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//行权应答
	virtual void OnRspExecOrder(PBStepRspExecOrderField* RspExecOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//行权撤单应答
	virtual void OnRspCancelExecOrder(PBStepRspCancelExecOrderField* RspCancelExecOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//询价应答
	virtual void OnRspInquiry(PBStepRspInquiryField* RspInquiry, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询期货手续费率应答
	virtual void OnRspQryFutureCommissionRate(PBStepFutureCommissionRateField* FutureCommissionRate, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询期货保证金率应答
	virtual void OnRspQryFutureMarginRate(PBStepFutureMarginRateField* FutureMarginRate, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询银证转账流水应答
	virtual void OnRspQryTransferMoney(PBStepTransferMoneyField* TransferMoney, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询成交增量应答
	virtual void OnRspQryIncTrade(PBStepTodayTradeField* TodayTrade, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询委托增量应答
	virtual void OnRspQryIncOrder(PBStepTodayOrderField* TodayOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//查询备兑证券锁定或解锁数量应答
	virtual void OnRspQryLockAvailable(PBStepLockAvailableField* LockAvailable, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//备兑证券锁定或解锁应答
	virtual void OnRspLockSecurityOrder(PBStepRspLockSecurityOrderField* RspLockSecurityOrder, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
	//系统状态推送
	virtual void OnRtnSystemStatus(PBStepSystemStatusField* SystemStatus);
	//委托推送
	virtual void OnRtnOrder(PBStepOrderField* Order);
	//成交推送
	virtual void OnRtnTrade(PBStepTradeField* Trade);
	//行权委托推送
	virtual void OnRtnExecOrder(PBStepExecOrderField* ExecOrder);
};
