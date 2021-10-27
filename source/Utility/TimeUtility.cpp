#include "TimeUtility.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <sys/timeb.h>

using namespace std;

tm* GetTime()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	time_t t = std::chrono::system_clock::to_time_t(now);
	return std::localtime(&t);
}

long long GetUnixTimeStamp()
{
	return time(nullptr);
}
string GetDateFromUnixTimeStamp(long long timeStamp)
{
	static char buff[16];
	int len = strftime(buff, 16, "%Y%m%d", localtime(&timeStamp));
	return string(buff);
}
string GetTimeFromUnixTimeStamp(long long timeStamp)
{
	static char buff[16];
	int len = strftime(buff, 16, "%H:%M:%S", localtime(&timeStamp));
	return string(buff);
}

string GetFormatDateTime()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

	static char buff[32];
	time_t t = std::chrono::system_clock::to_time_t(now);
	int len = strftime(buff, 32, "%Y%m%d %H:%M:%S", localtime(&t));
	len = _snprintf(buff + len, 32 - len, ".%03d", int(ms.time_since_epoch().count() % 1000));
	return string(buff);
}
string GetFormatDate()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

	static char buff[16];
	time_t t = std::chrono::system_clock::to_time_t(now);
	int len = strftime(buff, 16, "%Y%m%d", localtime(&t));
	return string(buff);
}
string GetFormatTime()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

	static char buff[16];
	time_t t = std::chrono::system_clock::to_time_t(now);
	int len = strftime(buff, 16, "%H:%M:%S", localtime(&t));
	return string(buff);
}
string GetFormatTimeMilliSecond()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

	static char buff[32];
	time_t t = std::chrono::system_clock::to_time_t(now);
	int len = strftime(buff, 32, "%H:%M:%S", localtime(&t));
	len = _snprintf(buff + len, 32 - len, ".%03d", int(ms.time_since_epoch().count() % 1000));
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
string GetDateFromUtcTime(string utcTime)
{
	return string(utcTime.begin(), utcTime.begin() + 8);
}
string GetTimeFromUtcTime(string utcTime)
{
	return string(utcTime.begin() + 9, utcTime.begin() + 17);
}
