#include "CacheList.h"
#include <algorithm>
#include <assert.h>
using namespace std;

CacheNode::CacheNode(int blockSize)
	:m_BlockSize(blockSize), m_Length(0), m_Next(nullptr)
{
	m_Head = new char[blockSize];
	m_Read = m_Write = m_Head;
	m_End = m_Head + blockSize;
}
CacheNode::~CacheNode()
{
	delete[] m_Head;
}
int CacheNode::PushBack(void* data, int length)
{
	length = min(length, int(m_End - m_Write));
	::memcpy(m_Write, data, length);
	m_Write += length;
	m_Length += length;
	return length;
}
int CacheNode::PopFront(void* data, int length)
{
	length = min(length, m_Length);
	if (data)
	{
		::memcpy(data, m_Read, length);
	}
	m_Read += length;
	m_Length -= length;
	return length;
}
void* CacheNode::GetRead()
{
	return m_Read;
}
void* CacheNode::GetWrite()
{
	return m_Write;
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
bool CacheNode::IsFull()
{
	return m_Write == m_End;
}
void CacheNode::SetNext(CacheNode* next)
{
	m_Next = next;
}
CacheNode* CacheNode::GetNext()
{
	return m_Next;
}
void CacheNode::Clear()
{
	m_Read = m_Write = m_Head;
	m_Next = nullptr;
	m_Length = 0;
}



CacheList::CacheList(int blockSize)
	:m_BlockSize(blockSize)
{
	m_HeadNode = new CacheNode(m_BlockSize);
	m_WriteNode = m_TailNode = m_HeadNode;
	m_Length = 0;
}
CacheList::~CacheList()
{
	CacheNode* cacheNode;
	while (m_HeadNode)
	{
		cacheNode = m_HeadNode;
		m_HeadNode = m_HeadNode->GetNext();
		delete cacheNode;
	}
}
void CacheList::PushBack(const void* data, int length)
{
	lock_guard<mutex> guard(m_Mutex);
	int pushLen = 0;
	while (pushLen < length)
	{
		pushLen += m_WriteNode->PushBack((char*)data + pushLen, length - pushLen);
		if (m_WriteNode->IsFull())
		{
			if (m_WriteNode == m_TailNode)
			{
				AddNewNode();
			}
			m_WriteNode = m_WriteNode->GetNext();
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
			popLen += m_HeadNode->PopFront((char*)data + popLen, length - popLen);
		}
		else //用于GetData之后
		{
			popLen += m_HeadNode->PopFront(data, length - popLen);
		}
		if (m_HeadNode->IsEmpty() && m_WriteNode != m_HeadNode && m_HeadNode->GetNext())
		{
			PopFrontNode();
		}
		if (popLen < length)
		{
			if (m_HeadNode->IsEmpty())
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
void* CacheList::GetData(int& length)
{
	lock_guard<mutex> guard(m_Mutex);
	return m_HeadNode->GetData(length);
}
int CacheList::GetLength()
{
	lock_guard<mutex> guard(m_Mutex);
	return m_Length;
}
bool CacheList::IsEmpty()
{
	lock_guard<mutex> guard(m_Mutex);
	return m_HeadNode->IsEmpty();
}
void CacheList::Clear()
{
	lock_guard<mutex> guard(m_Mutex);
	while (m_HeadNode != m_WriteNode)
	{
		PopFrontNode();
	}
	m_HeadNode->Clear();
}

void CacheList::PopFrontNode()
{
	CacheNode* cacheNode = m_HeadNode;
	m_HeadNode = m_HeadNode->GetNext();
	cacheNode->Clear();

	m_TailNode->SetNext(cacheNode);
	m_TailNode = cacheNode;
}
void CacheList::AddNewNode()
{
	CacheNode* cacheNode = new CacheNode(m_BlockSize);
	m_TailNode->SetNext(cacheNode);
	m_TailNode = cacheNode;
}
