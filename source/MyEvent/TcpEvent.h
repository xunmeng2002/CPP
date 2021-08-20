#pragma once
#include "Event.h"

using namespace std;

constexpr int BuffSize = 64 * 1024;

struct TcpEvent : public Event
{
	TcpEvent(int buffSize = 64 * 1024);
	~TcpEvent();
	int SessionID;
	string IP;
	int Port;
	char* ReadPos;
	char* Buff;
	int Length;


	static TcpEvent* Allocate();
	virtual void Free() override;
};
