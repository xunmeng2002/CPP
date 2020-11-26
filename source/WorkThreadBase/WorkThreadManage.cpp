#include "WorkThreadManage.h"
#include "WorkThreadBase.h"

WorkThreadManage WorkThreadManage::m_Instance;

WorkThreadManage::WorkThreadManage()
{
	m_MinSessionNum = 0;
}
WorkThreadManage::~WorkThreadManage()
{
	for (auto workThread : m_WorkThreads)
	{
		delete workThread;
	}
	m_WorkThreads.clear();
}
WorkThreadManage& WorkThreadManage::GetInstance()
{
	return m_Instance;
}
void WorkThreadManage::Init(std::vector<WorkThreadBase*> workThreads)
{
	m_WorkThreads = workThreads;
}

void WorkThreadManage::Start()
{
	for (auto workThread : m_WorkThreads)
	{
		workThread->Start();
	}
}
void WorkThreadManage::Stop()
{
	for (auto workThread : m_WorkThreads)
	{
		workThread->Stop();
	}
}
void WorkThreadManage::Join()
{
	for (auto workThread : m_WorkThreads)
	{
		workThread->Join();
	}
}

void WorkThreadManage::CloseConnects()
{
	for (auto workThread : m_WorkThreads)
	{
		workThread->CloseConnects();
	}
}
void WorkThreadManage::SendTestMessage(const std::string& message)
{
	for (auto workThread : m_WorkThreads)
	{
		workThread->SendTestMessage(message);
	}
}

WorkThreadBase* WorkThreadManage::DispatchWorkThread()
{
	int currMinSessionNum = m_WorkThreads.front()->GetSessionNum();
	WorkThreadBase* currWorkThread = m_WorkThreads.front();
	if (currMinSessionNum == m_MinSessionNum)
	{
		return currWorkThread;
	}
	for (auto workThread : m_WorkThreads)
	{
		if (workThread->GetSessionNum() <= currMinSessionNum)
		{
			currMinSessionNum = workThread->GetSessionNum();
			currWorkThread = workThread;
		}
	}
	m_MinSessionNum = currMinSessionNum;
	return currWorkThread;
}