#ifndef __h_tcp_client_h__
#define __h_tcp_client_h__

#include "socket.h"
#include "tcp_base.h"
#include "cache_manager.h"
#include <string>
#include <mutex>
#include <thread>
#include <vector>

class TcpClient : public TcpBase
{
public:
	TcpClient(const char* ip_address, unsigned int port, int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP, long micro_seconds = 1000000);

	virtual ~TcpClient();

	virtual bool start();
	
	virtual void stop();

	virtual int send(const char* data, int length, int flags = 0);

	virtual int recv(char* data, int length, int flags = 0);

private:
	virtual void run();

	void prepare_fds();

	void handle_events();

private:
	CacheManager* m_send_cache_manager;
};

#endif