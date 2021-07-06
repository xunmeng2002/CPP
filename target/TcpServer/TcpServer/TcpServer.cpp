#include <stdio.h>
#include <iostream>
#include "TcpServer.h"
#include "SocketInit.h"
#include "Logger.h"

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
	WRITE_LOG(LogLevel::Info, "bind: ret[%d]", ret);
	if (ret == SOCKET_ERROR)
	{
		return;
	}
	listen(sockServer, SOMAXCONN);

	SOCKET sockConnect = accept(sockServer, (struct sockaddr*)&addrClient, &addrLen);
	WRITE_LOG(LogLevel::Info, "accept: sockConnect[%lld] [%s:%u]", sockConnect, inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));

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
		
		WRITE_LOG(LogLevel::Info, "retSend[%d], retRecv[%d]", retSend, retRecv);
		WRITE_LOG(LogLevel::Info, "recv: [%s]", buff);
		
		
		if (strcmp(buff, "quit") == 0)
		{
			break;
		}
	}
	closesocket(sockServer);
}