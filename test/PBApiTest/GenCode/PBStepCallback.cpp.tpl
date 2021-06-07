#include "PBStepCallback.h"
#include "PBApiDataStruct.h"
#include "Logger.h"
#include <iostream>

using namespace std;

#define PBSTEP_ERROR_DISCONNECT -3
#define PBSTEP_ERROR_NOT_LOGIN -8

std::map<HANDLE_USER, PBStepSpi*> g_UserSpis;

void SetSpi(HANDLE_USER user, PBStepSpi* stepSpi)
{
	g_UserSpis[user] = stepSpi;
}

PBStepSpi* GetSpi(HANDLE_USER user)
{
	if (g_UserSpis.find(user) == g_UserSpis.end())
	{
		return nullptr;
	}
	return g_UserSpis[user];
}

int StepApiCallback(HANDLE_USER user, HANDLE_RESPONSE response)
{
	if (user == NULL || response == NULL)
	{
		return -1;
	}
	auto spi = GetSpi(user);
	if (spi == nullptr)
	{
		WRITE_LOG(LogLevel::Error, "StepApiCallback Cannot find SPI for User[%p]", user);
		return -1;
	}
	int reqno = 0;
	PBStepRspErrorField RspError;
	::memset(&RspError, 0, sizeof(RspError));
	int errorID = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	sprintf(RspError.CODE, "%d", errorID);
	if (errorID < 0)
	{
		StepApi_PBSTEP_GetBaseRecFieldValueString(response, STEP_MSG, RspError.MSG, sizeof(RspError.MSG));
		reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	}
	if (errorID == PBSTEP_ERROR_DISCONNECT)
	{
		WRITE_LOG(LogLevel::Error, "StepApiCallback PBSTEP_ERROR_DISCONNECT");
		spi->OnDisConnected();
		return 0;
	}
	
	int funcNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_FUNC);
	printf("funcNo=%d\n", funcNo);
	switch(funcNo)
	{
!!entry packages!!
!!travel!!
!!packageName=@name!!
!!if @name.startswith("Rsp"):!!
!!inc indent!!
	case !!@funcid!!:
	{
		if (errorID < 0)
		{
			spi->On!!$packageName!!(nullptr, &RspError, reqno, true);
			break;
		}
!!entry field!!
!!fieldName=@name!!
		PBStep!!$fieldName!!Field !!$fieldName!!;
		::memset(&!!$fieldName!!, 0, sizeof(!!$fieldName!!));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		int reqno = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
!!travel!!
			StepApi_PBSTEP_GetFieldValueString(response, STEP_!!@name!!, !!$fieldName!!.!!@name!!, sizeof(!!$fieldName!!.!!@name!!));
!!leave!!

			if (!StepApi_PBSTEP_GotoNext(response) || j == recnum)
			{
				spi->On!!$packageName!!(&!!$fieldName!!, &RspError, reqno, true);
				break;
			}
			spi->On!!$packageName!!(&!!$fieldName!!, &RspError, reqno, false);
		}
		if (recnum == 0)
		{
			spi->On!!$packageName!!(nullptr, &RspError, reqno, true);
		}
		break;
	}
!!leave!!
!!dec indent!!
!!elif @name.startswith("Rtn"):!!
!!inc indent!!
	case !!@funcid!!:
	{
!!entry field!!
!!fieldName=@name!!
		PBStep!!$fieldName!!Field !!$fieldName!!;
		::memset(&!!$fieldName!!, 0, sizeof(!!$fieldName!!));

		int recnum = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_RETURNNUM);
		//StepApi_PBSTEP_GotoFirst(response);
		for (int j = 0; j < recnum; j++)
		{
!!travel!!
			StepApi_PBSTEP_GetFieldValueString(response, STEP_!!@name!!, !!$fieldName!!.!!@name!!, sizeof(!!$fieldName!!.!!@name!!));
!!leave!!

			spi->On!!$packageName!!(&!!$fieldName!!);
		}
		if (recnum == 0)
		{
			spi->On!!$packageName!!(nullptr);
		}
		break;
	}
!!leave!!
!!dec indent!!
!!leave!!
!!leave!!
	}
	return 0;
}