#include <list>
#include <mutex>
#include "SocketDataStruct.h"
#include "Logger.h"
#pragma once
using namespace std;


template <typename T>
class MemCacheTemplate
{
private:
	MemCacheTemplate()
	{
	}
	~MemCacheTemplate()
	{
		for (auto item : m_Items)
		{
			delete item;
		}
		
		m_Items.clear();
	}
	MemCacheTemplate(MemCacheTemplate&) = delete;
	MemCacheTemplate& operator=(MemCacheTemplate&) = delete;
public:
	static MemCacheTemplate<T>& GetInstance()
	{
		return m_Instance;
	}
	void Init(int initNum = 64)
	{
		for (auto i = 0; i < initNum; i++)
		{
			m_Items.push_back(new T());
		}
	}

	T* Allocate()
	{
		lock_guard<mutex> guard(m_Mutex);
		if (!m_Items.empty())
		{
			auto item = m_Items.front();
			m_Items.pop_front();
			return item;
		}
		return new T();
	}
	void Free(T* item)
	{
		lock_guard<mutex> guard(m_Mutex);
		m_Items.push_back(item);
	}

private:
	static MemCacheTemplate<T> m_Instance;
	std::list<T*> m_Items;
	std::mutex m_Mutex;
};

template<typename T>
MemCacheTemplate<T> MemCacheTemplate<T>::m_Instance;