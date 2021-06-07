#pragma once

#include "StepApi.h"
#include <Windows.h>

extern HINSTANCE										DllInstance;
extern __StepApi_Init									StepApi_Init;
extern __StepApi_Release								StepApi_Release;
extern __StepApi_CreateUser								StepApi_CreateUser;
extern __StepApi_CloseUser								StepApi_CloseUser;
extern __StepApi_SetAddr								StepApi_SetAddr;
extern __StepApi_SetHQAddr								StepApi_SetHQAddr;
extern __StepApi_SetCallBackFunc						StepApi_SetCallBackFunc;
extern __StepApi_CreateRequestHandle					StepApi_CreateRequestHandle;
extern __StepApi_CreateResponseHandle					StepApi_CreateResponseHandle;
extern __StepApi_ReleaseMemory							StepApi_ReleaseMemory;
extern __StepApi_Request								StepApi_Request;
extern __StepApi_PBSTEP_Init							StepApi_PBSTEP_Init;
extern __StepApi_PBSTEP_Free							StepApi_PBSTEP_Free;
extern __StepApi_PBSTEP_InitRecord						StepApi_PBSTEP_InitRecord;
extern __StepApi_PBSTEP_AppendRecord					StepApi_PBSTEP_AppendRecord;
extern __StepApi_PBSTEP_DeleteCurrRecord				StepApi_PBSTEP_DeleteCurrRecord;
extern __StepApi_PBSTEP_GotoFirst						StepApi_PBSTEP_GotoFirst;
extern __StepApi_PBSTEP_GotoNext						StepApi_PBSTEP_GotoNext;
extern __StepApi_PBSTEP_GetCurrRecNo					StepApi_PBSTEP_GetCurrRecNo;
extern __StepApi_PBSTEP_GetRecNum						StepApi_PBSTEP_GetRecNum;
extern __StepApi_PBSTEP_GetTotalRecNum					StepApi_PBSTEP_GetTotalRecNum;
extern __StepApi_PBSTEP_SetFieldValueINT				StepApi_PBSTEP_SetFieldValueINT;
extern __StepApi_PBSTEP_SetFieldValueString				StepApi_PBSTEP_SetFieldValueString;
extern __StepApi_PBSTEP_AddFieldValueINT				StepApi_PBSTEP_AddFieldValueINT;
extern __StepApi_PBSTEP_AddFieldValueString				StepApi_PBSTEP_AddFieldValueString;
extern __StepApi_PBSTEP_GetFieldValueInt				StepApi_PBSTEP_GetFieldValueInt;
extern __StepApi_PBSTEP_GetFieldValueString				StepApi_PBSTEP_GetFieldValueString;
extern __StepApi_PBSTEP_IsEmptyRec						StepApi_PBSTEP_IsEmptyRec;
extern __StepApi_PBSTEP_SetBaseRecFieldValueString		StepApi_PBSTEP_SetBaseRecFieldValueString;
extern __StepApi_PBSTEP_SetBaseRecFieldValueINT			StepApi_PBSTEP_SetBaseRecFieldValueINT;
extern __StepApi_PBSTEP_GetBaseRecFieldValueINT			StepApi_PBSTEP_GetBaseRecFieldValueINT;
extern __StepApi_PBSTEP_GetBaseRecFieldValueString		StepApi_PBSTEP_GetBaseRecFieldValueString;
extern __StepApi_PBSTEP_SetFieldValueString_StringID	StepApi_PBSTEP_SetFieldValueString_StringID;
extern __StepApi_PBSTEP_GetFieldValueString_StringID	StepApi_PBSTEP_GetFieldValueString_StringID;
extern __StepApi_PBSTEP_GetBaseRecFieldByPos			StepApi_PBSTEP_GetBaseRecFieldByPos;
extern __StepApi_PBSTEP_GetFieldByPos					StepApi_PBSTEP_GetFieldByPos;
extern __StepApi_PBSTEP_EncryptValueString				StepApi_PBSTEP_EncryptValueString;
extern __StepApi_PBSTEP_SetConfigPath					StepApi_SetConfigPath;

bool LoadStepApiFunc(const char* fileName);

bool StepApiInit(const char* fileName);
