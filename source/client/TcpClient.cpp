#include "TcpClient.h"
#include <iostream>

using namespace std;

#define BUFFER_SIZE 64 * 1024

TcpClient::TcpClient(const char* ip_address, unsigned int port, int af, int type, int protocol, long micro_seconds)
	:TcpBase(ip_address, port, af, type, protocol, micro_seconds)
{
	m_send_cache_manager = new CacheManager();
}

TcpClient::~TcpClient()
{
	if (m_socket)
	{
		delete m_socket;
	}
	m_socket = nullptr;

	delete m_send_cache_manager;
}


bool TcpClient::start()
{
	m_socket = new Socket();
	m_socket_id = m_socket->get_sock_id();

	unsigned long on_windows = 1;
	int ret = m_socket->ioctl(FIONBIO, &on_windows);
	if (ret < 0)
	{
		cout << "call ioctlsocket failed. return code = " << ret << endl;
		return false;
	}

	char flag = 1;
	ret = m_socket->set_sock_opt(IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));
	if (ret < 0)
	{
		cout << "call setsockopt failed. return code = " << ret << endl;
		return false;
	}
	
	ret = m_socket->connect(m_ip_address.c_str(), m_port);

	FD_ZERO(&m_send_fds);
	FD_SET(m_socket->get_sock_id(), &m_send_fds);
	ret = select(0, nullptr, &m_send_fds, nullptr, &m_time_out);
	if (ret > 0)
	{
		cout << "connected socket:" << m_socket->get_sock_id() << endl;
	}
	else if (ret <= 0)
	{
		cout << "connect failed return code = " << ret << endl;
		delete m_socket;
		return false;
	}

	m_run_status = true;
	m_thread = thread(thread_func, this);
	return true;
}

void TcpClient::stop()
{
	post_event(SOCKET_CLOSE);
}

int TcpClient::send(const char* data, int length, int flags)
{
	return m_send_cache_manager->push_back(data, length);
}

int TcpClient::recv(char* data, int length, int flags)
{
	return m_socket->recv(data, length, flags);
}

void TcpClient::run()
{
	while (m_run_status)
	{
		if (m_run_status)
		{
			prepare_fds();

			int ret =::select(m_socket_id + 1, &m_recv_fds, &m_send_fds, nullptr, &m_time_out);

			if (FD_ISSET(m_socket_id, &m_recv_fds))
			{
				::memset(m_recv_cache_buffer, 0, BUFFER_SIZE);
				int len = recv(m_recv_cache_buffer, BUFFER_SIZE);
				if (len > 0)
				{
					m_tcp_callback->on_recv(m_socket, m_recv_cache_buffer, len);
				}
				else
				{
					cout << "Recv Length = " << len << endl;
					stop();
				}
			}

			if (FD_ISSET(m_socket_id, &m_send_fds))
			{
				int len = m_send_cache_manager->get_length();
				auto data = m_send_cache_manager->get_curr_read();
				int send_len = m_socket->send(data, len, 0);
				if (send_len > 0)
				{
					m_send_cache_manager->pop_front(m_send_cache_buffer, send_len);
				}
				else
				{
					cout << "Send Length = " << len << endl;
					stop();
				}
			}
		}

		handle_events();
	}

	cout << "Tcp Client Thread Exit!" << endl;
}

void TcpClient::prepare_fds()
{
	FD_ZERO(&m_send_fds);
	FD_ZERO(&m_recv_fds);
	if (!m_send_cache_manager->is_empty())
	{
		FD_SET(m_socket_id, &m_send_fds);
	}
	FD_SET(m_socket_id, &m_recv_fds);
}

void TcpClient::handle_events()
{
	std::lock_guard<std::mutex> gurad(m_mutex);
	if (m_events.empty())
	{
		return;
	}
	for (auto event_id : m_events)
	{
		switch (event_id)
		{
		case SOCKET_CLOSE:
		{
			if (m_socket)
			{
				delete m_socket;
				m_socket = nullptr;
			}
			m_run_status = false;
		}
			break;
		}
	}
}
