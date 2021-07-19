#pragma once
#include "TradeApiDataStruct.h"
#include "TradeApiReqFields.h"
#include <string>

std::string GetCanonicalReq(const ReqLogonField& reqLogon);

std::string calculateHMAC(std::string& key, std::string& canonicalRequest);

