#pragma once
#include "Event.h"

using namespace std;


struct TcpEvent : public Event
{
	TcpEvent(int buffSize = 64 * 1024);
	~TcpEvent();
	int SessionID;
	char* ReadPos;
	char* Buff;
	int Length;


	static TcpEvent* Allocate();
	virtual void Free() override;
};
