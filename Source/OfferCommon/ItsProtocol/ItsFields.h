#pragma once
#include <string>
#include <vector>

using namespace std;

class ItsReqQryPrimaryAccountInfo
{
public:
	ItsReqQryPrimaryAccountInfo();
	ItsReqQryPrimaryAccountInfo(const vector<string>& items);
	int ToString(char* buff, int size);
	int ToStream(char* buff, int size);
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
	string ProtocolType;
	string Command;
	string SequenceNo;
	string Reserve1;
	string Reserve2;
	string Reserve3;
	string Reserve4;
	string Reserve5;
	string Reserve6;
	string Unknown;
	string ChannelID;

	static constexpr char* TableName = "t_ItsReqQryPrimaryAccountInfo";
private:
	char m_Buff[4096];
};

class ItsRspQryPrimaryAccountInfo
{
public:
	ItsRspQryPrimaryAccountInfo();
	ItsRspQryPrimaryAccountInfo(const vector<string>& items);
	int ToString(char* buff, int size);
	int ToStream(char* buff, int size);
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
	string ProtocolType;
	string SequenceNo;
	string IsLast;
	string Reserve1;
	string ErrorCode;
	string ErrorMessage;
	string ChannelID;
	string PrimaryAccountID;
	string Password;
	string Port;

	static constexpr char* TableName = "t_ItsRspQryPrimaryAccountInfo";
private:
	char m_Buff[4096];
};

class ItsInsertOrder
{
public:
	ItsInsertOrder();
	ItsInsertOrder(const vector<string>& items);
	int ToString(char* buff, int size);
	int ToStream(char* buff, int size);
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
	string ProtocolType;
	string Command;
	string SequenceNo;
	string Reserve1;
	string Reserve2;
	string Reserve3;
	string Reserve4;
	string Reserve5;
	string Reserve6;
	string ExchangeID;
	string InstrumentID;
	string Price;
	string Direction;
	string Reserve7;
	string CombHedgeFlag;
	string Volume;
	string OrderPriceType;
	string RequestID;
	string Reserve8;
	string TimeCondition;
	string GTDDate;
	string VolumeCondition;
	string MinVolume;
	string IsSwapOrder;
	string ForceCloseReason;
	string AccountID;
	string TradingDay;

	static constexpr char* TableName = "t_ItsInsertOrder";
private:
	char m_Buff[4096];
};

class ItsInsertOrderCancel
{
public:
	ItsInsertOrderCancel();
	ItsInsertOrderCancel(const vector<string>& items);
	int ToString(char* buff, int size);
	int ToStream(char* buff, int size);
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
	string ProtocolType;
	string Command;
	string SequenceNo;
	string Reserve1;
	string Reserve2;
	string Reserve3;
	string Reserve4;
	string Reserve5;
	string Reserve6;
	string OrderRef;
	string FrontID;
	string SessionID;
	string ExchangeID;
	string OrderSysID;
	string ChannelOrderID;
	string BrokerOrderID;
	string InstrumentID;
	string Direction;
	string TradingDay;

	static constexpr char* TableName = "t_ItsInsertOrderCancel";
private:
	char m_Buff[4096];
};

class ItsRspOrder
{
public:
	ItsRspOrder();
	ItsRspOrder(const vector<string>& items);
	int ToString(char* buff, int size);
	int ToStream(char* buff, int size);
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
	string ProtocolType;
	string SequenceNo;
	string Reserve1;
	string Reserve2;
	string ErrorID;
	string ErrorMsg;
	string TradingDay;

	static constexpr char* TableName = "t_ItsRspOrder";
private:
	char m_Buff[4096];
};

class ItsOrder
{
public:
	ItsOrder();
	ItsOrder(const vector<string>& items);
	int ToString(char* buff, int size);
	int ToStream(char* buff, int size);
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
	string ProtocolType;
	string Command;
	string Reserve1;
	string Reserve2;
	string Reserve3;
	string Reserve4;
	string ChannelID;
	string ExchangeID;
	string InstrumentID;
	string OrderRef;
	string InsertTime;
	string CancelTime;
	string OrderSysID;
	string StatusMsg;
	string Direction;
	string CombOffsetFlag;
	string CombHedgeFlag;
	string OrderPriceType;
	string OrderStatus;
	string ForceCloseReason;
	string RequestID;
	string FrontID;
	string SessionID;
	string BrokerOrderID;
	string VolumeTotalOriginal;
	string VolumeTraded;
	string InsertDate;
	string TradingDay;
	string LimitPrice;
	string IsLocalOrder;
	string UserProductInfo;
	string TimeCondition;
	string GTDDate;
	string VolumeCondition;
	string MinVolume;
	string ContingentCondition;
	string StopPrice;
	string IsSwapOrder;
	string Reserve5;

	static constexpr char* TableName = "t_ItsOrder";
private:
	char m_Buff[4096];
};

class ItsTrade
{
public:
	ItsTrade();
	ItsTrade(const vector<string>& items);
	int ToString(char* buff, int size);
	int ToStream(char* buff, int size);
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
	string ProtocolType;
	string Command;
	string Reserve1;
	string Reserve2;
	string Reserve3;
	string Reserve4;
	string ChannelID;
	string ExchangeID;
	string InstrumentID;
	string OrderRef;
	string OrderSysID;
	string TradeTime;
	string TradeID;
	string Direction;
	string OffsetFlag;
	string HedgeFlag;
	string BrokerOrderID;
	string Volume;
	string TradeDate;
	string TradingDay;
	string Price;
	string Reserve5;
	string TradeType;
	string ExchangeTradeID;
	string Reserve7;
	string Reserve8;

	static constexpr char* TableName = "t_ItsTrade";
private:
	char m_Buff[4096];
};

class ItsErrRtnOrderCancel
{
public:
	ItsErrRtnOrderCancel();
	ItsErrRtnOrderCancel(const vector<string>& items);
	int ToString(char* buff, int size);
	int ToStream(char* buff, int size);
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
	string ProtocolType;
	string Command;
	string Reserve1;
	string Reserve2;
	string Reserve3;
	string Reserve4;
	string ChannelID;
	string BrokerOrderID;
	string OrderRef;
	string FrontID;
	string SessionID;
	string ExchangeID;
	string OrderSysID;
	string Reserve5;
	string ErrorID;
	string ErrorMsg;
	string TradingDay;

	static constexpr char* TableName = "t_ItsErrRtnOrderCancel";
private:
	char m_Buff[4096];
};


class ItsMdbCallback
{
public:
	virtual void SelectItsReqQryPrimaryAccountInfoCallback(ItsReqQryPrimaryAccountInfo* field) { delete field; }
	virtual void SelectItsRspQryPrimaryAccountInfoCallback(ItsRspQryPrimaryAccountInfo* field) { delete field; }
	virtual void SelectItsInsertOrderCallback(ItsInsertOrder* field) { delete field; }
	virtual void SelectItsInsertOrderCancelCallback(ItsInsertOrderCancel* field) { delete field; }
	virtual void SelectItsRspOrderCallback(ItsRspOrder* field) { delete field; }
	virtual void SelectItsOrderCallback(ItsOrder* field) { delete field; }
	virtual void SelectItsTradeCallback(ItsTrade* field) { delete field; }
	virtual void SelectItsErrRtnOrderCancelCallback(ItsErrRtnOrderCancel* field) { delete field; }
};

