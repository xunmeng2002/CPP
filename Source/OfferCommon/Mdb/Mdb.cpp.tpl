#include "Mdb.h"


Mdb Mdb::m_Instance;

!!entry tables!!
Mdb::Mdb()
	:m_DB(nullptr), m_Callback(nullptr), m_ErrorMsg(nullptr)
{
}
Mdb& Mdb::GetInstance()
{
	return m_Instance;
}
void Mdb::SetDB(sqlite3* db)
{
	m_DB = db;
}
void Mdb::SetCallback(MdbCallback* callback)
{
	m_Callback = callback;
}
void Mdb::CreateAllTables()
{
!!travel!!
	CreateTable<!!@name!!>();
!!leave!!
}
void Mdb::TruncateAllTables()
{
!!travel!!
	TruncateTable<!!@name!!>();
!!leave!!
}
void Mdb::SelectAllTables()
{
!!travel!!
	SelectTable<!!@name!!>();
!!leave!!
}

!!leave!!
