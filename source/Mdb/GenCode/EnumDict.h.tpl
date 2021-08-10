#pragma once
#include <string>

using namespace std;

!!entry enums!!
!!travel!!
enum class !!@name!! : char
{
!!travel!!
	!!@name!! = '!!@value!!',
!!leave!!
};

!!leave!!
!!travel!!
string ToString(!!@name!! value);
!!@name!! !!@name!!Convert(const string& value);
!!leave!!
!!leave!!
