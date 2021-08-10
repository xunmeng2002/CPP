#pragma once
#include "Event.h"
#include <vector>
#include <string>

using namespace std;



struct MyEvent : public Event
{
	vector<int> NumParams;
	vector<string> StringParams;

	static MyEvent* Allocate();
	virtual void Free() override;
};
