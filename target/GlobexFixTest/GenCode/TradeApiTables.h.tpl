#pragma once
#include <string>
#include "sqlite3.h"
#include "Logger.h"
#include "TradeApiReqFields.h"
#include "TradeApiRspFields.h"

using namespace std;


class TradeApiTables
{
	TradeApiTables();
	TradeApiTables(const TradeApiTables&) = delete;
	TradeApiTables& operator=(const TradeApiTables&) = delete;
public:
	static TradeApiTables& GetInstance();
	void SetDB(sqlite3* db);
	
	void CreateAllTables();
	void SelectAllTables();
	
!!entry ReqFields!!
!!travel!!
	int Create!!@name!!Table();
	int Truncate!!@name!!Table();
	int Select!!@name!!Table();
!!leave!!
!!leave!!

!!entry RspFields!!
!!travel!!
	int Create!!@name!!Table();
	int Truncate!!@name!!Table();
	int Select!!@name!!Table();
!!leave!!
!!leave!!
	
	
	template<typename T>
	int InsertRecord(T* field)
	{
		string sql = field->InsertSql();
		int rc = sqlite3_exec(m_DB, sql.c_str(), nullptr, "InsertRecord", &m_ErrorMsg);
		if (rc != SQLITE_OK)
		{
			WRITE_LOG(LogLevel::Warning, "SQL error: %s", m_ErrorMsg);
			sqlite3_free(m_ErrorMsg);
		}
		return rc;
	}
	template<typename T>
	int DeleteRecord(T* field)
	{
		string sql = "DELETE FROM " + string(T::Name) + " WHERE MsgSeqNum = '" + field->MsgSeqNum + "';";

		int rc = sqlite3_exec(m_DB, sql.c_str(), nullptr, "DeleteRecord", &m_ErrorMsg);
		if (rc != SQLITE_OK)
		{
			WRITE_LOG(LogLevel::Warning, "SQL error: %s", m_ErrorMsg);
			sqlite3_free(m_ErrorMsg);
		}
		return rc;
	}
private:
	static TradeApiTables m_Instance;
	sqlite3* m_DB;
	char* m_ErrorMsg;
};

!!entry ReqFields!!
!!travel!!
int SelectCallback!!@name!!(void* id, int argc, char** argv, char** azColName);
!!leave!!
!!leave!!

!!entry RspFields!!
!!travel!!
int SelectCallback!!@name!!(void* id, int argc, char** argv, char** azColName);
!!leave!!
!!leave!!
