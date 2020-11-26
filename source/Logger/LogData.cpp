#include "LogData.h"
#include "MemCacheTemplate.h"


LogData::LogData()
{
	LogFile = nullptr;
	CurrBuffer = MemCacheTemplate<Buffer>::GetInstance().Allocate();
}
LogData::~LogData()
{
	if (LogFile)
	{
		fclose(LogFile);
		LogFile = nullptr;
	}
	MemCacheTemplate<Buffer>::GetInstance().Free(CurrBuffer);
	for (auto logBuffer : LogBuffers)
	{
		MemCacheTemplate<Buffer>::GetInstance().Free(logBuffer);
	}
	LogBuffers.clear();

	for (auto logBuffer : InnerLogBuffers)
	{
		MemCacheTemplate<Buffer>::GetInstance().Free(logBuffer);
	}
	InnerLogBuffers.clear();
}