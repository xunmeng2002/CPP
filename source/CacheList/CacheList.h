#ifndef __CACHE_LIST_H__
#define __CACHE_LIST_H__

#define NODE_BLOCK_SIZE 1024
#include <mutex>

class CacheNode
{
public:
	CacheNode(int blockSize = NODE_BLOCK_SIZE);
	~CacheNode();
	int PushBack(void* data, int length);
	int PopFront(void* data, int length);
	void* GetRead();
	void* GetWrite();
	void* GetData(int& length);
	bool IsEmpty();
	bool IsFull();
	void SetNext(CacheNode* next);
	CacheNode* GetNext();
	void Clear();

private:
	char* m_Head;
	char* m_End;
	char* m_Read;
	char* m_Write;
	int m_Length;
	int m_BlockSize;

	CacheNode* m_Next;
};

class CacheList
{
public:
	CacheList(int blockSize = NODE_BLOCK_SIZE);
	~CacheList();
	void PushBack(const void* data, int length);
	bool PopFront(void* data, int length);
	void* GetData(int& length);
	int GetLength();
	bool IsEmpty();
	void Clear();

private:
	void PopFrontNode();
	void AddNewNode();

private:
	int m_BlockSize;
	int m_Length;
	CacheNode* m_HeadNode;
	CacheNode* m_TailNode;
	CacheNode* m_WriteNode;

	std::mutex m_Mutex;
};

#endif
