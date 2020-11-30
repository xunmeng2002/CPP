#include "SocketDataStruct.h"
#include "WorkThreadBase.h"

#pragma once


class WorkThread : public WorkThreadBase
{
public:
	WorkThread(int workThreadID);
	~WorkThread();

	virtual void CloseConnects() override;
	virtual void SendTestMessage(const std::string& message);

protected:
	virtual void HandleRecvMessage(SocketData* socketData) override;

	void SendTestMessage(int sessionID, const std::string& message);

private:
	char m_MessageBuffer[1024];
};

