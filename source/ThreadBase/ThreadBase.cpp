#include "ThreadBase.h"
#include <Windows.h>
#include <iostream>
#include <sstream>
using namespace std;

ThreadBase::ThreadBase(const char* name)
	:m_ShouldRun(false)
{
	m_ThreadName = name;
}
ThreadBase::~ThreadBase()
{
}

void ThreadBase::Join()
{
	m_Thread.join();
}
void ThreadBase::Start()
{
	//m_ShouldRun为True，说明已经启动了，不能再启动了
	if (m_ShouldRun)
		return;

	m_ShouldRun = true;
	m_Thread = thread(std::bind(&ThreadBase::ThreadProc, this));
}
void ThreadBase::Stop()
{
	m_ShouldRun = false;
}


void ThreadBase::ThreadProc()
{
	m_ThreadID = GetCurrentThreadId();

	InitThread();

	while (m_ShouldRun)
	{
		this->Run();
	}

	ReleaseThread();
}
