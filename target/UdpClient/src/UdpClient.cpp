#include <Winsock2.h>
#include <stdio.h>
#include <iostream>


using namespace std;


void main()
{
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in  addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	int len = sizeof(SOCKADDR);
	char recvBuf[1024];
	char sendBuf[1024];

	while(true)
	{
		printf("Please input data:");
		cin >> sendBuf;
		sendto(sockSrv, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrSrv, len);
		
		recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrSrv, &len);
		printf("recv from [%s:%u]: [%s]\n", inet_ntoa(addrSrv.sin_addr), ntohs(addrSrv.sin_port), recvBuf);
		
		
		if (strcmp(recvBuf, "quit") == 0)
		{
			break;
		}
	}
	closesocket(sockSrv);
}