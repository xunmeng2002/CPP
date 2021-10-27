#pragma once
#include <string>
#include "FixMessage.h"

using namespace std;

#define HEAD_LEN 18
#define TRAILER_LEN 7

!!entry Headers!!
!!travel!!
class Fix!!@name!!
{
public:
	Fix!!@name!!(const string& fieldName, const string& msgType, const string& MsgClass, FixMessage* fixMessage);
	Fix!!@name!!(const Fix!!@name!!&) = delete;
	Fix!!@name!! operator=(const Fix!!@name!!&) = delete;
	Fix!!@name!!(Fix!!@name!!&& other) noexcept;
	Fix!!@name!!& operator=(Fix!!@name!!&& other) noexcept;
	~Fix!!@name!!();
	
	virtual int ToString(char* buff, int size);
	virtual int ToStream(char* buff);
	virtual FixMessage* GetFixMessage();
	static string CreateSql();
	virtual string InsertSql();
	int AddHeader(char* buff, int bodyLen);
	void SetHeader(const string& senderCompID, const string& senderSubID, const string& targetCompID, const string& targetSubID);
	
public:
!!travel!!
	string !!@name!!;
!!leave!!

	FixMessage* m_FixMessage;
	string FieldName;
	string MsgClass;
protected:
	char HeadBuff[HEAD_LEN];
	unordered_map<int, string> Items;
};
!!leave!!
!!leave!!

!!entry Trailers!!
!!travel!!
class Fix!!@name!!
{
public:
	Fix!!@name!!(FixMessage* fixMessage);
	int ToString(char* buff, int size);
	void GetFixMessage(FixMessage* fixMessage);
	int AddTrailer(char* buff, int len);
	
public:
!!travel!!
	string !!@name!!;
!!leave!!
};
!!leave!!
!!leave!!


!!entry ReqFields!!
!!travel!!
class Fix!!@name!!Field : public FixReqHeader, public FixTrailer
{
public:
	Fix!!@name!!Field(FixMessage* fixMessage);
	Fix!!@name!!Field(const Fix!!@name!!Field&) = delete;
	Fix!!@name!!Field& operator=(const Fix!!@name!!Field&) = delete;
	Fix!!@name!!Field(Fix!!@name!!Field&& other) noexcept;
	Fix!!@name!!Field& operator=(Fix!!@name!!Field&& other) noexcept;
	~Fix!!@name!!Field();
	
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
!!travel!!
	string !!@name!!;
!!leave!!

	static constexpr char* TableName = "t_Fix!!@name!!";
};
!!leave!!
!!leave!!

!!entry RspFields!!
!!travel!!
class Fix!!@name!!Field : public FixRspHeader, public FixTrailer
{
public:
	Fix!!@name!!Field(FixMessage* fixMessage);
	Fix!!@name!!Field(const Fix!!@name!!Field&) = delete;
	Fix!!@name!!Field& operator=(const Fix!!@name!!Field&) = delete;
	Fix!!@name!!Field(Fix!!@name!!Field&& other) noexcept;
	Fix!!@name!!Field& operator=(Fix!!@name!!Field&& other) noexcept;
	~Fix!!@name!!Field();
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	virtual FixMessage* GetFixMessage() override;
	static string CreateSql();
	virtual string InsertSql() override;
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);
	
public:
!!travel!!
	string !!@name!!;
!!leave!!

	static constexpr char* TableName = "t_Fix!!@name!!";
};
!!leave!!
!!leave!!
