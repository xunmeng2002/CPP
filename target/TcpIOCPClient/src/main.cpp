#include <iostream>
#include "Utility.h"
#include "TcpIOCPClient.h"
#include "WorkThread.h"
#include "WorkThreadManage.h"
#include "Logger.h"


using namespace std;

int main(int argc, char* argv[])
{
    Logger::GetInstance().Init(argv[0]);
    Logger::GetInstance().Start();

    std::vector<WorkThreadBase*> workThreads;
    for (auto i = 0; i < 10; i++)
    {
        auto workThread = new WorkThread(i);
        workThreads.push_back(workThread);
    }
    WorkThreadManage::GetInstance().Init(workThreads);
    WorkThreadManage::GetInstance().Start();

    TcpIOCPClient::GetInstance().SetServerAddress("192.168.6.78", 20000);
    if (!TcpIOCPClient::GetInstance().Init())
    {
        WRITE_ERROR_LOG(-1, "TcpServer Init Failed.");
        return 0;
    }
    TcpIOCPClient::GetInstance().Start();


    for (auto i = 0; i < 20480; i++)
    {
        if (!TcpIOCPClient::GetInstance().Connect())
        {
            WRITE_ERROR_LOG(-1, "TcpIOCPClient Connect Failed.");
        }
        Sleep(10);
    }

    Sleep(5000);
    for (int i = 0; i < 10; i++)
    {
        WorkThreadManage::GetInstance().SendTestMessage("Hello");
        Sleep(1000);
    }

    Sleep(5000);
    WorkThreadManage::GetInstance().PrintSessions();
    Sleep(1000);

    WorkThreadManage::GetInstance().CloseConnects();

    Sleep(5000);

    WorkThreadManage::GetInstance().Stop();
    WorkThreadManage::GetInstance().Join();

    TcpIOCPClient::GetInstance().Stop();
    TcpIOCPClient::GetInstance().Join();

    Logger::GetInstance().Stop();
    Logger::GetInstance().Join();
    std::cout << "Hello World!\n";
	return 0;
}