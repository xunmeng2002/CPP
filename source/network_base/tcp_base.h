#ifndef __h_tcp_base_h__
#define __h_tcp_base_h__

#include "SocketInit.h"
#include "socket.h"
#include <vector>
#include <thread>
#include <mutex>
#include <string>


#define BUFFER_SIZE 10 * 1024 * 1024

#define SOCKET_CLOSE 1


class ITcpCallback
{
public:
	virtual void on_recv(Socket* socket, const char* data, int length) = 0;
};

class TcpBase
{
public:
	TcpBase(const char* ip_address, unsigned int port, int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, long micro_seconds = 1000000);
	virtual ~TcpBase();

	void register_callback(ITcpCallback* tcp_callback);

	virtual bool start() = 0;
	virtual void stop() = 0;

	void join();

	static void thread_func(TcpBase* tcp_base);

	virtual void run() = 0;

	void post_event(int event_id);

protected:
	Socket* m_socket;
	SOCKET m_socket_id;

	bool m_run_status;
	std::string m_ip_address;
	int m_port;
	int m_af;
	int m_type;
	int m_protocol;
	ITcpCallback* m_tcp_callback;

	fd_set m_recv_fds;
	fd_set m_send_fds;
	timeval m_time_out;

	char* m_send_cache_buffer;
	char* m_recv_cache_buffer;

	std::mutex m_mutex;
	std::thread m_thread;
	std::vector<int> m_events;
};


#endif
