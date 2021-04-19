#pragma once
#include "ThostFtdcUserApiDataType.h"


struct AccountInfo 
{
	TThostFtdcBrokerIDType	BrokerID;
	TThostFtdcUserIDType	UserID;
	TThostFtdcPasswordType	Password;
	TThostFtdcProductInfoType	UserProductInfo;
	TThostFtdcAuthCodeType	AuthCode;
	TThostFtdcAppIDType	AppID;
};
