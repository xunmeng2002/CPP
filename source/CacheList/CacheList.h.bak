#ifndef CACHE_LIST_H
#define CACHE_LIST_H

#define NODE_BLOCK_SIZE 64 * 1024
#include <mutex>

class CacheNode
{
public:
	CacheNode(bool reverse, int blockSize = NODE_BLOCK_SIZE);
	~CacheNode();
	void Init();
	int PushFront(const void* data, int length);
	int PushBack(void* data, int length);
	int PopFront(void* data, int length);
	int PopBack(void* data, int length);
	void* GetData(int& length);
	bool IsEmpty();
	bool IsFrontFull();
	bool IsFull();
	void SetPrev(CacheNode* prev);
	void SetNext(CacheNode* next);
	CacheNode* GetPrev();
	CacheNode* GetNext();
	void Clear();

private:
	char* m_Head;
	char* m_End;
	char* m_Read;
	char* m_Write;
	int m_Length;
	int m_BlockSize;

	CacheNode* m_Prev;
	CacheNode* m_Next;
};

class CacheList
{
public:
	CacheList(int blockSize = NODE_BLOCK_SIZE);
	~CacheList();
	void PushFront(const void* data, int length);
	void PushBack(const void* data, int length);
	bool PopFront(void* data, int length);
	bool PopBack(void* data, int length);
	void* GetData(int& length);
	int GetLength();
	bool IsEmpty();
	void Clear();

private:
	void PopFrontNode();
	void AddHeadNode();
	void AddTailNode();

private:
	int m_BlockSize;
	int m_Length;
	CacheNode* m_Head;
	CacheNode* m_Tail;
	CacheNode* m_Write;

	std::mutex m_Mutex;
};

#endif
