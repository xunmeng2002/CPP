#include <stdio.h>
#include <iostream>
#include "TcpServer.h"
#include "SocketInit.h"

using namespace std;


void TcpServerTest()
{
	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, 0);
	int addrLen = sizeof(SOCKADDR);
	sockaddr_in  addrSrv, addrClient;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	int ret = bind(sockServer, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	printf("bind: ret[%d]\n", ret);
	if (ret == SOCKET_ERROR)
	{
		return;
	}
	listen(sockServer, SOMAXCONN);

	SOCKET sockConnect = accept(sockServer, (struct sockaddr*)&addrClient, &addrLen);
	printf("accept: sockConnect[%lld] [%s:%u]\n", sockConnect, inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));

	char buff[1024];
	buff[1023] = '\0';
	int retSend, retRecv;
	while(true)
	{
		retRecv = recv(sockConnect, buff, 1023, 0);

		retSend = send(sockConnect, buff, retRecv, 0);
		
		if (retRecv < 1024)
		{
			buff[retRecv] = '\0';
		}
		
		printf("retSend[%d], retRecv[%d]\n", retSend, retRecv);
		printf("recv: [%s]\n", buff);
		
		
		if (strcmp(buff, "quit") == 0)
		{
			break;
		}
	}
	closesocket(sockServer);
}