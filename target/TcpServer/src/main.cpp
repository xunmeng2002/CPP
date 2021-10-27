#include "Logger.h"
#include "UdpServer.h"
#include "TcpServer.h"
#include "TcpServerSelect.h"

using namespace std;


int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();
	//UdpServerTest();
	TcpServerTest();
	//TcpServerSelectTest();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}