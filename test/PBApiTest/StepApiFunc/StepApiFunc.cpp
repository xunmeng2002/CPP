#include "StepApiFunc.h"
#include "Logger.h"
#include "PBStepCallback.h"


HINSTANCE										DllInstance;
__StepApi_Init									StepApi_Init;
__StepApi_Release								StepApi_Release;
__StepApi_CreateUser							StepApi_CreateUser;
__StepApi_CloseUser								StepApi_CloseUser;
__StepApi_SetAddr								StepApi_SetAddr;
__StepApi_SetHQAddr								StepApi_SetHQAddr;
__StepApi_SetCallBackFunc						StepApi_SetCallBackFunc;
__StepApi_CreateRequestHandle					StepApi_CreateRequestHandle;
__StepApi_CreateResponseHandle					StepApi_CreateResponseHandle;
__StepApi_ReleaseMemory							StepApi_ReleaseMemory;
__StepApi_Request								StepApi_Request;
__StepApi_PBSTEP_Init							StepApi_PBSTEP_Init;
__StepApi_PBSTEP_Free							StepApi_PBSTEP_Free;
__StepApi_PBSTEP_InitRecord						StepApi_PBSTEP_InitRecord;
__StepApi_PBSTEP_AppendRecord					StepApi_PBSTEP_AppendRecord;
__StepApi_PBSTEP_DeleteCurrRecord				StepApi_PBSTEP_DeleteCurrRecord;
__StepApi_PBSTEP_GotoFirst						StepApi_PBSTEP_GotoFirst;
__StepApi_PBSTEP_GotoNext						StepApi_PBSTEP_GotoNext;
__StepApi_PBSTEP_GetCurrRecNo					StepApi_PBSTEP_GetCurrRecNo;
__StepApi_PBSTEP_GetRecNum						StepApi_PBSTEP_GetRecNum;
__StepApi_PBSTEP_GetTotalRecNum					StepApi_PBSTEP_GetTotalRecNum;
__StepApi_PBSTEP_SetFieldValueINT				StepApi_PBSTEP_SetFieldValueINT;
__StepApi_PBSTEP_SetFieldValueString			StepApi_PBSTEP_SetFieldValueString;
__StepApi_PBSTEP_AddFieldValueINT				StepApi_PBSTEP_AddFieldValueINT;
__StepApi_PBSTEP_AddFieldValueString			StepApi_PBSTEP_AddFieldValueString;
__StepApi_PBSTEP_GetFieldValueInt				StepApi_PBSTEP_GetFieldValueInt;
__StepApi_PBSTEP_GetFieldValueString			StepApi_PBSTEP_GetFieldValueString;
__StepApi_PBSTEP_IsEmptyRec						StepApi_PBSTEP_IsEmptyRec;
__StepApi_PBSTEP_SetBaseRecFieldValueString		StepApi_PBSTEP_SetBaseRecFieldValueString;
__StepApi_PBSTEP_SetBaseRecFieldValueINT		StepApi_PBSTEP_SetBaseRecFieldValueINT;
__StepApi_PBSTEP_GetBaseRecFieldValueINT		StepApi_PBSTEP_GetBaseRecFieldValueINT;
__StepApi_PBSTEP_GetBaseRecFieldValueString		StepApi_PBSTEP_GetBaseRecFieldValueString;
__StepApi_PBSTEP_SetFieldValueString_StringID	StepApi_PBSTEP_SetFieldValueString_StringID;
__StepApi_PBSTEP_GetFieldValueString_StringID	StepApi_PBSTEP_GetFieldValueString_StringID;
__StepApi_PBSTEP_GetBaseRecFieldByPos			StepApi_PBSTEP_GetBaseRecFieldByPos;
__StepApi_PBSTEP_GetFieldByPos					StepApi_PBSTEP_GetFieldByPos;
__StepApi_PBSTEP_EncryptValueString				StepApi_PBSTEP_EncryptValueString;
__StepApi_PBSTEP_SetConfigPath					StepApi_SetConfigPath;


bool LoadStepApiFunc(const char* fileName)
{
	DllInstance = LoadLibrary(fileName);
	if (DllInstance == nullptr)
	{
		WRITE_LOG(LogLevel::Error, "loadLibrary Failed. FileName:[%s], Error:[%s]", fileName, GetLastError());
		return false;
	}

	StepApi_Init = (__StepApi_Init)GetProcAddress(DllInstance, "StepApi_Init");
	StepApi_Release = (__StepApi_Release)GetProcAddress(DllInstance, "StepApi_Release");
	StepApi_CreateUser = (__StepApi_CreateUser)GetProcAddress(DllInstance, "StepApi_CreateUser");
	StepApi_CloseUser = (__StepApi_CloseUser)GetProcAddress(DllInstance, "StepApi_CloseUser");
	StepApi_SetAddr = (__StepApi_SetAddr)GetProcAddress(DllInstance, "StepApi_SetAddr");
	StepApi_SetHQAddr = (__StepApi_SetHQAddr)GetProcAddress(DllInstance, "StepApi_SetHQAddr");
	StepApi_SetCallBackFunc = (__StepApi_SetCallBackFunc)GetProcAddress(DllInstance, "StepApi_SetCallBackFunc");
	StepApi_CreateRequestHandle = (__StepApi_CreateRequestHandle)GetProcAddress(DllInstance, "StepApi_CreateRequestHandle");
	StepApi_CreateResponseHandle = (__StepApi_CreateResponseHandle)GetProcAddress(DllInstance, "StepApi_CreateResponseHandle");
	StepApi_ReleaseMemory = (__StepApi_ReleaseMemory)GetProcAddress(DllInstance, "StepApi_ReleaseMemory");
	StepApi_Request = (__StepApi_Request)GetProcAddress(DllInstance, "StepApi_Request");
	StepApi_PBSTEP_Init = (__StepApi_PBSTEP_Init)GetProcAddress(DllInstance, "StepApi_PBSTEP_Init");
	StepApi_PBSTEP_Free = (__StepApi_PBSTEP_Free)GetProcAddress(DllInstance, "StepApi_PBSTEP_Free");
	StepApi_PBSTEP_InitRecord = (__StepApi_PBSTEP_InitRecord)GetProcAddress(DllInstance, "StepApi_PBSTEP_InitRecord");
	StepApi_PBSTEP_AppendRecord = (__StepApi_PBSTEP_AppendRecord)GetProcAddress(DllInstance, "StepApi_PBSTEP_AppendRecord");
	StepApi_PBSTEP_DeleteCurrRecord = (__StepApi_PBSTEP_DeleteCurrRecord)GetProcAddress(DllInstance, "StepApi_PBSTEP_DeleteCurrRecord");
	StepApi_PBSTEP_GotoFirst = (__StepApi_PBSTEP_GotoFirst)GetProcAddress(DllInstance, "StepApi_PBSTEP_GotoFirst");
	StepApi_PBSTEP_GotoNext = (__StepApi_PBSTEP_GotoNext)GetProcAddress(DllInstance, "StepApi_PBSTEP_GotoNext");
	StepApi_PBSTEP_GetCurrRecNo = (__StepApi_PBSTEP_GetCurrRecNo)GetProcAddress(DllInstance, "StepApi_PBSTEP_GetCurrRecNo");
	StepApi_PBSTEP_GetRecNum = (__StepApi_PBSTEP_GetRecNum)GetProcAddress(DllInstance, "StepApi_PBSTEP_GetRecNum");
	StepApi_PBSTEP_GetTotalRecNum = (__StepApi_PBSTEP_GetTotalRecNum)GetProcAddress(DllInstance, "StepApi_PBSTEP_GetTotalRecNum");
	StepApi_PBSTEP_SetFieldValueINT = (__StepApi_PBSTEP_SetFieldValueINT)GetProcAddress(DllInstance, "StepApi_PBSTEP_SetFieldValueINT");
	StepApi_PBSTEP_SetFieldValueString = (__StepApi_PBSTEP_SetFieldValueString)GetProcAddress(DllInstance, "StepApi_PBSTEP_SetFieldValueString");
	StepApi_PBSTEP_AddFieldValueINT = (__StepApi_PBSTEP_AddFieldValueINT)GetProcAddress(DllInstance, "StepApi_PBSTEP_AddFieldValueINT");
	StepApi_PBSTEP_AddFieldValueString = (__StepApi_PBSTEP_AddFieldValueString)GetProcAddress(DllInstance, "StepApi_PBSTEP_AddFieldValueString");
	StepApi_PBSTEP_GetFieldValueInt = (__StepApi_PBSTEP_GetFieldValueInt)GetProcAddress(DllInstance, "StepApi_PBSTEP_GetFieldValueInt");
	StepApi_PBSTEP_GetFieldValueString = (__StepApi_PBSTEP_GetFieldValueString)GetProcAddress(DllInstance, "StepApi_PBSTEP_GetFieldValueString");
	StepApi_PBSTEP_IsEmptyRec = (__StepApi_PBSTEP_IsEmptyRec)GetProcAddress(DllInstance, "StepApi_PBSTEP_IsEmptyRec");
	StepApi_PBSTEP_SetBaseRecFieldValueString = (__StepApi_PBSTEP_SetBaseRecFieldValueString)GetProcAddress(DllInstance, "StepApi_PBSTEP_SetBaseRecFieldValueString");
	StepApi_PBSTEP_SetBaseRecFieldValueINT = (__StepApi_PBSTEP_SetBaseRecFieldValueINT)GetProcAddress(DllInstance, "StepApi_PBSTEP_SetBaseRecFieldValueINT");
	StepApi_PBSTEP_GetBaseRecFieldValueINT = (__StepApi_PBSTEP_GetBaseRecFieldValueINT)GetProcAddress(DllInstance, "StepApi_PBSTEP_GetBaseRecFieldValueINT");
	StepApi_PBSTEP_GetBaseRecFieldValueString = (__StepApi_PBSTEP_GetBaseRecFieldValueString)GetProcAddress(DllInstance, "StepApi_PBSTEP_GetBaseRecFieldValueString");
	StepApi_PBSTEP_SetFieldValueString_StringID = (__StepApi_PBSTEP_SetFieldValueString_StringID)GetProcAddress(DllInstance, "StepApi_PBSTEP_SetFieldValueString_StringID");
	StepApi_PBSTEP_GetFieldValueString_StringID = (__StepApi_PBSTEP_GetFieldValueString_StringID)GetProcAddress(DllInstance, "StepApi_PBSTEP_GetFieldValueString_StringID");
	StepApi_PBSTEP_GetBaseRecFieldByPos = (__StepApi_PBSTEP_GetBaseRecFieldByPos)GetProcAddress(DllInstance, "StepApi_PBSTEP_GetBaseRecFieldByPos");
	StepApi_PBSTEP_GetFieldByPos = (__StepApi_PBSTEP_GetFieldByPos)GetProcAddress(DllInstance, "StepApi_PBSTEP_GetFieldByPos");
	StepApi_PBSTEP_EncryptValueString = (__StepApi_PBSTEP_EncryptValueString)GetProcAddress(DllInstance, "StepApi_PBSTEP_EncryptValueString");
	StepApi_SetConfigPath = (__StepApi_PBSTEP_SetConfigPath)GetProcAddress(DllInstance, "StepApi_SetConfigPath");

	if ((StepApi_Init == NULL) || (StepApi_Release == NULL) || (StepApi_CreateUser == NULL) || (StepApi_CloseUser == NULL)
		|| (StepApi_SetAddr == NULL) || (StepApi_SetHQAddr == NULL) || (StepApi_SetCallBackFunc == NULL) || (StepApi_CreateRequestHandle == NULL)
		|| (StepApi_CreateResponseHandle == NULL) || (StepApi_ReleaseMemory == NULL) || (StepApi_Request == NULL) || (StepApi_PBSTEP_Init == NULL)
		|| (StepApi_PBSTEP_Free == NULL) || (StepApi_PBSTEP_InitRecord == NULL) || (StepApi_PBSTEP_AppendRecord == NULL) || (StepApi_PBSTEP_DeleteCurrRecord == NULL)
		|| (StepApi_PBSTEP_GotoFirst == NULL) || (StepApi_PBSTEP_GotoNext == NULL) || (StepApi_PBSTEP_GetCurrRecNo == NULL) || (StepApi_PBSTEP_GetRecNum == NULL)
		|| (StepApi_PBSTEP_GetTotalRecNum == NULL) || (StepApi_PBSTEP_SetFieldValueINT == NULL) || (StepApi_PBSTEP_SetFieldValueString == NULL) || (StepApi_PBSTEP_AddFieldValueINT == NULL)
		|| (StepApi_PBSTEP_AddFieldValueString == NULL) || (StepApi_PBSTEP_GetFieldValueInt == NULL) || (StepApi_PBSTEP_GetFieldValueString == NULL) || (StepApi_PBSTEP_IsEmptyRec == NULL)
		|| (StepApi_PBSTEP_SetBaseRecFieldValueString == NULL) || (StepApi_PBSTEP_SetBaseRecFieldValueINT == NULL) || (StepApi_PBSTEP_GetBaseRecFieldValueINT == NULL) || (StepApi_PBSTEP_GetBaseRecFieldValueString == NULL)
		|| (StepApi_PBSTEP_SetFieldValueString_StringID == NULL) || (StepApi_PBSTEP_GetFieldValueString_StringID == NULL) || (StepApi_PBSTEP_GetBaseRecFieldByPos == NULL) || (StepApi_PBSTEP_GetFieldByPos == NULL)
		|| (StepApi_PBSTEP_EncryptValueString == NULL) || (StepApi_SetConfigPath == NULL))
	{
		WRITE_LOG(LogLevel::Error, "loadLibrary Failed. StepApi_Init[%p], StepApi_Release[%p], StepApi_CreateUser[%p], StepApi_CloseUser[%p], StepApi_SetAddr[%p], \
			StepApi_SetHQAddr[%p], StepApi_SetCallBackFunc[%p], StepApi_CreateRequestHandle[%p], StepApi_CreateResponseHandle[%p], StepApi_ReleaseMemory[%p], \
			StepApi_Request[%p], StepApi_PBSTEP_Init[%p], StepApi_PBSTEP_Free[%p], StepApi_PBSTEP_InitRecord[%p], StepApi_PBSTEP_AppendRecord[%p], \
			StepApi_PBSTEP_DeleteCurrRecord[%p], StepApi_PBSTEP_GotoFirst[%p], StepApi_PBSTEP_GotoNext[%p], StepApi_PBSTEP_GetCurrRecNo[%p], StepApi_PBSTEP_GetRecNum[%p], \
			StepApi_PBSTEP_GetTotalRecNum[%p], StepApi_PBSTEP_SetFieldValueINT[%p], StepApi_PBSTEP_SetFieldValueString[%p], StepApi_PBSTEP_AddFieldValueINT[%p], StepApi_PBSTEP_AddFieldValueString[%p], \
			StepApi_PBSTEP_GetFieldValueInt[%p], StepApi_PBSTEP_GetFieldValueString[%p], StepApi_PBSTEP_IsEmptyRec[%p], StepApi_PBSTEP_SetBaseRecFieldValueString[%p], StepApi_PBSTEP_SetBaseRecFieldValueINT[%p], \
			StepApi_PBSTEP_GetBaseRecFieldValueINT[%p], StepApi_PBSTEP_GetBaseRecFieldValueString[%p], StepApi_PBSTEP_SetFieldValueString_StringID[%p], StepApi_PBSTEP_GetFieldValueString_StringID[%p], StepApi_PBSTEP_GetBaseRecFieldByPos[%p], \
			StepApi_PBSTEP_GetFieldByPos[%p], StepApi_PBSTEP_EncryptValueString[%p], StepApi_SetConfigPath[%p]",
			StepApi_Init, StepApi_Release, StepApi_CreateUser, StepApi_CloseUser, StepApi_SetAddr,
			StepApi_SetHQAddr, StepApi_SetCallBackFunc, StepApi_CreateRequestHandle, StepApi_CreateResponseHandle, StepApi_ReleaseMemory,
			StepApi_Request, StepApi_PBSTEP_Init, StepApi_PBSTEP_Free, StepApi_PBSTEP_InitRecord, StepApi_PBSTEP_AppendRecord,
			StepApi_PBSTEP_DeleteCurrRecord, StepApi_PBSTEP_GotoFirst, StepApi_PBSTEP_GotoNext, StepApi_PBSTEP_GetCurrRecNo, StepApi_PBSTEP_GetRecNum,
			StepApi_PBSTEP_GetTotalRecNum, StepApi_PBSTEP_SetFieldValueINT, StepApi_PBSTEP_SetFieldValueString, StepApi_PBSTEP_AddFieldValueINT, StepApi_PBSTEP_AddFieldValueString,
			StepApi_PBSTEP_GetFieldValueInt, StepApi_PBSTEP_GetFieldValueString, StepApi_PBSTEP_IsEmptyRec, StepApi_PBSTEP_SetBaseRecFieldValueString, StepApi_PBSTEP_SetBaseRecFieldValueINT,
			StepApi_PBSTEP_GetBaseRecFieldValueINT, StepApi_PBSTEP_GetBaseRecFieldValueString, StepApi_PBSTEP_SetFieldValueString_StringID, StepApi_PBSTEP_GetFieldValueString_StringID, StepApi_PBSTEP_GetBaseRecFieldByPos,
			StepApi_PBSTEP_GetFieldByPos, StepApi_PBSTEP_EncryptValueString, StepApi_SetConfigPath);
		
		FreeLibrary(DllInstance);
		DllInstance = nullptr;
		return false;
	}
	return true;
}

bool Init(const char* fileName)
{
	if (!StepApi_Init())
	{
		WRITE_LOG(LogLevel::Error, "StepApi_Init Failed.");
		return false;
	}
	StepApi_SetConfigPath(NULL, fileName);
	tagMainFuncPtr MainFuncPtr = { 0 };
	MainFuncPtr.pSTEPRequestCallBack = StepApiCallback;
	StepApi_SetCallBackFunc(&MainFuncPtr, sizeof(MainFuncPtr));
	return true;
}
