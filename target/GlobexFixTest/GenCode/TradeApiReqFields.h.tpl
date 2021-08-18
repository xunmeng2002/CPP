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
	!!@name!!Field(const !!@name!!Field&) = delete;
	!!@name!!Field& operator=(const !!@name!!Field&) = delete;
	!!@name!!Field(!!@name!!Field&& other) noexcept;
	!!@name!!Field& operator=(!!@name!!Field&& other) noexcept;
	~!!@name!!Field();
	
	virtual int ToString(char* buff, int size) override;
	virtual int ToStream(char* buff) override;
	static string CreateSql();
	virtual string InsertSql() override;
	
public:
!!travel!!
	string !!@name!!;
!!leave!!

	FixMessage* m_FixMessage;
	static constexpr char* Name = "!!@name!!";
};

!!leave!!
!!leave!!
