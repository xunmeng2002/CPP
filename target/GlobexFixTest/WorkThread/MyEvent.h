#pragma once

#include <vector>
#include <string>

using namespace std;

#define EVENT_CONNECTED 1
#define EVENT_DISCONNECTED 2
#define EVENT_ON_SEQUENCE_GAP 3
#define EVENT_DO_RESEND_REQUEST 4
#define EVENT_DO_TEST_REQUEST 5
#define EVENT_DO_REQ_LOGOUT 6

#define EVENT_DO_REQ_NEW_ORDER 10

struct MyEvent
{
	int EventID;
	vector<int> NumParams;
	vector<string> StringParams;

	static MyEvent* Allocate();
	static void Free(MyEvent* myEvent);
};
