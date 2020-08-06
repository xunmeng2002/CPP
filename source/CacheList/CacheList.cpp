#include "CacheList.h"
#include <algorithm>
#include <assert.h>
using namespace std;

CacheNode::CacheNode(bool reverse, int blockSize)
	:m_BlockSize(blockSize), m_Length(0), m_Prev(nullptr), m_Next(nullptr)
{
	m_Head = new char[blockSize];
	m_End = m_Head + blockSize;
	if (reverse)
	{
		m_Read = m_Write = m_End;
	}
	else
	{
		m_Read = m_Write = m_Head;
	}
}
CacheNode::~CacheNode()
{
	delete[] m_Head;
}
void CacheNode::Init()
{
	m_Read = m_Write = m_Head;
	m_Prev = nullptr;
	m_Next = nullptr;
	m_Length = 0;
}
int CacheNode::PushFront(const void* data, int length)
{
	int pushLen = min(length, (m_Read - m_Head));
	m_Read = m_Read - pushLen;
	m_Length += pushLen;
	::memcpy(m_Read, ((char*)data + (length - pushLen)), pushLen);
	return pushLen;
}
int CacheNode::PushBack(void* data, int length)
{
	int pushLen = min(length, (m_End - m_Write));
	::memcpy(m_Write, data, pushLen);
	m_Write += pushLen;
	m_Length += pushLen;
	return pushLen;
}
int CacheNode::PopFront(void* data, int length)
{
	int popLen = min(length, m_Length);
	if (data)
	{
		::memcpy(data, m_Read, popLen);
	}
	m_Read += popLen;
	m_Length -= popLen;
	return popLen;
}
int CacheNode::PopBack(void* data, int length)
{
	int popLen = min(length, m_Length);
	m_Write -= popLen;
	m_Length -= popLen;
	if (data)
	{
		::memcpy(((char*)data + (length - popLen)), m_Write, popLen);
	}
	return popLen;
}

void* CacheNode::GetData(int& length)
{
	length = m_Length;
	return m_Read;
}
bool CacheNode::IsEmpty()
{
	return m_Length == 0;
}
bool CacheNode::IsFrontFull()
{
	return m_Head == m_Read;
}
bool CacheNode::IsFull()
{
	return m_Write == m_End;
}
void CacheNode::SetPrev(CacheNode* prev)
{
	m_Prev = prev;
}
void CacheNode::SetNext(CacheNode* next)
{
	m_Next = next;
}
CacheNode* CacheNode::GetPrev()
{
	return m_Prev;
}
CacheNode* CacheNode::GetNext()
{
	return m_Next;
}
void CacheNode::Clear()
{
	m_Read = m_Write = m_Head;
	m_Length = 0;
}



CacheList::CacheList(int blockSize)
	:m_BlockSize(blockSize)
{
	m_Head = new CacheNode(false, m_BlockSize);
	m_Write = m_Tail = m_Head;
	m_Length = 0;
}
CacheList::~CacheList()
{
	CacheNode* cacheNode;
	while (m_Head)
	{
		cacheNode = m_Head;
		m_Head = m_Head->GetNext();
		delete cacheNode;
	}
}
void CacheList::PushFront(const void* data, int length)
{
	lock_guard<mutex> guard(m_Mutex);
	int pushLen = 0;
	while (pushLen < length)
	{
		if (m_Head->IsFrontFull())
		{
			AddHeadNode();
		}
		pushLen += m_Head->PushFront(data, length - pushLen);
	}
	m_Length += length;
}
void CacheList::PushBack(const void* data, int length)
{
	lock_guard<mutex> guard(m_Mutex);
	int pushLen = 0;
	while (pushLen < length)
	{
		pushLen += m_Write->PushBack((char*)data + pushLen, length - pushLen);
		if (m_Write->IsFull())
		{
			if (m_Write == m_Tail)
			{
				AddTailNode();
			}
			m_Write = m_Write->GetNext();
		}
	}
	m_Length += length;
}
bool CacheList::PopFront(void* data, int length)
{
	lock_guard<mutex> guard(m_Mutex);
	if (m_Length < length)
	{
		assert(false);
		return false;
	}
	int popLen = 0;
	while (popLen < length)
	{
		if (data)
		{
			popLen += m_Head->PopFront((char*)data + popLen, length - popLen);
		}
		else //用于GetData之后
		{
			popLen += m_Head->PopFront(nullptr, length - popLen);
		}
		if (m_Head->IsEmpty() && m_Write != m_Head && m_Head->GetNext())
		{
			PopFrontNode();
		}
		if (popLen < length)
		{
			if (m_Head->IsEmpty())
			{
				assert(false);
				m_Length -= popLen;
				return false;
			}
		}
	}
	m_Length -= length;
	return true;
}
bool CacheList::PopBack(void* data, int length)
{
	lock_guard<mutex> guard(m_Mutex);
	if (m_Length < length)
	{
		assert(false);
		return false;
	}
	int popLen = 0;
	while (popLen < length)
	{
		if (data)
		{
			popLen += m_Write->PopBack((char*)data, length - popLen);
		}
		else
		{
			popLen += m_Write->PopBack(nullptr, length - popLen);
		}

		if (m_Write->IsEmpty() && m_Write != m_Head)
		{
			m_Write = m_Write->GetPrev();
		}
	}
	m_Length -= length;
	return true;
}
void* CacheList::GetData(int& length)
{
	lock_guard<mutex> guard(m_Mutex);
	return m_Head->GetData(length);
}
int CacheList::GetLength()
{
	lock_guard<mutex> guard(m_Mutex);
	return m_Length;
}
bool CacheList::IsEmpty()
{
	lock_guard<mutex> guard(m_Mutex);
	return m_Head->IsEmpty();
}
void CacheList::Clear()
{
	while (m_Write != m_Head)
	{
		m_Write->Clear();
		m_Write = m_Write->GetPrev();
	}
	m_Head->Clear();
	m_Length = 0;
}

void CacheList::PopFrontNode()
{
	CacheNode* cacheNode = m_Head;
	m_Head = m_Head->GetNext();
	cacheNode->Init();

	m_Tail->SetNext(cacheNode);
	m_Tail = cacheNode;
}
void CacheList::AddHeadNode()
{
	CacheNode* cacheNode = new CacheNode(true, m_BlockSize);
	cacheNode->SetNext(m_Head);
	m_Head->SetPrev(cacheNode);
	m_Head = cacheNode;
}
void CacheList::AddTailNode()
{
	CacheNode* cacheNode = new CacheNode(false, m_BlockSize);
	cacheNode->SetPrev(m_Tail);
	m_Tail->SetNext(cacheNode);
	m_Tail = cacheNode;
}
