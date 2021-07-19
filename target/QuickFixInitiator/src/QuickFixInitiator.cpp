#include "Logger.h"
#include "TradeApi.h"
#include "ApplicationImpl.h"
#include "MessageCrackerImpl.h"
#include "quickfix/SessionSettings.h"
#include "quickfix/FileStore.h"
#include "quickfix/Log.h"
#include "quickfix/SocketInitiator.h"
#include <iostream>


using namespace std;

#define CONFIG_FILE "./iLinkSession.txt"


int main(int argc, char* argv[])
{
	Logger::GetInstance().Init(argv[0]);
	Logger::GetInstance().Start();
	string configFile = CONFIG_FILE;
	cout << "ConfigFile:" << configFile << endl;

	FIX::SessionSettings settings(configFile);
	FIX::FileStoreFactory storeFactory(settings);
	FIX::ScreenLogFactory logFactory(settings);

	MessageCrackerImpl messageCracker;
	ApplicationImpl application(&messageCracker);
	FIX::SynchronizedApplication SynApp(application);

	FIX::Initiator* initiator = new FIX::SocketInitiator(SynApp, storeFactory, settings, logFactory);
	initiator->start();
	
	while (true)
	{
		Sleep(30000);
	}

	initiator->stop();

	Logger::GetInstance().Stop();
	Logger::GetInstance().Join();

	return 0;
}

