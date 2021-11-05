#pragma once
#include <string>
#include "MdbEnumDict.h"
#include "sqlite3.h"
#include "Logger.h"
#include "Mdbtables.h"

using namespace std;


class Mdb
{
	Mdb();
	Mdb(const Mdb&) = delete;
	Mdb& operator=(const Mdb&) = delete;
public:
	static Mdb& GetInstance();
	void SetDB(sqlite3* db);
	void SetCallback(MdbCallback* callback);
	
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
	static Mdb m_Instance;
	sqlite3* m_DB;
	MdbCallback* m_Callback;
	char* m_ErrorMsg;
};
