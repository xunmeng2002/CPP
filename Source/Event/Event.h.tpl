#pragma once
#include <string>
#include <vector>

using namespace std;


constexpr int BuffSize = 64 * 1024;

struct Event
{
	int EventID;

	static Event* Allocate();
	virtual void Free();
};

struct TcpEvent : public Event
{
	TcpEvent(int buffSize = BuffSize);
	~TcpEvent();
	int SessionID;
	string IP;
	int Port;
	char* ReadPos;
	char* Buff;
	int Length;


	static TcpEvent* Allocate();
	virtual void Free() override;
	virtual void Shift(int len);
};

struct MyEvent : public Event
{
	void* Field;
	vector<int> NumParams;
	vector<string> StringParams;

	static MyEvent* Allocate();
	virtual void Free() override;
};


!!travel!!
!!startID = @startID!!
!!travel!!
!!id = int(startID) + pumpid!!
constexpr int Event!!@name!! = !!$id!!;		//!!@desc!!
!!leave!!


!!leave!!
