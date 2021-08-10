#include "Common.h"
#include <time.h>
#include <sys/timeb.h>


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

string GetUtcTime()
{
    struct timeb timePoint;
    ftime(&timePoint);
    auto tmTime = gmtime(&timePoint.time);

    char buff[32];
    auto len = strftime(buff, sizeof(buff), "%Y%m%d-%H:%M:%S", gmtime(&timePoint.time));
    sprintf(buff + len, ".%03u", timePoint.millitm);
    return string(buff);
}