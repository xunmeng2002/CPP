#include <stdio.h>
#include <iostream>
#include "UdpServer.h"
#include "SocketInit.h"

using namespace std;


void UdpServerTest()
{
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	int addrLen = sizeof(SOCKADDR);
	SOCKADDR_IN addrSrv, addrClient;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	auto ret = bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	printf("bind: ret[%d]\n", ret);
	if (ret == SOCKET_ERROR)
	{
		return;
	}


	char buff[1024];
	buff[1023] = '\0';

	int retSend, retRecv;
	while (true)
	{
		retRecv = recvfrom(sockSrv, buff, 1023, 0, (SOCKADDR*)&addrClient, &addrLen);

		retSend = sendto(sockSrv, buff, retRecv, 0, (SOCKADDR*)&addrClient, addrLen);

		printf("retSend[%d], retRecv[%d]\n", retSend, retRecv);
		printf("recv from [%s:%u]: [%s]\n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port), buff);

		if (strcmp(buff, "quit") == 0)
		{
			break;
		}
	}
	closesocket(sockSrv);
}