#include "SocketMemCache.h"

using namespace std;

SocketMemCache::SocketMemCache()
	:m_Family(AF_INET)
{
	
}
SocketMemCache::~SocketMemCache()
{
	for (auto& item : m_Items)
	{
		closesocket(item);
	}
	m_Items.clear();
}

void SocketMemCache::Init(int initNum, int family)
{
	m_Family = family;
	for (auto i = 0; i < initNum; i++)
	{
		auto socket = WSASocket(m_Family, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (socket == INVALID_SOCKET)
		{
			break;
		}
		m_Items.push_back(socket);
	}
}
SOCKET SocketMemCache::Allocate()
{
	if (!m_Items.empty())
	{
		auto item = m_Items.front();
		m_Items.pop_front();
		return item;
	}
	return WSASocket(m_Family, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
}
void SocketMemCache::Free(SOCKET socket)
{
	m_Items.push_back(socket);
}