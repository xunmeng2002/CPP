#pragma once
#include <list>
#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>
#include "ThreadBase.h"
#include "Buffer.h"

enum class LogLevel : int
{
	Ignore = 0,
	Debug = 1,
	Info = 2,
	Warning = 3,
	Error = 4,
	Critical = 5,
	Emergency = 6,
	None = 7,
};

struct LogData;
class Logger : public ThreadBase
{
private:
	Logger();
	~Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

public:
	static Logger& GetInstance();
	bool Init(const char* fullProcessName);
	void WriteLog(LogLevel level, const char* file, int line, const char* func, const char* formatStr, ...);


protected:
	virtual void ThreadInit() override;
	virtual void Run() override;
	virtual void ThreadExit() override;
	virtual void HandleEvent() override {}


	bool CreateLogDir(const char* path);
	void SwapInnerLogBuffers();
	void FlushBuffers();
	void WriteToLog(LogLevel level, const char* file, int line, const char* func, const char* format, va_list va);
	void WriteToConsole(LogLevel level, const char* formatStr, va_list va);
	void CreateLogFile();

private:
	static Logger m_Instance;

	char m_HostName[128];
	int m_Pid;
	char m_ProcessName[128];
	tm m_CreateLogFileTime;
	LogData* m_LogData;
};

#define WRITE_LOG(level, formatStr, ...)\
	Logger::GetInstance().WriteLog(level, __FILE__, __LINE__, __func__, formatStr, ##__VA_ARGS__);

#define WRITE_ERROR_LOG(errorID, errorMsg)\
	Logger::GetInstance().WriteLog(LogLevel::Error, __FILE__, __LINE__, __func__, "ErrorID:[%d], ErrorMsg:[%s].", errorID, errorMsg);