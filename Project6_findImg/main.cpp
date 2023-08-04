#include <stdio.h>
/*#include "combi.h"*/
/*#include "bitmap.h"*/
#include "Timer.h"
#include "Ham.h"
#include "IDSet.h"

#define RIF(x) if((x) == 0) { puts(""#x); return 0; }

int main(){

	Ham h;

	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

	// h.combi(a, sizeof(a) * 0.25, 5);
	h.combi2(a, sizeof(a) * 0.25, 7, 3);	

	char test[64];
	char test2[64];
	char test3[64];


	/*f.open("tok/952837_stat.txt");*/
// 
// 	f.readLine(test);
// 	f.readLine(test2);
// 	f.readLine(test3);
// 	printf("%x %x %x %d\n", test[13], test[14], *((uint16*)&test[13]), *((uint16*)&test[13]) == 0x0a0e);
// 	f.close();

// 	IDSet a;
// 	IDSet b;
// 	IDSet c;
// 
// 	a.open("tok/952837_stat.txt");
// 	/*a.open("tok/test.txt");*/
// 	b.open("tok/952837.txt");

	/*c.open("tok/result.txt", "w+b");*/

	puts("");

	return 0;
}