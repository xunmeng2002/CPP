#include "Logger.h"
#include "Udp.h"
#include "TcpServer.h"
#include "TcpServerSelect.h"

using namespace std;

void UdpTest()
{
	Udp::GetInstance().SetBindAddress("127.0.0.1", 6000);
	if (!Udp::GetInstance().Init(false))
	{
		return;
	}

	while (true)
	{
		TcpEvent* tcpEvent = TcpEvent::Allocate();
		Udp::GetInstance().ZipRecvFrom(tcpEvent);
		tcpEvent->Free();
	}
}


int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();
	UdpTest();
	//UdpServerTest();
	//TcpServerTest();
	//TcpServerSelectTest();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}