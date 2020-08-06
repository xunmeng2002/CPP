#ifndef STEP_CLIENT_H
#define STEP_CLIENT_H

#include "StepBase.h"
#include "TcpClient.h"


class StepPackage;
class StepClient : public StepBase, public TcpClient
{
public:
	StepClient();
	~StepClient();
};


#endif
