#pragma once

#include <map>
#include <string>

using namespace std;



class CmeMonthMap
{
	CmeMonthMap();
public:
	static CmeMonthMap GetInstance();
	string GetMonthLetter(string month);
	string GetMonthNum(string letter);


private:
	static CmeMonthMap m_Instance;
	std::map<string, string> m_CmeMonthMap;
};


