#pragma once
#include <stdio.h>
#include <list>
#include <mutex>
#include <condition_variable>
#include "Buffer.h"


struct LogData
{
	LogData();
	~LogData();

	FILE* LogFile;
	Buffer* CurrBuffer;
	std::list<Buffer*> LogBuffers;
	std::list<Buffer*> InnerLogBuffers;

	std::mutex Mutex;
	std::condition_variable ConditionVariable;
};