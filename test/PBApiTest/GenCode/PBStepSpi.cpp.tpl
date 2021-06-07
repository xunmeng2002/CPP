#include "PBStepSpi.h"
#include "Logger.h"

using namespace std;

void PBStepSpi::OnDisConnected()
{
	WRITE_LOG(LogLevel::Info, "OnDisConnected");
}

!!entry packages!!
!!travel!!
!!packageName=@name!!
!!if @name.startswith("Rsp"):!!
!!inc indent!!
!!entry field!!
!!fieldName=@name!!
void PBStepSpi::On!!$packageName!!(PBStep!!$fieldName!!Field* !!$fieldName!!, PBStepRspErrorField* RspError, int& reqNo, bool isLast)
{
	WRITE_LOG(LogLevel::Info, "On!!$packageName!!");
	if (RspError)
	{
		WRITE_LOG(LogLevel::Info, "PBStepRspErrorField: CODE[%s] MSG[%s]", RspError->CODE, RspError->MSG);
	}
	if (!!$fieldName!!)
	{
		WRITE_LOG(LogLevel::Info, "PBStep!!$fieldName!!Field:!!travel!! !!@name!![%s]!!leave!!"!!travel!!, !!$fieldName!!->!!@name!!!!leave!!);
	}
}
!!leave!!
!!dec indent!!
!!elif @name.startswith("Rtn"):!!
!!inc indent!!
!!entry field!!
!!fieldName=@name!!
void PBStepSpi::On!!$packageName!!(PBStep!!$fieldName!!Field* !!$fieldName!!)
{
	WRITE_LOG(LogLevel::Info, "On!!$packageName!!");
	WRITE_LOG(LogLevel::Info, "PBStep!!$fieldName!!Field:!!travel!! !!@name!![%s]!!leave!!"!!travel!!, !!$fieldName!!->!!@name!!!!leave!!);
}
!!leave!!
!!dec indent!!
!!leave!!
!!leave!!