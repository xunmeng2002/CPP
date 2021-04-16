#pragma once
#include <list>
#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>
#include "ThreadBase.h"
#include "Buffer.h"

enum class LogLayer : int
{
	System = 0,
	Normal = 1,
};

enum class LogLevel : int
{
	None = 0,
	Emergency = 1,
	Critical = 2,
	Error = 3,
	Warning = 4,
	Info = 5,
	Debug = 6,
	Ignore = 7,
};

struct LogData;
namespace LogSpace
{
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
		void WriteLog(LogLayer layer, LogLevel level, const char* file, int line, const char* format, va_list va);


	protected:
		virtual void ThreadInit() override;
		virtual void Run() override;
		virtual void ThreadExit() override;


		bool CreateLogDir(const char* path);
		void SwapInnerLogBuffers();
		void WriteLog();
		void CreateLogFile();

	private:
		static Logger m_Instance;

		char m_HostName[128];
		int m_Pid;
		char m_ProcessName[128];
		tm m_CreateLogFileTime;

		std::map<LogLayer, LogData*> m_LogDatas;
	};

	void Write(LogLayer layer, LogLevel level, const char* formatStr, va_list va);

	void WriteLog(LogLayer layer, LogLevel level, const char* file, int line, const char* formatStr, ...);

	void WriteErrorLog(const char* file, int line, int errorID, const char* errorMsg);
}

#define WRITE_LOG(layer, level, formatStr, ...)\
	LogSpace::WriteLog(layer, level, __FILE__, __LINE__, formatStr, ##__VA_ARGS__);

#define WRITE_ERROR_LOG(errorID, errorMsg)\
	LogSpace::WriteErrorLog(__FILE__, __LINE__, errorID, errorMsg);