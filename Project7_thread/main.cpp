#include <stdio.h>
#include "thread.h"


int main(){

	Mutex m;
	Semaphore t;
	HANDLE h;
	Thread a(m, t, h);
	Thread b(m, t, h);

	a.start();

	Sleep(1000);

	b.start();

	Sleep(30000);

	return 0;
}