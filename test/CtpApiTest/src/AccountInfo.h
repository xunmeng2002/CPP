#pragma once

#include "ThostFtdcUserApiDataType.h"
#include <set>
#include <map>
#include <string>

typedef char TThostFtdcAccountTypeType[10];

struct AccountInfo
{
	TThostFtdcAccountTypeType AccountType;
	TThostFtdcBrokerIDType	BrokerID;
	TThostFtdcUserIDType	UserID;
	TThostFtdcPasswordType	Password;
	TThostFtdcProductInfoType	UserProductInfo;
	TThostFtdcAuthCodeType	AuthCode;
	TThostFtdcAppIDType	AppID;
	std::set<std::string> FrontAddrs;
};

void PrintAccountInfo(AccountInfo* accountInfo);

void ReadAccountInfo(std::map<std::string, AccountInfo*>& accountInfos);
