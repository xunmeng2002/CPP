#pragma once
#include "TradeApiDataStruct.h"
#include <string>

using namespace std;

!!entry Headers!!
!!travel!!
class !!@name!!
{
public:
	!!@name!!(const string& fieldName, FixMessage* fixMessage);
	int ToString(char* buff, int size);
	int ToStream(char* buff);
	int AddHeader(char* buff, int bodyLen);
	void SetHeader(const string& senderCompID, const string& senderSubID, const string& targetCompID, const string& targetSubID);
	
public:
!!travel!!
	string !!@name!!;
!!leave!!

protected:
	string FieldName;

	char HeadBuff[HEAD_LEN];
	unordered_map<int, string> Items;
};

!!leave!!
!!leave!!

!!entry Trailers!!
!!travel!!
class !!@name!!
{
public:
	!!@name!!(){}
	int ToString(char* buff, int size);
	int AddTrailer(char* buff, int len);
	
public:
!!travel!!
	string !!@name!!;
!!leave!!
};

!!leave!!
!!leave!!
