#include "PBStepSpiImpl.h"
#include "Logger.h"
#include "ClientServerVerify.h"
#include "Base64.h"


PBStepSpiImpl::PBStepSpiImpl(PBStepApi* stepApi, AccountInfo* accountInfo)
	:m_StepApi(stepApi), m_AccountInfo(accountInfo)
{

}

void PBStepSpiImpl::OnDisConnected()
{
	PBStepSpi::OnDisConnected();
}
void PBStepSpiImpl::OnRspSetUserInfo(PBStepRspSetUserInfoField* RspSetUserInfo, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	PBStepSpi::OnRspSetUserInfo(RspSetUserInfo, RspError, reqNo, isLast);


}
void PBStepSpiImpl::OnRspSecurityVerity(PBStepRspSecurityVerityField* RspSecurityVerity, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	PBStepSpi::OnRspSecurityVerity(RspSecurityVerity, RspError, reqNo, isLast);
	if (RspSecurityVerity)
	{
		::memcpy(m_AeskeySecurity, RspSecurityVerity->AQMY, sizeof(RspSecurityVerity->AQMY));
		m_AeskeySecurityTimeInterval = atoi(RspSecurityVerity->SJJGS);
	}


	PBStepQryInstrumentField qryInstrument;
	::memset(&qryInstrument, 0, sizeof(qryInstrument));
	int errorCode = m_StepApi->ReqQryInstrument(qryInstrument, reqNo);
	WRITE_LOG(LogLevel::Info, "ReqQryInstrument  ErrorCode:[%d]  ReqNo:[%d]", errorCode, reqNo);
}
void PBStepSpiImpl::OnRspLogin(PBStepRspLoginField* RspLogin, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	PBStepSpi::OnRspLogin(RspLogin, RspError, reqNo, isLast);
	if (!RspLogin)
	{
		return;
	}
	::memcpy(m_AeskeySecurity, RspLogin->AQMY, sizeof(RspLogin->AQMY));

	size_t result_size = 0;
	Pobo::Security::GetResultA(nullptr, result_size, 0, 500, true);
	Pobo::Security::GetResultA(m_AeskeyResultBuffer, result_size, 0, 500, true);
	Pobo::Security::ChangeAWithR(m_AeskeySecurity, strlen((char*)m_AeskeySecurity), m_AeskeyResultBuffer, result_size);
	int len = 0;
	Base64Encode(m_AeskeyResultBuffer, result_size, m_AeskeyResultBufferBase64, len);

	PBStepReqSecurityVerityField reqSecurityVerity;
	::memset(&reqSecurityVerity, 0, sizeof(reqSecurityVerity));
	::memcpy(reqSecurityVerity.MYKL, m_AeskeyResultBufferBase64, len);
	int errorCode = m_StepApi->ReqSecurityVerity(reqSecurityVerity, reqNo);
	WRITE_LOG(LogLevel::Info, "ReqSecurityVerity  ErrorCode:[%d]  ReqNo:[%d]", errorCode, reqNo);
}
