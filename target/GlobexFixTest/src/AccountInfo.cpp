#include "AccountInfo.h"
#include "json/json.h"
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;


void PrintAccountInfo(AccountInfo* accountInfo)
{
	WRITE_LOG(LogLevel::Info, "IP[%s], PrimaryPort[%s], BackupPort[%s], BeginString[%s], SenderCompID[%s],  SenderSubID[%s], TargetCompID[%s], TargetSubID[%s], "
		"SenderLocationID[%s], HeartBtInt[%s], ResetSeqNumFlag[%s], ApplicationSystemName[%s], ApplicationSystemVersion[%s], ApplicationSystemVendor[%s], "
		"AccountID[%s], EncryptedPasswordMethod[%s], SecretKey[%s].",
		accountInfo->IP.c_str(), accountInfo->PrimaryPort.c_str(), accountInfo->BackupPort.c_str(), accountInfo->BeginString.c_str(), accountInfo->SenderCompID.c_str(), accountInfo->SenderSubID.c_str(), accountInfo->TargetCompID.c_str(), accountInfo->TargetSubID.c_str(),
		accountInfo->SenderLocationID.c_str(), accountInfo->HeartBtInt.c_str(), accountInfo->ResetSeqNumFlag.c_str(), accountInfo->ApplicationSystemName.c_str(), accountInfo->ApplicationSystemVersion.c_str(), accountInfo->ApplicationSystemVendor.c_str(),
		accountInfo->AccountID.c_str(), accountInfo->EncryptedPasswordMethod.c_str(), accountInfo->SecretKey.c_str());
}

void ReadAccountInfo(AccountInfo* accountInfo)
{
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value root;

	ifstream in_file("AccountInfo.json", ios::binary);
	cout << "parse: " << reader.parse(in_file, root) << endl;
	in_file.close();
	accountInfo->IP = root["IP"].asString();
	accountInfo->PrimaryPort = root["PrimaryPort"].asString();
	accountInfo->BackupPort = root["BackupPort"].asString();
	accountInfo->BeginString = root["BeginString"].asString();
	accountInfo->SenderCompID = root["SenderCompID"].asString();
	accountInfo->SenderSubID = root["SenderSubID"].asString();
	accountInfo->TargetCompID = root["TargetCompID"].asString();
	accountInfo->TargetSubID = root["TargetSubID"].asString();
	accountInfo->SenderLocationID = root["SenderLocationID"].asString();
	accountInfo->HeartBtInt = root["HeartBtInt"].asString();
	accountInfo->ResetSeqNumFlag = root["ResetSeqNumFlag"].asString();
	accountInfo->ApplicationSystemName = root["ApplicationSystemName"].asString();
	accountInfo->ApplicationSystemVersion = root["ApplicationSystemVersion"].asString();
	accountInfo->ApplicationSystemVendor = root["ApplicationSystemVendor"].asString();
	accountInfo->AccountID = root["AccountID"].asString();
	accountInfo->EncryptedPasswordMethod = root["EncryptedPasswordMethod"].asString();
	accountInfo->SecretKey = root["SecretKey"].asString();

	PrintAccountInfo(accountInfo);
}
