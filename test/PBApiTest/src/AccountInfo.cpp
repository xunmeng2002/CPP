#include "AccountInfo.h"
#include "json/json.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;


void PrintAccountInfo(AccountInfo* accountInfo)
{
	printf("AccountInfo: BrokerID[%s],  AccountID[%s], Password[%s], AuthFilePath[%s],"
		"FrontAddr[%s], AccountClass[%s], LoginType[%s], Product[%s], Platform[%s], Version[%s]\n",
		accountInfo->BrokerID.c_str(), accountInfo->AccountID.c_str(), accountInfo->Password.c_str(), accountInfo->AuthFilePath.c_str(),
		accountInfo->FrontAddr.c_str(), accountInfo->AccountClass.c_str(), accountInfo->LoginType.c_str(), accountInfo->Product.c_str(),
		accountInfo->Platform.c_str(), accountInfo->Version.c_str());
}

void ReadAccountInfo(map<string, AccountInfo*>& accountInfos)
{
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value root;

	ifstream in_file("AccountInfo.json", ios::binary);
	cout << "parse: " << reader.parse(in_file, root) << endl;
	in_file.close();

	for (auto i = 0; i < root.size(); i++)
	{
		AccountInfo* accountInfo = new AccountInfo();
		accountInfo->BrokerID = root[i]["BrokerID"].asString();
		accountInfo->AccountID = root[i]["AccountID"].asString();
		accountInfo->Password = root[i]["Password"].asString();
		accountInfo->AuthFilePath = root[i]["AuthFilePath"].asString();
		accountInfo->FrontAddr = root[i]["FrontAddr"].asString();
		accountInfo->AccountClass = root[i]["AccountClass"].asString();
		accountInfo->LoginType = root[i]["LoginType"].asString();
		accountInfo->Product = root[i]["Product"].asString();
		accountInfo->Platform = root[i]["Platform"].asString();
		accountInfo->Version = root[i]["Version"].asString();
		accountInfos.insert(make_pair(accountInfo->AccountID, accountInfo));
	}
	for (auto& it : accountInfos)
	{
		PrintAccountInfo(it.second);
	}
}
