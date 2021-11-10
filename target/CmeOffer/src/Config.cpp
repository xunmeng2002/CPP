#include "Config.h"
#include "json/json.h"
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

Config Config::m_Instance;

Config::Config()
{

}
Config& Config::GetInstance()
{
	return m_Instance;
}

void Config::Load(const char* fileName)
{
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value root;

	ifstream in_file(fileName, ios::binary);
	cout << "parse: " << reader.parse(in_file, root) << endl;
	in_file.close();

	ChannelID = root["ChannelID"].asInt();
	ListenPort = root["ListenPort"].asInt();
	BroadCastPort = root["BroadCastPort"].asInt();
	CmeGlobexIP = root["CmeGlobexIP"].asString();
	CmeGlobexPrimaryPort = root["CmeGlobexPrimaryPort"].asInt();
	CmeGlobexBackupPort = root["CmeGlobexBackupPort"].asInt();
	BeginString = root["BeginString"].asString();
	LogonSenderCompID = root["LogonSenderCompID"].asString();
	SenderCompID = root["SenderCompID"].asString();
	SenderSubID = root["SenderSubID"].asString();
	TargetCompID = root["TargetCompID"].asString();
	TargetSubID = root["TargetSubID"].asString();
	SenderLocationID = root["SenderLocationID"].asString();
	HeartBtInt = root["HeartBtInt"].asInt();
	ResetSeqNumFlag = root["ResetSeqNumFlag"].asBool();
	ApplicationSystemName = root["ApplicationSystemName"].asString();
	ApplicationSystemVersion = root["ApplicationSystemVersion"].asString();
	ApplicationSystemVendor = root["ApplicationSystemVendor"].asString();
	AccessID = root["AccessID"].asString();
	EncryptedPasswordMethod = root["EncryptedPasswordMethod"].asString();
	SecretKey = root["SecretKey"].asString();
	Account = root["Account"].asString();
	RecordFixAuditTrail = root["RecordFixAuditTrail"].asBool();
	FixAuditTrailFileName = root["FixAuditTrailFileName"].asString();

	Print();
}

void Config::Print()
{
	WRITE_LOG(LogLevel::Info, "ChannelID[%d], ListenPort[%d], BroadCastPort[%d], CmeGlobexIP[%s], CmeGlobexPrimaryPort[%d], CmeGlobexBackupPort[%d], "
		"BeginString[%s], LogonSenderCompID[%s], SenderCompID[%s],  SenderSubID[%s], TargetCompID[%s], TargetSubID[%s], "
		"SenderLocationID[%s], HeartBtInt[%d], ResetSeqNumFlag[%d], ApplicationSystemName[%s], ApplicationSystemVersion[%s], ApplicationSystemVendor[%s], "
		"AccountID[%s], EncryptedPasswordMethod[%s], SecretKey[%s], Account[%s], RecordFixAuditTrail[%d], FixAuditTrailFileName[%s].",
		ChannelID, ListenPort, BroadCastPort, CmeGlobexIP.c_str(), CmeGlobexPrimaryPort, CmeGlobexBackupPort,
		BeginString.c_str(), LogonSenderCompID.c_str(), SenderCompID.c_str(), SenderSubID.c_str(), TargetCompID.c_str(), TargetSubID.c_str(),
		SenderLocationID.c_str(), HeartBtInt, ResetSeqNumFlag, ApplicationSystemName.c_str(), ApplicationSystemVersion.c_str(), ApplicationSystemVendor.c_str(),
		AccessID.c_str(), EncryptedPasswordMethod.c_str(), SecretKey.c_str(), Account.c_str(), RecordFixAuditTrail, FixAuditTrailFileName.c_str());
}