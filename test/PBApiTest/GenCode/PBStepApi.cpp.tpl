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
!!funcID=@funcid!!
!!entry field!!
int PBStepApi::!!$packageName!!(PBStep!!@name!!Field& !!@name!!, int& reqNo)
{
	HANDLE_REQUEST	request = StepApi_CreateRequestHandle(m_User);
	HANDLE_RESPONSE response = StepApi_CreateResponseHandle(m_User);
	StepApi_PBSTEP_Init(request);
	StepApi_PBSTEP_Init(response);
	SetBaseInfo(request, !!@name!!.BaseInfo);
	StepApi_PBSTEP_SetBaseRecFieldValueINT(request, STEP_FUNC, !!$funcID!!);
!!if $packageName=="ReqLogin":!!
!!inc indent!!
	char JYMM[256] = { 0 };
	int JYMMLen = sizeof(JYMM);
	StepApi_PBSTEP_EncryptValueString(m_User, ReqLogin.HXMM, JYMM, JYMMLen, ReqLogin.DLZH);
	StepApi_PBSTEP_SetBaseRecFieldValueString(request, STEP_JYMM, JYMM);
!!dec indent!!
	
	StepApi_PBSTEP_AppendRecord(request);
!!fieldName=@name!!
!!travel!!
!!if @encrypt=='1':!!
!!inc indent!!
	char !!@name!![256] = { 0 };
	int !!@name!!Len = sizeof(!!@name!!);
	StepApi_PBSTEP_EncryptValueString(m_User, !!$fieldName!!.!!@name!!, !!@name!!, !!@name!!Len, !!$fieldName!!.!!@name!!);
	StepApi_PBSTEP_AddFieldValueString(request, STEP_!!@name!!, !!@name!!);
!!dec indent!!
!!else:!!
!!inc indent!!
	StepApi_PBSTEP_AddFieldValueString(request, STEP_!!@name!!, !!$fieldName!!.!!@name!!);
!!dec indent!!
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

