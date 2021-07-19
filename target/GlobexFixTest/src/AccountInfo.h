#pragma once


#include "Common.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Address
{
	Address() {}
	Address(const char* ip, unsigned int port)
		:IP(ip), Port(ItoA(port))
	{}
	Address(const string& ip, unsigned int port)
		:IP(ip), Port(ItoA(port))
	{}

	bool operator<(const Address& other) const
	{
		if (IP < other.IP)
		{
			return true;
		}
		else if (IP > other.IP)
		{
			return false;
		}
		return Port < other.Port;
	}

	string IP;
	string Port;
};

struct AccountInfo
{
	string IP;
	string Port;
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

void PrintAccountInfo(map<Address, AccountInfo*>& accountInfos);

void ReadAccountInfo(map<Address, AccountInfo*>& accountInfos);
