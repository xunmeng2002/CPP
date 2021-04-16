#include "Logger.h"
#include <Windows.h>


int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();

	WRITE_LOG(LogLevel::Info, "This is a Log Test.");
	WRITE_LOG(LogLevel::Info, "True[%d]", true);

	Sleep(5000);
	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
}

