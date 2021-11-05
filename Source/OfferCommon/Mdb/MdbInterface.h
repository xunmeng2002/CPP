#pragma once
#include <string>
#include "MdbTables.h"


class MdbSubscriber
{
public:
	virtual void ReqInsertOrder(Order* order) {}
	virtual void ReqInsertOrderCancel(OrderCancel* orderCancel) {}
};

class MdbPublisher
{
public:
	virtual void OnRtnOrder(Order* field) {}
	virtual void OnRtnTrade(Trade* field) {}
	virtual void OnErrRtnOrderCancel(OrderCancel* field) {}
};

