#pragma once
#include <string>
#include <vector>

using namespace std;

!!travel!!
!!travel!!
class Its!!@name!!
{
public:
	Its!!@name!!();
	Its!!@name!!(const vector<string>& items);
	int ToString(char* buff, int size);
	int ToStream(char* buff, int size);
	static string CreateSql();
	string InsertSql();
	static int OnSelectCallback(void* callback, int colCount, char** colValues, char** colNames);

public:
!!entry items!!
!!travel!!
	string !!@name!!;
!!leave!!
!!leave!!

	static constexpr char* TableName = "t_Its!!@name!!";
private:
	char m_Buff[4096];
};

!!leave!!
!!leave!!

class ItsMdbCallback
{
public:
!!travel!!
!!travel!!
	virtual void SelectIts!!@name!!Callback(Its!!@name!!* field) { delete field; }
!!leave!!
!!leave!!
};

