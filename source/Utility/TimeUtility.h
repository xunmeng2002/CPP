#pragma once

#include <chrono>


#define TIMERSTART(tag)  auto tag##_start = std::chrono::steady_clock::now()
#define TIMEREND(tag)  auto tag##_end =  std::chrono::steady_clock::now()
#define DURATION_s(tag) std::chrono::duration_cast<std::chrono::seconds>(tag##_end - tag##_start).count()
#define DURATION_ms(tag) std::chrono::duration_cast<std::chrono::milliseconds>(tag##_end - tag##_start).count()
#define DURATION_us(tag) std::chrono::duration_cast<std::chrono::microseconds>(tag##_end - tag##_start).count()
#define DURATION_ns(tag) std::chrono::duration_cast<std::chrono::nanoseconds>(tag##_end - tag##_start).count()

tm* GetTime();

int GetTimeStamp();

//write format datetime into buff. format:YYYYMMDD HH:mm:ss.ms
void GetFormatDateTime(char* buff, int size);
//write format time into buff. format:HH:mm:ss.ms
void GetFormatTime(char* buff, int size);

template<typename T>
long long GetDuration(std::chrono::system_clock::time_point& start, std::chrono::system_clock::time_point& end)
{
	return std::chrono::duration_cast<T>(end - start).count();
}