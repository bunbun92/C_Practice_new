#include <stdio.h>
#include "thread.h"
#include "thread2.h"

int main(){


// 	Thread a[2];
// 
// 
// 	a[1].start();
// 
// 	Sleep(3000);
// 
// 
// 	a[0].start();
// 
// 	Sleep(5000);
// 
// 
// 	a[1].join();
// 	a[0].join();

// 	Mutex m;
// 	Thread a(m);
// 	Thread b(m);
// 
// 	a.start();
// 
// 
// 	b.start();
// 
// 	Sleep(20000);
// 	a.join();
// 	b.join();

	Thread2 a;
	Thread2 b;

	a.start();

	Sleep(1500);

	b.start();

	Sleep(30000);

	return 0;
}