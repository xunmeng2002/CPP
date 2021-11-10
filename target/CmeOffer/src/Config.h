#pragma once


#include <string>
#include <vector>
#include <map>

using namespace std;

class Config
{
	Config();
public:
	static Config& GetInstance();
	void Load(const char* fileName = "CmeOffer.json");
	void Print();

public:
	int ChannelID;
	int ListenPort;
	int BroadCastPort;
	string CmeGlobexIP;
	int CmeGlobexPrimaryPort;
	int CmeGlobexBackupPort;
	string BeginString;
	string LogonSenderCompID;
	string SenderCompID;
	string SenderSubID;
	string TargetCompID;
	string TargetSubID;
	string SenderLocationID;
	int HeartBtInt;
	bool ResetSeqNumFlag;
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
	static Config m_Instance;
};



