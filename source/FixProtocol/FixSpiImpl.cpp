#include "FixSpiImpl.h"
#include "Utility.h"
#include "TimeUtility.h"
#include "FixEnumTransfer.h"
#include "GlobalParam.h"
#include "Logger.h"



void FixSpiImpl::OnFixRspSessionLevelReject(FixRspSessionLevelRejectField* rspField)
{
	FixSpi::OnFixRspSessionLevelReject(rspField);
}
void FixSpiImpl::OnFixExecutionReport(FixExecutionReportField* rspField)
{
	FixSpi::OnFixExecutionReport(rspField);

	auto orderStatus = ConvertToFixOrderStatus(rspField->OrderStatus);
	auto execType = ConvertToFixExecType(rspField->ExecType);

	if (orderStatus == FixOrderStatus::PartiallyFilled || orderStatus == FixOrderStatus::Filled)
	{
		OnRtnOrder(rspField);
		OnRtnTrade(rspField);
	}
	else if (orderStatus == FixOrderStatus::New || orderStatus == FixOrderStatus::Cancelled || orderStatus == FixOrderStatus::Replaced || orderStatus == FixOrderStatus::Rejected || orderStatus == FixOrderStatus::Eliminated)
	{
		OnRtnOrder(rspField);
	}
	else if (execType == FixExecType::OrderStatus)
	{
		OnRtnOrder(rspField);
	}
	else
	{
		WRITE_LOG(LogLevel::Warning, "UnExepected Order Status. OrderStatus[%s], ExecType[%s]", rspField->OrderStatus.c_str(), rspField->ExecType.c_str());
	}
}
void FixSpiImpl::OnFixRspOrderCancelReject(FixRspOrderCancelRejectField* rspField)
{
	FixSpi::OnFixRspOrderCancelReject(rspField);
	OnErrRtnOrderCancel(rspField);
}


void FixSpiImpl::OnRtnOrder(FixExecutionReportField* rspField)
{
	auto requestTimeStamp = atoll(rspField->RequestTime.c_str()) / 1000000000LL;
	string requestDate = GetDateFromUnixTimeStamp(requestTimeStamp);
	string requestTime = GetTimeFromUnixTimeStamp(requestTimeStamp);

	Order* order = new Order();
	order->AccountID = "";
	order->ExchangeID = "";
	order->ContractID = "";
	order->MarketSegmentID = rspField->MarketSegmentID;
	order->InstrumentID = rspField->SecurityDesc;
	order->OrderLocalID = atoi(rspField->CorrelationClOrdID.c_str());
	order->OrderSysID = rspField->OrderID;
	order->Direction = FromFixDirection(FixDirection(rspField->Side[0]));
	order->OffsetFlag = OffsetFlag::Open;
	order->HedgeFlag = HedgeFlag::Speculation;
	order->OrderPriceType = FromFixPriceType(FixOrderType(rspField->OrdType[0]));
	order->Price = atof(rspField->Price.c_str());
	order->Volume = atoi(rspField->OrderQty.c_str());
	order->VolumeTraded = atoi(rspField->CumQty.c_str());
	order->OrderStatus = (OrderStatus)FromFixOrderStatus(FixOrderStatus(rspField->OrderStatus[0]));
	order->StatusMsg = rspField->SplitMsg;
	order->RequestID = "";
	order->FrontID = "";
	order->SessionID = 0;
	
	order->InsertTime = requestTime;
	if (order->OrderStatus == OrderStatus::Canceled)
	{
		order->CancelTime = GetTimeFromUtcTime(rspField->TransactTime);
	}
	order->InsertDate = requestDate;
	order->TradingDay = requestDate;
	order->ForceCloseReason = ForceCloseReason::NotForceClose;
	order->IsLocalOrder = IsLocalOrder::Others;
	order->UserProductInfo = "";
	order->TimeCondition = FromFixTimeInForce(FixTimeInForce(rspField->TimeInForce[0]));
	order->GTDDate = rspField->ExpireDate;
	if (rspField->MinQty.empty())
	{
		order->VolumeCondition = VolumeCondition::AV;
		order->MinVolume = 0;
	}
	else if (rspField->MinQty == rspField->OrderQty)
	{
		order->VolumeCondition = VolumeCondition::CV;
		order->MinVolume = 0;
	}
	else
	{
		order->VolumeCondition = VolumeCondition::MV;
		order->MinVolume = atoi(rspField->MinQty.c_str());
	}
	order->ContingentCondition = ContingentCondition::Immediately;
	order->StopPrice = rspField->StopPx;
	order->IsSwapOrder = "0";
	
	m_MdbPublisher->OnRtnOrder(order);
}
void FixSpiImpl::OnRtnTrade(FixExecutionReportField* rspField)
{
	Trade* trade = new Trade();
	trade->AccountID = rspField->Account;
	trade->ExchangeID = "";
	trade->ContractID = "";
	trade->MarketSegmentID = rspField->MarketSegmentID;
	trade->InstrumentID = rspField->SecurityDesc;
	trade->TradeID = rspField->MDTradeEntryID;
	trade->Direction = FromFixDirection(FixDirection(rspField->Side[0]));
	trade->OffsetFlag = OffsetFlag::Open;
	trade->HedgeFlag = HedgeFlag::Speculation;
	trade->Price = atof(rspField->LastPx.c_str());
	trade->Volume = atoi(rspField->LastQty.c_str());
	trade->OrderLocalID = atoi(rspField->CorrelationClOrdID.c_str());
	trade->OrderSysID = rspField->OrderID;
	trade->TradeTime = GetTimeFromUtcTime(rspField->TransactTime);
	trade->TradeDate = GetDateFromUtcTime(rspField->TransactTime);
	trade->TradingDay = GetDateFromUtcTime(rspField->TransactTime);

	m_MdbPublisher->OnRtnTrade(trade);
}
void FixSpiImpl::OnErrRtnOrderCancel(FixRspOrderCancelRejectField* rspField)
{
	OrderCancel* orderCancel = new OrderCancel();
	orderCancel->AccountID = rspField->Account;
	orderCancel->ExchangeID = "";
	orderCancel->ContractID = "";
	orderCancel->MarketSegmentID = "";
	orderCancel->InstrumentID = rspField->SecurityDesc;
	orderCancel->OrderLocalID = atoi(rspField->ClOrdID.c_str());
	orderCancel->OrigOrderLocalID = atoi(rspField->CorrelationClOrdID.c_str());
	orderCancel->OrderSysID = rspField->OrderID;
	orderCancel->Direction = Direction::Buy;
	orderCancel->OrderRef = "";
	orderCancel->FrontID = "";
	orderCancel->SessionID = 0;
	orderCancel->ErrorID = atoi(rspField->CxlRejReason.c_str());
	orderCancel->ErrorMsg = rspField->Text;
	
	m_MdbPublisher->OnErrRtnOrderCancel(orderCancel);
}
