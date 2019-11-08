#ifndef __h_socket_h__
#define __h_socket_h__

#include "SocketInit.h"
#include <string>


class Socket
{
public:
	Socket(int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
	Socket(const SOCKET& socket, int af = AF_INET, int type = SOCK_STREAM, int protocol = 0);
	Socket(const Socket&) = delete;
	Socket& operator=(const Socket&) = delete;
	Socket(Socket&& socket);
	Socket& operator=(Socket&& socket);
	~Socket();

	SOCKET get_sock_id();

	int bind(int port);

	int listen(int back_log = 5);

	Socket* accept();

	int connect(const char* ip_address, unsigned int port);

	int recv(char* data, int length, int flags);

	int send(const char* data, int length, int flags);

	int send_all(const char* data, int length, int flags);

	int recv_from(char* data, int length, int flags, sockaddr* from_addr, int* from_len);

	int send_to(const char* data, int length, int flags, const sockaddr* to_addr, int to_len);

	void set_peer_address(const sockaddr_in& peer_address);

	void set_peer_address(const char* ip, unsigned int port);

	const char* get_peer_name();

	const char* get_sock_name();

	int get_sock_opt(int level, int optname, char* optval, int* optlen);

	int set_sock_opt(int level, int optname, const char* optval, int optlen);

	int shut_down(int how);

	int close();

	int ioctl(long cmd, unsigned long* argp);

	int set_blocking(unsigned long* flag);

protected:
	SOCKET m_socket_id;
	int m_af;
	int m_type;
	int m_protocol;
	sockaddr_in m_peer_address;
	char m_peer_ip[20];
};


#endif
