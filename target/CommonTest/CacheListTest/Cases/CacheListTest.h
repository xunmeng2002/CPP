#ifndef CACHE_LIST_TEST_H
#define CACHE_LIST_TEST_H

#include "UnitTest.h"
#include "CacheList.h"
#include <iostream>

using namespace std;

namespace CacheListTest
{
	bool PushBackAndPopFrontTest(std::string& errorMsg)
	{
		CacheList* cacheList = new CacheList(64);
		
		string values[15] = { 
			"�����ڴ�ǰ���Ŵ����������",
			"�����ǻ������",
			"ʱ������͵��һ��",
			"ʮ������һ��ץס��ֻ����Ϊ��ץס����",
			"ʮ����������ǹ�����������Ϊ��������Զ",
			"��û������һ����Զ ��Զ���ı�",
			"ӵ��������������Ҳ������ ",
			"���վ����²�����������Ұ ",
			"�����������ңԶ��˭������",
			"�����ڴ�ǰת��ͷ��˭�ڳ�˯",
			"��һ�Ų��ϵ��� �������ҽ���˫��", 
			"�����ǰ��ҵĺ������ ", 
			"��Χ���������",
			"�����ߵ���Щ�ź��;���",
			"�ͻ������һ������" };
		
		for (auto& value : values)
		{
			cacheList->PushBack(value.c_str(), value.length());
		}
		string s = "Hello World!";
		cacheList->PushBack(s.c_str(), s.length());
		char buff[256];
		for (auto& value : values)
		{
			cacheList->PopFront(buff, value.length());
			buff[value.length()] = '\0';
			
			ASSERT_EQUAL(value, string(buff));
		}

		cacheList->PopFront(buff, s.length());
		buff[s.length()] = '\0';
		ASSERT_EQUAL(s, string(buff));

		ASSERT_EQUAL(cacheList->GetLength(), 0);
		return true;
	}

	bool PushFrontAndPopBackTest(std::string& errorMsg)
	{
		CacheList* cacheList = new CacheList(64);

		string values[15] = {
			"�����ڴ�ǰ���Ŵ����������",
			"�����ǻ������",
			"ʱ������͵��һ��",
			"ʮ������һ��ץס��ֻ����Ϊ��ץס����",
			"ʮ����������ǹ�����������Ϊ��������Զ",
			"��û������һ����Զ ��Զ���ı�",
			"ӵ��������������Ҳ������ ",
			"���վ����²�����������Ұ ",
			"�����������ңԶ��˭������",
			"�����ڴ�ǰת��ͷ��˭�ڳ�˯",
			"��һ�Ų��ϵ��� �������ҽ���˫��",
			"�����ǰ��ҵĺ������ ",
			"��Χ���������",
			"�����ߵ���Щ�ź��;���",
			"�ͻ������һ������" };

		for (auto& value : values)
		{
			cacheList->PushFront(value.c_str(), value.length());
		}
		string s = "Hello World!";
		cacheList->PushFront(s.c_str(), s.length());
		char buff[256];
		for (auto& value : values)
		{
			cacheList->PopBack(buff, value.length());
			buff[value.length()] = '\0';

			ASSERT_EQUAL(value, string(buff));
		}

		cacheList->PopBack(buff, s.length());
		buff[s.length()] = '\0';
		ASSERT_EQUAL(s, string(buff));

		ASSERT_EQUAL(cacheList->GetLength(), 0);
		return true;
	}

	bool PushFrontAndPushBackTest(std::string& errorMsg)
	{
		CacheList* cacheList = new CacheList(64);

		string values[15] = {
			"�����ڴ�ǰ���Ŵ����������",
			"�����ǻ������",
			"ʱ������͵��һ��",
			"ʮ������һ��ץס��ֻ����Ϊ��ץס����",
			"ʮ����������ǹ�����������Ϊ��������Զ",
			"��û������һ����Զ ��Զ���ı�",
			"ӵ��������������Ҳ������ ",
			"���վ����²�����������Ұ ",
			"�����������ңԶ��˭������",
			"�����ڴ�ǰת��ͷ��˭�ڳ�˯",
			"��һ�Ų��ϵ��� �������ҽ���˫��",
			"�����ǰ��ҵĺ������ ",
			"��Χ���������",
			"�����ߵ���Щ�ź��;���",
			"�ͻ������һ������" };

		for (auto& value : values)
		{
			cacheList->PushFront(value.c_str(), value.length());
		}
		string s = "Hello World!";
		cacheList->PushBack(s.c_str(), s.length());
		char buff[256];

		cacheList->PopBack(buff, s.length());
		buff[s.length()] = '\0';
		ASSERT_EQUAL(s, string(buff));

		for (auto& value : values)
		{
			cacheList->PopBack(buff, value.length());
			buff[value.length()] = '\0';

			ASSERT_EQUAL(value, string(buff));
		}

		ASSERT_EQUAL(cacheList->GetLength(), 0);
		return true;
	}

	bool GetDataTest(std::string& errorMsg)
	{
		CacheList* cacheList = new CacheList(64);

		string values[15] = {
			"�����ڴ�ǰ���Ŵ����������",
			"�����ǻ������",
			"ʱ������͵��һ��",
			"ʮ������һ��ץס��ֻ����Ϊ��ץס����",
			"ʮ����������ǹ�����������Ϊ��������Զ",
			"��û������һ����Զ ��Զ���ı�",
			"ӵ��������������Ҳ������ ",
			"���վ����²�����������Ұ ",
			"�����������ңԶ��˭������",
			"�����ڴ�ǰת��ͷ��˭�ڳ�˯",
			"��һ�Ų��ϵ��� �������ҽ���˫��",
			"�����ǰ��ҵĺ������ ",
			"��Χ���������",
			"�����ߵ���Щ�ź��;���",
			"�ͻ������һ������" };

		for (auto& value : values)
		{
			cacheList->PushBack(value.c_str(), value.length());
		}
		string s = "Hello World!";
		cacheList->PushFront(s.c_str(), s.length());
		
		string result = s;
		for (auto& value : values)
		{
			result += value;
		}

		char buff[1024] = { 0 };
		int len = 0;
		int totalLen = 0;
		while (!cacheList->IsEmpty())
		{
			auto data = cacheList->GetData(len);
			::memcpy(buff + totalLen, data, len);
			cacheList->PopFront(nullptr, len);

			totalLen += len;
		}
		ASSERT_EQUAL(result, string(buff));
		//cout << endl << buff << endl;

		ASSERT_EQUAL(cacheList->GetLength(), 0);
		return true;
	}

	bool ClearTest(std::string& errorMsg)
	{
		CacheList* cacheList = new CacheList(64);

		string values[15] = {
			"�����ڴ�ǰ���Ŵ����������",
			"�����ǻ������",
			"ʱ������͵��һ��",
			"ʮ������һ��ץס��ֻ����Ϊ��ץס����",
			"ʮ����������ǹ�����������Ϊ��������Զ",
			"��û������һ����Զ ��Զ���ı�",
			"ӵ��������������Ҳ������ ",
			"���վ����²�����������Ұ ",
			"�����������ңԶ��˭������",
			"�����ڴ�ǰת��ͷ��˭�ڳ�˯",
			"��һ�Ų��ϵ��� �������ҽ���˫��",
			"�����ǰ��ҵĺ������ ",
			"��Χ���������",
			"�����ߵ���Щ�ź��;���",
			"�ͻ������һ������" };

		for (auto& value : values)
		{
			cacheList->PushBack(value.c_str(), value.length());
		}
		string s = "Hello World!";
		cacheList->PushFront(s.c_str(), s.length());

		cacheList->Clear();

		ASSERT_EQUAL(cacheList->GetLength(), 0);
		return true;
	}

	void RegisterCases()
	{
		ADD_CASE("CacheListTest", CacheListTest::PushBackAndPopFrontTest);
		ADD_CASE("CacheListTest", CacheListTest::PushFrontAndPopBackTest);
		ADD_CASE("CacheListTest", CacheListTest::PushFrontAndPushBackTest);
		ADD_CASE("CacheListTest", CacheListTest::GetDataTest);
		ADD_CASE("CacheListTest", CacheListTest::ClearTest);
	}
}

#endif
