#include <functional>
#include "ThreadBase.h"
#include "Logger.h"
#include <Windows.h>

using namespace std;

ThreadBase::ThreadBase(const char* name)
	:m_ShouldRun(false)
{
	m_ThreadName = name;
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
	ThreadInit();
	while (m_ShouldRun.load())
	{
		Run();
	}
	ThreadExit();
}
void ThreadBase::ThreadInit()
{
	WRITE_LOG(LogLevel::Info, "Thread[%d]:%s Start", m_ThreadID, m_ThreadName.c_str());
}
void ThreadBase::ThreadExit()
{
	WRITE_LOG(LogLevel::Info, "Thread[%d]:%s Exit", m_ThreadID, m_ThreadName.c_str());
}

void ThreadBase::CheckEvent()
{
	unique_lock<mutex> guard(m_ThreadMutex);
	m_ThreadConditionVariable.wait_for(guard, std::chrono::seconds(1), [&] {return !m_MyEvents.empty();});
}
MyEvent* ThreadBase::GetEvent()
{
	lock_guard<mutex> guard(m_MyEventMutex);
	if (m_MyEvents.empty())
	{
		return nullptr;
	}
	auto myEvent = m_MyEvents.front();
	m_MyEvents.pop_front();
	return myEvent;
}
void ThreadBase::OnEvent(MyEvent* myEvent)
{
	lock_guard<mutex> guard(m_MyEventMutex);
	m_MyEvents.push_back(myEvent);

	m_ThreadConditionVariable.notify_one();
}