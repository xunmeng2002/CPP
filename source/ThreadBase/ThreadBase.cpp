#include <functional>
#include "ThreadBase.h"
#include "Logger.h"
#include <Windows.h>

using namespace std;

ThreadBase::ThreadBase(const char* name)
	:m_ShouldRun(false)
{
	m_Name = name;
}
ThreadBase::~ThreadBase()
{
}

bool ThreadBase::Start()
{
	if (m_ShouldRun.load())
		return false;

	m_ShouldRun.store(true);
	m_Thread = thread(std::bind(&ThreadBase::ThreadFunc, this));
	return true;
}
void ThreadBase::Stop()
{
	m_ShouldRun.store(false);
}
void ThreadBase::Join()
{
	if (m_Thread.joinable())
		m_Thread.join();
}

void ThreadBase::ThreadFunc()
{
	m_ThreadID = GetCurrentThreadId();
	WRITE_LOG(LogLayer::Normal, LogLevel::Info, "Thread[%d]:%s Start", m_ThreadID, m_Name.c_str());
	ThreadInit();
	while (m_ShouldRun.load())
	{
		Run();
	}
	ThreadExit();
	WRITE_LOG(LogLayer::Normal, LogLevel::Info, "Thread[%d]:%s Exit", m_ThreadID, m_Name.c_str());
}