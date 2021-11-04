#include "Logger.h"
#include "TcpClient.h"
#include "Udp.h"
#include "TcpClientSelect.h"
#include <iostream>

using namespace std;

void UdpTest()
{
	Udp::GetInstance().SetBindAddress();
	Udp::GetInstance().SetRemoteAddress("127.0.0.1", 6000);
	Udp::GetInstance().Init(true);

	while (true)
	{
		TcpEvent* tcpEvent = TcpEvent::Allocate();
		cin >> tcpEvent->Buff;
		tcpEvent->Length = strlen(tcpEvent->Buff) + 1;
		Udp::GetInstance().ZipSendTo(tcpEvent);
		tcpEvent->Free();
	}
}


int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();
	UdpTest();
	//UdpClientTest();
	//TcpClientTest();
	//TcpClientSelectTest();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}