#pragma once

#include <chrono>
#include <string>

using namespace std;

#define TIMERSTART(tag)  auto tag##_start = std::chrono::steady_clock::now()
#define TIMEREND(tag)  auto tag##_end =  std::chrono::steady_clock::now()
#define DURATION_s(tag) std::chrono::duration_cast<std::chrono::seconds>(tag##_end - tag##_start).count()
#define DURATION_ms(tag) std::chrono::duration_cast<std::chrono::milliseconds>(tag##_end - tag##_start).count()
#define DURATION_us(tag) std::chrono::duration_cast<std::chrono::microseconds>(tag##_end - tag##_start).count()
#define DURATION_ns(tag) std::chrono::duration_cast<std::chrono::nanoseconds>(tag##_end - tag##_start).count()

tm* GetTime();

long long GetUnixTimeStamp();
string GetDateFromUnixTimeStamp(long long timeStamp);
string GetTimeFromUnixTimeStamp(long long timeStamp);

string GetFormatDateTime();
string GetFormatDate();
string GetFormatTime();
string GetFormatTimeMilliSecond();
std::string GetUtcTime();
string GetDateFromUtcTime(string utcTime);
string GetTimeFromUtcTime(string utcTime);

template<typename T>
long long GetDuration(std::chrono::system_clock::time_point& start, std::chrono::system_clock::time_point& end)
{
	return std::chrono::duration_cast<T>(end - start).count();
}
