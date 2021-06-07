#include <WinSock2.h>
#include "PBStepApi.h"
#include "PBStepSpiImpl.h"
#include "StepApiFunc.h"
#include "AccountInfo.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include <Windows.h>

using namespace std;

const char* ApiPath = "../../../libs/pbapi/Stds/win32/PBTradeAPI_STDS.dll";
//const char* ApiPath = "./PBTradeAPI_STDS.dll";

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	int nRet;
	if ((nRet = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
	{
		printf("WSAStartup failed\n");
		exit(0);
	}

	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();
	
	Sleep(1000);

	LoadStepApiFunc(ApiPath);
	StepApiInit(ApiPath);

	map<string, AccountInfo*> accountInfos;
	ReadAccountInfo(accountInfos);
	string accountID = "18511899894";
	AccountInfo* accountInfo = accountInfos[accountID];

	PBStepApi* stepApi = new PBStepApi();
	PBStepSpiImpl* stepSpi = new PBStepSpiImpl(stepApi, accountInfo);
	stepApi->Init(stepSpi, accountInfo->FrontAddr.c_str(), ApiPath);
	
	PBStepReqSetUserInfoField reqSetUserInfo;
	::memset(&reqSetUserInfo, 0, sizeof(reqSetUserInfo));
	strcpy(reqSetUserInfo.RZMWJ, accountInfo->AuthFilePath.c_str());

	int reqNo = 0;
	int errorCode = stepApi->ReqSetUserInfo(reqSetUserInfo, reqNo);
	WRITE_LOG(LogLevel::Info, "ReqSetUserInfo  ErrorCode:[%d]  ReqNo:[%d]", errorCode, reqNo);

	Sleep(2000);


	PBStepReqLoginField reqLogin;
	::memset(&reqLogin, 0, sizeof(reqLogin));
	strcpy(reqLogin.BROKER_ID, accountInfo->BrokerID.c_str());
	strcpy(reqLogin.DLZH, accountInfo->AccountID.c_str());
	strcpy(reqLogin.HXMM, accountInfo->Password.c_str());
	strcpy(reqLogin.DLLB, accountInfo->LoginType.c_str());
	strcpy(reqLogin.ZHLB, accountInfo->AccountClass.c_str());
	strcpy(reqLogin.CP, accountInfo->Product.c_str());
	strcpy(reqLogin.PT, accountInfo->Platform.c_str());
	strcpy(reqLogin.VERSION, accountInfo->Version.c_str());
	strcpy(reqLogin.CPU, "");
	strcpy(reqLogin.ZBRQ, "");
	strcpy(reqLogin.YPBH, "");
	strcpy(reqLogin.YPFQ, "");
	strcpy(reqLogin.JSJM, "");
	strcpy(reqLogin.LOCAL_IP, "");
	strcpy(reqLogin.LOCAL_MAC, "");

	errorCode = stepApi->ReqLogin(reqLogin, reqNo);
	WRITE_LOG(LogLevel::Info, "ReqLogin  ErrorCode:[%d]  ReqNo:[%d]", errorCode, reqNo);


	Sleep(10000);
	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}

