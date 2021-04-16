#include "Logger.h"
#include "Utility.h"
#include "MemCacheTemplate.h"
#include <Windows.h>
#include <assert.h>
#include <process.h>
#include <iostream>
#include "LogData.h"
#include "TimeUtility.h"


using namespace std;
using namespace LogSpace;

#define LOG_LINE_LENGTH 64 * 1024

static LogLevel s_logLevel = LogLevel::Debug;

static map<LogLevel, string> s_LogLevelName = {
	{ LogLevel::None, "NONE"},
	{ LogLevel::Emergency, "EMERGENCY"},
	{ LogLevel::Critical, "CRITICAL"},
	{ LogLevel::Error, "ERROR"},
	{ LogLevel::Warning, "WARNING"},
	{ LogLevel::Info, "INFO"},
	{ LogLevel::Debug, "DEBUG"},
	{ LogLevel::Ignore, "IGNORE"}
};

thread_local char* t_LogBuffer = new char[LOG_LINE_LENGTH];


Logger Logger::m_Instance;

Logger::Logger()
	:ThreadBase("Logger"), m_ProcessName("")
{
	unsigned long buffSize = 128;
	GetComputerName(m_HostName, &buffSize);
	m_Pid = getpid();
}
Logger::~Logger()
{

}

Logger& Logger::GetInstance()
{
	return m_Instance;
}
bool Logger::Init(const char* fullProcessName)
{
	ParseProcessName(fullProcessName, m_ProcessName, 128);
	m_LogData = new LogData();
	return CreateLogDir("log");
}
void Logger::WriteLog(LogLevel level, const char* file, int line, const char* format, va_list va)
{
	for (auto p = file; *p != '\0'; p++)
		if (*p == '\\' || *p == '/')
			file = p + 1;


	char time_buff[32];
	GetFormatDateTime(time_buff, 32);
	int len = sprintf(t_LogBuffer, "%s %d %s ",
		time_buff, GetCurrentThreadId(), s_LogLevelName[level].c_str());

	len += vsnprintf(t_LogBuffer + len, (sizeof(t_LogBuffer) - len - 1), format, va);

	len += _snprintf(t_LogBuffer + len, (sizeof(t_LogBuffer) - len - 1), "\t\t---%s:%d\n", file, line);

	lock_guard<mutex> guard(m_LogData->Mutex);
	if (m_LogData->CurrBuffer->Available() < len)
	{
		m_LogData->PushBuffer();
	}
	m_LogData->CurrBuffer->Append(t_LogBuffer, len);
	m_LogData->ConditionVariable.notify_one();
}
void Logger::ThreadInit()
{
	m_CreateLogFileTime = *GetTime();
	CreateLogFile();
}
void Logger::Run()
{
	SwapInnerLogBuffers();
	WriteLog();

	static int count = 0;
	if (++count >= 120)
	{
		count = 0;
		auto currTime = *GetTime();
		if (m_CreateLogFileTime.tm_mday != currTime.tm_mday)
		{
			m_CreateLogFileTime = currTime;
			CreateLogFile();
		}
	}
}
void Logger::ThreadExit()
{
	if (m_LogData)
	{
		delete m_LogData;
	}
	m_LogData = nullptr;
}

bool Logger::CreateLogDir(const char* path)
{
	return CreateDirectory(path, NULL) || ERROR_ALREADY_EXISTS == GetLastError();
}
void Logger::SwapInnerLogBuffers()
{
	unique_lock<mutex> lock(m_LogData->Mutex);
	if (m_LogData->LogBuffers.empty())
	{
		m_LogData->ConditionVariable.wait_for(lock, chrono::seconds(1));
		if (m_LogData->CurrBuffer->Length() > 0)
		{
			m_LogData->PushBuffer();
		}
	}
	m_LogData->InnerLogBuffers.swap(m_LogData->LogBuffers);
}
void Logger::WriteLog()
{
	for (auto buffer : m_LogData->InnerLogBuffers)
	{
		fwrite(buffer->GetData(), buffer->Length(), 1, m_LogData->LogFile);
		buffer->Reset();
		m_LogData->FreeBuffer(buffer);
	}
	m_LogData->InnerLogBuffers.clear();
	fflush(m_LogData->LogFile);
}
void Logger::CreateLogFile()
{
	if (m_LogData->LogFile)
	{
		fclose(m_LogData->LogFile);
		m_LogData->LogFile = nullptr;
	}
	char timeBuff[32];
	strftime(timeBuff, 32, "%Y%m%d-%H%M%S", &m_CreateLogFileTime);
	char fileName[256];		
	sprintf(fileName, "log/%s.%s.%s.%d.log", m_ProcessName, timeBuff, m_HostName, m_Pid);
	m_LogData->LogFile = fopen(fileName, "a+");
	assert(m_LogData->LogFile != nullptr);
}


void LogSpace::Write(LogLevel level, const char* formatStr, va_list va)
{
	if (level > s_logLevel)
		return;
	char logString[10240];
	int len = snprintf(logString, sizeof(logString), "ThreadID[%05d] ", GetCurrentThreadId());

	len += vsnprintf(logString + len, sizeof(logString) - len - 3, formatStr, va);

	printf("%s\n", logString);
}

void LogSpace::WriteLog(LogLevel level, const char* file, int line, const char* formatStr, ...)
{
	va_list va;
	va_start(va, formatStr);
	Logger::GetInstance().WriteLog(level, file, line, formatStr, va);
	if (level <= LogLevel::Error)
	{
		Write(level, formatStr, va);
	}
	va_end(va);
}

void LogSpace::WriteErrorLog(const char* file, int line, int errorID, const char* errorMsg)
{
	WriteLog(LogLevel::Error, file, line, "ErrorID:[%d], ErrorMsg:[%s].", errorID, errorMsg);
}

