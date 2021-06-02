#include "PBStepApi.h"
#include "StepApiFunc.h"
#include "Logger.h"
#include <mutex>
using namespace std;


PBStepApi::PBStepApi()
	:m_User(nullptr)
{
}
PBStepApi::~PBStepApi()
{
}
bool PBStepApi::Init(const char* address)
{
	m_User = StepApi_CreateUser();
	if (m_User == nullptr)
		return false;
}

!!entry packages!!
!!travel!!
!!if @name.startswith("Req"):!!
!!inc indent!!
!!packageName=@name!!
!!entry field!!
int PBStepApi::!!$packageName!!(PBStep!!@name!!Field& !!@name!!, int& reqNo)
{
	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	StepApi_PBSTEP_AppendRecord(request);
	SetBaseInfo(request, !!@name!!.BaseInfo);
	
!!fieldName=@name!!
!!travel!!
	StepApi_PBSTEP_AddFieldValueString(request, STEP_!!@name!!, !!$fieldName!!.!!@name!!);
!!leave!!
	
	StepApi_Request(m_User, request, response);
	int errorCode = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_CODE);
	reqNo = StepApi_PBSTEP_GetBaseRecFieldValueINT(response, STEP_REQUESTNO);
	StepApi_PBSTEP_Free(request);
	StepApi_PBSTEP_Free(response);
	return errorCode;
}
!!leave!!
!!dec indent!!
!!leave!!
!!leave!!


void PBStepApi::SetBaseInfo(HANDLE_REQUEST request, PBStepBaseInfoField& baseInfo)
{
	StepApi_PBSTEP_SetBaseRecFieldValueString(request, STEP_LOCAL_IP, baseInfo.LOCAL_IP);
	StepApi_PBSTEP_SetBaseRecFieldValueString(request, STEP_IP, baseInfo.IP);
	StepApi_PBSTEP_SetBaseRecFieldValueString(request, STEP_LOCAL_MAC, baseInfo.LOCAL_MAC);
}

