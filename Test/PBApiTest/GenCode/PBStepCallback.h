#pragma once

#include "StepApiFunc.h"
#include "PBStepSpi.h"
#include <map>



void SetSpi(HANDLE_USER user, PBStepSpi* stepSpi);

PBStepSpi* GetSpi(HANDLE_USER user);


int StepApiCallback(HANDLE_USER user, HANDLE_RESPONSE response);

