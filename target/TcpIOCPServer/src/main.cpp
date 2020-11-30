// ConsoleApplication25.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Logger.h"
#include "TcpIOCPServer.h"
#include "WorkThread.h"
#include "WorkThreadManage.h"
#include "Logger.h"

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

    TcpIOCPServer::GetInstance().SetSocketInfo(20000, "0.0.0.0");
    if (!TcpIOCPServer::GetInstance().Init())
    {
        WRITE_ERROR_LOG(-1, "TcpIOCPServer Init Failed.");
        return 0;
    }
    TcpIOCPServer::GetInstance().Start();

    Sleep(1000000);
    
    WorkThreadManage::GetInstance().CloseConnects();

    Sleep(5000);

    WorkThreadManage::GetInstance().Stop();
    WorkThreadManage::GetInstance().Join();

    TcpIOCPServer::GetInstance().Stop();
    TcpIOCPServer::GetInstance().Join();

    Logger::GetInstance().Stop();
    Logger::GetInstance().Join();
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
