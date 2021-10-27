#include "Utility.h"
#include <iostream>

using namespace std;



void ParseProcessName(const char* fullProcessName, char* processName, int len)
{
	const char* temp = strrchr(fullProcessName, '\\');
	if (temp != NULL)
	{
		temp++;
	}
	else
	{
		temp = fullProcessName;
	}
	char* last_pos;
	temp = strtok_s((char*)temp, ".", &last_pos);
	strncpy(processName, temp, len);
}

string ItoA(int value)
{
	static char buff[32];
	sprintf(buff, "%d", value);
	return string(buff);
}

string FtoA(double value)
{
	static char buff[32];
	sprintf(buff, "%f", value);
	return string(buff);
}

