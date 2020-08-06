#include "StepBase.h"
#include "StepPackage.h"
#include "TcpBase.h"

StepBase::StepBase(TcpBase* tcpBase)
	:m_TcpBase(tcpBase)
{

}
StepBase::~StepBase()
{

}

bool StepBase::SendPackage(unsigned int sessionID, StepPackage* package)
{
	package->MakePackage();
	int len = 0;
	while (!package->IsEmpty())
	{
		auto data = package->GetData(len);
		if (!m_TcpBase->Send(sessionID, data, len))
		{
			return false;
		}
	}
	return true;
}