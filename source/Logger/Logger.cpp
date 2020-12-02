#include "Logger.h"
#include "Utility.h"
#include "MemCacheTemplate.h"
#include <Windows.h>
#include <assert.h>
#include <process.h>
#include <iostream>
#include "LogData.h"



using namespace std;

#define LOG_LINE_LENGTH 64 * 1024

static LogLevel s_logLevel = LogLevel::Debug;

static map<LogLayer, string> s_LogLayerName = {
	{ LogLayer::System, "SystemLog"},
	{ LogLayer::Normal, "NormalLog"}
};

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
	:ThreadBase("Logger"), m_ProcessName(""), m_CurrDate("")
{
	gethostname(m_HostName, 128);
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
	m_LogDatas.insert(make_pair(LogLayer::System, new LogData()));
	m_LogDatas.insert(make_pair(LogLayer::Normal, new LogData()));
	return CreateLogDir("log");
}
void Logger::WriteLog(LogLayer layer, LogLevel level, const char* file, int line, const char* format, va_list va)
{
	if (m_LogDatas.find(layer) == m_LogDatas.end())
	{
		cerr << "LogData not Exist. LogLayer:" << s_LogLayerName[layer] << endl;
		Write(layer, level, format, va);
		return;
	}
	for (auto p = file; *p != '\0'; p++)
		if (*p == '\\' || *p == '/')
			file = p + 1;


	time_t now;
	time(&now);
	char time_buff[128];
	strftime(time_buff, 128, "%Y%m%d %H:%M:%S", localtime(&now));
	int len = sprintf(t_LogBuffer, "%s %s %d %s ",
		time_buff, m_HostName, GetCurrentThreadId(), s_LogLevelName[level].c_str());

	len += vsnprintf(t_LogBuffer + len, (sizeof(t_LogBuffer) - len - 1), format, va);

	len += _snprintf(t_LogBuffer + len, (sizeof(t_LogBuffer) - len - 1), "\t\t---%s:%d\n", file, line);

	auto logData = m_LogDatas[layer];
	lock_guard<mutex> guard(logData->Mutex);
	if (logData->CurrBuffer->Available() < len)
	{
		logData->PushBuffer();
	}
	logData->CurrBuffer->Append(t_LogBuffer, len);
	logData->ConditionVariable.notify_one();
}
void Logger::ThreadInit()
{
	
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
		static char date[9];
		GetDateTime(date, nullptr);
		if (strcmp(date, m_CurrDate) != 0)
		{
			CreateLogFile();
		}
	}
}
void Logger::ThreadExit()
{
	for (auto& it : m_LogDatas)
	{
		delete it.second;
	}
	m_LogDatas.clear();
}

bool Logger::CreateLogDir(const char* path)
{
	return CreateDirectory(path, NULL) || ERROR_ALREADY_EXISTS == GetLastError();
}
void Logger::SwapInnerLogBuffers()
{
	for (auto& it : m_LogDatas)
	{
		auto logData = it.second;
		unique_lock<mutex> lock(logData->Mutex);
		if (logData->LogBuffers.empty())
		{
			logData->ConditionVariable.wait_for(lock, chrono::seconds(1));
			if (logData->CurrBuffer->Length() > 0)
			{
				logData->PushBuffer();
			}
		}
		logData->InnerLogBuffers.swap(logData->LogBuffers);
	}
}
void Logger::WriteLog()
{
	for (auto& it : m_LogDatas)
	{
		auto logData = it.second;
		for (auto buffer : logData->InnerLogBuffers)
		{
			fwrite(buffer->GetData(), buffer->Length(), 1, logData->LogFile);
			buffer->Reset();
			logData->FreeBuffer(buffer);
		}
		logData->InnerLogBuffers.clear();
		fflush(logData->LogFile);
	}
}
void Logger::CreateLogFile()
{
	for (auto& it : m_LogDatas)
	{
		auto logData = it.second;
		if (logData->LogFile)
		{
			fclose(logData->LogFile);
			logData->LogFile = nullptr;
		}
		time_t now;
		time(&now);
		char timeBuff[32];
		strftime(timeBuff, 32, "%Y%m%d-%H%M%S", localtime(&now));
		strncpy(m_CurrDate, timeBuff, 8);
		m_CurrDate[8] = '\0';

		char fileName[256];
		
		sprintf(fileName, "log/%s.%s.%s.%d.%s", m_ProcessName, timeBuff, m_HostName, m_Pid, s_LogLayerName[it.first].c_str());
		logData->LogFile = fopen(fileName, "a+");
		assert(logData->LogFile != nullptr);
	}
}


void Write(LogLayer layer, LogLevel level, const char* formatStr, va_list va)
{
	if (level > s_logLevel)
		return;
	char logString[10240];
	int len = snprintf(logString, sizeof(logString), "ThreadID[%05d] ", GetCurrentThreadId());

	len += vsnprintf(logString + len, sizeof(logString) - len - 3, formatStr, va);

	printf("%s\n", logString);
}


void WriteLog(LogLayer layer, LogLevel level, const char* file, int line, const char* formatStr, ...)
{
	va_list va;
	va_start(va, formatStr);
	Logger::GetInstance().WriteLog(layer, level, file, line, formatStr, va);
	if (level <= LogLevel::Error)
	{
		Write(layer, level, formatStr, va);
	}
	va_end(va);
}

void WriteErrorLog(const char* file, int line, int errorID, const char* errorMsg)
{
	WriteLog(LogLayer::System, LogLevel::Error, file, line, "ErrorID:[%d], ErrorMsg:[%s].", errorID, errorMsg);
}

