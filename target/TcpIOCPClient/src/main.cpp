#include <iostream>
#include "Utility.h"
#include "TcpIOCPClient.h"
#include "WorkThread.h"
#include "Logger.h"


using namespace std;

int main(int argc, char* argv[])
{
    Logger::GetInstance().Init(argv[0]);
    Logger::GetInstance().Start();


    TcpIOCPClient::GetInstance().SetLocalAddress();
    TcpIOCPClient::GetInstance().RegisterSubscriber(&WorkThread::GetInstance());
    if (!TcpIOCPClient::GetInstance().Init())
    {
        WRITE_LOG(LogLevel::Error, "TcpIOCPClient Init Failed.");
        return 0;
    }
    TcpIOCPClient::GetInstance().Start();

    WorkThread::GetInstance().RegisterTcp(&TcpIOCPClient::GetInstance());
    WorkThread::GetInstance().Start();

    TcpIOCPClient::GetInstance().Connect("127.0.0.1", 20000);

    for (auto i = 0; i < 10; i++)
    {
        Sleep(5000);
        static char buff[1024];
        auto len = sprintf(buff, "Test Message Index:[%d].", i);
        WorkThread::GetInstance().Send(buff, len);
    }
    Sleep(5000);

    WorkThread::GetInstance().Stop();
    WorkThread::GetInstance().Join();

    TcpIOCPClient::GetInstance().Stop();
    TcpIOCPClient::GetInstance().Join();

    Logger::GetInstance().Stop();
    Logger::GetInstance().Join();
	return 0;
}