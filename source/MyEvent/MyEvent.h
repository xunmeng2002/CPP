#pragma once

#include <vector>
#include <string>

using namespace std;

#define EVENT_CONNECT 1
#define EVENT_DISCONNECT 2
#define EVENT_ON_CONNECTED 3
#define EVENT_ON_DISCONNECTED 4
#define EVENT_ON_SEQUENCE_GAP 10
#define EVENT_DO_RESEND_REQUEST 11
#define EVENT_DO_TEST_REQUEST 12
#define EVENT_DO_REQ_LOGOUT 13
#define EVENT_DO_REQ_NEW_ORDER 20

struct MyEvent
{
	int EventID;
	vector<int> NumParams;
	vector<string> StringParams;

	static MyEvent* Allocate();
	static void Free(MyEvent* myEvent);
};
