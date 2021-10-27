#include "AccountInfo.h"
#include "json/json.h"
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

AccountInfo AccountInfo::m_Instance;

AccountInfo::AccountInfo()
{

}
AccountInfo& AccountInfo::GetInstance()
{
	return m_Instance;
}

void AccountInfo::Load(const char* fileName)
{
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value root;

	ifstream in_file(fileName, ios::binary);
	cout << "parse: " << reader.parse(in_file, root) << endl;
	in_file.close();

	ChannelID = root["ChannelID"].asString();
	ListenPort = root["ListenPort"].asString();
	BroadCastPort = root["BroadCastPort"].asString();
	CmeGlobexIP = root["CmeGlobexIP"].asString();
	CmeGlobexPrimaryPort = root["CmeGlobexPrimaryPort"].asString();
	CmeGlobexBackupPort = root["CmeGlobexBackupPort"].asString();
	BeginString = root["BeginString"].asString();
	LogonSenderCompID = root["LogonSenderCompID"].asString();
	SenderCompID = root["SenderCompID"].asString();
	SenderSubID = root["SenderSubID"].asString();
	TargetCompID = root["TargetCompID"].asString();
	TargetSubID = root["TargetSubID"].asString();
	SenderLocationID = root["SenderLocationID"].asString();
	HeartBtInt = root["HeartBtInt"].asString();
	ResetSeqNumFlag = root["ResetSeqNumFlag"].asString();
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

void AccountInfo::Print()
{
	WRITE_LOG(LogLevel::Info, "ChannelID[%s], ListenPort[%s], BroadCastPort[%s], CmeGlobexIP[%s], CmeGlobexPrimaryPort[%s], CmeGlobexBackupPort[%s], "
		"BeginString[%s], LogonSenderCompID[%s], SenderCompID[%s],  SenderSubID[%s], TargetCompID[%s], TargetSubID[%s], "
		"SenderLocationID[%s], HeartBtInt[%s], ResetSeqNumFlag[%s], ApplicationSystemName[%s], ApplicationSystemVersion[%s], ApplicationSystemVendor[%s], "
		"AccountID[%s], EncryptedPasswordMethod[%s], SecretKey[%s], Account[%s], RecordFixAuditTrail[%d], FixAuditTrailFileName[%s].",
		ChannelID.c_str(), ListenPort.c_str(), BroadCastPort.c_str(), CmeGlobexIP.c_str(), CmeGlobexPrimaryPort.c_str(), CmeGlobexBackupPort.c_str(),
		BeginString.c_str(), LogonSenderCompID.c_str(), SenderCompID.c_str(), SenderSubID.c_str(), TargetCompID.c_str(), TargetSubID.c_str(),
		SenderLocationID.c_str(), HeartBtInt.c_str(), ResetSeqNumFlag.c_str(), ApplicationSystemName.c_str(), ApplicationSystemVersion.c_str(), ApplicationSystemVendor.c_str(),
		AccessID.c_str(), EncryptedPasswordMethod.c_str(), SecretKey.c_str(), Account.c_str(), RecordFixAuditTrail, FixAuditTrailFileName.c_str());
}