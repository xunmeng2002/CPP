#include "AccountInfo.h"
#include "json/json.h"
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;


void PrintAccountInfo(map<Address, AccountInfo*>& accountInfos)
{
	for (auto& it : accountInfos)
	{
		auto accountInfo = it.second;
		WRITE_LOG(LogLevel::Info, "Address: IP[%s], Port[%s], BeginString[%s], SenderCompID[%s],  SenderSubID[%s], TargetCompID[%s], TargetSubID[%s], "
			"SenderLocationID[%s], HeartBtInt[%s], ResetSeqNumFlag[%s], ApplicationSystemName[%s], ApplicationSystemVersion[%s], ApplicationSystemVendor[%s], "
			"AccountID[%s], EncryptedPasswordMethod[%s], SecretKey[%s].",
			accountInfo->IP.c_str(), accountInfo->Port.c_str(), accountInfo->BeginString.c_str(), accountInfo->SenderCompID.c_str(), accountInfo->SenderSubID.c_str(), accountInfo->TargetCompID.c_str(), accountInfo->TargetSubID.c_str(),
			accountInfo->SenderLocationID.c_str(), accountInfo->HeartBtInt.c_str(), accountInfo->ResetSeqNumFlag.c_str(), accountInfo->ApplicationSystemName.c_str(), accountInfo->ApplicationSystemVersion.c_str(), accountInfo->ApplicationSystemVendor.c_str(),
			accountInfo->AccountID.c_str(), accountInfo->EncryptedPasswordMethod.c_str(), accountInfo->SecretKey.c_str());
	}
}

void ReadAccountInfo(map<Address, AccountInfo*>& accountInfos)
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
		accountInfo->IP = root[i]["IP"].asString();
		accountInfo->Port = root[i]["Port"].asString();
		accountInfo->BeginString = root[i]["BeginString"].asString();
		accountInfo->SenderCompID = root[i]["SenderCompID"].asString();
		accountInfo->SenderSubID = root[i]["SenderSubID"].asString();
		accountInfo->TargetCompID = root[i]["TargetCompID"].asString();
		accountInfo->TargetSubID = root[i]["TargetSubID"].asString();
		accountInfo->SenderLocationID = root[i]["SenderLocationID"].asString();
		accountInfo->HeartBtInt = root[i]["HeartBtInt"].asString();
		accountInfo->ResetSeqNumFlag = root[i]["ResetSeqNumFlag"].asString();
		accountInfo->ApplicationSystemName = root[i]["ApplicationSystemName"].asString();
		accountInfo->ApplicationSystemVersion = root[i]["ApplicationSystemVersion"].asString();
		accountInfo->ApplicationSystemVendor = root[i]["ApplicationSystemVendor"].asString();
		accountInfo->AccountID = root[i]["AccountID"].asString();
		accountInfo->EncryptedPasswordMethod = root[i]["EncryptedPasswordMethod"].asString();
		accountInfo->SecretKey = root[i]["SecretKey"].asString();

		Address address;
		address.IP = accountInfo->IP;
		address.Port = accountInfo->Port;

		accountInfos.insert(make_pair(address, accountInfo));
	}
	PrintAccountInfo(accountInfos);
}
