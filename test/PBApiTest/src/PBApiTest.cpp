#include "PBStepApi.h"
#include "PBStepSpiImpl.h"
#include "AccountInfo.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>



int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();
	
	map<string, AccountInfo*> accountInfos;
	ReadAccountInfo(accountInfos);
	string accountID = "18511899894";
	AccountInfo* accountInfo = accountInfos[accountID];

	PBStepApi* stepApi = new PBStepApi();
	PBStepSpiImpl* stepSpi = new PBStepSpiImpl(stepApi, accountInfo);
	stepApi->Init(accountInfo->FrontAddr.c_str());
	
	PBStepReqSetUserInfoField reqSetUserInfo;
	::memset(&reqSetUserInfo, 0, sizeof(reqSetUserInfo));
	strcpy(reqSetUserInfo.RZMWJ, accountInfo->AuthFilePath.c_str());

	int reqNo = 0;
	stepApi->ReqSetUserInfo(reqSetUserInfo, reqNo);

	PBStepReqLoginField reqLogin;
	::memset(&reqLogin, 0, sizeof(reqLogin));
	strcpy(reqLogin.BROKER_ID, accountInfo->BrokerID.c_str());
	strcpy(reqLogin.DLZH, accountInfo->AccountID.c_str());
	strcpy(reqLogin.HXMM, accountInfo->Password.c_str());
	strcpy(reqLogin.DLLB, accountInfo->AccountClass.c_str());
	strcpy(reqLogin.ZHLB, accountInfo->LoginType.c_str());
	strcpy(reqLogin.CP, accountInfo->Product.c_str());
	strcpy(reqLogin.CPU, "");
	strcpy(reqLogin.ZBRQ, "");
	strcpy(reqLogin.YPBH, "");
	strcpy(reqLogin.YPFQ, "");
	strcpy(reqLogin.JSJM, "");
	strcpy(reqLogin.LOCAL_IP, "");
	strcpy(reqLogin.LOCAL_MAC, "");

	stepApi->ReqLogin(reqLogin, reqNo);




	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}

