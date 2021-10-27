#pragma once
#include <string>
#include "MdbEnumDict.h"

using namespace std;


class CmeProduct
{
public:
	int ToStream(char* buff, int size) const;
	int ToString(char* buff, int size) const;
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
	string ExchangeID;
	string ProductID;
	string MarketSegmentID;
	
	static constexpr char* TableName = "t_MdbCmeProduct";
private:
	char m_Buff[4096];
};

class CmeInstrumentBrief
{
public:
	int ToStream(char* buff, int size) const;
	int ToString(char* buff, int size) const;
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
	string ExchangeID;
	string ProductID;
	string ContractID;
	string ITCAlias;
	string GenCode;
	string MktID;
	string MarketSegmentID;
	
	static constexpr char* TableName = "t_MdbCmeInstrumentBrief";
private:
	char m_Buff[4096];
};

class Order
{
public:
	int ToStream(char* buff, int size) const;
	int ToString(char* buff, int size) const;
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
	string AccountID;
	string ExchangeID;
	string ContractID;
	string MarketSegmentID;
	string InstrumentID;
	int OrderLocalID;
	string OrderSysID;
	Direction Direction;
	OffsetFlag OffsetFlag;
	HedgeFlag HedgeFlag;
	OrderPriceType OrderPriceType;
	double Price;
	int Volume;
	int VolumeTraded;
	OrderStatus OrderStatus;
	string StatusMsg;
	string RequestID;
	string FrontID;
	int SessionID;
	string InsertTime;
	string CancelTime;
	string InsertDate;
	string TradingDay;
	ForceCloseReason ForceCloseReason;
	IsLocalOrder IsLocalOrder;
	string UserProductInfo;
	TimeCondition TimeCondition;
	string GTDDate;
	VolumeCondition VolumeCondition;
	int MinVolume;
	ContingentCondition ContingentCondition;
	string StopPrice;
	string IsSwapOrder;
	
	static constexpr char* TableName = "t_MdbOrder";
private:
	char m_Buff[4096];
};

class OrderCancel
{
public:
	int ToStream(char* buff, int size) const;
	int ToString(char* buff, int size) const;
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
	string AccountID;
	string ExchangeID;
	string ContractID;
	string MarketSegmentID;
	string InstrumentID;
	int OrderLocalID;
	int OrigOrderLocalID;
	string OrderSysID;
	Direction Direction;
	string OrderRef;
	string FrontID;
	int SessionID;
	int ErrorID;
	string ErrorMsg;
	string TradingDay;
	
	static constexpr char* TableName = "t_MdbOrderCancel";
private:
	char m_Buff[4096];
};

class Trade
{
public:
	int ToStream(char* buff, int size) const;
	int ToString(char* buff, int size) const;
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
	string AccountID;
	string ExchangeID;
	string ContractID;
	string MarketSegmentID;
	string InstrumentID;
	string TradeID;
	Direction Direction;
	OffsetFlag OffsetFlag;
	HedgeFlag HedgeFlag;
	double Price;
	int Volume;
	int OrderLocalID;
	string OrderSysID;
	string TradeTime;
	string TradeDate;
	string TradingDay;
	
	static constexpr char* TableName = "t_MdbTrade";
private:
	char m_Buff[4096];
};


class MdbCallback
{
public:
	virtual void SelectMdbCmeProductCallback(CmeProduct* field) { delete field; }
	virtual void SelectMdbCmeInstrumentBriefCallback(CmeInstrumentBrief* field) { delete field; }
	virtual void SelectMdbOrderCallback(Order* field) { delete field; }
	virtual void SelectMdbOrderCancelCallback(OrderCancel* field) { delete field; }
	virtual void SelectMdbTradeCallback(Trade* field) { delete field; }
};

