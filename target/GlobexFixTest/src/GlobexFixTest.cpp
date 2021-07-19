#include "Logger.h"
#include "TradeApi.h"
#include "TcpThread.h"
#include "WorkThread.h"
#include "AccountInfo.h"
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();


	TcpThread::GetInstance().SetTcpInfo();
	if (!TcpThread::GetInstance().Init())
	{
		WRITE_LOG(LogLevel::Error, "TcpThread Init Failed.");
		return -1;
	}
	TcpThread::GetInstance().Start();

	if (!WorkThread::GetInstance().Init())
	{
		WRITE_LOG(LogLevel::Error, "WorkThread Init Failed.");
		return -1;
	}
	WorkThread::GetInstance().Start();
	
	while (true)
	{
		Sleep(30000);
	}
	TcpThread::GetInstance().Stop();
	TcpThread::GetInstance().Join();
	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();

	return 0;
}

