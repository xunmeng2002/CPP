#include "Logger.h"
#include "MdbEngine.h"
#include "ItsEngine.h"
#include "FixEngine.h"
#include "Config.h"
#include "Udp.h"
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

	Config::GetInstance().Load();
	auto& config = Config::GetInstance();

	ItsEngine* itsEngine = new ItsEngine();
	MdbEngine* mdbEngine = new MdbEngine();
	FixEngine* fixEngine = new FixEngine();

	Udp::GetInstance().SetBindAddress("127.0.0.1");
	Udp::GetInstance().SetRemoteAddress("127.0.0.1", atoi(config.BroadCastPort.c_str()));
	Udp::GetInstance().Init(true);
	itsEngine->SetBindAddress("127.0.0.1", atoi(config.ListenPort.c_str()));
	fixEngine->RegisterAddress(config.CmeGlobexIP.c_str(), atoi(config.CmeGlobexPrimaryPort.c_str()), config.CmeGlobexIP.c_str(), atoi(config.CmeGlobexBackupPort.c_str()));

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

