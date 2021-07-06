#include <stdio.h>
#include <iostream>
#include "UdpServer.h"
#include "SocketInit.h"
#include "Logger.h"

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
	WRITE_LOG(LogLevel::Info, "bind: ret[%d]", ret);
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

		WRITE_LOG(LogLevel::Info, "retSend[%d], retRecv[%d]", retSend, retRecv);
		WRITE_LOG(LogLevel::Info, "recv from [%s:%u]: [%s]", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port), buff);

		if (strcmp(buff, "quit") == 0)
		{
			break;
		}
	}
	closesocket(sockSrv);
}