#pragma once
#include <string>

using namespace std;

!!entry dict!!
!!travel!!
constexpr auto FIX_!!@name!! = "!!@value!!";
!!leave!!
!!leave!!

!!entry enums!!
!!travel!!
enum class Fix!!@name!! : char
{
!!travel!!
	//!!@desc!!
	!!@name!! = '!!@value!!',
!!leave!!
};

!!leave!!

!!travel!!
Fix!!@name!! ConvertToFix!!@name!!(const string& value);
!!leave!!
!!leave!!
