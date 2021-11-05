#pragma once
#include <string>
#include <unordered_map>

#define SOH 1
#define BUFF_SIZE 64 * 1024

class FixMessage;

FixMessage* PrepareReqHeader(const std::string& msgSeqNum = "");

int WriteString(char* buff, int size, const std::string& name, const std::string& value);
int WriteStream(char* ppos, int key, std::string value);


int CalculateSum(unsigned char* buff, int len);
bool GetItemEnd(char* buff, int len, int& itemLen);
bool ParseOneItem(char* buff, int len, int& tag, std::string& value);
