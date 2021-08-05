#pragma once
#include "TradeApiHeaderFields.h"
#include <string>

using namespace std;

!!entry RspFields!!
!!travel!!
class !!@name!!Field : public RspHeader, public Trailer
{
public:
	!!@name!!Field(FixMessage* fixMessage);
	~!!@name!!Field();
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	
public:
!!travel!!
	string !!@name!!;
!!leave!!

	FixMessage* m_FixMessage;
};

!!leave!!
!!leave!!
