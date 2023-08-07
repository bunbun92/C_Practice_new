#include <stdio.h>
#include "thread.h"


int main(){

	Mutex m;
	Semaphore t(2, 3);
	HANDLE h;
	Thread a(m, t, h, 'a');
	Thread b(m, t, h, 'b');
	Thread c(m, t, h, 'c');

	a.start();

	Sleep(1000);

	b.start();
	Sleep(1000);

	c.start();

	Sleep(1000);

	a.join();
	b.join();
	c.join();


	return 0;
}