#pragma once
#include "FixFields.h"
#include "FixMessage.h"
#include "MdbInterface.h"
#include <string>

using namespace std;

class FixSpi
{
public:
	FixSpi();
	virtual ~FixSpi();
	
	void RegisterSubscriber(MdbPublisher* mdbPublisher) { m_MdbPublisher = mdbPublisher; }
	virtual void OnFixConnected();
	virtual void OnFixDisConnected();
	
!!entry RspFields!!
!!travel!!
	virtual void OnFix!!@name!!(Fix!!@name!!Field* rspField);
!!leave!!
!!leave!!
protected:
	MdbPublisher* m_MdbPublisher;
	char* m_FixLogBuff;
};


class FixApi
{
public:
!!entry ReqFields!!
!!travel!!
	virtual void !!@name!!(Fix!!@name!!Field* reqField);
!!leave!!
!!leave!!
};

