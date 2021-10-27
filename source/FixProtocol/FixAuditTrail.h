#pragma once
#include <string>
#include "FixMessage.h"

using namespace std;

class FixAuditTrail
{
public:
	FixAuditTrail();
	~FixAuditTrail();
	void SetMessage(FixMessage* fixMessage, string messageDirection);
	char* ToString() const;

public:
	string SendingTimestamps;
	string ReceivingTimestamps;
	string MessageDirection;
	string OperatorID;
	string SelfMatchPreventionID;
	string Account;
	string SessionID;
	string ExecutingFirmID;
	string ManualOrderIndicator;
	string MsgType;
	string CtiCode;
	string CustomerOrFirm;
	string ExecID;
	string MessageLinkID;
	string CorrelationClOrdID;
	string SecondaryExecID;
	string SecurityDesc;
	string MarketSegmentID;
	string ClOrdID;
	string OrderID;
	string Side;
	string OrderQty;
	string Price;
	string StopPx;
	string OrdType;
	string TimeInForce;
	string OFMOverride;
	string MaxShow;
	string MinQty;
	string SenderLocationID;
	string LastPx;
	string LastQty;
	string CumQty;
	string LeavesQty;
	string AggressorIndicator;
	string ExecRestatementReason;
	string RejectReason;
	string NoProcessedEntries;
	string CrossID;
	string QuoteReqID;
	string QuoteID;
	string QuoteEntryID;
	string BidPx;
	string BidSize;
	string OfferPx;
	string OfferSize;

private:
	char* Buff;
	int SendIndex;
	int RecvIndex;
};

constexpr char FixAuditTrailHeader[] = "Sending Timestamps, Receiving Timestamps, Message Direction, Operator ID, Self-Match Prevention ID, Account Number, Session ID, Executing Firm ID, Manual Order Identifier, Message Type, Customer Type Indicator, Origin, CME Globex Message ID, Message Link ID, Order Flow ID , Spread/Leg Link ID, Instrument Description, Market Segment ID, Client Order ID, CME Globex Order ID, Buy/Sell Indicator, Quantity, Limit Price, Stop Price, Order Type, Order Qualifier, IFM Flag, Display Quantity, Minimum Quantity, Country of Origin, Fill Price, Fill Quantity, Cumulative Quantity, Remaining Quantity, Aggressor Flag, Source of Cancellation, Reject Reason, Processed Quotes, Cross ID, Quote Request ID, Message Quote ID, Quote Entry ID, Bid Price, Bid Size, Offer Price, Offer Size\n";

