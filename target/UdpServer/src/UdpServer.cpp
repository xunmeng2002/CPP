#include <Winsock2.h>
#include <stdio.h>
#include <iostream>


using namespace std;


void main()
{
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	char recvBuf[1024];
	char sendBuf[1024];

	printf("Udp Server Start.\n");
	while (true)
	{
		recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &len);
		printf("recv from [%s:%u]: [%s]\n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port), recvBuf);
		sendto(sockSrv, recvBuf, strlen(recvBuf) + 1, 0, (SOCKADDR*)&addrClient, len);
		
		if (strcmp(recvBuf, "quit") == 0)
		{
			break;
		}
	}
	closesocket(sockSrv);
}