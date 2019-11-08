#include <iostream>
#include "TcpClient.h"

using namespace std;

#define IP_ADDRESS "127.0.0.1"
#define PORT 10010

class TcpCallback : public ITcpCallback
{
public:
	virtual void on_recv(Socket* socket, const char* data, int length)
	{
		cout << "on_recv length : " << length << "\tdata : " << data << endl;
	}
};

int main()
{
	TcpCallback tcp_callback;
	TcpClient tcp_client(IP_ADDRESS, PORT);
	tcp_client.register_callback(&tcp_callback);
	tcp_client.start();
	tcp_client.send("hello world", 100);

	char send_buffer[1024];
	while (true)
	{
		::memset(send_buffer, 0, 1024);
		cin.getline(send_buffer, 1024);
		if (strcmp(send_buffer, "exit") == 0)
		{
			tcp_client.send("Bye bye.", 20, 0);
			break;
		}
		else
		{
			tcp_client.send(send_buffer, strlen(send_buffer));
		}
	}
	tcp_client.stop();
	tcp_client.join();
	cout << "----------------End----------------" << endl;
}
