#include "FixAuditTrail.h"
#include "FixItems.h"


FixAuditTrail::FixAuditTrail()
{
	Buff = new char[10240];
	SendIndex = 0;
	RecvIndex = 0;
}
FixAuditTrail::~FixAuditTrail()
{
	if (Buff)
		delete Buff;
	Buff = nullptr;
}
void FixAuditTrail::SetMessage(FixMessage* fixMessage, string messageDirection)
{
	SelfMatchPreventionID = fixMessage->GetItem(FIX_SelfMatchPreventionID);
	Account = fixMessage->GetItem(FIX_Account);
	ManualOrderIndicator = fixMessage->GetItem(FIX_ManualOrderIndicator);
	MsgType = fixMessage->GetItem(FIX_MsgType);
	CtiCode = fixMessage->GetItem(FIX_CtiCode);
	CustomerOrFirm = fixMessage->GetItem(FIX_CustomerOrFirm);
	ExecID = fixMessage->GetItem(FIX_ExecID);
	CorrelationClOrdID = fixMessage->GetItem(FIX_CorrelationClOrdID);
	SecondaryExecID = fixMessage->GetItem(FIX_SecondaryExecID);
	SecurityDesc = fixMessage->GetItem(FIX_SecurityDesc);
	MarketSegmentID = fixMessage->GetItem(FIX_MarketSegmentID);
	ClOrdID = fixMessage->GetItem(FIX_ClOrdID);
	OrderID = fixMessage->GetItem(FIX_OrderID);
	Side = fixMessage->GetItem(FIX_Side);
	OrderQty = fixMessage->GetItem(FIX_OrderQty);
	Price = fixMessage->GetItem(FIX_Price);
	StopPx = fixMessage->GetItem(FIX_StopPx);
	OrdType = fixMessage->GetItem(FIX_OrdType);
	TimeInForce = fixMessage->GetItem(FIX_TimeInForce);
	OFMOverride = fixMessage->GetItem(FIX_OFMOverride);
	MaxShow = fixMessage->GetItem(FIX_MaxShow);
	MinQty = fixMessage->GetItem(FIX_MinQty);
	SenderLocationID = fixMessage->GetItem(FIX_SenderLocationID);
	LastPx = fixMessage->GetItem(FIX_LastPx);
	LastQty = fixMessage->GetItem(FIX_LastQty);
	CumQty = fixMessage->GetItem(FIX_CumQty);
	LeavesQty = fixMessage->GetItem(FIX_LeavesQty);
	AggressorIndicator = fixMessage->GetItem(FIX_AggressorIndicator);
	ExecRestatementReason = fixMessage->GetItem(FIX_ExecRestatementReason);
	NoProcessedEntries = fixMessage->GetItem(FIX_NoProcessedEntries);
	CrossID = fixMessage->GetItem(FIX_CrossID);
	QuoteReqID = fixMessage->GetItem(FIX_QuoteReqID);
	QuoteID = fixMessage->GetItem(FIX_QuoteID);
	QuoteEntryID = fixMessage->GetItem(FIX_QuoteEntryID);
	BidPx = fixMessage->GetItem(FIX_BidPx);
	BidSize = fixMessage->GetItem(FIX_BidSize);
	OfferPx = fixMessage->GetItem(FIX_OfferPx);
	OfferSize = fixMessage->GetItem(FIX_OfferSize);
	
	static char buff[256];
	MessageDirection = messageDirection;
	if (messageDirection == "TO CME")
	{
		SendingTimestamps = fixMessage->GetItem(FIX_SendingTime);
		ReceivingTimestamps = "";
		OperatorID = fixMessage->GetItem(FIX_SenderSubID);
		auto SenderCompID = fixMessage->GetItem(FIX_SenderCompID);
		SessionID = string(SenderCompID.begin(), SenderCompID.begin() + 3);
		ExecutingFirmID = fixMessage->GetItem(FIX_SenderSubID);
		MarketSegmentID = fixMessage->GetItem(FIX_TargetSubID);
		
		sprintf(buff, "Send_%08d", SendIndex++);
		MessageLinkID = string(buff);
	}
	else
	{
		SendingTimestamps = "";
		ReceivingTimestamps = fixMessage->GetItem(FIX_TransactTime);
		if (ReceivingTimestamps.empty())
		{
			ReceivingTimestamps = fixMessage->GetItem(FIX_SendingTime);
		}
		OperatorID = fixMessage->GetItem(FIX_TargetSubID);
		auto TargetCompID = fixMessage->GetItem(FIX_TargetCompID);
		SessionID = string(TargetCompID.begin(), TargetCompID.begin() + 3);
		ExecutingFirmID = fixMessage->GetItem(FIX_TargetSubID);
		MarketSegmentID = fixMessage->GetItem(FIX_SenderSubID);
		
		sprintf(buff, "Recv_%08d", RecvIndex++);
		MessageLinkID = string(buff);
	}
	if (MsgType == "8")
	{
		RejectReason = fixMessage->GetItem(FIX_OrdRejReason);
		MsgType = MsgType + "/" + fixMessage->GetItem(FIX_OrderStatus);
	}
	else if(MsgType == "9")
	{ 
		RejectReason = fixMessage->GetItem(FIX_CxlRejReason);
	}
	else
	{
		RejectReason = "";
	}
}
char* FixAuditTrail::ToString() const
{
	sprintf(Buff, "%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n", SendingTimestamps.c_str(), ReceivingTimestamps.c_str(), MessageDirection.c_str(), OperatorID.c_str(), SelfMatchPreventionID.c_str(), Account.c_str(), SessionID.c_str(), ExecutingFirmID.c_str(), ManualOrderIndicator.c_str(), MsgType.c_str(), CtiCode.c_str(), CustomerOrFirm.c_str(), ExecID.c_str(), MessageLinkID.c_str(), CorrelationClOrdID.c_str(), SecondaryExecID.c_str(), SecurityDesc.c_str(), MarketSegmentID.c_str(), ClOrdID.c_str(), OrderID.c_str(), Side.c_str(), OrderQty.c_str(), Price.c_str(), StopPx.c_str(), OrdType.c_str(), TimeInForce.c_str(), OFMOverride.c_str(), MaxShow.c_str(), MinQty.c_str(), SenderLocationID.c_str(), LastPx.c_str(), LastQty.c_str(), CumQty.c_str(), LeavesQty.c_str(), AggressorIndicator.c_str(), ExecRestatementReason.c_str(), RejectReason.c_str(), NoProcessedEntries.c_str(), CrossID.c_str(), QuoteReqID.c_str(), QuoteID.c_str(), QuoteEntryID.c_str(), BidPx.c_str(), BidSize.c_str(), OfferPx.c_str(), OfferSize.c_str());
	return Buff;
}

