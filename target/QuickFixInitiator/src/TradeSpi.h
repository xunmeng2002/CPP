#pragma once
#include "TradeApiDataStruct.h"

class TradeSpi
{
public:
	virtual void OnRspLogon(RspHeader* rspHeader, RspLogon* rspLogon);

	virtual void OnRspLogout(RspHeader* rspHeader, RspLogout* rspLogout);

};