#include "EnumDict.h"


!!entry enums!!
!!travel!!
string ToString(!!@name!! value)
{
	return string(1, (char)value);
}
!!@name!! !!@name!!Convert(const string& value)
{
	return (!!@name!!)value[0];
}
!!leave!!
!!leave!!

