#include "LogData.h"
#include "MemCacheTemplateSingleton.h"

LogData::LogData()
{
	LogFile = nullptr;
	CurrBuffer = new Buffer();
}
LogData::~LogData()
{
	if (LogFile)
	{
		fclose(LogFile);
		LogFile = nullptr;
	}
	delete CurrBuffer;
	for (auto& logBuffer : LogBuffers)
	{
		delete logBuffer;
	}
	LogBuffers.clear();

	for (auto& logBuffer : InnerLogBuffers)
	{
		delete logBuffer;
	}
	InnerLogBuffers.clear();
}
void LogData::PushBuffer()
{
	LogBuffers.push_back(CurrBuffer);
	CurrBuffer = MemCacheTemplateSingleton<Buffer>::GetInstance().Allocate();
}
void LogData::FreeBuffer(Buffer* buffer)
{
	buffer->Reset();
	MemCacheTemplateSingleton<Buffer>::GetInstance().Free(buffer);
}