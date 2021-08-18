#include "TradeApiItems.h"

using namespace std;

TradeApiItems TradeApiItems::m_Instance;

!!entry items!!
TradeApiItems::TradeApiItems()
{
!!travel!!
	m_TradeApiItems["!!@name!!"] = !!@key!!;
!!leave!!
}

TradeApiItems& TradeApiItems::GetInstance()
{
	return m_Instance;
}

int TradeApiItems::GetItemKey(std::string name)
{
	return m_TradeApiItems[name];
}

!!leave!!
