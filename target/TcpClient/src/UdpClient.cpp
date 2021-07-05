#include <stdio.h>
#include <iostream>
#include "UdpClient.h"
#include "SocketInit.h"


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
		printf("retSend[%d], retRecv[%d]\n", retSend, retRecv);
		printf("recv from [%s:%u]: [%s]\n", inet_ntoa(addrSrv.sin_addr), ntohs(addrSrv.sin_port), recvBuf);


		if (strcmp(recvBuf, "quit") == 0)
		{
			break;
		}
	}
	closesocket(sockSrv);
}