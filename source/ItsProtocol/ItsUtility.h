#pragma once
#include <string>
#include <vector>

using namespace std;

void GetItsItems(const char* buff, const char* end, vector<string>& items);

const char* GetItsItemEnd(const char* buff, const char* end, char op = '|');

bool CheckItsMessage(const vector<string>& items);
