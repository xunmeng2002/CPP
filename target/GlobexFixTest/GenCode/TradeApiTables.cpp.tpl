#include "TradeApiTables.h"
#include "TradeApiItems.h"
#include "WorkThread.h"

!!items = {}!!
!!entry items!!
!!travel!!
!!items[@name] = @key!!
!!leave!!
!!leave!!

TradeApiTables TradeApiTables::m_Instance;

TradeApiTables::TradeApiTables()
	:m_DB(nullptr), m_ErrorMsg(nullptr)
{
}
TradeApiTables& TradeApiTables::GetInstance()
{
	return m_Instance;
}
void TradeApiTables::SetDB(sqlite3* db)
{
	m_DB = db;
}

void TradeApiTables::CreateAllTables()
{
!!entry ReqFields!!
!!travel!!
	Create!!@name!!Table();
!!leave!!
!!leave!!
}
void TradeApiTables::SelectAllTables()
{
!!entry ReqFields!!
!!travel!!
	Select!!@name!!Table();
!!leave!!
!!leave!!
}

!!entry ReqFields!!
!!travel!!
int TradeApiTables::Create!!@name!!Table()
{
	string sql = !!@name!!Field::CreateSql();
	
	int rc = sqlite3_exec(m_DB, sql.c_str(), nullptr, "Create !!@name!!", &m_ErrorMsg);
	if (rc != SQLITE_OK)
    {
        WRITE_LOG(LogLevel::Warning, "SQL error: %s", m_ErrorMsg);
        sqlite3_free(m_ErrorMsg);
    }
    else
    {
        WRITE_LOG(LogLevel::Info, "CREATE Table !!@name!! successfully");
    }
	return rc;
}
int TradeApiTables::Truncate!!@name!!Table()
{
	string sql = "DELETE FROM !!@name!!";
	
	int rc = sqlite3_exec(m_DB, sql.c_str(), nullptr, "Truncate !!@name!!", &m_ErrorMsg);
	if (rc != SQLITE_OK)
    {
        WRITE_LOG(LogLevel::Warning, "SQL error: %s", m_ErrorMsg);
        sqlite3_free(m_ErrorMsg);
    }
    else
    {
        WRITE_LOG(LogLevel::Info, "Truncate Table !!@name!! successfully");
    }
	return rc;
}
int TradeApiTables::Select!!@name!!Table()
{
	string sql = "SELECT * FROM !!@name!!;";
	
	int rc = sqlite3_exec(m_DB, sql.c_str(), SelectCallback!!@name!!, "Select !!@name!!", &m_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WRITE_LOG(LogLevel::Warning, "SQL error: %s", m_ErrorMsg);
		sqlite3_free(m_ErrorMsg);
	}
	return rc;
}
!!leave!!
!!leave!!

!!entry RspFields!!
!!travel!!
int TradeApiTables::Create!!@name!!Table()
{
	string sql = !!@name!!Field::CreateSql();
	
	int rc = sqlite3_exec(m_DB, sql.c_str(), nullptr, "Create !!@name!!", &m_ErrorMsg);
	if (rc != SQLITE_OK)
    {
        WRITE_LOG(LogLevel::Warning, "SQL error: %s", m_ErrorMsg);
        sqlite3_free(m_ErrorMsg);
    }
    else
    {
		WRITE_LOG(LogLevel::Info, "CREATE Table !!@name!! successfully");
    }
	return rc;
}
int TradeApiTables::Select!!@name!!Table()
{
	string sql = "SELECT * FROM !!@name!!;";
	
	int rc = sqlite3_exec(m_DB, sql.c_str(), SelectCallback!!@name!!, "Select !!@name!!", &m_ErrorMsg);
	if (rc != SQLITE_OK)
	{
		WRITE_LOG(LogLevel::Warning, "SQL error: %s", m_ErrorMsg);
		sqlite3_free(m_ErrorMsg);
	}
	return rc;
}
!!leave!!
!!leave!!


!!entry ReqFields!!
!!travel!!
int SelectCallback!!@name!!(void* id, int argc, char** argv, char** azColName)
{
	FixMessage* fixMessage = FixMessage::Allocate();
	for (auto i = 0; i < argc; i++)
	{
		fixMessage->SetItem(TradeApiItems::GetInstance().GetItemKey(azColName[i]), argv[i]);
	}
	WorkThread::GetInstance().InitReqMessage(new !!@name!!Field(fixMessage));
	return 0;
}
!!leave!!
!!leave!!

!!entry RspFields!!
!!travel!!
int SelectCallback!!@name!!(void* id, int argc, char** argv, char** azColName)
{
	FixMessage* fixMessage = FixMessage::Allocate();
	for (auto i = 0; i < argc; i++)
	{
		fixMessage->SetItem(TradeApiItems::GetInstance().GetItemKey(azColName[i]), argv[i]);
	}
	WorkThread::GetInstance().InitRspMessage(new !!@name!!Field(fixMessage));
	return 0;
}
!!leave!!
!!leave!!

