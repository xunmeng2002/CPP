#include "Logger.h"
#include "TcpClient.h"
#include "UdpClient.h"
#include "TcpClientSelect.h"

using namespace std;


int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();
	//UdpClientTest();
	TcpClientTest();
	//TcpClientSelectTest();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}