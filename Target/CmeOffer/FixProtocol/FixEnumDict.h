#pragma once
#include <string>

using namespace std;

constexpr auto FIX_Future = "FUT";
constexpr auto FIX_Option = "OPT";
constexpr auto FIX_InterestRateSwap = "IRS";
constexpr auto FIX_FXSpot = "FXSPOT";

enum class FixDirection : char
{
	//买
	Buy = '1',
	//卖
	Sell = '2',
};

enum class FixOrderType : char
{
	//市价单
	MarketOrder = '1',
	//限价单
	LimitOrder = '2',
	//止损单
	StopOrder = '3',
	//限价止损单
	StopLimitOrder = '4',
	//
	MarketLimitOrder = 'K',
};

enum class FixOrderStatus : char
{
	//已报
	New = '0',
	//部分成交
	PartiallyFilled = '1',
	//全部成交
	Filled = '2',
	//已撤销
	Cancelled = '4',
	//改单
	Replaced = '5',
	//正在撤销
	PendingCancel = '6',
	//已拒绝
	Rejected = '8',
	//废单
	Eliminated = 'C',
	//正在改单
	PendingReplace = 'E',
	//成交修正
	TradeCorrect = 'G',
	//成交撤销
	TradeCancel = 'H',
	//未定义
	Undefined = 'U',
};

enum class FixTimeInForce : char
{
	//当日有效
	Day = '0',
	//撤销前有效
	GoodTillCancel = '1',
	//立即成交剩余撤销
	FillAndKill = '3',
	//指定日期前有效
	GoodTillDate = '6',
};

enum class FixExecType : char
{
	//报单回报
	NewOrderAck = '0',
	//部分成交
	PartialFill = '1',
	//全部成交
	CompleteFill = '2',
	//撤单回报
	CancelAck = '4',
	//改单回报
	ModifyAck = '5',
	//拒绝回报
	RejectAck = '8',
	//废单回报
	EliminationAck = 'C',
	//交易修正
	TradeCorrect = 'G',
	//交易撤销回报
	TradeCancelAck = 'H',
	//查询报单状态回报
	OrderStatus = 'I',
};


FixDirection ConvertToFixDirection(const string& value);
FixOrderType ConvertToFixOrderType(const string& value);
FixOrderStatus ConvertToFixOrderStatus(const string& value);
FixTimeInForce ConvertToFixTimeInForce(const string& value);
FixExecType ConvertToFixExecType(const string& value);
