#include "Utility.h"
#include <iostream>
#include <time.h>
#include "Logger.h"

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

void GetDateTime(char* currDate, char* currTime)
{
	time_t ltime;
	struct tm* now;
	time(&ltime);
	now = localtime(&ltime);

	static char time_buffer[21];
	if (currDate)
	{
		sprintf(time_buffer, "%04d%02d%02d",
			now->tm_year + 1900,
			now->tm_mon + 1,
			now->tm_mday);
		strcpy(currDate, time_buffer);
	}

	if (currTime)
	{
		sprintf(time_buffer, "%02d:%02d:%02d",
			now->tm_hour,
			now->tm_min,
			now->tm_sec);
		strcpy(currTime, time_buffer);
	}
}

