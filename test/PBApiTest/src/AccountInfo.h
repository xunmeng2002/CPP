#pragma once

#include <set>
#include <map>
#include <string>
using namespace std;

struct AccountInfo
{
	string BrokerID;
	string AccountID;
	string Password;
	string AuthFilePath;
	string FrontAddr;
	string AccountClass;
	string LoginType;
	string Product;
	string Platform;
	string Version;
};

void PrintAccountInfo(AccountInfo* accountInfo);

void ReadAccountInfo(std::map<std::string, AccountInfo*>& accountInfos);
