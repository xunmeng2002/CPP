#pragma once
#include "TradeApiHeaderFields.h"
#include <string>

using namespace std;

!!entry ReqFields!!
!!travel!!
class !!@name!!Field : public ReqHeader, public Trailer
{
public:
	!!@name!!Field(FixMessage* fixMessage);
	~!!@name!!Field();
	int ToString(char* buff, int size);
	int ToStream(char* buff);
	
public:
!!travel!!
	string !!@name!!;
!!leave!!

	FixMessage* m_FixMessage;
};

!!leave!!
!!leave!!
