#pragma once
#include "quickfix/Field.h"
#include "quickfix/Message.h"
#include <string>

std::string GetCanonicalReq(const FIX::Message& logonMsg);

std::string calculateHMAC(std::string& key, std::string& canonicalRequest);

