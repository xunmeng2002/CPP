#include "PBStepSpiImpl.h"


PBStepSpiImpl::PBStepSpiImpl(PBStepApi* stepApi, AccountInfo* accountInfo)
	:m_StepApi(stepApi), m_AccountInfo(accountInfo)
{

}

void PBStepSpiImpl::OnDisConnected()
{
	PBStepSpi::OnDisConnected();
}
void PBStepSpiImpl::OnRspSecurityVerity(PBStepRspSecurityVerityField* RspSecurityVerity, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	PBStepSpi::OnRspSecurityVerity(RspSecurityVerity, RspError, reqNo, isLast);
}
void PBStepSpiImpl::OnRspLogin(PBStepRspLoginField* RspLogin, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	PBStepSpi::OnRspLogin(RspLogin, RspError, reqNo, isLast);
}
