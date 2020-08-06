#ifndef STEP_SERVER_H
#define STEP_SERVER_H

#include "StepBase.h"
#include "TcpServer.h"


class StepPackage;
class StepServer : public StepBase, public TcpServer
{
public:
	StepServer();
	~StepServer();
};

#endif
