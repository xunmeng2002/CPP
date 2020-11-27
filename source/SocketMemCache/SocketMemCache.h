#include <WinSock2.h>
#include <list>
#include <mutex>

#pragma once
class SocketMemCache
{
public:
	SocketMemCache();
	~SocketMemCache();
	SocketMemCache(SocketMemCache&) = delete;
	SocketMemCache& operator=(SocketMemCache&) = delete;

	void Init(int initNum = 64, int family = AF_INET);

	SOCKET Allocate();
	void Free(SOCKET socket);

private:
	std::list<SOCKET> m_Items;

	int m_Family;
};

