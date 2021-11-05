#pragma once
#include <string>

using namespace std;

enum class OrderStatus : char
{
	//正在申报
	Inserting = '0',
	//已报
	Inserted = '1',
	//部成
	PartTraded = '2',
	//已成
	AllTraded = '3',
	//已撤
	Canceled = '4',
	//部成部撤
	PartTradedCanceled = '5',
	//废单
	Error = 'e',
	//未触发
	NotTouched = 'p',
	//已触发
	Touched = 't',
	//未知
	Unknown = 'x',
};

enum class Direction : char
{
	//买
	Buy = '0',
	//卖
	Sell = '1',
};

enum class HedgeFlag : char
{
	//投机
	Speculation = '1',
	//套利
	Arbitrage = '2',
	//保值
	Hedge = '3',
};

enum class OrderPriceType : char
{
	//市价
	Anyprice = '1',
	//限价
	LimitPrice = '2',
	//最优价
	BestPrice = '3',
	//最新价
	LastPrice = '4',
};

enum class OffsetFlag : char
{
	//开仓
	Open = '0',
	//平仓
	Close = '1',
	//平今
	CloseToday = '2',
};

enum class ContingentCondition : char
{
	//立即
	Immediately = '1',
	//止损
	Touch = '2',
	//止赢
	TouchProfit = '3',
	//预埋单
	ParkedOrder = '4',
};

enum class TimeCondition : char
{
	//立即完成，否则撤销
	IOC = '1',
	//本节有效
	GFS = '2',
	//当日有效
	GFD = '3',
	//指定日期前有效
	GTD = '4',
	//撤销前有效
	GTC = '5',
	//集合竞价有效
	GFA = '6',
};

enum class VolumeCondition : char
{
	//任何数量
	AV = '1',
	//最小数量
	MV = '2',
	//全部数量
	CV = '3',
};

enum class ForceCloseReason : char
{
	//非强平
	NotForceClose = '0',
	//资金不足
	LackDeposit = '1',
	//客户超仓
	ClientOverPositionLimit = '2',
	//会员超仓
	MemberOverPositionLimit = '3',
	//持仓非整数倍
	NotMultiple = '4',
	//违规
	Violation = '5',
	//其它
	Other = '6',
	//自然人临近交割
	PersonDeliv = '7',
};

enum class TradeType : char
{
	//普通成交
	Common = '0',
	//期权执行
	OptionsExecution = '1',
	//OTC成交
	OTC = '2',
	//期转现衍生成交
	EFPDerived = '3',
	//组合衍生成交
	CombinationDerived = '4',
};

enum class MarginPriceType : char
{
	//昨结算价
	PreSettlementPrice = '1',
	//最新价
	SettlementPrice = '2',
	//成交均价
	AveragePrice = '3',
	//开仓价
	OpenPrice = '4',
};

enum class IsLocalOrder : char
{
	//外部
	Others = '0',
	//本地
	Local = '1',
};


OrderStatus ConvertToOrderStatus(const string& value);
Direction ConvertToDirection(const string& value);
HedgeFlag ConvertToHedgeFlag(const string& value);
OrderPriceType ConvertToOrderPriceType(const string& value);
OffsetFlag ConvertToOffsetFlag(const string& value);
ContingentCondition ConvertToContingentCondition(const string& value);
TimeCondition ConvertToTimeCondition(const string& value);
VolumeCondition ConvertToVolumeCondition(const string& value);
ForceCloseReason ConvertToForceCloseReason(const string& value);
TradeType ConvertToTradeType(const string& value);
MarginPriceType ConvertToMarginPriceType(const string& value);
IsLocalOrder ConvertToIsLocalOrder(const string& value);
