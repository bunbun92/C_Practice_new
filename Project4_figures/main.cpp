#include <stdio.h>
#include <string.h>
#include <math.h>
#include "distance.h"
#include "print.h"
#include "img.h"
#include "list.h"

typedef unsigned char uint8;

int main(){

	BinImg a;
	BinImg* b= &a;

	bim_init(b);
	bim_alloc(b, 40, 40);

/*	drawLine(b, 2, 2, 33, 2, 1);*/
	/*drawLine(b, 2, 10, 12, 16, 1);*/
/*	drawLine2(b, 2, 14, 33, 35, 1);*/
	/*drawCircle(b, 20, 20, 14);*/
	drawCircle2(b, 20, 20, 14);
	draw(b);

	free(b);

	puts("");


// 	int r= 4;
// 	float x= 0;
// 	float y= 0;
// 	float A = 270;
// 	float radianA = A * 3.141592 / 180;
// 
// 	printf("%.2lf %.2lf %.2lf", sin(radianA), cos(radianA), tan(radianA));
// 	puts("");
// 	x= r * cos(radianA);
// 	y= r * sin(radianA);
// 	printf("%.2lf %.2lf", x, y);
// 	puts("");

	return 0;
}