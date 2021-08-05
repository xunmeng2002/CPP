#pragma once
#include "FixMessage.h"
#include <string>

using namespace std;

#define HEAD_LEN 18
#define TRAILER_LEN 7

!!entry Headers!!
!!travel!!
class !!@name!!
{
public:
	!!@name!!(const string& fieldName, const string& msgType, FixMessage* fixMessage);
	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff);
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
	!!@name!!(FixMessage* fixMessage);
	int ToString(char* buff, int size);
	int AddTrailer(char* buff, int len);
	
public:
!!travel!!
	string !!@name!!;
!!leave!!
};

!!leave!!
!!leave!!
