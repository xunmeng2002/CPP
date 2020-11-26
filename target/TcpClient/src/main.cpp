#include <iostream>
#include "Utility.h"
#include "TcpClient.h"
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

    TcpClient::GetInstance().SetServerAddress("192.168.6.78", 20000);
    if (!TcpClient::GetInstance().Init())
    {
        WRITE_ERROR_LOG(-1, "TcpServer Init Failed.");
        return 0;
    }
    TcpClient::GetInstance().Start();


    for (auto i = 0; i < 200; i++)
    {
        if (!TcpClient::GetInstance().Connect())
        {
            WRITE_ERROR_LOG(-1, "TcpClient Connect Failed.");
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

    WorkThreadManage::GetInstance().CloseConnects();

    Sleep(5000);

    WorkThreadManage::GetInstance().Stop();
    WorkThreadManage::GetInstance().Join();

    TcpClient::GetInstance().Stop();
    TcpClient::GetInstance().Join();

    Logger::GetInstance().Stop();
    Logger::GetInstance().Join();
    std::cout << "Hello World!\n";
	return 0;
}