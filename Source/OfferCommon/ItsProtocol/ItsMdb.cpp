#include "ItsMdb.h"


ItsMdb ItsMdb::m_Instance;

ItsMdb::ItsMdb()
	:m_DB(nullptr), m_Callback(nullptr), m_ErrorMsg(nullptr)
{
}
ItsMdb& ItsMdb::GetInstance()
{
	return m_Instance;
}
void ItsMdb::SetDB(sqlite3* db)
{
	m_DB = db;
}
void ItsMdb::SetCallback(ItsMdbCallback* callback)
{
	m_Callback = callback;
}
void ItsMdb::CreateAllTables()
{
	CreateTable<ItsInsertOrder>();
	CreateTable<ItsInsertOrderCancel>();
	CreateTable<ItsRspOrder>();
	CreateTable<ItsOrder>();
	CreateTable<ItsTrade>();
	CreateTable<ItsErrRtnOrderCancel>();
}
void ItsMdb::TruncateAllTables()
{
	TruncateTable<ItsInsertOrder>();
	TruncateTable<ItsInsertOrderCancel>();
	TruncateTable<ItsRspOrder>();
	TruncateTable<ItsOrder>();
	TruncateTable<ItsTrade>();
	TruncateTable<ItsErrRtnOrderCancel>();
}
void ItsMdb::SelectAllTables()
{
	SelectTable<ItsInsertOrder>();
	SelectTable<ItsInsertOrderCancel>();
	SelectTable<ItsRspOrder>();
	SelectTable<ItsOrder>();
	SelectTable<ItsTrade>();
	SelectTable<ItsErrRtnOrderCancel>();
}

