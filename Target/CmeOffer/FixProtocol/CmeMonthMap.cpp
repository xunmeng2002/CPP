#include "CmeMonthMap.h"


CmeMonthMap CmeMonthMap::m_Instance;
CmeMonthMap::CmeMonthMap()
{
	m_CmeMonthMap = {
	{"01", "F"},
	{"02", "G"},
	{"03", "H"},
	{"04", "J"},
	{"05", "K"},
	{"06", "M"},
	{"07", "N"},
	{"08", "Q"},
	{"09", "U"},
	{"10", "V"},
	{"11", "X"},
	{"12", "Z"}
	};
}
CmeMonthMap CmeMonthMap::GetInstance()
{
	return m_Instance;
}
string CmeMonthMap::GetMonthLetter(string month)
{
	return m_CmeMonthMap[month];
}
string CmeMonthMap::GetMonthNum(string letter)
{
	auto it = find_if(m_CmeMonthMap.begin(), m_CmeMonthMap.end(), [&](const std::pair<string, string>& it) {
		return it.second == letter;
		});
	if (it == m_CmeMonthMap.end())
	{
		return "";
	}
	return it->first;
}
