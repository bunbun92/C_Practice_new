#include  <windows.h>
typedef unsigned int uint32;

inline uint32 GetClock(){
	static bool bInit= 0;
	static LARGE_INTEGER ticksPerSec;

	if (bInit == 0){
		QueryPerformanceFrequency((LARGE_INTEGER*) &ticksPerSec);
		bInit = 1;
	}
	LARGE_INTEGER ticks;
	QueryPerformanceCounter((LARGE_INTEGER*) &ticks);
	double t = (double)ticks.QuadPart / (double) ticksPerSec.QuadPart * 1000.;
	return (uint32)t;
}

class Timer{
	uint32 s;

public:
	Timer() {on();}

	void on(){ s= GetClock();}
	int off(bool re=0){
		int r = GetClock()-s;
		if(re)
			on();
		return r;
	}
};