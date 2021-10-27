#include "Mdb.h"


Mdb Mdb::m_Instance;

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
	CreateTable<CmeProduct>();
	CreateTable<CmeInstrumentBrief>();
	CreateTable<Order>();
	CreateTable<OrderCancel>();
	CreateTable<Trade>();
}
void Mdb::TruncateAllTables()
{
	TruncateTable<CmeProduct>();
	TruncateTable<CmeInstrumentBrief>();
	TruncateTable<Order>();
	TruncateTable<OrderCancel>();
	TruncateTable<Trade>();
}
void Mdb::SelectAllTables()
{
	SelectTable<CmeProduct>();
	SelectTable<CmeInstrumentBrief>();
	SelectTable<Order>();
	SelectTable<OrderCancel>();
	SelectTable<Trade>();
}

