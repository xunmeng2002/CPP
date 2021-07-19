#include "CacheLoop.h"
#include <string.h>
#include<algorithm>

CacheLoop::CacheLoop(int block_size)
	:m_BlockSize(block_size), m_Length(0)
{
	m_Front = new char[block_size];
	m_End = m_Front + block_size;

	m_Read = m_Front;
	m_Write = m_Front;
}
CacheLoop::~CacheLoop()
{
	delete[] m_Front;
}

int CacheLoop::PushBack(const char* data, int len)
{
	std::lock_guard<std::mutex> gurad(m_Mutex);
	if (len <= 0 || m_BlockSize - m_Length <= 0)
		return 0;

	if (len > m_BlockSize - m_Length)
		len = m_BlockSize - m_Length;

	m_Length += len;
	if (m_End - m_Write >= len)
	{
		::memcpy(m_Write, data, len);
		m_Write += len;
	}
	else if (m_End - m_Write == len)
	{
		::memcpy(m_Write, data, len);
		m_Write = m_Front;
	}
	else
	{
		auto len1 = m_End - m_Write;
		auto len2 = len - len1;
		::memcpy(m_Write, data, len1);
		::memcpy(m_Front, data + len1, len2);
		m_Write = m_Front + len2;
	}
	return len;
}

int CacheLoop::PopFront(int len)
{
	std::lock_guard<std::mutex> gurad(m_Mutex);
	if (len <= 0 || m_Length <= 0)
		return 0;
	len = std::min(len, m_Length);

	m_Length -= len;
	if (m_End - m_Read > len)
	{
		m_Read += len;
	}
	else if (m_End - m_Read == len)
	{
		m_Read = m_Front;
	}
	else
	{
		m_Read = m_Front + len - (m_End - m_Read);
	}
	return len;
}

const char* CacheLoop::GetData(int& len)
{
	std::lock_guard<std::mutex> gurad(m_Mutex);
	len = std::min(m_Length, int(m_End - m_Read));
	return m_Read; 
}

int CacheLoop::Length()
{
	std::lock_guard<std::mutex> gurad(m_Mutex);
	return m_Length;
}

bool CacheLoop::IsEmpty()
{
	std::lock_guard<std::mutex> gurad(m_Mutex);
	return m_Length == 0;
}