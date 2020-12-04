#include "TimeUtility.h"
#include <iostream>
#include <ctime>

using namespace std;

tm* GetTime()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	time_t t = std::chrono::system_clock::to_time_t(now);
	return std::localtime(&t);
}

int GetTimeStamp()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

	time_t t = std::chrono::system_clock::to_time_t(now);
	std::tm tm = *std::localtime(&t);

	return (tm.tm_hour * 10000 + tm.tm_min * 100 + tm.tm_sec) * 1000 + ms.time_since_epoch().count() % 1000;
}

void GetFormatDateTime(char* buff, int size)
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

	time_t t = std::chrono::system_clock::to_time_t(now);
	int len = strftime(buff, size, "%Y%m%d  %H:%M:%S", localtime(&t));
	snprintf(buff + len, uint64_t(size) - len, ".%03d", int(ms.time_since_epoch().count() % 1000));
}

void GetFormatTime(char* buff, int size)
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

	time_t t = std::chrono::system_clock::to_time_t(now);
	int len = strftime(buff, size, "%H:%M:%S", localtime(&t));
	snprintf(buff + len, uint64_t(size) - len, ".%03d", int(ms.time_since_epoch().count() % 1000));
}

