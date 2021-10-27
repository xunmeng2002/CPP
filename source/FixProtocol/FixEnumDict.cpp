#include "FixEnumDict.h"


FixDirection ConvertToFixDirection(const string& value)
{
	return (FixDirection)value[0];
}
FixOrderType ConvertToFixOrderType(const string& value)
{
	return (FixOrderType)value[0];
}
FixOrderStatus ConvertToFixOrderStatus(const string& value)
{
	return (FixOrderStatus)value[0];
}
FixTimeInForce ConvertToFixTimeInForce(const string& value)
{
	return (FixTimeInForce)value[0];
}
FixExecType ConvertToFixExecType(const string& value)
{
	return (FixExecType)value[0];
}
