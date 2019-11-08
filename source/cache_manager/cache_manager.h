#ifndef __h_cache_manager_h__
#define __h_cache_manager_h__

#include <mutex>

#define BLOCK_SIZE 10 * 1024 * 1024

class CacheManager
{
public:
	CacheManager(int block_size = BLOCK_SIZE);
	~CacheManager();

	int push_back(const char* data, int length);

	int pop_front(char* data, int length);

	const char* get_curr_read();

	int get_length();

	bool is_empty();
private:
	int m_block_size;
	int m_length;
	char* m_front;
	char* m_end;
	char* m_read;
	char* m_write;

	std::mutex m_mutex;
};

#endif