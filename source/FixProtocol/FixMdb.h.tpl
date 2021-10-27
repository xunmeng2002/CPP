#pragma once
#include <string>
#include "sqlite3.h"
#include "Logger.h"
#include "FixFields.h"

using namespace std;


class FixTableCallback
{
public:
	virtual void InitReqMessage(FixReqHeader* reqField) { delete reqField; }
	virtual void InitRspMessage(FixRspHeader* rspField) { delete rspField; }
};


class FixMdb
{
	FixMdb();
	FixMdb(const FixMdb&) = delete;
	FixMdb& operator=(const FixMdb&) = delete;
public:
	static FixMdb& GetInstance();
	void SetDB(sqlite3* db);
	void SetCallback(FixTableCallback* callback);
	
	void CreateAllTables();
	void TruncateAllTables();
	void SelectAllTables();
	
	template<typename T>
	int CreateTable()
	{
		string sql = T::CreateSql();
		WRITE_LOG(LogLevel::Debug, "CreateSql SQL:[%s]", sql.c_str());

		int rc = sqlite3_exec(m_DB, sql.c_str(), nullptr, "CreateTable", &m_ErrorMsg);
		if (rc != SQLITE_OK)
		{
			WRITE_LOG(LogLevel::Warning, "SQL error: %s", m_ErrorMsg);
			sqlite3_free(m_ErrorMsg);
		}
		return rc;
	}
	template<typename T>
	int TruncateTable()
	{
		string sql = string("DELETE FROM ") + T::TableName + ";";
		WRITE_LOG(LogLevel::Debug, "TruncateSql SQL:[%s]", sql.c_str());

		int rc = sqlite3_exec(m_DB, sql.c_str(), nullptr, "TruncateTable", &m_ErrorMsg);
		if (rc != SQLITE_OK)
		{
			WRITE_LOG(LogLevel::Warning, "SQL error: %s", m_ErrorMsg);
			sqlite3_free(m_ErrorMsg);
		}
		return rc;
	}
	template<typename T>
	int InsertRecord(T* field)
	{
		string sql = field->InsertSql();
		WRITE_LOG(LogLevel::Debug, "InsertRecord SQL:[%s]", sql.c_str());
		
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
		string sql = "DELETE FROM " + string(T::TableName) + " WHERE MsgSeqNum = '" + field->MsgSeqNum + "';";
		WRITE_LOG(LogLevel::Debug, "DeleteRecord SQL:[%s]", sql.c_str());

		int rc = sqlite3_exec(m_DB, sql.c_str(), nullptr, "DeleteRecord", &m_ErrorMsg);
		if (rc != SQLITE_OK)
		{
			WRITE_LOG(LogLevel::Warning, "SQL error: %s", m_ErrorMsg);
			sqlite3_free(m_ErrorMsg);
		}
		return rc;
	}
	template<typename T>
	int SelectTable()
	{
		string sql = string("SELECT * FROM ") + T::TableName + ";";
		WRITE_LOG(LogLevel::Debug, "SelectTable SQL:[%s]", sql.c_str());

		int rc = sqlite3_exec(m_DB, sql.c_str(), T::OnSelectCallback, m_Callback, &m_ErrorMsg);
		if (rc != SQLITE_OK)
		{
			WRITE_LOG(LogLevel::Warning, "SQL error: %s", m_ErrorMsg);
			sqlite3_free(m_ErrorMsg);
		}
		else
		{
			WRITE_LOG(LogLevel::Info, "Select Table %s successfully", T::TableName);
		}
		return rc;
	}
private:
	static FixMdb m_Instance;
	sqlite3* m_DB;
	FixTableCallback* m_Callback;
	char* m_ErrorMsg;
};

