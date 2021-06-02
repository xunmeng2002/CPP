#ifndef PBSTEP_CALLBACK_H
#define PBSTEP_CALLBACK_H

#include "StepApiFunc.h"
#include "PBStepSpi.h"
#include <map>



extern std::map<HANDLE_USER, PBStepSpi*> g_UserSpis;


int StepApiCallback(HANDLE_USER user, HANDLE_RESPONSE response);



#endif