#pragma once
#include "TradeApiHeaderFields.h"
#include <string>

using namespace std;

!!entry RspFields!!
!!travel!!
class !!@name!! : public RspHeader, public Trailer
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
