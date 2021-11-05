#include "ItsMdb.h"


ItsMdb ItsMdb::m_Instance;

!!entry Its!!
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
!!travel!!
	CreateTable<Its!!@name!!>();
!!leave!!
}
void ItsMdb::TruncateAllTables()
{
!!travel!!
	TruncateTable<Its!!@name!!>();
!!leave!!
}
void ItsMdb::SelectAllTables()
{
!!travel!!
	SelectTable<Its!!@name!!>();
!!leave!!
}

!!leave!!
