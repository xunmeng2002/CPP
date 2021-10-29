#include "FixMdb.h"
#include "FixItems.h"


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
	CreateTable<FixReqLogonField>();
	CreateTable<FixReqLogoutField>();
	CreateTable<FixReqHeartBeatField>();
	CreateTable<FixReqTestRequestField>();
	CreateTable<FixReqResendRequestField>();
	CreateTable<FixReqSequenceResetField>();
	CreateTable<FixReqNewOrderField>();
	CreateTable<FixReqOrderCancelRequestField>();
	CreateTable<FixReqOrderCancelReplaceRequestField>();
	CreateTable<FixReqOrderStatusRequestField>();

	CreateTable<FixRspLogonField>();
	CreateTable<FixRspLogoutField>();
	CreateTable<FixRspHeartBeatField>();
	CreateTable<FixRspTestRequestField>();
	CreateTable<FixRspResendRequestField>();
	CreateTable<FixRspSessionLevelRejectField>();
	CreateTable<FixRspSequenceResetField>();
	CreateTable<FixExecutionReportField>();
	CreateTable<FixRspOrderCancelRejectField>();

	CreateTable<FixProduct>();
	CreateTable<FixInstrument>();
}
void FixMdb::TruncateAllTables()
{
	TruncateTable<FixReqLogonField>();
	TruncateTable<FixReqLogoutField>();
	TruncateTable<FixReqHeartBeatField>();
	TruncateTable<FixReqTestRequestField>();
	TruncateTable<FixReqResendRequestField>();
	TruncateTable<FixReqSequenceResetField>();
	TruncateTable<FixReqNewOrderField>();
	TruncateTable<FixReqOrderCancelRequestField>();
	TruncateTable<FixReqOrderCancelReplaceRequestField>();
	TruncateTable<FixReqOrderStatusRequestField>();

	TruncateTable<FixRspLogonField>();
	TruncateTable<FixRspLogoutField>();
	TruncateTable<FixRspHeartBeatField>();
	TruncateTable<FixRspTestRequestField>();
	TruncateTable<FixRspResendRequestField>();
	TruncateTable<FixRspSessionLevelRejectField>();
	TruncateTable<FixRspSequenceResetField>();
	TruncateTable<FixExecutionReportField>();
	TruncateTable<FixRspOrderCancelRejectField>();

	TruncateTable<FixProduct>();
	TruncateTable<FixInstrument>();
}
void FixMdb::SelectAllTables()
{
	SelectTable<FixReqLogonField>();
	SelectTable<FixReqLogoutField>();
	SelectTable<FixReqHeartBeatField>();
	SelectTable<FixReqTestRequestField>();
	SelectTable<FixReqResendRequestField>();
	SelectTable<FixReqSequenceResetField>();
	SelectTable<FixReqNewOrderField>();
	SelectTable<FixReqOrderCancelRequestField>();
	SelectTable<FixReqOrderCancelReplaceRequestField>();
	SelectTable<FixReqOrderStatusRequestField>();

	SelectTable<FixRspLogonField>();
	SelectTable<FixRspLogoutField>();
	SelectTable<FixRspHeartBeatField>();
	SelectTable<FixRspTestRequestField>();
	SelectTable<FixRspResendRequestField>();
	SelectTable<FixRspSessionLevelRejectField>();
	SelectTable<FixRspSequenceResetField>();
	SelectTable<FixExecutionReportField>();
	SelectTable<FixRspOrderCancelRejectField>();

	TruncateTable<FixProduct>();
	TruncateTable<FixInstrument>();
}

