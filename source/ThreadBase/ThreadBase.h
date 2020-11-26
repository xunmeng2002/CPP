#include <thread>
#include <atomic>
#include <string>
#pragma once


class ThreadBase
{
public:
	ThreadBase(const char* name);
	virtual ~ThreadBase();

	virtual bool Start();
	virtual void Stop();
	virtual void Join();
	
protected:
	void ThreadFunc();
	virtual void ThreadInit() = 0;
	virtual void Run() = 0;
	virtual void ThreadExit() = 0;

protected:
	unsigned long m_ThreadID;
	std::thread m_Thread;
	std::string m_Name;
	std::atomic<bool> m_ShouldRun;
};

