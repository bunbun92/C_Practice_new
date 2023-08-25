#ifndef def_h__
#define def_h__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <Windows.h>
#pragma warning(disable:4267) 
#pragma warning(disable:4244) 
#pragma warning(disable:4018) 
using namespace std;

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

#define _Delete(p) if ((p)) { delete p; p=0; }
#define _In(s, x, e) ((s)<=(x) && (x)<(e))
#define _ABS(a) ((a)<=0 ? -(a) : (a))

inline HANDLE thread_start(int(*thr)(void*), void* para) {
	return CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thr, para, 0, 0);
}
inline uint32 GetClock() {
	static bool bInit=0;
	static LARGE_INTEGER ticksPerSec;
	if (bInit==0) {
		QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSec);
		bInit=1;
	}
	LARGE_INTEGER ticks;
	QueryPerformanceCounter((LARGE_INTEGER*)&ticks);
	double t= (double)ticks.QuadPart / (double)ticksPerSec.QuadPart * 1000.;
	return (uint32)t;
}
inline char* strdup(char* s) {
	char* n = new char[strlen(s)+1];
	strcpy(n, s);
	return n;
}

#endif // def_h__
