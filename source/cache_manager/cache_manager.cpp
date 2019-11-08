#include "cache_manager.h"
#include <string.h>
#include<algorithm>

CacheManager::CacheManager(int block_size)
	:m_block_size(block_size), m_length(0)
{
	m_front = new char[block_size];
	m_end = m_front + block_size;

	m_read = m_front;
	m_write = m_front;
}
CacheManager::~CacheManager()
{
	delete[] m_front;
}

int CacheManager::push_back(const char* data, int length)
{
	std::lock_guard<std::mutex> gurad(m_mutex);
	if (length <= 0 || m_block_size - m_length <= 0)
		return 0;

	if (length > m_block_size - m_length)
		length = m_block_size - m_length;

	m_length += length;
	if (m_write < m_read || (m_write >= m_read && m_end - m_write > length))
	{
		::memcpy(m_write, data, length);
		m_write += length;
	}
	else
	{
		auto len1 = m_end - m_write;
		auto len2 = length - len1;
		::memcpy(m_write, data, len1);
		::memcpy(m_front, data + len1, len2);
		m_write = m_front + len2;
	}
	return length;
}

int CacheManager::pop_front(char* data, int length)
{
	std::lock_guard<std::mutex> gurad(m_mutex);
	if (length <= 0 || m_length <= 0)
		return 0;
	length = std::min(length, m_length);

	m_length -= length;
	if (m_read < m_write || (m_read >= m_write && m_end - m_read > length))
	{
		::memcpy(data, m_read, length);
		m_read += length;
	}
	else
	{
		auto len1 = m_end - m_read;
		auto len2 = length = len1;
		::memcpy(data, m_read, len1);
		::memcpy(data + len1, m_front, len2);
		m_read = m_front + len2;
	}
	return length;
}

const char* CacheManager::get_curr_read()
{
	std::lock_guard<std::mutex> gurad(m_mutex);
	return m_read; 
}

int CacheManager::get_length()
{
	std::lock_guard<std::mutex> gurad(m_mutex);
	return std::min(m_length, (m_end - m_read));
}

bool CacheManager::is_empty()
{
	std::lock_guard<std::mutex> gurad(m_mutex);
	return m_length == 0;
}