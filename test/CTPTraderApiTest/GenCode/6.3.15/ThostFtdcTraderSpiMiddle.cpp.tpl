#include "ThostFtdcTraderSpiMiddle.h"
#include "Logger.h"
#include "StructWriteLogFunc.h"


!!types={}!!
!!types['char']='c'!!
!!types['short']='d'!!
!!types['int']='d'!!
!!types['double']='f'!!
!!types['string']='s'!!

!!entry spi!!
!!travel!!
!!if @type == "On":!!
!!inc indent!!
void CThostFtdcTraderSpiMiddle::!!@name!!(!!travel!!!!if $pumpid != '1':!!!!inc indent!!, !!dec indent!!!!@type!! !!@name!!!!leave!!)
{
	WRITE_LOG(LogLevel::Info, "!!@name!!: !!travel!!!!currType=types[@type]!!!!if $pumpid != '1':!!!!inc indent!!, !!dec indent!!!!@name!![%!!$currType!!]!!leave!!"!!travel!!, !!@name!!!!leave!!);
}
!!dec indent!!
!!elif @type == "OnRsp" or @type == "OnRspQry":!!
!!inc indent!!
void CThostFtdcTraderSpiMiddle::!!@name!!(!!travel!!CThostFtdc!!@name!!Field* !!@name!!, !!leave!!CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	WRITE_LOG(LogLevel::Info, "!!@name!!: nRequestID[%d], bIsLast[%d]", nRequestID, bIsLast);
	WriteRspInfo(pRspInfo);
!!travel!!
	Write!!@name!!(!!@name!!);
!!leave!!
}
!!dec indent!!
!!elif @type == "OnErrRtn":!!
!!inc indent!!
void CThostFtdcTraderSpiMiddle::!!@name!!(!!travel!!CThostFtdc!!@name!!Field* !!@name!!, !!leave!!CThostFtdcRspInfoField* pRspInfo)
{
	WRITE_LOG(LogLevel::Info, "!!@name!!");
	WriteRspInfo(pRspInfo);
!!travel!!
	Write!!@name!!(!!@name!!);
!!leave!!
}
!!dec indent!!
!!elif @type == "OnRtn":!!
!!inc indent!!
void CThostFtdcTraderSpiMiddle::!!@name!!(!!travel!!!!if $pumpid != '1':!!!!inc indent!!, !!dec indent!!CThostFtdc!!@name!!Field* !!@name!!!!leave!!)
{
	WRITE_LOG(LogLevel::Info, "!!@name!!");
!!travel!!
	Write!!@name!!(!!@name!!);
!!leave!!
}
!!dec indent!!

!!leave!!
!!leave!!