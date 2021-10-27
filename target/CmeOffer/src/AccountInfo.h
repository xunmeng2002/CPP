#pragma once


#include <string>
#include <vector>
#include <map>

using namespace std;

class AccountInfo
{
	AccountInfo();
public:
	static AccountInfo& GetInstance();
	void Load(const char* fileName = "CmeOffer.json");
	void Print();

public:
	string ChannelID;
	string ListenPort;
	string BroadCastPort;
	string CmeGlobexIP;
	string CmeGlobexPrimaryPort;
	string CmeGlobexBackupPort;
	string BeginString;
	string LogonSenderCompID;
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
	string AccessID;
	string EncryptedPasswordMethod;
	string SecretKey;
	string Account;
	bool RecordFixAuditTrail;
	string FixAuditTrailFileName;

private:
	static AccountInfo m_Instance;
};



