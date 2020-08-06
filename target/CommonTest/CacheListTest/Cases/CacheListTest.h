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
			"我坐在床前望着窗外回忆满天",
			"生命是华丽错觉",
			"时间是贼偷走一切",
			"十七岁那一年抓住那只蝉以为能抓住夏天",
			"十七岁的那年吻过他的脸就以为和他能永远",
			"有没有那麽一种永远 永远不改变",
			"拥抱过的美丽都再也不破碎 ",
			"让险峻岁月不能在脸上撒野 ",
			"让生离和死别都遥远有谁能听见",
			"我坐在床前转过头看谁在沉睡",
			"那一张苍老的脸 好像是我紧闭双眼", 
			"曾经是爱我的和我深爱的 ", 
			"都围绕在我身边",
			"带不走的那些遗憾和眷恋",
			"就化成最后一滴眼泪" };
		
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
			"我坐在床前望着窗外回忆满天",
			"生命是华丽错觉",
			"时间是贼偷走一切",
			"十七岁那一年抓住那只蝉以为能抓住夏天",
			"十七岁的那年吻过他的脸就以为和他能永远",
			"有没有那麽一种永远 永远不改变",
			"拥抱过的美丽都再也不破碎 ",
			"让险峻岁月不能在脸上撒野 ",
			"让生离和死别都遥远有谁能听见",
			"我坐在床前转过头看谁在沉睡",
			"那一张苍老的脸 好像是我紧闭双眼",
			"曾经是爱我的和我深爱的 ",
			"都围绕在我身边",
			"带不走的那些遗憾和眷恋",
			"就化成最后一滴眼泪" };

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
			"我坐在床前望着窗外回忆满天",
			"生命是华丽错觉",
			"时间是贼偷走一切",
			"十七岁那一年抓住那只蝉以为能抓住夏天",
			"十七岁的那年吻过他的脸就以为和他能永远",
			"有没有那麽一种永远 永远不改变",
			"拥抱过的美丽都再也不破碎 ",
			"让险峻岁月不能在脸上撒野 ",
			"让生离和死别都遥远有谁能听见",
			"我坐在床前转过头看谁在沉睡",
			"那一张苍老的脸 好像是我紧闭双眼",
			"曾经是爱我的和我深爱的 ",
			"都围绕在我身边",
			"带不走的那些遗憾和眷恋",
			"就化成最后一滴眼泪" };

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
			"我坐在床前望着窗外回忆满天",
			"生命是华丽错觉",
			"时间是贼偷走一切",
			"十七岁那一年抓住那只蝉以为能抓住夏天",
			"十七岁的那年吻过他的脸就以为和他能永远",
			"有没有那麽一种永远 永远不改变",
			"拥抱过的美丽都再也不破碎 ",
			"让险峻岁月不能在脸上撒野 ",
			"让生离和死别都遥远有谁能听见",
			"我坐在床前转过头看谁在沉睡",
			"那一张苍老的脸 好像是我紧闭双眼",
			"曾经是爱我的和我深爱的 ",
			"都围绕在我身边",
			"带不走的那些遗憾和眷恋",
			"就化成最后一滴眼泪" };

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
			"我坐在床前望着窗外回忆满天",
			"生命是华丽错觉",
			"时间是贼偷走一切",
			"十七岁那一年抓住那只蝉以为能抓住夏天",
			"十七岁的那年吻过他的脸就以为和他能永远",
			"有没有那麽一种永远 永远不改变",
			"拥抱过的美丽都再也不破碎 ",
			"让险峻岁月不能在脸上撒野 ",
			"让生离和死别都遥远有谁能听见",
			"我坐在床前转过头看谁在沉睡",
			"那一张苍老的脸 好像是我紧闭双眼",
			"曾经是爱我的和我深爱的 ",
			"都围绕在我身边",
			"带不走的那些遗憾和眷恋",
			"就化成最后一滴眼泪" };

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
