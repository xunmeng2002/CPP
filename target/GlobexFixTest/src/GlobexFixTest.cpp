#include "Logger.h"
#include "TradeApi.h"
#include "TcpThread.h"
#include "WorkThread.h"
#include "AccountInfo.h"
#include <iostream>
#include <signal.h>
#include<stdlib.h>

using namespace std;

void OnExit()
{
	WRITE_LOG(LogLevel::Info, "OnExit");
	TcpThread::GetInstance().Stop();
	TcpThread::GetInstance().Join();

	WorkThread::GetInstance().Stop();
	WorkThread::GetInstance().Join();
	

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
}

void ReqTestRequest()
{
	Sleep(30000);

	auto myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_TEST_REQUEST;
	myEvent->StringParams.push_back("Hello world!");
	WorkThread::GetInstance().OnEvent(myEvent);
}
void ReqLogout()
{
	Sleep(30000);

	auto myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_REQ_LOGOUT;
	WorkThread::GetInstance().OnEvent(myEvent);
}
void ReqNewOrder()
{
	Sleep(2000);
	auto myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_REQ_NEW_ORDER;
	WorkThread::GetInstance().OnEvent(myEvent);
}

int main(int argc, char* argv[])
{
	atexit(OnExit);

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

	Sleep(20000);
	for (auto i = 0; i < 3; i++)
	{
		ReqNewOrder();
	}
	while (true)
	{
		Sleep(10000);
	}

	return 0;
}

