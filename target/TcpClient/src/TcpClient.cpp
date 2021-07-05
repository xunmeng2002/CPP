#include <stdio.h>
#include <iostream>
#include "TcpClient.h"
#include "SocketInit.h"

using namespace std;


void TcpClientTest()
{
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in  addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	int ret = connect(sockClient, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	printf("Connect Server: ret[%d]\n", ret);
	if (ret == SOCKET_ERROR)
	{
		closesocket(sockClient);
		return;
	}
	

	char recvBuf[1024];
	char sendBuf[1024];
	int retSend, retRecv;
	while(true)
	{
		printf("Please input data:");
		cin >> sendBuf;
		retSend = send(sockClient, sendBuf, strlen(sendBuf), 0);
		
		retRecv = recv(sockClient, recvBuf, 1023, 0);
		if (retRecv < 1024)
		{
			recvBuf[retRecv] = '\0';
		}
		
		printf("retSend[%d], retRecv[%d]\n", retSend, retRecv);
		printf("recv: [%s]\n", recvBuf);
		
		
		if (strcmp(recvBuf, "quit") == 0)
		{
			break;
		}
	}
	closesocket(sockClient);
}