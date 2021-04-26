#include "ThostFtdcTraderSpiMiddle.h"
#include "Logger.h"
#include "StructWriteLogFunc.h"


!!types={}!!
!!types['bool']='d'!!
!!types['char']='c'!!
!!types['short']='d'!!
!!types['int']='d'!!
!!types['double']='f'!!
!!types['string']='s'!!

!!entry spi!!
!!travel!!
void CThostFtdcTraderSpiMiddle::!!@name!!(!!travel!!!!if $pumpid != '1':!!!!inc indent!!, !!dec indent!!!!@type!! !!if @custom == "True":!!!!inc indent!!*!!dec indent!!!!@name!!!!leave!!)
{
	WRITE_LOG(LogLevel::Info, "!!@name!!:!!travel!!!!if @custom == "False":!!!!inc indent!!!!currType=types[@type]!! !!@name!![%!!$currType!!]!!dec indent!!!!leave!!"!!travel!!!!if @custom == "False":!!!!inc indent!!, !!@name!!!!dec indent!!!!leave!!);
!!travel!!
!!if @custom == "True":!!
!!inc indent!!
	Write!!@name!!(!!@name!!);
!!dec indent!!
!!leave!!
}

!!leave!!
!!leave!!