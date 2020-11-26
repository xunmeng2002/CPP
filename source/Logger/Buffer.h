#pragma once


class Buffer
{
public:
	Buffer();
	~Buffer();
	void Append(const void* data, int len);
	const char* GetData();
	int Length();
	int Available();
	void Reset();

private:
	char* m_Buffer;
	int m_BufferSize;
	int m_Length;
};

