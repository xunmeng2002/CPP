#include "tcp_base.h"

TcpBase::TcpBase(const char* ip_address, unsigned int port, int af, int type, int protocol, long micro_seconds)
	:m_ip_address(ip_address), m_port(port), m_af(af), m_type(type), m_protocol(protocol)
{
	m_time_out.tv_sec = micro_seconds / (1000000);
	m_time_out.tv_usec = micro_seconds % (1000000);

	m_run_status = false;

	m_send_cache_buffer = new char[BUFFER_SIZE];
	::memset(m_send_cache_buffer, 0, BUFFER_SIZE);

	m_recv_cache_buffer = new char[BUFFER_SIZE];
	::memset(m_recv_cache_buffer, 0, BUFFER_SIZE);
}

TcpBase::~TcpBase()
{
	delete[] m_send_cache_buffer;
	delete[] m_recv_cache_buffer;
}

void TcpBase::register_callback(ITcpCallback* tcp_callback)
{
	m_tcp_callback = tcp_callback;
}

void TcpBase::join()
{
	if (m_thread.joinable())
	{
		m_thread.join();
	}
}

void TcpBase::thread_func(TcpBase* tcp_base)
{
	tcp_base->run();
}


void TcpBase::post_event(int event_id)
{
	std::lock_guard<std::mutex> gurad(m_mutex);
	m_events.push_back(event_id);
}