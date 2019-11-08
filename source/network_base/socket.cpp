#include "socket.h"
#include <WS2tcpip.h>
#include <iostream>
using namespace std;

Socket::Socket(int af, int type, int protocol)
	:m_af(af), m_type(type), m_protocol(protocol)
{
	m_socket_id = socket(af, type, protocol);
}

Socket::Socket(const SOCKET& socket_id, int af, int type, int protocol)
	: m_af(af), m_type(type), m_protocol(protocol)
{
	m_socket_id = socket_id;
}

Socket::Socket(Socket&& socket)
{
	m_socket_id = socket.m_socket_id;
	m_af = socket.m_af;
	m_type = socket.m_type;
	m_protocol = socket.m_protocol;

	m_peer_address = std::move(socket.m_peer_address);
}

Socket& Socket::operator=(Socket&& socket)
{
	m_socket_id = socket.m_socket_id;
	m_af = socket.m_af;
	m_type = socket.m_type;
	m_protocol = socket.m_protocol;

	m_peer_address = std::move(socket.m_peer_address);

	socket.m_socket_id = -1;
	return *this;
}

Socket::~Socket()
{
	::closesocket(m_socket_id);
}

SOCKET Socket::get_sock_id()
{
	return m_socket_id;
}

int Socket::bind(int port)
{
	sockaddr_in m_sock_addr;
	memset(&m_sock_addr, 0, sizeof(m_sock_addr));
	m_sock_addr.sin_family = m_af;
	//::inet_pton(m_af, "127.0.0.1", &m_sock_addr.sin_addr);
	//m_sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	m_sock_addr.sin_port = htons(port);
	return ::bind(m_socket_id, (sockaddr*)&m_sock_addr, sizeof(m_sock_addr));
}

int Socket::listen(int back_log)
{
	return ::listen(m_socket_id, back_log);
}

Socket* Socket::accept()
{
	sockaddr_in client_addr;
	int addr_len = sizeof(client_addr);
	SOCKET client_socket = ::accept(m_socket_id, (sockaddr*)&client_addr, &addr_len);
	Socket* socket = new Socket(client_socket);
	

	socket->set_peer_address(client_addr);
	cout << "accept addr:" << get_peer_name() << "\tport:" << ntohs(client_addr.sin_port) << endl;
	return socket;
}

int Socket::connect(const char* ip, unsigned int port)
{
	set_peer_address(ip, port);
	return ::connect(m_socket_id, (sockaddr*)&m_peer_address, sizeof(m_peer_address));
}

int Socket::recv(char* data, int len, int flags)
{
	return ::recv(m_socket_id, data, len, flags);
}

int Socket::send(const char* data, int len, int flags)
{
	return ::send(m_socket_id, data, len, flags);
}

int Socket::send_all(const char* data, int len, int flags)
{
	int total_send_len = 0;
	while (total_send_len < len)
	{
		int send_len = ::send(m_socket_id, data + total_send_len, len - total_send_len, flags);
		if (send_len <= 0)
		{
			cout << "send data error: send_len = " << send_len << endl;
			return send_len;
		}
		total_send_len += send_len;
	}
	return total_send_len;
}

int Socket::recv_from(char* data, int len, int flags, sockaddr* from_addr, int* from_len)
{
	return ::recvfrom(m_socket_id, data, len, flags, from_addr, from_len);
}

int Socket::send_to(const char* data, int len, int flags, const sockaddr* to_addr, int to_len)
{
	return ::sendto(m_socket_id, data, len, flags, to_addr, to_len);
}

void Socket::set_peer_address(const sockaddr_in& peer_address)
{
	::memcpy(&m_peer_address, &peer_address, sizeof(peer_address));
}

void Socket::set_peer_address(const char* ip, unsigned int port)
{
	::memset(&m_peer_address, 0, sizeof(m_peer_address));
	m_peer_address.sin_family = m_af;
	::inet_pton(m_af, ip, &m_peer_address.sin_addr);
	m_peer_address.sin_port = htons(port);
}

const char* Socket::get_peer_name()
{
	return ::inet_ntop(m_af, &m_peer_address.sin_addr, m_peer_ip, 20);
}

const char* Socket::get_sock_name()
{
	return "localhost";
}

int Socket::get_sock_opt(int level, int optname, char* optval, int* optlen)
{
	return ::getsockopt(m_socket_id, level, optname, optval, optlen);
}

int Socket::set_sock_opt(int level, int optname, const char* optval, int optlen)
{
	return ::setsockopt(m_socket_id, level, optname, optval, optlen);
}

int Socket::shut_down(int how)
{
	return ::shutdown(m_socket_id, how);
}

int Socket::close() 
{
	return ::closesocket(m_socket_id);
}

int Socket::ioctl(long cmd, unsigned long* argp)
{
	return ::ioctlsocket(m_socket_id, cmd, argp);
}

int Socket::set_blocking(unsigned long* flag)
{
	return ::ioctlsocket(m_socket_id, FIONBIO, flag);
}
