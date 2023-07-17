#include <stdio.h>
#include <string.h>
#include "distance.h"
#include "print.h"
#include "img.h"

typedef unsigned char uint8;

int main(){
// 
// 	uint8 R[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 11, 15};
// 	uint8 Q[] = {4, 5, 6, 8, 7, 8};

// 	float d = 0;
// 	float* pd = &d;
// 	uint8 location = 0;
// 	uint8* p = &location;
// 		
// 	p = find_best_match(R, Q, 14, 6, pd, 0);
// 	printf("%d %.2lf\n", *p, *pd);
	
// 	print_1(50);
// 	print_2(80, 70);
// 
// 	int w = 16;
// 	int h = 8;
// 	char* M= new char[w*h];
// 	memset(M, 0, w*h);
// 
// 	for (int y= 0; y<h; y+=2){
// 		for (int x= 0; x<w; x++)
// 			M[w*y + x]= 1;
// 	}
// 
// 	delete M;
// 
// 	puts("");

	BinImg a;
	BinImg* b= &a;

	bim_init(b);
	bim_alloc(b, 16, 12);
	printf("%d \n", at(b, 1, 1));

	/*fillRect(b, 12, 10, 5, 5, 1);*/
	/*drawRect(b, 14, 10, 5, 7, 1);*/
	drawLine(b, 18, 15, 2, 4, 1);

	return 0;
}