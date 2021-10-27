#pragma once
#include <string>
#include "FixMessage.h"

using namespace std;

class FixAuditTrail
{
public:
	FixAuditTrail();
	~FixAuditTrail();
	void SetMessage(FixMessage* fixMessage, string messageDirection);
	char* ToString() const;

public:
!!entry AuditTrail!!
!!travel!!
	string !!@name!!;
!!leave!!

private:
	char* Buff;
	int SendIndex;
	int RecvIndex;
};

constexpr char FixAuditTrailHeader[] = "!!travel!!!!if $pumpid > "1":!!!!inc indent!!, !!dec indent!!!!@desc!!!!leave!!\n";

!!leave!!
