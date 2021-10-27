#include "FixMdb.h"
#include "FixItems.h"

!!items = {}!!
!!entry items!!
!!travel!!
!!items[@name] = @key!!
!!leave!!
!!leave!!

FixMdb FixMdb::m_Instance;

FixMdb::FixMdb()
	:m_DB(nullptr), m_Callback(nullptr), m_ErrorMsg(nullptr)
{
}
FixMdb& FixMdb::GetInstance()
{
	return m_Instance;
}
void FixMdb::SetDB(sqlite3* db)
{
	m_DB = db;
}
void FixMdb::SetCallback(FixTableCallback* callback)
{
	m_Callback = callback;
}

void FixMdb::CreateAllTables()
{
!!entry ReqFields!!
!!travel!!
	CreateTable<Fix!!@name!!Field>();
!!leave!!
!!leave!!

!!entry RspFields!!
!!travel!!
	CreateTable<Fix!!@name!!Field>();
!!leave!!
!!leave!!
}
void FixMdb::TruncateAllTables()
{
!!entry ReqFields!!
!!travel!!
	TruncateTable<Fix!!@name!!Field>();
!!leave!!
!!leave!!

!!entry RspFields!!
!!travel!!
	TruncateTable<Fix!!@name!!Field>();
!!leave!!
!!leave!!
}
void FixMdb::SelectAllTables()
{
!!entry ReqFields!!
!!travel!!
	SelectTable<Fix!!@name!!Field>();
!!leave!!
!!leave!!

!!entry RspFields!!
!!travel!!
	SelectTable<Fix!!@name!!Field>();
!!leave!!
!!leave!!
}

