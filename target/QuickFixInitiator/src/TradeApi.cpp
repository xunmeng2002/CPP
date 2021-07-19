#include "TradeApi.h"
#include "quickfix/Session.h"
#include "quickfix/fix42/NewOrderSingle.h"

bool TradeApi::ReqOrderInsert()
{
	FIX42::NewOrderSingle newOrderSingle;

	FIX::Session::sendToTarget(newOrderSingle);
	return true;
}