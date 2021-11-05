#pragma once

#include <string>
#include "FixEnumDict.h"
#include "MdbEnumDict.h"

using namespace std;


FixDirection ToFixDirection(Direction direction);
FixOrderType ToFixPriceType(OrderPriceType orderPriceType);
FixOrderStatus ToFixOrderStatus(OrderStatus orderStatus);
FixTimeInForce ToFixTimeInForce(TimeCondition timeCondition);

Direction FromFixDirection(FixDirection direction);
OrderPriceType FromFixPriceType(FixOrderType orderType);
OrderStatus FromFixOrderStatus(FixOrderStatus orderStatus);
TimeCondition FromFixTimeInForce(FixTimeInForce timeInForce);
