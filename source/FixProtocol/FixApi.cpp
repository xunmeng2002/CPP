#include "FixApi.h"
#include "Logger.h"
#include "TcpEvent.h"


FixSpi::FixSpi()
{
	m_MdbPublisher = nullptr;
	m_FixLogBuff = new char[BuffSize];
}
FixSpi::~FixSpi()
{
	if (m_FixLogBuff)
	{
		delete m_FixLogBuff;
	}
	m_FixLogBuff = nullptr;
}
void FixSpi::OnFixConnected()
{
	WRITE_LOG(LogLevel::Info, "OnFixConnected");
}
void FixSpi::OnFixDisConnected()
{
	WRITE_LOG(LogLevel::Info, "OnFixDisConnected");
}
void FixSpi::OnFixRspLogon(FixRspLogonField* rspField)
{
	rspField->ToString(m_FixLogBuff, BuffSize);
	WRITE_LOG(LogLevel::Info, "OnFixRspLogon: %s", m_FixLogBuff);
}
void FixSpi::OnFixRspLogout(FixRspLogoutField* rspField)
{
	rspField->ToString(m_FixLogBuff, BuffSize);
	WRITE_LOG(LogLevel::Info, "OnFixRspLogout: %s", m_FixLogBuff);
}
void FixSpi::OnFixRspHeartBeat(FixRspHeartBeatField* rspField)
{
	rspField->ToString(m_FixLogBuff, BuffSize);
	WRITE_LOG(LogLevel::Info, "OnFixRspHeartBeat: %s", m_FixLogBuff);
}
void FixSpi::OnFixRspTestRequest(FixRspTestRequestField* rspField)
{
	rspField->ToString(m_FixLogBuff, BuffSize);
	WRITE_LOG(LogLevel::Info, "OnFixRspTestRequest: %s", m_FixLogBuff);
}
void FixSpi::OnFixRspResendRequest(FixRspResendRequestField* rspField)
{
	rspField->ToString(m_FixLogBuff, BuffSize);
	WRITE_LOG(LogLevel::Info, "OnFixRspResendRequest: %s", m_FixLogBuff);
}
void FixSpi::OnFixRspSessionLevelReject(FixRspSessionLevelRejectField* rspField)
{
	rspField->ToString(m_FixLogBuff, BuffSize);
	WRITE_LOG(LogLevel::Info, "OnFixRspSessionLevelReject: %s", m_FixLogBuff);
}
void FixSpi::OnFixRspSequenceReset(FixRspSequenceResetField* rspField)
{
	rspField->ToString(m_FixLogBuff, BuffSize);
	WRITE_LOG(LogLevel::Info, "OnFixRspSequenceReset: %s", m_FixLogBuff);
}
void FixSpi::OnFixExecutionReport(FixExecutionReportField* rspField)
{
	rspField->ToString(m_FixLogBuff, BuffSize);
	WRITE_LOG(LogLevel::Info, "OnFixExecutionReport: %s", m_FixLogBuff);
}
void FixSpi::OnFixRspOrderCancelReject(FixRspOrderCancelRejectField* rspField)
{
	rspField->ToString(m_FixLogBuff, BuffSize);
	WRITE_LOG(LogLevel::Info, "OnFixRspOrderCancelReject: %s", m_FixLogBuff);
}


void FixApi::ReqLogon(FixReqLogonField* reqField)
{
	WRITE_LOG(LogLevel::Error, "ReqLogon was Not Implemented.");
}
void FixApi::ReqLogout(FixReqLogoutField* reqField)
{
	WRITE_LOG(LogLevel::Error, "ReqLogout was Not Implemented.");
}
void FixApi::ReqHeartBeat(FixReqHeartBeatField* reqField)
{
	WRITE_LOG(LogLevel::Error, "ReqHeartBeat was Not Implemented.");
}
void FixApi::ReqTestRequest(FixReqTestRequestField* reqField)
{
	WRITE_LOG(LogLevel::Error, "ReqTestRequest was Not Implemented.");
}
void FixApi::ReqResendRequest(FixReqResendRequestField* reqField)
{
	WRITE_LOG(LogLevel::Error, "ReqResendRequest was Not Implemented.");
}
void FixApi::ReqSequenceReset(FixReqSequenceResetField* reqField)
{
	WRITE_LOG(LogLevel::Error, "ReqSequenceReset was Not Implemented.");
}
void FixApi::ReqNewOrder(FixReqNewOrderField* reqField)
{
	WRITE_LOG(LogLevel::Error, "ReqNewOrder was Not Implemented.");
}
void FixApi::ReqOrderCancelRequest(FixReqOrderCancelRequestField* reqField)
{
	WRITE_LOG(LogLevel::Error, "ReqOrderCancelRequest was Not Implemented.");
}
void FixApi::ReqOrderCancelReplaceRequest(FixReqOrderCancelReplaceRequestField* reqField)
{
	WRITE_LOG(LogLevel::Error, "ReqOrderCancelReplaceRequest was Not Implemented.");
}
void FixApi::ReqOrderStatusRequest(FixReqOrderStatusRequestField* reqField)
{
	WRITE_LOG(LogLevel::Error, "ReqOrderStatusRequest was Not Implemented.");
}
