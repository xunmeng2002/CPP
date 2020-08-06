#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>

using namespace std;

class BaseRecord
{
public:
	int BrokerID;
	int AccountID;
};

class ReqOrder
{
public:
	int OrderLocalID;
	int Volume;
	string StatusMsg;
};



#endif
