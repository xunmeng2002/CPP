#include "ThostFtdcTraderApiMiddle.h"
#include "ThostFtdcTraderSpiImpl.h"
#include "AccountInfo.h"
#include "Logger.h"
#include <iostream>
#include <map>

using namespace std;


int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();

	map<string, AccountInfo*> accountInfos;
	ReadAccountInfo(accountInfos);
	string accountID = "71020537";
	CThostFtdcTraderApi* traderApi = CThostFtdcTraderApiMiddle::CreateFtdcTraderApi();
	cout << "API Version:" << traderApi->GetApiVersion() << endl;
	CThostFtdcTraderSpiImpl* traderSpi = new CThostFtdcTraderSpiImpl(traderApi);
	traderSpi->SetAccountInfo(accountInfos[accountID]);
	traderApi->RegisterSpi(traderSpi);
	for (auto frontAddr : accountInfos[accountID]->FrontAddrs)
	{
		traderApi->RegisterFront((char*)frontAddr.c_str());
	}
	traderApi->SubscribePrivateTopic(THOST_TE_RESUME_TYPE::THOST_TERT_RESTART);
	traderApi->SubscribePublicTopic(THOST_TE_RESUME_TYPE::THOST_TERT_RESTART);
	traderApi->Init();

	traderApi->Join();
	

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}


