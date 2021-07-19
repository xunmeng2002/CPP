#ifndef __h_cache_manager_h__
#define __h_cache_manager_h__

#include <mutex>

#define BLOCK_SIZE 10 * 1024 * 1024

class CacheLoop
{
public:
	CacheLoop(int block_size = BLOCK_SIZE);
	~CacheLoop();

	int PushBack(const char* data, int len);

	int PopFront(int len);

	const char* GetData(int& len);

	int Length();

	bool IsEmpty();
private:
	int m_BlockSize;
	int m_Length;
	char* m_Front;
	char* m_End;
	char* m_Read;
	char* m_Write;

	std::mutex m_Mutex;
};

#endif