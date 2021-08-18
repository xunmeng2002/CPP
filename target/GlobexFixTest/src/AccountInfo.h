#pragma once


#include "Common.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

struct AccountInfo
{
	string IP;
	string PrimaryPort;
	string BackupPort;
	string BeginString;
	string SenderCompID;
	string SenderSubID;
	string TargetCompID;
	string TargetSubID;
	string SenderLocationID;
	string HeartBtInt;
	string ResetSeqNumFlag;
	string ApplicationSystemName;
	string ApplicationSystemVersion;
	string ApplicationSystemVendor;
	string AccountID;
	string EncryptedPasswordMethod;
	string SecretKey;
};

void PrintAccountInfo(AccountInfo* accountInfo);

void ReadAccountInfo(AccountInfo* accountInfo);
