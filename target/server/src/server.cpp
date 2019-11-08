#include <iostream>
#include <vector>
#include "TcpServer.h"

using namespace std;

#define IP_ADDRESS "127.0.0.1"
#define PORT 10010

class TcpCallback : public ITcpCallback
{
public:
	virtual void on_recv(Socket* socket, const char* data, int length)
	{
		cout << "on_recv length : " << length << "\tdata : " << data << endl;
		std::string rsp_msg = "server recv data = " + std::string(data);
		socket->send(rsp_msg.c_str(), rsp_msg.length(), 0);
	}
};

int main()
{
	TcpCallback tcp_callback;
	TcpServer tcp_server("127.0.0.1", PORT);
	tcp_server.register_callback(&tcp_callback);
	tcp_server.start();
	tcp_server.join();
}

//int main()
//{
//	sockaddr_in server_addr, client_addr;
//
//	SOCKET severScoket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (severScoket == INVALID_SOCKET)
//	{
//		cout << "creat failed" << GetLastError() << endl;
//		return -1;
//	}
//
//	unsigned long on_windows = 1;
//	int ret = ::ioctlsocket(severScoket, FIONBIO, &on_windows);
//	cout << "return code from ioctlsocket: " << ret << endl;
//
//	server_addr.sin_family = AF_INET;
//	server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
//	server_addr.sin_port = htons(PORT);
//	memset(server_addr.sin_zero, 0x00, 8);
//
//	ret = ::bind(severScoket, (sockaddr*)&server_addr, sizeof(sockaddr_in));
//	cout << "return code from bind: " << ret << endl;
//
//	ret = ::listen(severScoket, 5);
//	cout << "return code from listen: " << ret << endl;
//
//	int max_sock = severScoket;
//	vector<SOCKET> client_sock_vec;
//	while (true)
//	{
//		int addr_len = sizeof(sockaddr_in);
//		fd_set read_fds, write_fds;
//		FD_ZERO(&read_fds);
//		FD_ZERO(&write_fds);
//		for (auto client_sock : client_sock_vec)
//		{
//			if (client_sock > 0)
//			{
//				FD_SET(client_sock, &read_fds);
//				FD_SET(client_sock, &read_fds);
//				max_sock = (max_sock < client_sock) ? client_sock : max_sock;
//			}
//		}
//
//		::select(0, &read_fds, &write_fds, nullptr, nullptr);
//		SOCKET clientScoket = ::accept(severScoket, (sockaddr*)&client_addr, &addr_len);
//		if (clientScoket == INVALID_SOCKET)
//		{
//			cout << "accept failed";
//			break;
//		}
//		cout << "客户端连接" << inet_ntoa(client_addr.sin_addr) << ":" << htons(client_addr.sin_port) << endl;
//
//		while (true)
//		{
//			char RecvBuff[1024] = { 0 };
//			int ret = ::recv(clientScoket, RecvBuff, sizeof(RecvBuff), 0);
//			cout << "return code from recv: " << ret << endl;
//			if (ret == 0 || ret == SOCKET_ERROR)
//			{
//				cout << "failed exit!" << endl;
//				break;
//			}
//			cout << "接受的消息为：" << RecvBuff << endl;
//			std::string send_message = "收到消息：" + std::string(RecvBuff);
//			ret =::send(clientScoket, send_message.c_str(), send_message.length(), 0);
//			cout << "return code from send: " << ret << endl;
//		}
//
//		closesocket(clientScoket);
//	}
//	closesocket(severScoket);
//	WSACleanup();
//
//	return 0;
//}