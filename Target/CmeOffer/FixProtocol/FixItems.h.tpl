#pragma once
#include <string>
#include <map>


!!entry ReqFields!!
!!travel!!
constexpr auto FIX_Message_!!@name!! = "!!@msgtype!!";
!!leave!!
!!leave!!

!!entry RspFields!!
!!travel!!
constexpr auto FIX_Message_!!@name!! = "!!@msgtype!!";
!!leave!!
!!leave!!


!!entry items!!
!!travel!!
constexpr auto FIX_!!@name!! = !!@key!!;
!!leave!!
!!leave!!


class FixItems
{
	FixItems();
	FixItems(const FixItems&) = delete;
	FixItems& operator=(const FixItems&) = delete;
public:
	static FixItems& GetInstance();
	int GetItemKey(std::string name);
	
private:
	static FixItems m_Instance;
	std::map<std::string, int> m_FixItems;
};
