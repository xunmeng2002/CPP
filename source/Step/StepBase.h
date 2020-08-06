#ifndef STEP_BASE_H
#define STEP_BASE_H


class TcpBase;
class StepPackage;
class StepBase
{
public:
	StepBase(TcpBase* tcpBase);
	~StepBase();

	virtual bool SendPackage(unsigned int sessionID, StepPackage* package);

protected:
	TcpBase* m_TcpBase;
};


#endif
