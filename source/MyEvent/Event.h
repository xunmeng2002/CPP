#pragma once

#include <vector>
#include <string>

using namespace std;

#define EVENT_CONNECT 1
#define EVENT_DISCONNECT 2
#define EVENT_ON_CONNECTED 3
#define EVENT_ON_DISCONNECTED 4
#define EVENT_ON_TCP_SEND 5
#define EVENT_ON_TCP_RECV 6
#define EVENT_ON_SEQUENCE_GAP 10
#define EVENT_ON_RESEND_LAST_RESEND_REQUEST 11
#define EVENT_DO_RESEND_REQUEST 12
#define EVENT_DO_TEST_REQUEST 13
#define EVENT_DO_REQ_LOGOUT 14
#define EVENT_DO_REQ_NEW_ORDER 20
#define EVENT_DO_REQ_ORDER_CANCEL 21
#define EVENT_DO_REQ_ORDER_CANCEL_REPLACE 22


struct Event
{
	int EventID;

	static Event* Allocate();
	virtual void Free();
};
