#include "MdbEnumDict.h"


OrderStatus ConvertToOrderStatus(const string& value)
{
	return (OrderStatus)value[0];
}
Direction ConvertToDirection(const string& value)
{
	return (Direction)value[0];
}
HedgeFlag ConvertToHedgeFlag(const string& value)
{
	return (HedgeFlag)value[0];
}
OrderPriceType ConvertToOrderPriceType(const string& value)
{
	return (OrderPriceType)value[0];
}
OffsetFlag ConvertToOffsetFlag(const string& value)
{
	return (OffsetFlag)value[0];
}
ContingentCondition ConvertToContingentCondition(const string& value)
{
	return (ContingentCondition)value[0];
}
TimeCondition ConvertToTimeCondition(const string& value)
{
	return (TimeCondition)value[0];
}
VolumeCondition ConvertToVolumeCondition(const string& value)
{
	return (VolumeCondition)value[0];
}
ForceCloseReason ConvertToForceCloseReason(const string& value)
{
	return (ForceCloseReason)value[0];
}
TradeType ConvertToTradeType(const string& value)
{
	return (TradeType)value[0];
}
MarginPriceType ConvertToMarginPriceType(const string& value)
{
	return (MarginPriceType)value[0];
}
IsLocalOrder ConvertToIsLocalOrder(const string& value)
{
	return (IsLocalOrder)value[0];
}

