#pragma once
#include <string>

using namespace std;

!!entry enums!!
!!travel!!
enum class !!@name!! : char
{
!!travel!!
	//!!@desc!!
	!!@name!! = '!!@value!!',
!!leave!!
};

!!leave!!

!!travel!!
!!@name!! ConvertTo!!@name!!(const string& value);
!!leave!!
!!leave!!
