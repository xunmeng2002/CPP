#pragma once
#include "TradeApiHeaderFields.h"
#include <string>

using namespace std;

!!entry ReqFields!!
!!travel!!
class !!@name!! : public ReqHeader, public Trailer
{
public:
	!!@name!!(const string& fieldName, FixMessage* fixMessage);
	int ToString(char* buff, int size);
	int ToStream(char* buff);
	
public:
!!travel!!
	string !!@name!!;
!!leave!!
};

!!leave!!
!!leave!!
