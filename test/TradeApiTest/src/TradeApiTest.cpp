#include "ThostFtdcTraderSpiImpl.h"
#include "Logger.h"
#include "UserData.h"

int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();
	
	AccountInfo* accountInfo = new AccountInfo();
	strcpy(accountInfo->BrokerID, "8000");
	strcpy(accountInfo->UserID, "71020537");
	strcpy(accountInfo->Password, "Liuxing167756");
	strcpy(accountInfo->UserProductInfo, "PBSDSV5400");
	strcpy(accountInfo->AuthCode, "PRDCTPLZPTOFVEUE");
	strcpy(accountInfo->AppID, "POBO_BYSDS_5.0.0");

	CThostFtdcTraderApi* traderApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
	CThostFtdcTraderSpiImpl* traderSpi = new CThostFtdcTraderSpiImpl(traderApi);
	traderSpi->SetAccountInfo(accountInfo);
	traderApi->RegisterSpi(traderSpi);
	traderApi->RegisterFront("tcp://180.168.212.75:41305");
	traderApi->SubscribePrivateTopic(THOST_TE_RESUME_TYPE::THOST_TERT_RESTART);
	traderApi->SubscribePublicTopic(THOST_TE_RESUME_TYPE::THOST_TERT_RESTART);
	traderApi->Init();


	traderApi->Release();
	traderApi->Join();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}


