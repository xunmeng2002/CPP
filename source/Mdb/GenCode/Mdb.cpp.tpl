#include "Mdb.h"

!!formatSymbols = {}!!
!!formatSymbols["string"] = "s"!!
!!formatSymbols["int"] = "d"!!
!!formatSymbols["double"] = "f"!!
!!formatSymbols["enum"] = "c"!!

!!entry tables!!
!!travel!!
int !!@name!!::ToString(char* buff, int size) const
{
!!entry items!!
	return snprintf(buff, size, "!!@name!!: !!travel!!!!if pumpid > 1:!!!!inc indent!!, !!dec indent!!!!@name!!!!itemType=formatSymbols[@type]!!:[%!!$itemType!!]!!leave!!",
		!!travel!!!!if pumpid > 1:!!!!inc indent!!, !!dec indent!!!!@name!!!!if @type == "string":!!!!inc indent!!.c_str()!!dec indent!!!!leave!!);
!!leave!!
}

!!leave!!
!!leave!!