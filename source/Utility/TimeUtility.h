#pragma once

#include <chrono>


#define TIMERSTART(tag)  auto tag##_start = std::chrono::steady_clock::now()
#define TIMEREND(tag)  auto tag##_end =  std::chrono::steady_clock::now()
#define DURATION_s(tag) std::chrono::duration_cast<std::chrono::seconds>(tag##_end - tag##_start).count()
#define DURATION_ms(tag) std::chrono::duration_cast<std::chrono::milliseconds>(tag##_end - tag##_start).count()
#define DURATION_us(tag) std::chrono::duration_cast<std::chrono::microseconds>(tag##_end - tag##_start).count()
#define DURATION_ns(tag) std::chrono::duration_cast<std::chrono::nanoseconds>(tag##_end - tag##_start).count()

void GetDateTime(char* currDate, char* currTime);

tm* GetTime();

int GetTimeStamp();

void GetFormatDateTime(char* buff, int size);

void GetFormatTime(char* buff, int size);