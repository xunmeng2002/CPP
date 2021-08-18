#pragma once
#include <string>
#include <map>

!!entry items!!
!!travel!!
constexpr auto KEY_!!@name!! = !!@key!!;
!!leave!!
!!leave!!


class TradeApiItems
{
	TradeApiItems();
	TradeApiItems(const TradeApiItems&) = delete;
	TradeApiItems& operator=(const TradeApiItems&) = delete;
public:
	static TradeApiItems& GetInstance();
	int GetItemKey(std::string name);
	
private:
	static TradeApiItems m_Instance;
	std::map<std::string, int> m_TradeApiItems;
};
