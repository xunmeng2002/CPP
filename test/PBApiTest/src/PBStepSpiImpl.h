#ifndef PBSTEP_SPI_IMPL_H
#define PBSTEP_SPI_IMPL_H

#include "PBStepSpi.h"
#include "PBStepApi.h"
#include "AccountInfo.h"


class PBStepSpiImpl : public PBStepSpi
{
public:
	PBStepSpiImpl(PBStepApi* stepApi, AccountInfo* accountInfo);

	virtual void OnDisConnected() override;

	virtual void OnRspSecurityVerity(PBStepRspSecurityVerityField* RspSecurityVerity, PBStepRspErrorField* RspError, int& reqNo, bool isLast) override;

	virtual void OnRspLogin(PBStepRspLoginField* RspLogin, PBStepRspErrorField* RspError, int& reqNo, bool isLast) override;

private:
	PBStepApi* m_StepApi;
	AccountInfo* m_AccountInfo;
};


#endif