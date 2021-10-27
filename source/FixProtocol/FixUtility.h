#pragma once
#include <string>
#include <unordered_map>
#include "AccountInfo.h"

#define SOH 1
#define BUFF_SIZE 64 * 1024

class FixMessage;

FixMessage* PrepareReqHeader(const std::string& msgSeqNum = "");

int WriteString(char* buff, int size, const string& name, const string& value);
int WriteStream(char* ppos, int key, string value);


int CalculateSum(unsigned char* buff, int len);
bool GetItemEnd(char* buff, int len, int& itemLen);
bool ParseOneItem(char* buff, int len, int& tag, string& value);
