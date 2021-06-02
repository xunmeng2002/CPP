#ifndef PBSTEP_SPI_H
#define PBSTEP_SPI_H

#include "PBStepApi.h"

class PBStepSpi
{
public:
	virtual void OnDisConnected();
	
!!entry packages!!
!!travel!!
!!if @name.startswith("Rsp"):!!
!!inc indent!!
	//!!@desc!!
	virtual void On!!@name!!(!!entry field!!PBStep!!@name!!Field* !!@name!!!!leave!!, PBStepRspErrorField* RspError, int& reqNo, bool isLast);
!!dec indent!!
!!elif @name.startswith("Rtn"):!!
!!inc indent!!
	//!!@desc!!
	virtual void On!!@name!!(!!entry field!!PBStep!!@name!!Field* !!@name!!!!leave!!);
!!dec indent!!
!!leave!!
!!leave!!
};

#endif
