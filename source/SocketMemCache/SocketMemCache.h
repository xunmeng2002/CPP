#include <WinSock2.h>
#include <list>
#include <mutex>

#pragma once
class SocketMemCache
{
private:
	SocketMemCache();
	~SocketMemCache();
	SocketMemCache(SocketMemCache&) = delete;
	SocketMemCache& operator=(SocketMemCache&) = delete;
public:
	static SocketMemCache& GetInstance();

	void Init(int initNum = 64, int family = AF_INET);

	SOCKET Allocate();
	void Free(SOCKET socket);

private:
	static SocketMemCache m_Instance;
	std::list<SOCKET> m_Items;
	std::mutex m_Mutex;

	int m_Family;
};

