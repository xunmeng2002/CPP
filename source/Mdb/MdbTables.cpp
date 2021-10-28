#include "MdbTables.h"
#include "Mdb.h"


int CmeProduct::ToStream(char* buff, int size) const
{
	return snprintf(buff, size, " '%s',  '%s',  '%s'",
		ExchangeID.c_str(), ProductID.c_str(), MarketSegmentID.c_str());
}
int CmeProduct::ToString(char* buff, int size) const
{
	return snprintf(buff, size, "MdbCmeProduct: ExchangeID:[%s], ProductID:[%s], MarketSegmentID:[%s]",
		ExchangeID.c_str(), ProductID.c_str(), MarketSegmentID.c_str());
}
string CmeProduct::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_MdbCmeProduct(ExchangeID char(32), ProductID char(32), MarketSegmentID char(32), PRIMARY KEY(ExchangeID, ProductID));";
}
string CmeProduct::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	ToStream(m_Buff, 4096);
	return "REPLACE INTO t_MdbCmeProduct VALUES(" + string(m_Buff) + ");";
}
int CmeProduct::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new CmeProduct();
	field->ExchangeID = colValues[0];
	field->ProductID = colValues[1];
	field->MarketSegmentID = colValues[3];

	((MdbCallback*)callback)->SelectMdbCmeProductCallback(field);
	return 0;
}

int CmeInstrumentBrief::ToStream(char* buff, int size) const
{
	return snprintf(buff, size, " '%s',  '%s',  '%s',  '%s',  '%s',  '%s',  '%s'",
		ExchangeID.c_str(), ProductID.c_str(), ContractID.c_str(), ITCAlias.c_str(), GenCode.c_str(), MktID.c_str(), MarketSegmentID.c_str());
}
int CmeInstrumentBrief::ToString(char* buff, int size) const
{
	return snprintf(buff, size, "MdbCmeInstrumentBrief: ExchangeID:[%s], ProductID:[%s], ContractID:[%s], ITCAlias:[%s], GenCode:[%s], MktID:[%s], MarketSegmentID:[%s]",
		ExchangeID.c_str(), ProductID.c_str(), ContractID.c_str(), ITCAlias.c_str(), GenCode.c_str(), MktID.c_str(), MarketSegmentID.c_str());
}
string CmeInstrumentBrief::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_MdbCmeInstrumentBrief(ExchangeID char(32), ProductID char(32), ContractID char(32), ITCAlias char(32), GenCode char(32), MktID char(32), MarketSegmentID char(32), PRIMARY KEY(ExchangeID, ContractID));";
}
string CmeInstrumentBrief::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	ToStream(m_Buff, 4096);
	return "REPLACE INTO t_MdbCmeInstrumentBrief VALUES(" + string(m_Buff) + ");";
}
int CmeInstrumentBrief::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new CmeInstrumentBrief();
	field->ExchangeID = colValues[0];
	field->ProductID = colValues[1];
	field->ContractID = colValues[2];
	field->ITCAlias = colValues[3];
	field->GenCode = colValues[4];
	field->MktID = colValues[5];
	field->MarketSegmentID = colValues[6];

	((MdbCallback*)callback)->SelectMdbCmeInstrumentBriefCallback(field);
	return 0;
}

int OrderSequence::ToStream(char* buff, int size) const
{
	return snprintf(buff, size, " '%s',  '%d'",
		TradingDay.c_str(), MaxOrderLocalID);
}
int OrderSequence::ToString(char* buff, int size) const
{
	return snprintf(buff, size, "MdbOrderSequence: TradingDay:[%s], MaxOrderLocalID:[%d]",
		TradingDay.c_str(), MaxOrderLocalID);
}
string OrderSequence::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_MdbOrderSequence(TradingDay char(32), MaxOrderLocalID char(32), PRIMARY KEY(TradingDay));";
}
string OrderSequence::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	ToStream(m_Buff, 4096);
	return "REPLACE INTO t_MdbOrderSequence VALUES(" + string(m_Buff) + ");";
}
int OrderSequence::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new OrderSequence();
	field->TradingDay = colValues[0];
	field->MaxOrderLocalID = atoi(colValues[1]);

	((MdbCallback*)callback)->SelectMdbOrderSequenceCallback(field);
	return 0;
}

int Order::ToStream(char* buff, int size) const
{
	return snprintf(buff, size, " '%s',  '%s',  '%s',  '%s',  '%s',  '%d',  '%s',  '%c',  '%c',  '%c',  '%c',  '%f',  '%d',  '%d',  '%c',  '%s',  '%s',  '%s',  '%d',  '%s',  '%s',  '%s',  '%s',  '%c',  '%c',  '%s',  '%c',  '%s',  '%c',  '%d',  '%c',  '%s',  '%s'",
		AccountID.c_str(), ExchangeID.c_str(), ContractID.c_str(), MarketSegmentID.c_str(), InstrumentID.c_str(), OrderLocalID, OrderSysID.c_str(), Direction, OffsetFlag, HedgeFlag, OrderPriceType, Price, Volume, VolumeTraded, OrderStatus, StatusMsg.c_str(), RequestID.c_str(), FrontID.c_str(), SessionID, InsertTime.c_str(), CancelTime.c_str(), InsertDate.c_str(), TradingDay.c_str(), ForceCloseReason, IsLocalOrder, UserProductInfo.c_str(), TimeCondition, GTDDate.c_str(), VolumeCondition, MinVolume, ContingentCondition, StopPrice.c_str(), IsSwapOrder.c_str());
}
int Order::ToString(char* buff, int size) const
{
	return snprintf(buff, size, "MdbOrder: AccountID:[%s], ExchangeID:[%s], ContractID:[%s], MarketSegmentID:[%s], InstrumentID:[%s], OrderLocalID:[%d], OrderSysID:[%s], Direction:[%c], OffsetFlag:[%c], HedgeFlag:[%c], OrderPriceType:[%c], Price:[%f], Volume:[%d], VolumeTraded:[%d], OrderStatus:[%c], StatusMsg:[%s], RequestID:[%s], FrontID:[%s], SessionID:[%d], InsertTime:[%s], CancelTime:[%s], InsertDate:[%s], TradingDay:[%s], ForceCloseReason:[%c], IsLocalOrder:[%c], UserProductInfo:[%s], TimeCondition:[%c], GTDDate:[%s], VolumeCondition:[%c], MinVolume:[%d], ContingentCondition:[%c], StopPrice:[%s], IsSwapOrder:[%s]",
		AccountID.c_str(), ExchangeID.c_str(), ContractID.c_str(), MarketSegmentID.c_str(), InstrumentID.c_str(), OrderLocalID, OrderSysID.c_str(), Direction, OffsetFlag, HedgeFlag, OrderPriceType, Price, Volume, VolumeTraded, OrderStatus, StatusMsg.c_str(), RequestID.c_str(), FrontID.c_str(), SessionID, InsertTime.c_str(), CancelTime.c_str(), InsertDate.c_str(), TradingDay.c_str(), ForceCloseReason, IsLocalOrder, UserProductInfo.c_str(), TimeCondition, GTDDate.c_str(), VolumeCondition, MinVolume, ContingentCondition, StopPrice.c_str(), IsSwapOrder.c_str());
}
string Order::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_MdbOrder(AccountID char(32), ExchangeID char(32), ContractID char(32), MarketSegmentID char(32), InstrumentID char(32), OrderLocalID char(32), OrderSysID char(32), Direction char(32), OffsetFlag char(32), HedgeFlag char(32), OrderPriceType char(32), Price char(32), Volume char(32), VolumeTraded char(32), OrderStatus char(32), StatusMsg char(32), RequestID char(32), FrontID char(32), SessionID char(32), InsertTime char(32), CancelTime char(32), InsertDate char(32), TradingDay char(32), ForceCloseReason char(32), IsLocalOrder char(32), UserProductInfo char(32), TimeCondition char(32), GTDDate char(32), VolumeCondition char(32), MinVolume char(32), ContingentCondition char(32), StopPrice char(32), IsSwapOrder char(32), PRIMARY KEY(TradingDay, OrderLocalID));";
}
string Order::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	ToStream(m_Buff, 4096);
	return "REPLACE INTO t_MdbOrder VALUES(" + string(m_Buff) + ");";
}
int Order::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new Order();
	field->AccountID = colValues[0];
	field->ExchangeID = colValues[1];
	field->ContractID = colValues[2];
	field->MarketSegmentID = colValues[3];
	field->InstrumentID = colValues[4];
	field->OrderLocalID = atoi(colValues[5]);
	field->OrderSysID = colValues[6];
	field->Direction = ConvertToDirection(colValues[7]);
	field->OffsetFlag = ConvertToOffsetFlag(colValues[8]);
	field->HedgeFlag = ConvertToHedgeFlag(colValues[9]);
	field->OrderPriceType = ConvertToOrderPriceType(colValues[10]);
	field->Price = atof(colValues[11]);
	field->Volume = atoi(colValues[12]);
	field->VolumeTraded = atoi(colValues[13]);
	field->OrderStatus = ConvertToOrderStatus(colValues[14]);
	field->StatusMsg = colValues[15];
	field->RequestID = colValues[16];
	field->FrontID = colValues[17];
	field->SessionID = atoi(colValues[18]);
	field->InsertTime = colValues[19];
	field->CancelTime = colValues[20];
	field->InsertDate = colValues[21];
	field->TradingDay = colValues[22];
	field->ForceCloseReason = ConvertToForceCloseReason(colValues[23]);
	field->IsLocalOrder = ConvertToIsLocalOrder(colValues[24]);
	field->UserProductInfo = colValues[25];
	field->TimeCondition = ConvertToTimeCondition(colValues[26]);
	field->GTDDate = colValues[27];
	field->VolumeCondition = ConvertToVolumeCondition(colValues[28]);
	field->MinVolume = atoi(colValues[29]);
	field->ContingentCondition = ConvertToContingentCondition(colValues[30]);
	field->StopPrice = colValues[31];
	field->IsSwapOrder = colValues[32];

	((MdbCallback*)callback)->SelectMdbOrderCallback(field);
	return 0;
}

int OrderCancel::ToStream(char* buff, int size) const
{
	return snprintf(buff, size, " '%s',  '%s',  '%s',  '%s',  '%s',  '%d',  '%d',  '%s',  '%c',  '%s',  '%s',  '%d',  '%d',  '%s',  '%s'",
		AccountID.c_str(), ExchangeID.c_str(), ContractID.c_str(), MarketSegmentID.c_str(), InstrumentID.c_str(), OrderLocalID, OrigOrderLocalID, OrderSysID.c_str(), Direction, OrderRef.c_str(), FrontID.c_str(), SessionID, ErrorID, ErrorMsg.c_str(), TradingDay.c_str());
}
int OrderCancel::ToString(char* buff, int size) const
{
	return snprintf(buff, size, "MdbOrderCancel: AccountID:[%s], ExchangeID:[%s], ContractID:[%s], MarketSegmentID:[%s], InstrumentID:[%s], OrderLocalID:[%d], OrigOrderLocalID:[%d], OrderSysID:[%s], Direction:[%c], OrderRef:[%s], FrontID:[%s], SessionID:[%d], ErrorID:[%d], ErrorMsg:[%s], TradingDay:[%s]",
		AccountID.c_str(), ExchangeID.c_str(), ContractID.c_str(), MarketSegmentID.c_str(), InstrumentID.c_str(), OrderLocalID, OrigOrderLocalID, OrderSysID.c_str(), Direction, OrderRef.c_str(), FrontID.c_str(), SessionID, ErrorID, ErrorMsg.c_str(), TradingDay.c_str());
}
string OrderCancel::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_MdbOrderCancel(AccountID char(32), ExchangeID char(32), ContractID char(32), MarketSegmentID char(32), InstrumentID char(32), OrderLocalID char(32), OrigOrderLocalID char(32), OrderSysID char(32), Direction char(32), OrderRef char(32), FrontID char(32), SessionID char(32), ErrorID char(32), ErrorMsg char(32), TradingDay char(32), PRIMARY KEY(TradingDay, OrderLocalID));";
}
string OrderCancel::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	ToStream(m_Buff, 4096);
	return "REPLACE INTO t_MdbOrderCancel VALUES(" + string(m_Buff) + ");";
}
int OrderCancel::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new OrderCancel();
	field->AccountID = colValues[0];
	field->ExchangeID = colValues[1];
	field->ContractID = colValues[2];
	field->MarketSegmentID = colValues[3];
	field->InstrumentID = colValues[4];
	field->OrderLocalID = atoi(colValues[5]);
	field->OrigOrderLocalID = atoi(colValues[6]);
	field->OrderSysID = colValues[7];
	field->Direction = ConvertToDirection(colValues[8]);
	field->OrderRef = colValues[9];
	field->FrontID = colValues[10];
	field->SessionID = atoi(colValues[11]);
	field->ErrorID = atoi(colValues[12]);
	field->ErrorMsg = colValues[13];
	field->TradingDay = colValues[14];

	((MdbCallback*)callback)->SelectMdbOrderCancelCallback(field);
	return 0;
}

int Trade::ToStream(char* buff, int size) const
{
	return snprintf(buff, size, " '%s',  '%s',  '%s',  '%s',  '%s',  '%s',  '%c',  '%c',  '%c',  '%f',  '%d',  '%d',  '%s',  '%s',  '%s',  '%s'",
		AccountID.c_str(), ExchangeID.c_str(), ContractID.c_str(), MarketSegmentID.c_str(), InstrumentID.c_str(), TradeID.c_str(), Direction, OffsetFlag, HedgeFlag, Price, Volume, OrderLocalID, OrderSysID.c_str(), TradeTime.c_str(), TradeDate.c_str(), TradingDay.c_str());
}
int Trade::ToString(char* buff, int size) const
{
	return snprintf(buff, size, "MdbTrade: AccountID:[%s], ExchangeID:[%s], ContractID:[%s], MarketSegmentID:[%s], InstrumentID:[%s], TradeID:[%s], Direction:[%c], OffsetFlag:[%c], HedgeFlag:[%c], Price:[%f], Volume:[%d], OrderLocalID:[%d], OrderSysID:[%s], TradeTime:[%s], TradeDate:[%s], TradingDay:[%s]",
		AccountID.c_str(), ExchangeID.c_str(), ContractID.c_str(), MarketSegmentID.c_str(), InstrumentID.c_str(), TradeID.c_str(), Direction, OffsetFlag, HedgeFlag, Price, Volume, OrderLocalID, OrderSysID.c_str(), TradeTime.c_str(), TradeDate.c_str(), TradingDay.c_str());
}
string Trade::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_MdbTrade(AccountID char(32), ExchangeID char(32), ContractID char(32), MarketSegmentID char(32), InstrumentID char(32), TradeID char(32), Direction char(32), OffsetFlag char(32), HedgeFlag char(32), Price char(32), Volume char(32), OrderLocalID char(32), OrderSysID char(32), TradeTime char(32), TradeDate char(32), TradingDay char(32), PRIMARY KEY(TradingDay, OrderSysID, TradeID));";
}
string Trade::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	ToStream(m_Buff, 4096);
	return "REPLACE INTO t_MdbTrade VALUES(" + string(m_Buff) + ");";
}
int Trade::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new Trade();
	field->AccountID = colValues[0];
	field->ExchangeID = colValues[1];
	field->ContractID = colValues[2];
	field->MarketSegmentID = colValues[3];
	field->InstrumentID = colValues[4];
	field->TradeID = colValues[5];
	field->Direction = ConvertToDirection(colValues[6]);
	field->OffsetFlag = ConvertToOffsetFlag(colValues[7]);
	field->HedgeFlag = ConvertToHedgeFlag(colValues[8]);
	field->Price = atof(colValues[9]);
	field->Volume = atoi(colValues[10]);
	field->OrderLocalID = atoi(colValues[11]);
	field->OrderSysID = colValues[12];
	field->TradeTime = colValues[13];
	field->TradeDate = colValues[14];
	field->TradingDay = colValues[15];

	((MdbCallback*)callback)->SelectMdbTradeCallback(field);
	return 0;
}

