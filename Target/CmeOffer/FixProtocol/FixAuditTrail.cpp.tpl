#include "FixAuditTrail.h"
#include "FixItems.h"

!!items = {}!!
!!entry items!!
!!travel!!
!!items[@name] = @key!!
!!leave!!
!!leave!!

!!entry AuditTrail!!
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
!!travel!!
!!if @name in items:!!
!!inc indent!!
	!!@name!! = fixMessage->GetItem(FIX_!!@name!!);
!!dec indent!!
!!leave!!
	
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
	sprintf(Buff, "!!travel!!!!if pumpid > 0:!!!!inc indent!!, !!dec indent!!%s!!leave!!\n"!!travel!!, !!@name!!.c_str()!!leave!!);
	return Buff;
}

!!leave!!