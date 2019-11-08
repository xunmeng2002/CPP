#ifndef __h_tcp_server_h__
#define __h_tcp_server_h__

#include "SocketInit.h"
#include "socket.h"
#include "tcp_base.h"
#include "cache_manager.h"
#include <set>
#include <map>


class TcpServer : public TcpBase
{
public:
	TcpServer(const char* ip_address, int port, int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, long micro_seconds = 1000000);
	virtual ~TcpServer();

	virtual bool start();

	virtual void stop();

	void print_error(const char* message, int error_code);

	virtual void run();

	void prepare_fds();

	void accept();

	void recv();

	void send();

	void handle_events();

	void close_invalid_socket();

private:
	std::set<Socket*> m_invalid_sockets;
	std::map<Socket*, CacheManager*> m_send_cache_manager_map;
};

#endif