#pragma once
#include "FixFields.h"
#include <string>

std::string GetCanonicalReq(const FixReqLogonField& reqLogon);

std::string calculateHMAC(std::string& key, std::string& canonicalRequest);

