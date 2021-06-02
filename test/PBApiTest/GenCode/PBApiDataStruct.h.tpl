#ifndef PBAPI_DATA_STRUCT_H
#define PBAPI_DATA_STRUCT_H
#include "stepdef.h"

//基本信息
struct PBStepBaseInfoField
{
	char LOCAL_IP[64];   //客户端本机地址
	char LOCAL_MAC[64];  //客户端MAC地址
	char IP[64];         //终端公网IP
};

!!entry fields!!
!!travel!!
struct PBStep!!@name!!Field
{
	PBStepBaseInfoField BaseInfo;
!!travel!!
	//!!@desc!!
	char !!@name!![!!@length!!];
!!leave!!
};

!!leave!!
!!leave!!

#endif