#pragma once
#include "EnumDict.h"
#include <string>

using namespace std;

!!entry tables!!
!!travel!!
class !!@name!!
{
public:
!!entry items!!
!!travel!!
!!if @type == "enum":!!
!!inc indent!!
	!!@name!! !!@name!!;
!!dec indent!!
!!else:!!
!!inc indent!!
	!!@type!! !!@name!!;
!!dec indent!!
!!leave!!
!!leave!!

	int ToString(char* buff, int size) const;
};

!!leave!!
!!leave!!
