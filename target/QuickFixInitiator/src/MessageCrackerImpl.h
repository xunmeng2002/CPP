#pragma once

#include "quickfix/MessageCracker.h"
#include "quickfix/Application.h"
#include "quickfix/fix42/Heartbeat.h"
#include "quickfix/fix42/TestRequest.h"
#include "quickfix/fix42/ResendRequest.h"
#include "quickfix/fix42/Reject.h"
#include "quickfix/fix42/SequenceReset.h"
#include "quickfix/fix42/Logout.h"
#include "quickfix/fix42/IOI.h"
#include "quickfix/fix42/Advertisement.h"
#include "quickfix/fix42/ExecutionReport.h"
#include "quickfix/fix42/OrderCancelReject.h"
#include "quickfix/fix42/Logon.h"
#include "quickfix/fix42/News.h"
#include "quickfix/fix42/Email.h"
#include "quickfix/fix42/NewOrderSingle.h"
#include "quickfix/fix42/NewOrderList.h"
#include "quickfix/fix42/OrderCancelRequest.h"
#include "quickfix/fix42/OrderCancelReplaceRequest.h"
#include "quickfix/fix42/OrderStatusRequest.h"
#include "quickfix/fix42/Allocation.h"
#include "quickfix/fix42/ListCancelRequest.h"
#include "quickfix/fix42/ListExecute.h"
#include "quickfix/fix42/ListStatusRequest.h"
#include "quickfix/fix42/ListStatus.h"
#include "quickfix/fix42/AllocationInstructionAck.h"
#include "quickfix/fix42/DontKnowTrade.h"
#include "quickfix/fix42/QuoteRequest.h"
#include "quickfix/fix42/Quote.h"
#include "quickfix/fix42/SettlementInstructions.h"
#include "quickfix/fix42/MarketDataRequest.h"
#include "quickfix/fix42/MarketDataSnapshotFullRefresh.h"
#include "quickfix/fix42/MarketDataIncrementalRefresh.h"
#include "quickfix/fix42/MarketDataRequestReject.h"
#include "quickfix/fix42/QuoteCancel.h"
#include "quickfix/fix42/QuoteStatusRequest.h"
#include "quickfix/fix42/QuoteAcknowledgement.h"
#include "quickfix/fix42/SecurityDefinitionRequest.h"
#include "quickfix/fix42/SecurityDefinition.h"
#include "quickfix/fix42/SecurityStatusRequest.h"
#include "quickfix/fix42/SecurityStatus.h"
#include "quickfix/fix42/TradingSessionStatusRequest.h"
#include "quickfix/fix42/TradingSessionStatus.h"
#include "quickfix/fix42/MassQuote.h"
#include "quickfix/fix42/BusinessMessageReject.h"
#include "quickfix/fix42/BidRequest.h"
#include "quickfix/fix42/BidResponse.h"
#include "quickfix/fix42/ListStrikePrice.h"


using namespace FIX42;

class MessageCrackerImpl : public FIX::MessageCracker
{
public:
    virtual void onMessage(const Message&, const FIX::SessionID&) override;
    virtual void onMessage(Message&, const FIX::SessionID&) override;
    
    virtual void onMessage(const Heartbeat&, const FIX::SessionID&) override;
    virtual void onMessage(Heartbeat&, const FIX::SessionID&) override;

    virtual void onMessage(const TestRequest&, const FIX::SessionID&) override;
    virtual void onMessage(TestRequest&, const FIX::SessionID&) override;
    
    virtual void onMessage(const ResendRequest&, const FIX::SessionID&) override;
    virtual void onMessage(ResendRequest&, const FIX::SessionID&) override;
    virtual void onMessage(const Reject&, const FIX::SessionID&) override;
    virtual void onMessage(Reject&, const FIX::SessionID&) override;
    
    virtual void onMessage(const SequenceReset&, const FIX::SessionID&) override;
    virtual void onMessage(SequenceReset&, const FIX::SessionID&) override;

    virtual void onMessage(const Logout&, const FIX::SessionID&) override;
    virtual void onMessage(Logout&, const FIX::SessionID&) override;
    
    virtual void onMessage(const IOI&, const FIX::SessionID&) override;
    virtual void onMessage(IOI&, const FIX::SessionID&) override;
    
    virtual void onMessage(const Advertisement&, const FIX::SessionID&) override;
    virtual void onMessage(Advertisement&, const FIX::SessionID&) override;
    
    virtual void onMessage(const ExecutionReport&, const FIX::SessionID&) override;
    virtual void onMessage(ExecutionReport&, const FIX::SessionID&) override;

    virtual void onMessage(const OrderCancelReject&, const FIX::SessionID&) override;
    virtual void onMessage(OrderCancelReject&, const FIX::SessionID&) override;
    
    virtual void onMessage(const Logon&, const FIX::SessionID&) override;
    virtual void onMessage(Logon&, const FIX::SessionID&) override;
    
    virtual void onMessage(const News&, const FIX::SessionID&) override;
    virtual void onMessage(News&, const FIX::SessionID&) override;
    
    virtual void onMessage(const Email&, const FIX::SessionID&) override;
    virtual void onMessage(Email&, const FIX::SessionID&) override;
    
    virtual void onMessage(const NewOrderSingle&, const FIX::SessionID&) override;
    virtual void onMessage(NewOrderSingle&, const FIX::SessionID&) override;
    
    virtual void onMessage(const NewOrderList&, const FIX::SessionID&) override;
    virtual void onMessage(NewOrderList&, const FIX::SessionID&) override;
    
    virtual void onMessage(const OrderCancelRequest&, const FIX::SessionID&) override;
    virtual void onMessage(OrderCancelRequest&, const FIX::SessionID&) override;
    
    virtual void onMessage(const OrderCancelReplaceRequest&, const FIX::SessionID&) override;
    virtual void onMessage(OrderCancelReplaceRequest&, const FIX::SessionID&) override;
    
    virtual void onMessage(const OrderStatusRequest&, const FIX::SessionID&) override;
    virtual void onMessage(OrderStatusRequest&, const FIX::SessionID&) override;
    
    virtual void onMessage(const Allocation&, const FIX::SessionID&) override;
    virtual void onMessage(Allocation&, const FIX::SessionID&) override;
    
    virtual void onMessage(const ListCancelRequest&, const FIX::SessionID&) override;
    virtual void onMessage(ListCancelRequest&, const FIX::SessionID&) override;
    
    virtual void onMessage(const ListExecute&, const FIX::SessionID&) override;
    virtual void onMessage(ListExecute&, const FIX::SessionID&) override;
    
    virtual void onMessage(const ListStatusRequest&, const FIX::SessionID&) override;
    virtual void onMessage(ListStatusRequest&, const FIX::SessionID&) override;
    
    virtual void onMessage(const ListStatus&, const FIX::SessionID&) override;
    virtual void onMessage(ListStatus&, const FIX::SessionID&) override;
    
    virtual void onMessage(const AllocationInstructionAck&, const FIX::SessionID&) override;
    virtual void onMessage(AllocationInstructionAck&, const FIX::SessionID&) override;
    
    virtual void onMessage(const DontKnowTrade&, const FIX::SessionID&) override;
    virtual void onMessage(DontKnowTrade&, const FIX::SessionID&) override;

    virtual void onMessage(const QuoteRequest&, const FIX::SessionID&) override;
    virtual void onMessage(QuoteRequest&, const FIX::SessionID&) override;
    
    virtual void onMessage(const Quote&, const FIX::SessionID&) override;
    virtual void onMessage(Quote&, const FIX::SessionID&) override;
    
    virtual void onMessage(const SettlementInstructions&, const FIX::SessionID&) override;
    virtual void onMessage(SettlementInstructions&, const FIX::SessionID&) override;
    
    virtual void onMessage(const MarketDataRequest&, const FIX::SessionID&) override;
    virtual void onMessage(MarketDataRequest&, const FIX::SessionID&) override;
    
    virtual void onMessage(const MarketDataSnapshotFullRefresh&, const FIX::SessionID&) override;
    virtual void onMessage(MarketDataSnapshotFullRefresh&, const FIX::SessionID&) override;
    
    virtual void onMessage(const MarketDataIncrementalRefresh&, const FIX::SessionID&) override;
    virtual void onMessage(MarketDataIncrementalRefresh&, const FIX::SessionID&) override;
    
    virtual void onMessage(const MarketDataRequestReject&, const FIX::SessionID&) override;
    virtual void onMessage(MarketDataRequestReject&, const FIX::SessionID&) override;
    
    virtual void onMessage(const QuoteCancel&, const FIX::SessionID&) override;
    virtual void onMessage(QuoteCancel&, const FIX::SessionID&) override;
    
    virtual void onMessage(const QuoteStatusRequest&, const FIX::SessionID&) override;
    virtual void onMessage(QuoteStatusRequest&, const FIX::SessionID&) override;
    
    virtual void onMessage(const QuoteAcknowledgement&, const FIX::SessionID&) override;
    virtual void onMessage(QuoteAcknowledgement&, const FIX::SessionID&) override;
    
    virtual void onMessage(const SecurityDefinitionRequest&, const FIX::SessionID&) override;
    virtual void onMessage(SecurityDefinitionRequest&, const FIX::SessionID&) override;
    
    virtual void onMessage(const SecurityDefinition&, const FIX::SessionID&) override;
    virtual void onMessage(SecurityDefinition&, const FIX::SessionID&) override;
    
    virtual void onMessage(const SecurityStatusRequest&, const FIX::SessionID&) override;
    virtual void onMessage(SecurityStatusRequest&, const FIX::SessionID&) override;
    
    virtual void onMessage(const SecurityStatus&, const FIX::SessionID&) override;
    virtual void onMessage(SecurityStatus&, const FIX::SessionID&) override;

    virtual void onMessage(const TradingSessionStatusRequest&, const FIX::SessionID&) override;
    virtual void onMessage(TradingSessionStatusRequest&, const FIX::SessionID&) override;
    
    virtual void onMessage(const TradingSessionStatus&, const FIX::SessionID&) override;
    virtual void onMessage(TradingSessionStatus&, const FIX::SessionID&) override;
    
    virtual void onMessage(const MassQuote&, const FIX::SessionID&) override;
    virtual void onMessage(MassQuote&, const FIX::SessionID&) override;
    
    virtual void onMessage(const BusinessMessageReject&, const FIX::SessionID&) override;
    virtual void onMessage(BusinessMessageReject&, const FIX::SessionID&) override;
    
    virtual void onMessage(const BidRequest&, const FIX::SessionID&) override;
    virtual void onMessage(BidRequest&, const FIX::SessionID&) override;
    
    virtual void onMessage(const BidResponse&, const FIX::SessionID&) override;
    virtual void onMessage(BidResponse&, const FIX::SessionID&) override;
    
    virtual void onMessage(const ListStrikePrice&, const FIX::SessionID&) override;
    virtual void onMessage(ListStrikePrice&, const FIX::SessionID&) override;

};
