#pragma once
#include "ThostFtdcTraderApi.h"


class CThostFtdcTraderSpiMiddle : public CThostFtdcTraderSpi
{
public:
!!entry spi!!
!!travel!!
!!if @type == "On":!!
!!inc indent!!
	virtual void !!@name!!(!!travel!!!!if $pumpid != '1':!!!!inc indent!!, !!dec indent!!!!@type!! !!@name!!!!leave!!);
!!dec indent!!
!!elif @type == "OnRsp" or @type == "OnRspQry":!!
!!inc indent!!
	virtual void !!@name!!(!!travel!!CThostFtdc!!@name!!Field* !!@name!!, !!leave!!CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
!!dec indent!!
!!elif @type == "OnErrRtn":!!
!!inc indent!!
	virtual void !!@name!!(!!travel!!CThostFtdc!!@name!!Field* !!@name!!, !!leave!!CThostFtdcRspInfoField* pRspInfo);
!!dec indent!!
!!elif @type == "OnRtn":!!
!!inc indent!!
	virtual void !!@name!!(!!travel!!!!if $pumpid != '1':!!!!inc indent!!, !!dec indent!!CThostFtdc!!@name!!Field* !!@name!!!!leave!!);
!!dec indent!!

!!leave!!
!!leave!!
};