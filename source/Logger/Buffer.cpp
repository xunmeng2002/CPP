#include "Buffer.h"
#include <memory>

#define LOG_BUFFER_SIZE 10 * 1024 * 1024

using namespace std;

Buffer::Buffer()
{
	m_Buffer = new char[LOG_BUFFER_SIZE];
	m_BufferSize = LOG_BUFFER_SIZE;
	m_Length = 0;
}
Buffer::~Buffer()
{
	delete[] m_Buffer;
}
void Buffer::Append(const void* data, int len)
{
	::memcpy(m_Buffer + m_Length, data, len);
	m_Length += len;
}
const char* Buffer::GetData()
{
	return m_Buffer;
}
int Buffer::Length()
{
	return m_Length;
}
int Buffer::Available()
{
	return m_BufferSize - m_Length;
}
void Buffer::Reset()
{
	m_Length = 0;
}