#include "FixItems.h"

using namespace std;

FixItems FixItems::m_Instance;

!!entry items!!
FixItems::FixItems()
{
!!travel!!
	m_FixItems["!!@name!!"] = !!@key!!;
!!leave!!
}

FixItems& FixItems::GetInstance()
{
	return m_Instance;
}

int FixItems::GetItemKey(std::string name)
{
	return m_FixItems[name];
}

!!leave!!
