#pragma once
#include <string>
#include "ItsFields.h"

using namespace std;

class ItsSubscriber
{
public:
	virtual void ReqInsertOrder(int sessionID, ItsInsertOrder* field) {}
	virtual void ReqInsertOrderCancel(int sessionID, ItsInsertOrderCancel* field) {}
	
};

class ItsPublisher
{
public:
	virtual void OnRtnOrder(ItsOrder* field) {}
	virtual void OnRtnTrade(ItsTrade* field) {}
	virtual void OnErrRtnOrderCancel(ItsErrRtnOrderCancel* field) {}
	virtual void OnRspOrder(int sessionID, ItsRspOrder* field) {}
};


