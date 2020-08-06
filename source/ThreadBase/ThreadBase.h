#ifndef THREAD_BASE_H
#define THREAD_BASE_H
#include <thread>
#include <string>

class ThreadBase
{
public:
	ThreadBase(const char *name);
	virtual ~ThreadBase();

	void Join();
	void Start();
	void Stop();

protected:
	virtual void InitThread() {}
	virtual void ReleaseThread() {}
	virtual void Run() = 0;
	void ThreadProc();

protected:
	bool m_ShouldRun;
	std::thread m_Thread;
	DWORD m_ThreadID;
	std::string m_ThreadName;
};


#endif
