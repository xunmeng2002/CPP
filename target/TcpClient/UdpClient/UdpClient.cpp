#include <stdio.h>
#include <iostream>
#include "UdpClient.h"
#include "SocketInit.h"
#include "Logger.h"


using namespace std;


void UdpClientTest()
{
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in  addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	int addrLen = sizeof(SOCKADDR);
	char recvBuf[1024];
	char sendBuf[1024];
	int retSend, retRecv;

	while (true)
	{
		printf("Please input data:");
		cin >> sendBuf;
		retSend = sendto(sockSrv, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrSrv, addrLen);

		retRecv = recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrSrv, &addrLen);
		WRITE_LOG(LogLevel::Info, "retSend[%d], retRecv[%d]", retSend, retRecv);
		WRITE_LOG(LogLevel::Info, "recv from [%s:%u]: [%s]", inet_ntoa(addrSrv.sin_addr), ntohs(addrSrv.sin_port), recvBuf);


		if (strcmp(recvBuf, "quit") == 0)
		{
			break;
		}
	}
	closesocket(sockSrv);
}