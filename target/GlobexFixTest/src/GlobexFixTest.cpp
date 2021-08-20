#include <vector>
#include <map>
#include <iostream>
#include <signal.h>
#include<stdlib.h>
#include "Logger.h"
#include "TcpSelectClient.h"
#include "TcpSelectServer.h"
#include "WorkThread.h"
#include "AccountInfo.h"
#include "EnumDict.h"
#include "TradeApiTables.h"

using namespace std;

constexpr char* DB_Name = "CME.db";


struct MarketSegment
{
	string MarketSegmentID;
	vector<string> InstrumentIDs;
};

map<string, MarketSegment> g_MarketSegments;

void InitMarketSegMent()
{
	g_MarketSegments["910"] = MarketSegment{ "910", {"36MU0 C0285", "26MU0 P0285"} };
	g_MarketSegments["925"] = MarketSegment{ "925", {"0GLBZ0", "0GLBG1", "0GLBZ0-0GLBG1"} };
}

void ReqLogout()
{
	auto myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_REQ_LOGOUT;
	WorkThread::GetInstance().OnEvent(myEvent);
}
void ReqTestRequest(const string& testReqID)
{
	WorkThread::GetInstance().OnEventTestRequest(testReqID);
}
void ReqNewOrder(int marketSegmentID, int volume, OrderType orderType, double price, const string& stopPrice = "")
{
	Sleep(5000);
	auto& marketSegment = g_MarketSegments[ItoA(marketSegmentID)];

	auto myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_REQ_NEW_ORDER;
	myEvent->NumParams.push_back(volume);
	myEvent->StringParams.push_back(marketSegment.MarketSegmentID);
	myEvent->StringParams.push_back(marketSegment.InstrumentIDs[0]);
	myEvent->StringParams.push_back(ToString(orderType));
	myEvent->StringParams.push_back(FtoA(price));
	myEvent->StringParams.push_back(stopPrice);
	WorkThread::GetInstance().OnEvent(myEvent);
}
void ReqOrderCancel(int origOrderLocalID)
{
	Sleep(5000);
	auto myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_REQ_ORDER_CANCEL;
	myEvent->StringParams.push_back(ItoA(origOrderLocalID));
	WorkThread::GetInstance().OnEvent(myEvent);
}
void ReqOrderCancelReplace(int origOrderLocalID, double newPrice, int newVolume)
{
	Sleep(5000);
	auto myEvent = MyEvent::Allocate();
	myEvent->EventID = EVENT_DO_REQ_ORDER_CANCEL_REPLACE;
	myEvent->StringParams.push_back(ItoA(origOrderLocalID));
	myEvent->StringParams.push_back(FtoA(newPrice));
	myEvent->NumParams.push_back(newVolume);
	WorkThread::GetInstance().OnEvent(myEvent);
}

int main(int argc, char* argv[])
{
	InitMarketSegMent();

	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();

	sqlite3* db = nullptr;
	sqlite3_open(DB_Name, &db);
	TradeApiTables::GetInstance().SetDB(db);
	TradeApiTables::GetInstance().CreateAllTables();
	TradeApiTables::GetInstance().SelectAllTables();


	TcpSelectClient* tcpClient = new TcpSelectClient(&WorkThread::GetInstance());
	TcpSelectServer* tcpServer = new TcpSelectServer(&WorkThread::GetInstance());
	tcpClient->SetTcpInfo();
	if (!tcpClient->Init())
	{
		WRITE_LOG(LogLevel::Error, "TcpSelectClient Init Failed.");
		return -1;
	}
	tcpClient->Start();

	WorkThread::GetInstance().SetTcpInfo(tcpClient, tcpServer);
	if (!WorkThread::GetInstance().Init())
	{
		WRITE_LOG(LogLevel::Error, "WorkThread Init Failed.");
		return -1;
	}
	WorkThread::GetInstance().Start();
	Sleep(20000);

	ReqTestRequest("");


	ReqNewOrder(925, 2, OrderType::LimitOrder, 2.5);
	Sleep(5000);
	ReqNewOrder(925, 4, OrderType::LimitOrder, 3.5);
	Sleep(5000);
	ReqNewOrder(925, 6, OrderType::LimitOrder, 4.5);

	//Sleep(10000);
	//ReqLogout();

	//Sleep(10000);
	//ReqNewOrder(925, 2, OrderType::LimitOrder, 2.5);
	//Sleep(1000);
	//ReqNewOrder(925, 4, OrderType::LimitOrder, 3.5);
	//Sleep(1000);
	//ReqNewOrder(925, 6, OrderType::LimitOrder, 4.5);
	
	//Sleep(10000);
	//ReqOrderCancelReplace(1, 1.5, 10);
	//Sleep(10000);
	//ReqOrderCancelReplace(1, 2.5, 10);
	//Sleep(10000);
	//ReqOrderCancelReplace(1, 3.5, 20);

	//ReqNewOrder(925, 2, OrderType::LimitOrder, "2.5", "");
	//Sleep(10000);
	//ReqNewOrder(925, 3, OrderType::LimitOrder, "3.5", "");
	//Sleep(10000);
	//ReqOrderCancel(3);
	//Sleep(10000);
	//ReqNewOrder(925, 4, OrderType::LimitOrder, "4.5", "");
	//Sleep(10000);
	//ReqOrderCancelReplace(5, 5.5, 10);
	while (true)
	{
		Sleep(10000);
	}

	

	WRITE_LOG(LogLevel::Info, "OnExit");
	tcpClient->Stop();
	tcpClient->Join();

	WorkThread::GetInstance().Stop();
	WorkThread::GetInstance().Join();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	sqlite3_close(db);
	return 0;
}

