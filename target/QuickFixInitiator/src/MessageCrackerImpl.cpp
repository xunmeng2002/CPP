#include "MessageCrackerImpl.h"
#include "Logger.h"
#include "GlobalParam.h"


void MessageCrackerImpl::onMessage(const Message& message, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Message:[%s]", sessionID.toString().c_str(), message.toString().c_str());
}
void MessageCrackerImpl::onMessage(Message& message, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Message:[%s]", sessionID.toString().c_str(), message.toString().c_str());
}

void MessageCrackerImpl::onMessage(const Heartbeat& heartbeat, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Heartbeat:[%s]", sessionID.toString().c_str(), heartbeat.toString().c_str());
}
void MessageCrackerImpl::onMessage(Heartbeat& heartbeat, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Heartbeat:[%s]", sessionID.toString().c_str(), heartbeat.toString().c_str());
}

void MessageCrackerImpl::onMessage(const TestRequest& testRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], TestRequest:[%s]", sessionID.toString().c_str(), testRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(TestRequest& testRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], TestRequest:[%s]", sessionID.toString().c_str(), testRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const ResendRequest& resendRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ResendRequest:[%s]", sessionID.toString().c_str(), resendRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(ResendRequest& resendRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ResendRequest:[%s]", sessionID.toString().c_str(), resendRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const Reject& reject, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Reject:[%s]", sessionID.toString().c_str(), reject.toString().c_str());
}
void MessageCrackerImpl::onMessage(Reject& reject, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Reject:[%s]", sessionID.toString().c_str(), reject.toString().c_str());
}

void MessageCrackerImpl::onMessage(const SequenceReset& sequenceReset, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], SequenceReset:[%s]", sessionID.toString().c_str(), sequenceReset.toString().c_str());
}
void MessageCrackerImpl::onMessage(SequenceReset& sequenceReset, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], SequenceReset:[%s]", sessionID.toString().c_str(), sequenceReset.toString().c_str());
}

void MessageCrackerImpl::onMessage(const Logout& logout, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Logout:[%s]", sessionID.toString().c_str(), logout.toString().c_str());
	if (logout.isSetField(789))
	{
		auto nextExpectedMsgSeqNum = logout.getField(789);
		GlobalParam::GetInstance().SetNextExpectedMsgSeqNum(atoi(nextExpectedMsgSeqNum.c_str()));
	}
}
void MessageCrackerImpl::onMessage(Logout& logout, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Logout:[%s]", sessionID.toString().c_str(), logout.toString().c_str());
	if (logout.isSetField(789))
	{
		auto nextExpectedMsgSeqNum = logout.getField(789);
		GlobalParam::GetInstance().SetNextExpectedMsgSeqNum(atoi(nextExpectedMsgSeqNum.c_str()));
	}
}

void MessageCrackerImpl::onMessage(const IOI& ioi, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], IOI:[%s]", sessionID.toString().c_str(), ioi.toString().c_str());
}
void MessageCrackerImpl::onMessage(IOI& ioi, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], IOI:[%s]", sessionID.toString().c_str(), ioi.toString().c_str());
}

void MessageCrackerImpl::onMessage(const Advertisement& advertisement, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Advertisement:[%s]", sessionID.toString().c_str(), advertisement.toString().c_str());
}
void MessageCrackerImpl::onMessage(Advertisement& advertisement, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Advertisement:[%s]", sessionID.toString().c_str(), advertisement.toString().c_str());
}

void MessageCrackerImpl::onMessage(const ExecutionReport& executionReport, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ExecutionReport:[%s]", sessionID.toString().c_str(), executionReport.toString().c_str());
}
void MessageCrackerImpl::onMessage(ExecutionReport& executionReport, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ExecutionReport:[%s]", sessionID.toString().c_str(), executionReport.toString().c_str());
}

void MessageCrackerImpl::onMessage(const OrderCancelReject& orderCancelReject, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], OrderCancelReject:[%s]", sessionID.toString().c_str(), orderCancelReject.toString().c_str());
}
void MessageCrackerImpl::onMessage(OrderCancelReject& orderCancelReject, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], OrderCancelReject:[%s]", sessionID.toString().c_str(), orderCancelReject.toString().c_str());
}

void MessageCrackerImpl::onMessage(const Logon& logon, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Logon:[%s]", sessionID.toString().c_str(), logon.toString().c_str());
	auto header = logon.getHeader();
	if (header.isSetField(56))
	{
		auto senderCompID = header.getField(56);
		GlobalParam::GetInstance().SetSenderCompID(senderCompID);
	}
}
void MessageCrackerImpl::onMessage(Logon& logon, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Logon:[%s]", sessionID.toString().c_str(), logon.toString().c_str());
	auto header = logon.getHeader();
	if (header.isSetField(56))
	{
		auto senderCompID = header.getField(56);
		GlobalParam::GetInstance().SetSenderCompID(senderCompID);
	}
}

void MessageCrackerImpl::onMessage(const News& news, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], News: [%s]", sessionID.toString().c_str(), news.toString().c_str());
}
void MessageCrackerImpl::onMessage(News& news, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], News: [%s]", sessionID.toString().c_str(), news.toString().c_str());
}

void MessageCrackerImpl::onMessage(const Email& email, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Email:[%s]", sessionID.toString().c_str(), email.toString().c_str());
}
void MessageCrackerImpl::onMessage(Email& email, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Email:[%s]", sessionID.toString().c_str(), email.toString().c_str());
}

void MessageCrackerImpl::onMessage(const NewOrderSingle& newOrderSingle, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], NewOrderSingle:[%s]", sessionID.toString().c_str(), newOrderSingle.toString().c_str());
}
void MessageCrackerImpl::onMessage(NewOrderSingle& newOrderSingle, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], NewOrderSingle:[%s]", sessionID.toString().c_str(), newOrderSingle.toString().c_str());
}

void MessageCrackerImpl::onMessage(const NewOrderList& newOrderList, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], NewOrderList:[%s]", sessionID.toString().c_str(), newOrderList.toString().c_str());
}
void MessageCrackerImpl::onMessage(NewOrderList& newOrderList, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], NewOrderList:[%s]", sessionID.toString().c_str(), newOrderList.toString().c_str());
}

void MessageCrackerImpl::onMessage(const OrderCancelRequest& orderCancelRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], OrderCancelRequest:[%s]", sessionID.toString().c_str(), orderCancelRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(OrderCancelRequest& orderCancelRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], OrderCancelRequest:[%s]", sessionID.toString().c_str(), orderCancelRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const OrderCancelReplaceRequest& orderCancelReplaceRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], OrderCancelReplaceRequest:[%s]", sessionID.toString().c_str(), orderCancelReplaceRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(OrderCancelReplaceRequest& orderCancelReplaceRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], OrderCancelReplaceRequest:[%s]", sessionID.toString().c_str(), orderCancelReplaceRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const OrderStatusRequest& orderStatusRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], OrderStatusRequest:[%s]", sessionID.toString().c_str(), orderStatusRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(OrderStatusRequest& orderStatusRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], OrderStatusRequest:[%s]", sessionID.toString().c_str(), orderStatusRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const Allocation& allocation, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Allocation:[%s]", sessionID.toString().c_str(), allocation.toString().c_str());
}
void MessageCrackerImpl::onMessage(Allocation& allocation, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Allocation:[%s]", sessionID.toString().c_str(), allocation.toString().c_str());
}

void MessageCrackerImpl::onMessage(const ListCancelRequest& listCancelRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ListCancelRequest:[%s]", sessionID.toString().c_str(), listCancelRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(ListCancelRequest& listCancelRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ListCancelRequest:[%s]", sessionID.toString().c_str(), listCancelRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const ListExecute& listExecute, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ListExecute:[%s]", sessionID.toString().c_str(), listExecute.toString().c_str());
}
void MessageCrackerImpl::onMessage(ListExecute& listExecute, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ListExecute:[%s]", sessionID.toString().c_str(), listExecute.toString().c_str());
}

void MessageCrackerImpl::onMessage(const ListStatusRequest& listStatusRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ListStatusRequest:[%s]", sessionID.toString().c_str(), listStatusRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(ListStatusRequest& listStatusRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ListStatusRequest:[%s]", sessionID.toString().c_str(), listStatusRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const ListStatus& listStatus, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ListStatus:[%s]", sessionID.toString().c_str(), listStatus.toString().c_str());
}
void MessageCrackerImpl::onMessage(ListStatus& listStatus, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ListStatus:[%s]", sessionID.toString().c_str(), listStatus.toString().c_str());
}

void MessageCrackerImpl::onMessage(const AllocationInstructionAck& allocationInstructionAck, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], AllocationInstructionAck:[%s]", sessionID.toString().c_str(), allocationInstructionAck.toString().c_str());
}
void MessageCrackerImpl::onMessage(AllocationInstructionAck& allocationInstructionAck, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], AllocationInstructionAck:[%s]", sessionID.toString().c_str(), allocationInstructionAck.toString().c_str());
}

void MessageCrackerImpl::onMessage(const DontKnowTrade& dontKnowTrade, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], DontKnowTrade:[%s]", sessionID.toString().c_str(), dontKnowTrade.toString().c_str());
}
void MessageCrackerImpl::onMessage(DontKnowTrade& dontKnowTrade, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], DontKnowTrade:[%s]", sessionID.toString().c_str(), dontKnowTrade.toString().c_str());
}

void MessageCrackerImpl::onMessage(const QuoteRequest& quoteRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], QuoteRequest:[%s]", sessionID.toString().c_str(), quoteRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(QuoteRequest& quoteRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], QuoteRequest:[%s]", sessionID.toString().c_str(), quoteRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const Quote& quote, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Quote:[%s]", sessionID.toString().c_str(), quote.toString().c_str());
}
void MessageCrackerImpl::onMessage(Quote& quote, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], Quote:[%s]", sessionID.toString().c_str(), quote.toString().c_str());
}

void MessageCrackerImpl::onMessage(const SettlementInstructions& settlementInstructions, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], SettlementInstructions:[%s]", sessionID.toString().c_str(), settlementInstructions.toString().c_str());
}
void MessageCrackerImpl::onMessage(SettlementInstructions& settlementInstructions, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], SettlementInstructions:[%s]", sessionID.toString().c_str(), settlementInstructions.toString().c_str());
}

void MessageCrackerImpl::onMessage(const MarketDataRequest& marketDataRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], MarketDataRequest:[%s]", sessionID.toString().c_str(), marketDataRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(MarketDataRequest& marketDataRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], MarketDataRequest:[%s]", sessionID.toString().c_str(), marketDataRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const MarketDataSnapshotFullRefresh& marketDataSnapshotFullRefresh, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], MarketDataSnapshotFullRefresh:[%s]", sessionID.toString().c_str(), marketDataSnapshotFullRefresh.toString().c_str());
}
void MessageCrackerImpl::onMessage(MarketDataSnapshotFullRefresh& marketDataSnapshotFullRefresh, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], MarketDataSnapshotFullRefresh:[%s]", sessionID.toString().c_str(), marketDataSnapshotFullRefresh.toString().c_str());
}

void MessageCrackerImpl::onMessage(const MarketDataIncrementalRefresh& marketDataIncrementalRefresh, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], MarketDataIncrementalRefresh:[%s]", sessionID.toString().c_str(), marketDataIncrementalRefresh.toString().c_str());
}
void MessageCrackerImpl::onMessage(MarketDataIncrementalRefresh& marketDataIncrementalRefresh, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], MarketDataIncrementalRefresh:[%s]", sessionID.toString().c_str(), marketDataIncrementalRefresh.toString().c_str());
}

void MessageCrackerImpl::onMessage(const MarketDataRequestReject& marketDataRequestReject, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], MarketDataRequestReject:[%s]", sessionID.toString().c_str(), marketDataRequestReject.toString().c_str());
}
void MessageCrackerImpl::onMessage(MarketDataRequestReject& marketDataRequestReject, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], MarketDataRequestReject:[%s]", sessionID.toString().c_str(), marketDataRequestReject.toString().c_str());
}

void MessageCrackerImpl::onMessage(const QuoteCancel& quoteCancel, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], QuoteCancel:[%s]", sessionID.toString().c_str(), quoteCancel.toString().c_str());
}
void MessageCrackerImpl::onMessage(QuoteCancel& quoteCancel, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], QuoteCancel:[%s]", sessionID.toString().c_str(), quoteCancel.toString().c_str());
}

void MessageCrackerImpl::onMessage(const QuoteStatusRequest& quoteStatusRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], QuoteStatusRequest:[%s]", sessionID.toString().c_str(), quoteStatusRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(QuoteStatusRequest& quoteStatusRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], QuoteStatusRequest:[%s]", sessionID.toString().c_str(), quoteStatusRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const QuoteAcknowledgement& quoteAcknowledgement, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], QuoteAcknowledgement:[%s]", sessionID.toString().c_str(), quoteAcknowledgement.toString().c_str());
}
void MessageCrackerImpl::onMessage(QuoteAcknowledgement& quoteAcknowledgement, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], QuoteAcknowledgement:[%s]", sessionID.toString().c_str(), quoteAcknowledgement.toString().c_str());
}

void MessageCrackerImpl::onMessage(const SecurityDefinitionRequest& securityDefinitionRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], SecurityDefinitionRequest:[%s]", sessionID.toString().c_str(), securityDefinitionRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(SecurityDefinitionRequest& securityDefinitionRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], SecurityDefinitionRequest:[%s]", sessionID.toString().c_str(), securityDefinitionRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const SecurityDefinition& securityDefinition, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], SecurityDefinition:[%s]", sessionID.toString().c_str(), securityDefinition.toString().c_str());
}
void MessageCrackerImpl::onMessage(SecurityDefinition& securityDefinition, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], SecurityDefinition:[%s]", sessionID.toString().c_str(), securityDefinition.toString().c_str());
}

void MessageCrackerImpl::onMessage(const SecurityStatusRequest& securityStatusRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], SecurityStatusRequest:[%s]", sessionID.toString().c_str(), securityStatusRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(SecurityStatusRequest& securityStatusRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], SecurityStatusRequest:[%s]", sessionID.toString().c_str(), securityStatusRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const SecurityStatus& securityStatus, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], SecurityStatus:[%s]", sessionID.toString().c_str(), securityStatus.toString().c_str());
}
void MessageCrackerImpl::onMessage(SecurityStatus& securityStatus, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], SecurityStatus:[%s]", sessionID.toString().c_str(), securityStatus.toString().c_str());
}

void MessageCrackerImpl::onMessage(const TradingSessionStatusRequest& tradingSessionStatusRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], TradingSessionStatusRequest:[%s]", sessionID.toString().c_str(), tradingSessionStatusRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(TradingSessionStatusRequest& tradingSessionStatusRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], TradingSessionStatusRequest:[%s]", sessionID.toString().c_str(), tradingSessionStatusRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const TradingSessionStatus& tradingSessionStatus, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], TradingSessionStatus:[%s]", sessionID.toString().c_str(), tradingSessionStatus.toString().c_str());
}
void MessageCrackerImpl::onMessage(TradingSessionStatus& tradingSessionStatus, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], TradingSessionStatus:[%s]", sessionID.toString().c_str(), tradingSessionStatus.toString().c_str());
}

void MessageCrackerImpl::onMessage(const MassQuote& massQuote, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], MassQuote:[%s]", sessionID.toString().c_str(), massQuote.toString().c_str());
}
void MessageCrackerImpl::onMessage(MassQuote& massQuote, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], MassQuote:[%s]", sessionID.toString().c_str(), massQuote.toString().c_str());
}

void MessageCrackerImpl::onMessage(const BusinessMessageReject& businessMessageReject, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], BusinessMessageReject:[%s]", sessionID.toString().c_str(), businessMessageReject.toString().c_str());
}
void MessageCrackerImpl::onMessage(BusinessMessageReject& businessMessageReject, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], BusinessMessageReject:[%s]", sessionID.toString().c_str(), businessMessageReject.toString().c_str());
}

void MessageCrackerImpl::onMessage(const BidRequest& bidRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], BidRequest:[%s]", sessionID.toString().c_str(), bidRequest.toString().c_str());
}
void MessageCrackerImpl::onMessage(BidRequest& bidRequest, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], BidRequest:[%s]", sessionID.toString().c_str(), bidRequest.toString().c_str());
}

void MessageCrackerImpl::onMessage(const BidResponse& bidResponse, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], BidResponse:[%s]", sessionID.toString().c_str(), bidResponse.toString().c_str());
}
void MessageCrackerImpl::onMessage(BidResponse& bidResponse, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], BidResponse:[%s]", sessionID.toString().c_str(), bidResponse.toString().c_str());
}

void MessageCrackerImpl::onMessage(const ListStrikePrice& listStrikePrice, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ListStrikePrice:[%s]", sessionID.toString().c_str(), listStrikePrice.toString().c_str());
}
void MessageCrackerImpl::onMessage(ListStrikePrice& listStrikePrice, const FIX::SessionID& sessionID)
{
	WRITE_LOG(LogLevel::Info, "onMessage: SessionID:[%s], ListStrikePrice:[%s]", sessionID.toString().c_str(), listStrikePrice.toString().c_str());
}
