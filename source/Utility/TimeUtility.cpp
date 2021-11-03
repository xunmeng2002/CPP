#include "TimeUtility.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <sys/timeb.h>

using namespace std;


time_t GetTime()
{
	chrono::system_clock::time_point now = chrono::system_clock::now();
	return chrono::system_clock::to_time_t(now);
}
tm* GetUtcTm()
{
	time_t t = GetTime();
	return gmtime(&t);
}
tm* GetLocalTm()
{
	time_t t = GetTime();
	return localtime(&t);
}
string GetUtcDateTime()
{
	auto t = GetTime();
	auto localTm = gmtime(&t);
	char buff[32];
	strftime(buff, 32, "%Y%m%d-%H:%M:%S", localTm);
	return string(buff);
}
string GetUtcDate()
{
	auto t = GetTime();
	auto localTm = gmtime(&t);
	char buff[32];
	strftime(buff, 32, "%Y%m%d", localTm);
	return string(buff);
}
string GetUtcTime()
{
	auto t = GetTime();
	auto localTm = gmtime(&t);
	char buff[32];
	strftime(buff, 32, "%H:%M:%S", localTm);
	return string(buff);
}
string GetUtcDateTimeWithMilliSecond()
{
	auto now = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
	time_t t = chrono::system_clock::to_time_t(now);
	int milliSecond = now.time_since_epoch().count() % 1000;
	auto localTm = gmtime(&t);
	char buff[32];
	int len = strftime(buff, 32, "%Y%m%d-%H:%M:%S", localTm);
	sprintf(buff + len, ".%03u", milliSecond);
	return string(buff);
}
string GetLocalDateTime()
{
	auto t = GetTime();
	auto localTm = localtime(&t);
	char buff[32];
	strftime(buff, 32, "%Y%m%d-%H:%M:%S", localTm);
	return string(buff);
}
string GetLocalDate()
{
	auto t = GetTime();
	auto localTm = localtime(&t);
	char buff[32];
	strftime(buff, 32, "%Y%m%d", localTm);
	return string(buff);
}
string GetLocalTime()
{
	auto t = GetTime();
	auto localTm = localtime(&t);
	char buff[32];
	strftime(buff, 32, "%H:%M:%S", localTm);
	return string(buff);
}
string GetLocalDateTimeWithMilliSecond()
{
	auto now = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
	time_t t = chrono::system_clock::to_time_t(now);
	int milliSecond = now.time_since_epoch().count() % 1000;
	auto localTm = localtime(&t);
	char buff[32];
	int len = strftime(buff, 32, "%Y%m%d-%H:%M:%S", localTm);
	sprintf(buff + len, ".%03u", milliSecond);
	return string(buff);
}

string GetLocalDateFromUnixTimeStamp(long long timeStamp)
{
	time_t time = timeStamp / 1000000000LL;
	static char buff[16];
	int len = strftime(buff, 16, "%Y%m%d", localtime(&time));
	return string(buff);
}
string GetLocalTimeFromUnixTimeStamp(long long timeStamp)
{
	time_t time = timeStamp / 1000000000LL;
	static char buff[16];
	int len = strftime(buff, 16, "%H:%M:%S", localtime(&time));
	return string(buff);
}

time_t GetTimeFromString(string dateTime, string format)
{
	tm t;
	int len = sscanf(dateTime.c_str(), format.c_str(), &t.tm_year, &t.tm_mon, &t.tm_mday, &t.tm_hour, &t.tm_min, &t.tm_sec);
	t.tm_year -= 1900;
	t.tm_mon -= 1;

	return mktime(&t);
}
string ToUtcDateTime(time_t* time)
{
	char buff[32];
	strftime(buff, 32, "%Y%m%d-%H:%M:%S", gmtime(time));
	return string(buff);
}
string ToUtcDate(time_t* time)
{
	char buff[32];
	strftime(buff, 32, "%Y%m%d", gmtime(time));
	return string(buff);
}
string ToUtcTime(time_t* time)
{
	char buff[32];
	strftime(buff, 32, "%H:%M:%S", gmtime(time));
	return string(buff);
}
string ToLocalDateTime(time_t* time)
{
	char buff[32];
	strftime(buff, 32, "%Y%m%d-%H:%M:%S", localtime(time));
	return string(buff);
}
string ToLocalDate(time_t* time)
{
	char buff[32];
	strftime(buff, 32, "%Y%m%d", localtime(time));
	return string(buff);
}
string ToLocalTime(time_t* time)
{
	char buff[32];
	strftime(buff, 32, "%H:%M:%S", localtime(time));
	return string(buff);
}
