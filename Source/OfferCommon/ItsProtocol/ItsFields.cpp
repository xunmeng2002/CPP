#include "ItsFields.h"
#include "Logger.h"


ItsReqQryPrimaryAccountInfo::ItsReqQryPrimaryAccountInfo()
	:ProtocolType("R")
{
	memset(m_Buff, 0, sizeof(m_Buff));
}
ItsReqQryPrimaryAccountInfo::ItsReqQryPrimaryAccountInfo(const vector<string>& items)
{
	memset(m_Buff, 0, sizeof(m_Buff));
	ProtocolType = items[0];
	Command = items[1];
	SequenceNo = items[2];
	Reserve1 = items[3];
	Reserve2 = items[4];
	Reserve3 = items[5];
	Reserve4 = items[6];
	Reserve5 = items[7];
	Reserve6 = items[8];
	Unknown = items[9];
	ChannelID = items[10];
}
int ItsReqQryPrimaryAccountInfo::ToString(char* buff, int size)
{
	return snprintf(buff, size, "ItsReqQryPrimaryAccountInfo: ProtocolType[%s] Command[%s] SequenceNo[%s] Reserve1[%s] Reserve2[%s] Reserve3[%s] Reserve4[%s] Reserve5[%s] Reserve6[%s] Unknown[%s] ChannelID[%s] ", ProtocolType.c_str(), Command.c_str(), SequenceNo.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), Reserve5.c_str(), Reserve6.c_str(), Unknown.c_str(), ChannelID.c_str());
}
int ItsReqQryPrimaryAccountInfo::ToStream(char* buff, int size)
{
	return snprintf(buff, size, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|", ProtocolType.c_str(), Command.c_str(), SequenceNo.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), Reserve5.c_str(), Reserve6.c_str(), Unknown.c_str(), ChannelID.c_str());
}
string ItsReqQryPrimaryAccountInfo::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_ItsReqQryPrimaryAccountInfo(ProtocolType char(32), Command char(32), SequenceNo char(32), Reserve1 char(32), Reserve2 char(32), Reserve3 char(32), Reserve4 char(32), Reserve5 char(32), Reserve6 char(32), Unknown char(32), ChannelID char(32), PRIMARY KEY(SequenceNo));";
}
string ItsReqQryPrimaryAccountInfo::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	snprintf(m_Buff, 4096, "REPLACE INTO t_ItsReqQryPrimaryAccountInfo VALUES(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\");", ProtocolType.c_str(), Command.c_str(), SequenceNo.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), Reserve5.c_str(), Reserve6.c_str(), Unknown.c_str(), ChannelID.c_str());
	return string(m_Buff);
}
int ItsReqQryPrimaryAccountInfo::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new ItsReqQryPrimaryAccountInfo();
	field->ProtocolType = colValues[0];
	field->Command = colValues[1];
	field->SequenceNo = colValues[2];
	field->Reserve1 = colValues[3];
	field->Reserve2 = colValues[4];
	field->Reserve3 = colValues[5];
	field->Reserve4 = colValues[6];
	field->Reserve5 = colValues[7];
	field->Reserve6 = colValues[8];
	field->Unknown = colValues[9];
	field->ChannelID = colValues[10];

	((ItsMdbCallback*)callback)->SelectItsReqQryPrimaryAccountInfoCallback(field);
	return 0;
}

ItsRspQryPrimaryAccountInfo::ItsRspQryPrimaryAccountInfo()
	:ProtocolType("A")
{
	memset(m_Buff, 0, sizeof(m_Buff));
}
ItsRspQryPrimaryAccountInfo::ItsRspQryPrimaryAccountInfo(const vector<string>& items)
{
	memset(m_Buff, 0, sizeof(m_Buff));
	ProtocolType = items[0];
	SequenceNo = items[1];
	IsLast = items[2];
	Reserve1 = items[3];
	ErrorCode = items[4];
	ErrorMessage = items[5];
	ChannelID = items[6];
	PrimaryAccountID = items[7];
	Password = items[8];
	Port = items[9];
}
int ItsRspQryPrimaryAccountInfo::ToString(char* buff, int size)
{
	return snprintf(buff, size, "ItsRspQryPrimaryAccountInfo: ProtocolType[%s] SequenceNo[%s] IsLast[%s] Reserve1[%s] ErrorCode[%s] ErrorMessage[%s] ChannelID[%s] PrimaryAccountID[%s] Password[%s] Port[%s] ", ProtocolType.c_str(), SequenceNo.c_str(), IsLast.c_str(), Reserve1.c_str(), ErrorCode.c_str(), ErrorMessage.c_str(), ChannelID.c_str(), PrimaryAccountID.c_str(), Password.c_str(), Port.c_str());
}
int ItsRspQryPrimaryAccountInfo::ToStream(char* buff, int size)
{
	return snprintf(buff, size, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|", ProtocolType.c_str(), SequenceNo.c_str(), IsLast.c_str(), Reserve1.c_str(), ErrorCode.c_str(), ErrorMessage.c_str(), ChannelID.c_str(), PrimaryAccountID.c_str(), Password.c_str(), Port.c_str());
}
string ItsRspQryPrimaryAccountInfo::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_ItsRspQryPrimaryAccountInfo(ProtocolType char(32), SequenceNo char(32), IsLast char(32), Reserve1 char(32), ErrorCode char(32), ErrorMessage char(32), ChannelID char(32), PrimaryAccountID char(32), Password char(32), Port char(32), PRIMARY KEY(SequenceNo));";
}
string ItsRspQryPrimaryAccountInfo::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	snprintf(m_Buff, 4096, "REPLACE INTO t_ItsRspQryPrimaryAccountInfo VALUES(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\");", ProtocolType.c_str(), SequenceNo.c_str(), IsLast.c_str(), Reserve1.c_str(), ErrorCode.c_str(), ErrorMessage.c_str(), ChannelID.c_str(), PrimaryAccountID.c_str(), Password.c_str(), Port.c_str());
	return string(m_Buff);
}
int ItsRspQryPrimaryAccountInfo::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new ItsRspQryPrimaryAccountInfo();
	field->ProtocolType = colValues[0];
	field->SequenceNo = colValues[1];
	field->IsLast = colValues[2];
	field->Reserve1 = colValues[3];
	field->ErrorCode = colValues[4];
	field->ErrorMessage = colValues[5];
	field->ChannelID = colValues[6];
	field->PrimaryAccountID = colValues[7];
	field->Password = colValues[8];
	field->Port = colValues[9];

	((ItsMdbCallback*)callback)->SelectItsRspQryPrimaryAccountInfoCallback(field);
	return 0;
}

ItsInsertOrder::ItsInsertOrder()
	:ProtocolType("R")
{
	memset(m_Buff, 0, sizeof(m_Buff));
}
ItsInsertOrder::ItsInsertOrder(const vector<string>& items)
{
	memset(m_Buff, 0, sizeof(m_Buff));
	ProtocolType = items[0];
	Command = items[1];
	SequenceNo = items[2];
	Reserve1 = items[3];
	Reserve2 = items[4];
	Reserve3 = items[5];
	Reserve4 = items[6];
	Reserve5 = items[7];
	Reserve6 = items[8];
	ExchangeID = items[9];
	InstrumentID = items[10];
	Price = items[11];
	Direction = items[12];
	Reserve7 = items[13];
	CombHedgeFlag = items[14];
	Volume = items[15];
	OrderPriceType = items[16];
	RequestID = items[17];
	Reserve8 = items[18];
	TimeCondition = items[19];
	GTDDate = items[20];
	VolumeCondition = items[21];
	MinVolume = items[22];
	IsSwapOrder = items[23];
	ForceCloseReason = items[24];
	AccountID = items[25];
	TradingDay = items[26];
}
int ItsInsertOrder::ToString(char* buff, int size)
{
	return snprintf(buff, size, "ItsInsertOrder: ProtocolType[%s] Command[%s] SequenceNo[%s] Reserve1[%s] Reserve2[%s] Reserve3[%s] Reserve4[%s] Reserve5[%s] Reserve6[%s] ExchangeID[%s] InstrumentID[%s] Price[%s] Direction[%s] Reserve7[%s] CombHedgeFlag[%s] Volume[%s] OrderPriceType[%s] RequestID[%s] Reserve8[%s] TimeCondition[%s] GTDDate[%s] VolumeCondition[%s] MinVolume[%s] IsSwapOrder[%s] ForceCloseReason[%s] AccountID[%s] TradingDay[%s] ", ProtocolType.c_str(), Command.c_str(), SequenceNo.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), Reserve5.c_str(), Reserve6.c_str(), ExchangeID.c_str(), InstrumentID.c_str(), Price.c_str(), Direction.c_str(), Reserve7.c_str(), CombHedgeFlag.c_str(), Volume.c_str(), OrderPriceType.c_str(), RequestID.c_str(), Reserve8.c_str(), TimeCondition.c_str(), GTDDate.c_str(), VolumeCondition.c_str(), MinVolume.c_str(), IsSwapOrder.c_str(), ForceCloseReason.c_str(), AccountID.c_str(), TradingDay.c_str());
}
int ItsInsertOrder::ToStream(char* buff, int size)
{
	return snprintf(buff, size, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|", ProtocolType.c_str(), Command.c_str(), SequenceNo.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), Reserve5.c_str(), Reserve6.c_str(), ExchangeID.c_str(), InstrumentID.c_str(), Price.c_str(), Direction.c_str(), Reserve7.c_str(), CombHedgeFlag.c_str(), Volume.c_str(), OrderPriceType.c_str(), RequestID.c_str(), Reserve8.c_str(), TimeCondition.c_str(), GTDDate.c_str(), VolumeCondition.c_str(), MinVolume.c_str(), IsSwapOrder.c_str(), ForceCloseReason.c_str(), AccountID.c_str(), TradingDay.c_str());
}
string ItsInsertOrder::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_ItsInsertOrder(ProtocolType char(32), Command char(32), SequenceNo char(32), Reserve1 char(32), Reserve2 char(32), Reserve3 char(32), Reserve4 char(32), Reserve5 char(32), Reserve6 char(32), ExchangeID char(32), InstrumentID char(32), Price char(32), Direction char(32), Reserve7 char(32), CombHedgeFlag char(32), Volume char(32), OrderPriceType char(32), RequestID char(32), Reserve8 char(32), TimeCondition char(32), GTDDate char(32), VolumeCondition char(32), MinVolume char(32), IsSwapOrder char(32), ForceCloseReason char(32), AccountID char(32), TradingDay char(32), PRIMARY KEY(TradingDay, RequestID));";
}
string ItsInsertOrder::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	snprintf(m_Buff, 4096, "REPLACE INTO t_ItsInsertOrder VALUES(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\");", ProtocolType.c_str(), Command.c_str(), SequenceNo.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), Reserve5.c_str(), Reserve6.c_str(), ExchangeID.c_str(), InstrumentID.c_str(), Price.c_str(), Direction.c_str(), Reserve7.c_str(), CombHedgeFlag.c_str(), Volume.c_str(), OrderPriceType.c_str(), RequestID.c_str(), Reserve8.c_str(), TimeCondition.c_str(), GTDDate.c_str(), VolumeCondition.c_str(), MinVolume.c_str(), IsSwapOrder.c_str(), ForceCloseReason.c_str(), AccountID.c_str(), TradingDay.c_str());
	return string(m_Buff);
}
int ItsInsertOrder::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new ItsInsertOrder();
	field->ProtocolType = colValues[0];
	field->Command = colValues[1];
	field->SequenceNo = colValues[2];
	field->Reserve1 = colValues[3];
	field->Reserve2 = colValues[4];
	field->Reserve3 = colValues[5];
	field->Reserve4 = colValues[6];
	field->Reserve5 = colValues[7];
	field->Reserve6 = colValues[8];
	field->ExchangeID = colValues[9];
	field->InstrumentID = colValues[10];
	field->Price = colValues[11];
	field->Direction = colValues[12];
	field->Reserve7 = colValues[13];
	field->CombHedgeFlag = colValues[14];
	field->Volume = colValues[15];
	field->OrderPriceType = colValues[16];
	field->RequestID = colValues[17];
	field->Reserve8 = colValues[18];
	field->TimeCondition = colValues[19];
	field->GTDDate = colValues[20];
	field->VolumeCondition = colValues[21];
	field->MinVolume = colValues[22];
	field->IsSwapOrder = colValues[23];
	field->ForceCloseReason = colValues[24];
	field->AccountID = colValues[25];
	field->TradingDay = colValues[26];

	((ItsMdbCallback*)callback)->SelectItsInsertOrderCallback(field);
	return 0;
}

ItsInsertOrderCancel::ItsInsertOrderCancel()
	:ProtocolType("R")
{
	memset(m_Buff, 0, sizeof(m_Buff));
}
ItsInsertOrderCancel::ItsInsertOrderCancel(const vector<string>& items)
{
	memset(m_Buff, 0, sizeof(m_Buff));
	ProtocolType = items[0];
	Command = items[1];
	SequenceNo = items[2];
	Reserve1 = items[3];
	Reserve2 = items[4];
	Reserve3 = items[5];
	Reserve4 = items[6];
	Reserve5 = items[7];
	Reserve6 = items[8];
	OrderRef = items[9];
	FrontID = items[10];
	SessionID = items[11];
	ExchangeID = items[12];
	OrderSysID = items[13];
	ChannelOrderID = items[14];
	BrokerOrderID = items[15];
	InstrumentID = items[16];
	Direction = items[17];
	TradingDay = items[18];
}
int ItsInsertOrderCancel::ToString(char* buff, int size)
{
	return snprintf(buff, size, "ItsInsertOrderCancel: ProtocolType[%s] Command[%s] SequenceNo[%s] Reserve1[%s] Reserve2[%s] Reserve3[%s] Reserve4[%s] Reserve5[%s] Reserve6[%s] OrderRef[%s] FrontID[%s] SessionID[%s] ExchangeID[%s] OrderSysID[%s] ChannelOrderID[%s] BrokerOrderID[%s] InstrumentID[%s] Direction[%s] TradingDay[%s] ", ProtocolType.c_str(), Command.c_str(), SequenceNo.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), Reserve5.c_str(), Reserve6.c_str(), OrderRef.c_str(), FrontID.c_str(), SessionID.c_str(), ExchangeID.c_str(), OrderSysID.c_str(), ChannelOrderID.c_str(), BrokerOrderID.c_str(), InstrumentID.c_str(), Direction.c_str(), TradingDay.c_str());
}
int ItsInsertOrderCancel::ToStream(char* buff, int size)
{
	return snprintf(buff, size, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|", ProtocolType.c_str(), Command.c_str(), SequenceNo.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), Reserve5.c_str(), Reserve6.c_str(), OrderRef.c_str(), FrontID.c_str(), SessionID.c_str(), ExchangeID.c_str(), OrderSysID.c_str(), ChannelOrderID.c_str(), BrokerOrderID.c_str(), InstrumentID.c_str(), Direction.c_str(), TradingDay.c_str());
}
string ItsInsertOrderCancel::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_ItsInsertOrderCancel(ProtocolType char(32), Command char(32), SequenceNo char(32), Reserve1 char(32), Reserve2 char(32), Reserve3 char(32), Reserve4 char(32), Reserve5 char(32), Reserve6 char(32), OrderRef char(32), FrontID char(32), SessionID char(32), ExchangeID char(32), OrderSysID char(32), ChannelOrderID char(32), BrokerOrderID char(32), InstrumentID char(32), Direction char(32), TradingDay char(32), PRIMARY KEY(TradingDay, SequenceNo));";
}
string ItsInsertOrderCancel::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	snprintf(m_Buff, 4096, "REPLACE INTO t_ItsInsertOrderCancel VALUES(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\");", ProtocolType.c_str(), Command.c_str(), SequenceNo.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), Reserve5.c_str(), Reserve6.c_str(), OrderRef.c_str(), FrontID.c_str(), SessionID.c_str(), ExchangeID.c_str(), OrderSysID.c_str(), ChannelOrderID.c_str(), BrokerOrderID.c_str(), InstrumentID.c_str(), Direction.c_str(), TradingDay.c_str());
	return string(m_Buff);
}
int ItsInsertOrderCancel::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new ItsInsertOrderCancel();
	field->ProtocolType = colValues[0];
	field->Command = colValues[1];
	field->SequenceNo = colValues[2];
	field->Reserve1 = colValues[3];
	field->Reserve2 = colValues[4];
	field->Reserve3 = colValues[5];
	field->Reserve4 = colValues[6];
	field->Reserve5 = colValues[7];
	field->Reserve6 = colValues[8];
	field->OrderRef = colValues[9];
	field->FrontID = colValues[10];
	field->SessionID = colValues[11];
	field->ExchangeID = colValues[12];
	field->OrderSysID = colValues[13];
	field->ChannelOrderID = colValues[14];
	field->BrokerOrderID = colValues[15];
	field->InstrumentID = colValues[16];
	field->Direction = colValues[17];
	field->TradingDay = colValues[18];

	((ItsMdbCallback*)callback)->SelectItsInsertOrderCancelCallback(field);
	return 0;
}

ItsRspOrder::ItsRspOrder()
	:ProtocolType("A")
{
	memset(m_Buff, 0, sizeof(m_Buff));
}
ItsRspOrder::ItsRspOrder(const vector<string>& items)
{
	memset(m_Buff, 0, sizeof(m_Buff));
	ProtocolType = items[0];
	SequenceNo = items[1];
	Reserve1 = items[2];
	Reserve2 = items[3];
	ErrorID = items[4];
	ErrorMsg = items[5];
	TradingDay = items[6];
}
int ItsRspOrder::ToString(char* buff, int size)
{
	return snprintf(buff, size, "ItsRspOrder: ProtocolType[%s] SequenceNo[%s] Reserve1[%s] Reserve2[%s] ErrorID[%s] ErrorMsg[%s] TradingDay[%s] ", ProtocolType.c_str(), SequenceNo.c_str(), Reserve1.c_str(), Reserve2.c_str(), ErrorID.c_str(), ErrorMsg.c_str(), TradingDay.c_str());
}
int ItsRspOrder::ToStream(char* buff, int size)
{
	return snprintf(buff, size, "%s|%s|%s|%s|%s|%s|%s|", ProtocolType.c_str(), SequenceNo.c_str(), Reserve1.c_str(), Reserve2.c_str(), ErrorID.c_str(), ErrorMsg.c_str(), TradingDay.c_str());
}
string ItsRspOrder::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_ItsRspOrder(ProtocolType char(32), SequenceNo char(32), Reserve1 char(32), Reserve2 char(32), ErrorID char(32), ErrorMsg char(255), TradingDay char(32), PRIMARY KEY(TradingDay, SequenceNo));";
}
string ItsRspOrder::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	snprintf(m_Buff, 4096, "REPLACE INTO t_ItsRspOrder VALUES(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\");", ProtocolType.c_str(), SequenceNo.c_str(), Reserve1.c_str(), Reserve2.c_str(), ErrorID.c_str(), ErrorMsg.c_str(), TradingDay.c_str());
	return string(m_Buff);
}
int ItsRspOrder::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new ItsRspOrder();
	field->ProtocolType = colValues[0];
	field->SequenceNo = colValues[1];
	field->Reserve1 = colValues[2];
	field->Reserve2 = colValues[3];
	field->ErrorID = colValues[4];
	field->ErrorMsg = colValues[5];
	field->TradingDay = colValues[6];

	((ItsMdbCallback*)callback)->SelectItsRspOrderCallback(field);
	return 0;
}

ItsOrder::ItsOrder()
	:ProtocolType("B")
{
	memset(m_Buff, 0, sizeof(m_Buff));
}
ItsOrder::ItsOrder(const vector<string>& items)
{
	memset(m_Buff, 0, sizeof(m_Buff));
	ProtocolType = items[0];
	Command = items[1];
	Reserve1 = items[2];
	Reserve2 = items[3];
	Reserve3 = items[4];
	Reserve4 = items[5];
	ChannelID = items[6];
	ExchangeID = items[7];
	InstrumentID = items[8];
	OrderRef = items[9];
	InsertTime = items[10];
	CancelTime = items[11];
	OrderSysID = items[12];
	StatusMsg = items[13];
	Direction = items[14];
	CombOffsetFlag = items[15];
	CombHedgeFlag = items[16];
	OrderPriceType = items[17];
	OrderStatus = items[18];
	ForceCloseReason = items[19];
	RequestID = items[20];
	FrontID = items[21];
	SessionID = items[22];
	BrokerOrderID = items[23];
	VolumeTotalOriginal = items[24];
	VolumeTraded = items[25];
	InsertDate = items[26];
	TradingDay = items[27];
	LimitPrice = items[28];
	IsLocalOrder = items[29];
	UserProductInfo = items[30];
	TimeCondition = items[31];
	GTDDate = items[32];
	VolumeCondition = items[33];
	MinVolume = items[34];
	ContingentCondition = items[35];
	StopPrice = items[36];
	IsSwapOrder = items[37];
	Reserve5 = items[38];
}
int ItsOrder::ToString(char* buff, int size)
{
	return snprintf(buff, size, "ItsOrder: ProtocolType[%s] Command[%s] Reserve1[%s] Reserve2[%s] Reserve3[%s] Reserve4[%s] ChannelID[%s] ExchangeID[%s] InstrumentID[%s] OrderRef[%s] InsertTime[%s] CancelTime[%s] OrderSysID[%s] StatusMsg[%s] Direction[%s] CombOffsetFlag[%s] CombHedgeFlag[%s] OrderPriceType[%s] OrderStatus[%s] ForceCloseReason[%s] RequestID[%s] FrontID[%s] SessionID[%s] BrokerOrderID[%s] VolumeTotalOriginal[%s] VolumeTraded[%s] InsertDate[%s] TradingDay[%s] LimitPrice[%s] IsLocalOrder[%s] UserProductInfo[%s] TimeCondition[%s] GTDDate[%s] VolumeCondition[%s] MinVolume[%s] ContingentCondition[%s] StopPrice[%s] IsSwapOrder[%s] Reserve5[%s] ", ProtocolType.c_str(), Command.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), ChannelID.c_str(), ExchangeID.c_str(), InstrumentID.c_str(), OrderRef.c_str(), InsertTime.c_str(), CancelTime.c_str(), OrderSysID.c_str(), StatusMsg.c_str(), Direction.c_str(), CombOffsetFlag.c_str(), CombHedgeFlag.c_str(), OrderPriceType.c_str(), OrderStatus.c_str(), ForceCloseReason.c_str(), RequestID.c_str(), FrontID.c_str(), SessionID.c_str(), BrokerOrderID.c_str(), VolumeTotalOriginal.c_str(), VolumeTraded.c_str(), InsertDate.c_str(), TradingDay.c_str(), LimitPrice.c_str(), IsLocalOrder.c_str(), UserProductInfo.c_str(), TimeCondition.c_str(), GTDDate.c_str(), VolumeCondition.c_str(), MinVolume.c_str(), ContingentCondition.c_str(), StopPrice.c_str(), IsSwapOrder.c_str(), Reserve5.c_str());
}
int ItsOrder::ToStream(char* buff, int size)
{
	return snprintf(buff, size, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|", ProtocolType.c_str(), Command.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), ChannelID.c_str(), ExchangeID.c_str(), InstrumentID.c_str(), OrderRef.c_str(), InsertTime.c_str(), CancelTime.c_str(), OrderSysID.c_str(), StatusMsg.c_str(), Direction.c_str(), CombOffsetFlag.c_str(), CombHedgeFlag.c_str(), OrderPriceType.c_str(), OrderStatus.c_str(), ForceCloseReason.c_str(), RequestID.c_str(), FrontID.c_str(), SessionID.c_str(), BrokerOrderID.c_str(), VolumeTotalOriginal.c_str(), VolumeTraded.c_str(), InsertDate.c_str(), TradingDay.c_str(), LimitPrice.c_str(), IsLocalOrder.c_str(), UserProductInfo.c_str(), TimeCondition.c_str(), GTDDate.c_str(), VolumeCondition.c_str(), MinVolume.c_str(), ContingentCondition.c_str(), StopPrice.c_str(), IsSwapOrder.c_str(), Reserve5.c_str());
}
string ItsOrder::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_ItsOrder(ProtocolType char(32), Command char(32), Reserve1 char(32), Reserve2 char(32), Reserve3 char(32), Reserve4 char(32), ChannelID char(32), ExchangeID char(32), InstrumentID char(32), OrderRef char(32), InsertTime char(32), CancelTime char(32), OrderSysID char(32), StatusMsg char(32), Direction char(32), CombOffsetFlag char(32), CombHedgeFlag char(32), OrderPriceType char(32), OrderStatus char(32), ForceCloseReason char(32), RequestID char(32), FrontID char(32), SessionID char(32), BrokerOrderID char(32), VolumeTotalOriginal char(32), VolumeTraded char(32), InsertDate char(32), TradingDay char(32), LimitPrice char(32), IsLocalOrder char(32), UserProductInfo char(32), TimeCondition char(32), GTDDate char(32), VolumeCondition char(32), MinVolume char(32), ContingentCondition char(32), StopPrice char(32), IsSwapOrder char(32), Reserve5 char(32), PRIMARY KEY(TradingDay, ExchangeID, InstrumentID, Direction, BrokerOrderID));";
}
string ItsOrder::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	snprintf(m_Buff, 4096, "REPLACE INTO t_ItsOrder VALUES(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\");", ProtocolType.c_str(), Command.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), ChannelID.c_str(), ExchangeID.c_str(), InstrumentID.c_str(), OrderRef.c_str(), InsertTime.c_str(), CancelTime.c_str(), OrderSysID.c_str(), StatusMsg.c_str(), Direction.c_str(), CombOffsetFlag.c_str(), CombHedgeFlag.c_str(), OrderPriceType.c_str(), OrderStatus.c_str(), ForceCloseReason.c_str(), RequestID.c_str(), FrontID.c_str(), SessionID.c_str(), BrokerOrderID.c_str(), VolumeTotalOriginal.c_str(), VolumeTraded.c_str(), InsertDate.c_str(), TradingDay.c_str(), LimitPrice.c_str(), IsLocalOrder.c_str(), UserProductInfo.c_str(), TimeCondition.c_str(), GTDDate.c_str(), VolumeCondition.c_str(), MinVolume.c_str(), ContingentCondition.c_str(), StopPrice.c_str(), IsSwapOrder.c_str(), Reserve5.c_str());
	return string(m_Buff);
}
int ItsOrder::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new ItsOrder();
	field->ProtocolType = colValues[0];
	field->Command = colValues[1];
	field->Reserve1 = colValues[2];
	field->Reserve2 = colValues[3];
	field->Reserve3 = colValues[4];
	field->Reserve4 = colValues[5];
	field->ChannelID = colValues[6];
	field->ExchangeID = colValues[7];
	field->InstrumentID = colValues[8];
	field->OrderRef = colValues[9];
	field->InsertTime = colValues[10];
	field->CancelTime = colValues[11];
	field->OrderSysID = colValues[12];
	field->StatusMsg = colValues[13];
	field->Direction = colValues[14];
	field->CombOffsetFlag = colValues[15];
	field->CombHedgeFlag = colValues[16];
	field->OrderPriceType = colValues[17];
	field->OrderStatus = colValues[18];
	field->ForceCloseReason = colValues[19];
	field->RequestID = colValues[20];
	field->FrontID = colValues[21];
	field->SessionID = colValues[22];
	field->BrokerOrderID = colValues[23];
	field->VolumeTotalOriginal = colValues[24];
	field->VolumeTraded = colValues[25];
	field->InsertDate = colValues[26];
	field->TradingDay = colValues[27];
	field->LimitPrice = colValues[28];
	field->IsLocalOrder = colValues[29];
	field->UserProductInfo = colValues[30];
	field->TimeCondition = colValues[31];
	field->GTDDate = colValues[32];
	field->VolumeCondition = colValues[33];
	field->MinVolume = colValues[34];
	field->ContingentCondition = colValues[35];
	field->StopPrice = colValues[36];
	field->IsSwapOrder = colValues[37];
	field->Reserve5 = colValues[38];

	((ItsMdbCallback*)callback)->SelectItsOrderCallback(field);
	return 0;
}

ItsTrade::ItsTrade()
	:ProtocolType("B")
{
	memset(m_Buff, 0, sizeof(m_Buff));
}
ItsTrade::ItsTrade(const vector<string>& items)
{
	memset(m_Buff, 0, sizeof(m_Buff));
	ProtocolType = items[0];
	Command = items[1];
	Reserve1 = items[2];
	Reserve2 = items[3];
	Reserve3 = items[4];
	Reserve4 = items[5];
	ChannelID = items[6];
	ExchangeID = items[7];
	InstrumentID = items[8];
	OrderRef = items[9];
	OrderSysID = items[10];
	TradeTime = items[11];
	TradeID = items[12];
	Direction = items[13];
	OffsetFlag = items[14];
	HedgeFlag = items[15];
	BrokerOrderID = items[16];
	Volume = items[17];
	TradeDate = items[18];
	TradingDay = items[19];
	Price = items[20];
	Reserve5 = items[21];
	TradeType = items[22];
	ExchangeTradeID = items[23];
	Reserve7 = items[24];
	Reserve8 = items[25];
}
int ItsTrade::ToString(char* buff, int size)
{
	return snprintf(buff, size, "ItsTrade: ProtocolType[%s] Command[%s] Reserve1[%s] Reserve2[%s] Reserve3[%s] Reserve4[%s] ChannelID[%s] ExchangeID[%s] InstrumentID[%s] OrderRef[%s] OrderSysID[%s] TradeTime[%s] TradeID[%s] Direction[%s] OffsetFlag[%s] HedgeFlag[%s] BrokerOrderID[%s] Volume[%s] TradeDate[%s] TradingDay[%s] Price[%s] Reserve5[%s] TradeType[%s] ExchangeTradeID[%s] Reserve7[%s] Reserve8[%s] ", ProtocolType.c_str(), Command.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), ChannelID.c_str(), ExchangeID.c_str(), InstrumentID.c_str(), OrderRef.c_str(), OrderSysID.c_str(), TradeTime.c_str(), TradeID.c_str(), Direction.c_str(), OffsetFlag.c_str(), HedgeFlag.c_str(), BrokerOrderID.c_str(), Volume.c_str(), TradeDate.c_str(), TradingDay.c_str(), Price.c_str(), Reserve5.c_str(), TradeType.c_str(), ExchangeTradeID.c_str(), Reserve7.c_str(), Reserve8.c_str());
}
int ItsTrade::ToStream(char* buff, int size)
{
	return snprintf(buff, size, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|", ProtocolType.c_str(), Command.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), ChannelID.c_str(), ExchangeID.c_str(), InstrumentID.c_str(), OrderRef.c_str(), OrderSysID.c_str(), TradeTime.c_str(), TradeID.c_str(), Direction.c_str(), OffsetFlag.c_str(), HedgeFlag.c_str(), BrokerOrderID.c_str(), Volume.c_str(), TradeDate.c_str(), TradingDay.c_str(), Price.c_str(), Reserve5.c_str(), TradeType.c_str(), ExchangeTradeID.c_str(), Reserve7.c_str(), Reserve8.c_str());
}
string ItsTrade::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_ItsTrade(ProtocolType char(32), Command char(32), Reserve1 char(32), Reserve2 char(32), Reserve3 char(32), Reserve4 char(32), ChannelID char(32), ExchangeID char(32), InstrumentID char(32), OrderRef char(32), OrderSysID char(32), TradeTime char(32), TradeID char(32), Direction char(32), OffsetFlag char(32), HedgeFlag char(32), BrokerOrderID char(32), Volume char(32), TradeDate char(32), TradingDay char(32), Price char(32), Reserve5 char(32), TradeType char(32), ExchangeTradeID char(32), Reserve7 char(32), Reserve8 char(32), PRIMARY KEY(TradingDay, ExchangeID, InstrumentID, Direction, TradeID));";
}
string ItsTrade::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	snprintf(m_Buff, 4096, "REPLACE INTO t_ItsTrade VALUES(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\");", ProtocolType.c_str(), Command.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), ChannelID.c_str(), ExchangeID.c_str(), InstrumentID.c_str(), OrderRef.c_str(), OrderSysID.c_str(), TradeTime.c_str(), TradeID.c_str(), Direction.c_str(), OffsetFlag.c_str(), HedgeFlag.c_str(), BrokerOrderID.c_str(), Volume.c_str(), TradeDate.c_str(), TradingDay.c_str(), Price.c_str(), Reserve5.c_str(), TradeType.c_str(), ExchangeTradeID.c_str(), Reserve7.c_str(), Reserve8.c_str());
	return string(m_Buff);
}
int ItsTrade::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new ItsTrade();
	field->ProtocolType = colValues[0];
	field->Command = colValues[1];
	field->Reserve1 = colValues[2];
	field->Reserve2 = colValues[3];
	field->Reserve3 = colValues[4];
	field->Reserve4 = colValues[5];
	field->ChannelID = colValues[6];
	field->ExchangeID = colValues[7];
	field->InstrumentID = colValues[8];
	field->OrderRef = colValues[9];
	field->OrderSysID = colValues[10];
	field->TradeTime = colValues[11];
	field->TradeID = colValues[12];
	field->Direction = colValues[13];
	field->OffsetFlag = colValues[14];
	field->HedgeFlag = colValues[15];
	field->BrokerOrderID = colValues[16];
	field->Volume = colValues[17];
	field->TradeDate = colValues[18];
	field->TradingDay = colValues[19];
	field->Price = colValues[20];
	field->Reserve5 = colValues[21];
	field->TradeType = colValues[22];
	field->ExchangeTradeID = colValues[23];
	field->Reserve7 = colValues[24];
	field->Reserve8 = colValues[25];

	((ItsMdbCallback*)callback)->SelectItsTradeCallback(field);
	return 0;
}

ItsErrRtnOrderCancel::ItsErrRtnOrderCancel()
	:ProtocolType("B")
{
	memset(m_Buff, 0, sizeof(m_Buff));
}
ItsErrRtnOrderCancel::ItsErrRtnOrderCancel(const vector<string>& items)
{
	memset(m_Buff, 0, sizeof(m_Buff));
	ProtocolType = items[0];
	Command = items[1];
	Reserve1 = items[2];
	Reserve2 = items[3];
	Reserve3 = items[4];
	Reserve4 = items[5];
	ChannelID = items[6];
	BrokerOrderID = items[7];
	OrderRef = items[8];
	FrontID = items[9];
	SessionID = items[10];
	ExchangeID = items[11];
	OrderSysID = items[12];
	Reserve5 = items[13];
	ErrorID = items[14];
	ErrorMsg = items[15];
	TradingDay = items[16];
}
int ItsErrRtnOrderCancel::ToString(char* buff, int size)
{
	return snprintf(buff, size, "ItsErrRtnOrderCancel: ProtocolType[%s] Command[%s] Reserve1[%s] Reserve2[%s] Reserve3[%s] Reserve4[%s] ChannelID[%s] BrokerOrderID[%s] OrderRef[%s] FrontID[%s] SessionID[%s] ExchangeID[%s] OrderSysID[%s] Reserve5[%s] ErrorID[%s] ErrorMsg[%s] TradingDay[%s] ", ProtocolType.c_str(), Command.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), ChannelID.c_str(), BrokerOrderID.c_str(), OrderRef.c_str(), FrontID.c_str(), SessionID.c_str(), ExchangeID.c_str(), OrderSysID.c_str(), Reserve5.c_str(), ErrorID.c_str(), ErrorMsg.c_str(), TradingDay.c_str());
}
int ItsErrRtnOrderCancel::ToStream(char* buff, int size)
{
	return snprintf(buff, size, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|", ProtocolType.c_str(), Command.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), ChannelID.c_str(), BrokerOrderID.c_str(), OrderRef.c_str(), FrontID.c_str(), SessionID.c_str(), ExchangeID.c_str(), OrderSysID.c_str(), Reserve5.c_str(), ErrorID.c_str(), ErrorMsg.c_str(), TradingDay.c_str());
}
string ItsErrRtnOrderCancel::CreateSql()
{
	return "CREATE TABLE IF NOT EXISTS t_ItsErrRtnOrderCancel(ProtocolType char(32), Command char(32), Reserve1 char(32), Reserve2 char(32), Reserve3 char(32), Reserve4 char(32), ChannelID char(32), BrokerOrderID char(32), OrderRef char(32), FrontID char(32), SessionID char(32), ExchangeID char(32), OrderSysID char(32), Reserve5 char(32), ErrorID char(32), ErrorMsg char(255), TradingDay char(32), PRIMARY KEY(TradingDay, ExchangeID, BrokerOrderID, OrderSysID, OrderRef));";
}
string ItsErrRtnOrderCancel::InsertSql()
{
	::memset(m_Buff, 0, sizeof(m_Buff));
	snprintf(m_Buff, 4096, "REPLACE INTO t_ItsErrRtnOrderCancel VALUES(\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\");", ProtocolType.c_str(), Command.c_str(), Reserve1.c_str(), Reserve2.c_str(), Reserve3.c_str(), Reserve4.c_str(), ChannelID.c_str(), BrokerOrderID.c_str(), OrderRef.c_str(), FrontID.c_str(), SessionID.c_str(), ExchangeID.c_str(), OrderSysID.c_str(), Reserve5.c_str(), ErrorID.c_str(), ErrorMsg.c_str(), TradingDay.c_str());
	return string(m_Buff);
}
int ItsErrRtnOrderCancel::OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames)
{
	auto field = new ItsErrRtnOrderCancel();
	field->ProtocolType = colValues[0];
	field->Command = colValues[1];
	field->Reserve1 = colValues[2];
	field->Reserve2 = colValues[3];
	field->Reserve3 = colValues[4];
	field->Reserve4 = colValues[5];
	field->ChannelID = colValues[6];
	field->BrokerOrderID = colValues[7];
	field->OrderRef = colValues[8];
	field->FrontID = colValues[9];
	field->SessionID = colValues[10];
	field->ExchangeID = colValues[11];
	field->OrderSysID = colValues[12];
	field->Reserve5 = colValues[13];
	field->ErrorID = colValues[14];
	field->ErrorMsg = colValues[15];
	field->TradingDay = colValues[16];

	((ItsMdbCallback*)callback)->SelectItsErrRtnOrderCancelCallback(field);
	return 0;
}

