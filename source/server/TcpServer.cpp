#include "TcpServer.h"
#include <iostream>
using namespace std;

#define BUFFER_SIZE 64 * 1024

TcpServer::TcpServer(const char* ip_address, int port, int af, int type, int protocol, long micro_seconds)
	:TcpBase(ip_address, port, af, type, protocol, micro_seconds)
{
	
}

TcpServer::~TcpServer()
{
	if (m_socket)
	{
		delete m_socket;
	}
	m_socket = nullptr;
}

bool TcpServer::start()
{
	m_socket = new Socket();
	m_socket_id = m_socket->get_sock_id();
	
	unsigned long on_windows = 1;
	int ret = m_socket->ioctl(FIONBIO, &on_windows);
	if (ret < 0)
	{
		print_error("ioctlsocket failed.", ret);
		return false;
	}

	char flag = 1;
	ret = m_socket->bind(m_port);
	if (ret < 0)
	{
		print_error("bind failed.", ret);
		return false;
	}

	ret = m_socket->listen(5);
	if (ret < 0)
	{
		print_error("listen failed.", ret);
		return false;
	}
	m_run_status = true;
	m_thread = std::thread(thread_func, this);
	return true;
}

void TcpServer::stop()
{
	post_event(SOCKET_CLOSE);
}

void TcpServer::print_error(const char* message, int error_code)
{
	cout << message << "\terror_code:" << error_code << endl;
}

void TcpServer::run()
{
	while (m_run_status)
	{
		prepare_fds();
		::select(0, &m_recv_fds, &m_send_fds, nullptr, &m_time_out);
		
		accept();

		recv();
		
		send();
		
		handle_events();

		close_invalid_socket();
	}
}

void TcpServer::prepare_fds()
{
	FD_ZERO(&m_recv_fds);
	FD_ZERO(&m_send_fds);
	FD_SET(m_socket_id, &m_recv_fds);

	for (auto& it : m_send_cache_manager_map)
	{
		auto socket_id = it.first->get_sock_id();
		FD_SET(socket_id, &m_recv_fds);
		if (!it.second->is_empty())
		{
			FD_SET(socket_id, &m_send_fds);
		}
	}
}

void TcpServer::accept()
{
	if (FD_ISSET(m_socket_id, &m_recv_fds))
	{
		Socket* client_socket = m_socket->accept();
		cout << "accept socket:" << client_socket->get_sock_id() << endl;

		int flag = 1;
		int ret = client_socket->set_sock_opt(IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag));
		cout << "Set_sock_opt return code : " << ret << endl;

		CacheManager* cache_manager = new CacheManager();
		m_send_cache_manager_map.insert(make_pair(client_socket, cache_manager));
	}
}

void TcpServer::recv()
{
	for (auto& it : m_send_cache_manager_map)
	{
		auto socket = it.first;
		if (FD_ISSET(socket->get_sock_id(), &m_recv_fds))
		{
			::memset(m_recv_cache_buffer, 0, BUFFER_SIZE);
			int len = socket->recv(m_recv_cache_buffer, BUFFER_SIZE, 0);
			if (len > 0)
			{
				m_tcp_callback->on_recv(socket, m_recv_cache_buffer, len);
			}
			else
			{
				m_invalid_sockets.insert(socket);
			}
		}
	}
}

void TcpServer::send()
{
	for (auto& it : m_send_cache_manager_map)
	{
		auto socket = it.first;
		auto cache_manager = it.second;
		if (!cache_manager->is_empty() && FD_ISSET(socket->get_sock_id(), &m_send_fds))
		{
			int len = cache_manager->get_length();
			auto data = cache_manager->get_curr_read();
			int send_len = socket->send(data, len, 0);
			if (send_len > 0)
			{
				cache_manager->pop_front(m_send_cache_buffer, send_len);
			}
			else
			{
				m_invalid_sockets.insert(socket);
			}
		}
	}
}

void TcpServer::handle_events()
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
			::closesocket(m_socket_id);
			m_run_status = false;
			for (auto& it : m_send_cache_manager_map)
			{
				m_invalid_sockets.insert(it.first);
			}
		}
		default:
			break;
		}
	}
}

void TcpServer::close_invalid_socket()
{
	for (auto socket : m_invalid_sockets)
	{
		cout << "disconnected socket:" << socket->get_sock_id() << endl;
		auto cache_manager = m_send_cache_manager_map[socket];
		delete cache_manager;
		m_send_cache_manager_map.erase(socket);
		delete socket;
	}
	m_invalid_sockets.clear();
}