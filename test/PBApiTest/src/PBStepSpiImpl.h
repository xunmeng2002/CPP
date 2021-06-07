#pragma once

#include "PBStepSpi.h"
#include "PBStepApi.h"
#include "AccountInfo.h"


class PBStepSpiImpl : public PBStepSpi
{
public:
	PBStepSpiImpl(PBStepApi* stepApi, AccountInfo* accountInfo);

	virtual void OnDisConnected() override;

	virtual void OnRspSetUserInfo(PBStepRspSetUserInfoField* RspSetUserInfo, PBStepRspErrorField* RspError, int& reqNo, bool isLast) override;

	virtual void OnRspSecurityVerity(PBStepRspSecurityVerityField* RspSecurityVerity, PBStepRspErrorField* RspError, int& reqNo, bool isLast) override;

	virtual void OnRspLogin(PBStepRspLoginField* RspLogin, PBStepRspErrorField* RspError, int& reqNo, bool isLast) override;

private:
	PBStepApi* m_StepApi;
	AccountInfo* m_AccountInfo;

	unsigned char m_AeskeySecurity[256];
	unsigned char m_AeskeyResultBuffer[1024];
	unsigned char m_AeskeyResultBufferBase64[2048];
	int m_AeskeySecurityTimeInterval;
};
