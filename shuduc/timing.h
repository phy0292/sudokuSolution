#ifndef TIMING_H
#define TIMING_H

#include <time.h>
#include <stdio.h>

#ifdef __linux__
#include <unistd.h>  
typedef unsigned long long int64;  
#define timing_t int64  
#if defined(__i386__)  
inline int64 GetCycleCount() {  
    int64 result;  
    __asm__ __volatile__ ("rdtsc" : "=A" (result));  
    return result;  
}  
#elif defined(__x86_64__)  
inline int64 GetCycleCount()   
{  
    int64 hi, lo;  
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));  
    return ( (int64)lo)|( ((int64)hi)<<32 );  
}  
#endif  
  
//static int64 ticks_start, ticks_end;  
  
inline int64 nowTiming()  
{
	return GetCycleCount();  
}  
  
// unit: cycles  
inline int64 overDiffTiming(int64 oldTime)
{
	return GetCycleCount() - oldTime;
}
#else
#include <windows.h>  
//static _LARGE_INTEGER time_start, time_over;  


inline __int64 nowTiming()
{
	_LARGE_INTEGER time_start;
    QueryPerformanceCounter(&time_start);
    return time_start.QuadPart;
}
// unit: ms
/*inline timing_t stopTiming()
{
    QueryPerformanceCounter(&time_over);
    return ((double)(time_over.QuadPart-time_start.QuadPart)/dqFreq*1000);
}

inline timing_t stopWithPrintTiming()
{
    timing_t timing;
    QueryPerformanceCounter(&time_over);
    timing = ((double)(time_over.QuadPart-time_start.QuadPart)/dqFreq*1000);
    printf("----------Elapsed Timing(ms) : %.3lf----------\n", timing);
    return timing;
}*/
/*inline __int64 twoDiffTiming(__int64 start_time, __int64 stop_time)
{
    _LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
	return (stop_time-start_time)/(f.QuadPart/1000);
}*/
inline __int64 overDiffTiming(__int64 oldTime)
{//参数是之前的时间，求现在与之前的时间差，返回毫秒 
	_LARGE_INTEGER time_over;
    QueryPerformanceCounter(&time_over);
    
    _LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
	return (time_over.QuadPart-oldTime)/(f.QuadPart/1000);
}
#endif
#endif

