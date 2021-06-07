#pragma once

#include "PBApiDataStruct.h"
#include "StepApi.h"

#define PBSTEP_ERROR_DISCONNECT -3
#define PBSTEP_ERROR_NOT_LOGIN -8

class PBStepSpi;
class PBStepApi
{
public:
	PBStepApi();
	~PBStepApi();
	
	bool Init(PBStepSpi* stepSpi, const char* address, const char* fileName);
	
!!entry packages!!
!!travel!!
!!if @name.startswith("Req"):!!
!!inc indent!!
	//!!@desc!!
	int !!@name!!(!!travel!!PBStep!!@name!!Field& !!@name!!, !!leave!!int& reqNo);
!!dec indent!!
!!leave!!
!!leave!!

private:
	void SetBaseInfo(HANDLE_REQUEST request, PBStepBaseInfoField& baseInfo);

private:
	HANDLE_USER m_User;
};
