#include <stdio.h>
#include "combi.h"
#include "bitmap.h"
#include "Timer.h"
#include "Ham.h"

int main(){

	Ham h;

	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

	// h.combi(a, sizeof(a) * 0.25, 5);
	h.combi2(a, sizeof(a) * 0.25, 7, 3);

	return 0;
}