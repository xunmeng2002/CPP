#include "Logger.h"
#include "MdbEngine.h"
#include "ItsEngine.h"
#include "FixEngine.h"
#include "AccountInfo.h"
#include "UdpServer.h"
#include "CmeMonthMap.h"
#include <iostream>

using namespace std;

constexpr char* ItsdbName = "Its.db";
constexpr char* FixdbName = "Fix.db";
constexpr char* MdbName = "Mdb.db";



int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();

	AccountInfo::GetInstance().Load();
	auto& accountInfo = AccountInfo::GetInstance();

	ItsEngine* itsEngine = new ItsEngine();
	MdbEngine* mdbEngine = new MdbEngine();
	FixEngine* fixEngine = new FixEngine();

	UdpServer::GetInstance().SetBindAddress("127.0.0.1");
	UdpServer::GetInstance().SetBroadAddress("127.0.0.1", atoi(accountInfo.BroadCastPort.c_str()));
	UdpServer::GetInstance().Init();
	itsEngine->SetBindAddress("127.0.0.1", atoi(accountInfo.ListenPort.c_str()));
	fixEngine->RegisterAddress(AccountInfo::GetInstance().CmeGlobexIP.c_str(), atoi(AccountInfo::GetInstance().CmeGlobexPrimaryPort.c_str()), AccountInfo::GetInstance().CmeGlobexIP.c_str(), atoi(AccountInfo::GetInstance().CmeGlobexBackupPort.c_str()));

	itsEngine->RegisterSubscriber(mdbEngine);
	mdbEngine->RegisterItsPublisher(itsEngine);

	mdbEngine->RegisterSubscriber(fixEngine);
	fixEngine->RegisterMdbPublisher(mdbEngine);

	itsEngine->Init(ItsdbName);
	mdbEngine->Init(MdbName);
	fixEngine->Init(FixdbName);

	itsEngine->Start();
	mdbEngine->Start();
	fixEngine->Start();

	while (true)
	{
		Sleep(10000);
	}

	WRITE_LOG(LogLevel::Info, "OnExit");
	itsEngine->Stop();
	itsEngine->Join();
	
	fixEngine->Stop();
	fixEngine->Join();

	mdbEngine->Stop();
	mdbEngine->Join();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();
	return 0;
}

