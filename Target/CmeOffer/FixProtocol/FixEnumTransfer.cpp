#include "FixEnumTransfer.h"




FixDirection ToFixDirection(Direction direction)
{
	if (direction == Direction::Buy)
	{
		return FixDirection::Buy;
	}
	else
	{
		return FixDirection::Sell;
	}
}
FixOrderType ToFixPriceType(OrderPriceType orderPriceType)
{
	switch (orderPriceType)
	{
	case OrderPriceType::Anyprice:
		return FixOrderType::MarketOrder;
	case OrderPriceType::LimitPrice:
		return FixOrderType::LimitOrder;
	case OrderPriceType::BestPrice:
	case OrderPriceType::LastPrice:
		return FixOrderType::LimitOrder;
	}
	return FixOrderType::LimitOrder;
}
FixOrderStatus ToFixOrderStatus(OrderStatus orderStatus)
{
	switch (orderStatus)
	{
	case OrderStatus::Inserting:
		return FixOrderStatus::Undefined;
	case OrderStatus::Inserted:
		return FixOrderStatus::New;
	case OrderStatus::PartTraded:
		return FixOrderStatus::PartiallyFilled;
	case OrderStatus::AllTraded:
		return FixOrderStatus::Filled;
	case OrderStatus::Canceled:
		return FixOrderStatus::Cancelled;
	case OrderStatus::PartTradedCanceled:
		return FixOrderStatus::Cancelled;
	case OrderStatus::Error:
		return FixOrderStatus::Rejected;
	case OrderStatus::NotTouched:
	case OrderStatus::Touched:
	case OrderStatus::Unknown:
	default:
		return FixOrderStatus::Undefined;
	}
	return FixOrderStatus::Undefined;
}
FixTimeInForce ToFixTimeInForce(TimeCondition timeCondition)
{
	switch (timeCondition)
	{
	case TimeCondition::IOC:
		return FixTimeInForce::FillAndKill;
	case TimeCondition::GFA:
	case TimeCondition::GFS:
	case TimeCondition::GFD:
		return FixTimeInForce::Day;
	case TimeCondition::GTD:
		return FixTimeInForce::GoodTillDate;
	case TimeCondition::GTC:
		return FixTimeInForce::GoodTillCancel;
	}
	return FixTimeInForce::Day;
}


Direction FromFixDirection(FixDirection direction)
{
	if (direction == FixDirection::Buy)
	{
		return Direction::Buy;
	}
	else
	{
		return Direction::Sell;
	}
}
OrderPriceType FromFixPriceType(FixOrderType direction)
{
	if (direction == FixOrderType::MarketOrder)
	{
		return OrderPriceType::Anyprice;
	}
	else
	{
		return OrderPriceType::LimitPrice;
	}
}
OrderStatus FromFixOrderStatus(FixOrderStatus orderStatus)
{
	switch (orderStatus)
	{
	case FixOrderStatus::New:
		return OrderStatus::Inserted;
	case FixOrderStatus::PartiallyFilled:
		return OrderStatus::PartTraded;
	case FixOrderStatus::Filled:
		return OrderStatus::AllTraded;
	case FixOrderStatus::PendingCancel:
	case FixOrderStatus::Cancelled:
		return OrderStatus::Canceled;
	case FixOrderStatus::PendingReplace:
	case FixOrderStatus::Replaced:
		return OrderStatus::Inserted;
	case FixOrderStatus::Rejected:
	case FixOrderStatus::Eliminated:
		return OrderStatus::Error;
	case FixOrderStatus::TradeCorrect:
	case FixOrderStatus::TradeCancel:
	case FixOrderStatus::Undefined:
	default:
		return OrderStatus::Unknown;
	}
	return OrderStatus::Unknown;
}
TimeCondition FromFixTimeInForce(FixTimeInForce timeInForce)
{
	switch (timeInForce)
	{
	case FixTimeInForce::Day:
		return TimeCondition::GFD;
	case FixTimeInForce::GoodTillCancel:
		return TimeCondition::GTC;
	case FixTimeInForce::FillAndKill:
		return TimeCondition::IOC;
	case FixTimeInForce::GoodTillDate:
		return TimeCondition::GTD;
	}
	return TimeCondition::GFD;
}
