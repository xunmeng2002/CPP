#include "StructWriteLogFunc.h"
#include "Logger.h"

!!types={}!!
!!types['char']='c'!!
!!types['short']='d'!!
!!types['int']='d'!!
!!types['double']='f'!!
!!types['string']='s'!!


!!entry fields!!
!!travel!!
void Write!!@name!!(CThostFtdc!!@name!!Field* !!@name!!)
{
!!fieldName=@name!!
	if(!!@name!!)
	{
		WRITE_LOG(LogLevel::Info, "CThostFtdc!!@name!!Field: !!travel!!!!currType=types[@type]!!!!if $pumpid != '1':!!!!inc indent!!, !!dec indent!!!!@name!![%!!$currType!!]!!leave!!",
			!!travel!!!!if $pumpid != '1':!!!!inc indent!!, !!dec indent!!!!$fieldName!!->!!@name!!!!leave!!);
	}
}

!!leave!!
!!leave!!