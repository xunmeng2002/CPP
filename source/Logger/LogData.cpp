#include "LogData.h"
#include "MemCacheTemplate.h"

thread_local MemCacheTemplate<Buffer> t_BufferPool;

LogData::LogData()
{
	LogFile = nullptr;
	CurrBuffer = t_BufferPool.Allocate();
}
LogData::~LogData()
{
	if (LogFile)
	{
		fclose(LogFile);
		LogFile = nullptr;
	}
	t_BufferPool.Free(CurrBuffer);
	for (auto logBuffer : LogBuffers)
	{
		t_BufferPool.Free(logBuffer);
	}
	LogBuffers.clear();

	for (auto logBuffer : InnerLogBuffers)
	{
		t_BufferPool.Free(logBuffer);
	}
	InnerLogBuffers.clear();
}
void LogData::PushBuffer()
{
	LogBuffers.push_back(CurrBuffer);
	CurrBuffer = t_BufferPool.Allocate();
}
void LogData::FreeBuffer(Buffer* buffer)
{
	t_BufferPool.Free(buffer);
}