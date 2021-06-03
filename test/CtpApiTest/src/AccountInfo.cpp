#include "AccountInfo.h"
#include "json/json.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;


void PrintAccountInfo(AccountInfo* accountInfo)
{
	printf("AccountInfo: AccountType[%s], BrokerID[%s],  UserID[%s], Password[%s],  UserProductInfo[%s], AuthCode[%s],  AppID[%s]\nFrontAddrs",
		accountInfo->AccountType, accountInfo->BrokerID, accountInfo->UserID, accountInfo->Password, accountInfo->UserProductInfo, accountInfo->AuthCode, accountInfo->AppID);
	for (auto FrontAddr : accountInfo->FrontAddrs)
	{
		printf("  [%s]", FrontAddr.c_str());
	}
	printf("\n\n");
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
		strcpy(accountInfo->AccountType, root[i]["AccountType"].asString().c_str());
		strcpy(accountInfo->BrokerID, root[i]["BrokerID"].asString().c_str());
		strcpy(accountInfo->UserID, root[i]["UserID"].asString().c_str());
		strcpy(accountInfo->Password, root[i]["Password"].asString().c_str());
		strcpy(accountInfo->UserProductInfo, root[i]["UserProductInfo"].asString().c_str());
		strcpy(accountInfo->AuthCode, root[i]["AuthCode"].asString().c_str());
		strcpy(accountInfo->AppID, root[i]["AppID"].asString().c_str());
		for (auto j = 0; j < root[i]["FrontAddrs"].size(); j++)
		{
			accountInfo->FrontAddrs.insert(root[i]["FrontAddrs"][j].asString());
		}
		accountInfos.insert(make_pair(accountInfo->UserID, accountInfo));
	}
	for (auto it : accountInfos)
	{
		PrintAccountInfo(it.second);
	}
}
