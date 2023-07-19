#include <stdio.h>
#include <string.h>
#include "distance.h"
#include "print.h"
#include "img.h"
#include "list.h"

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
	bim_alloc(b, 16, 16);
	/*printf("%d \n", at(b, 1, 1));*/

	/*fillRect(b, 0, 0, 4, 4, 1);*/
	/*drawRect(b, 14, 10, 5, 7, 1);*/
	drawLine(b, 1, 2, 7, 14, 1);
	drawLine(b, 15, 16, 5, 3, 1);
 	/*flip_vertical(b)*/;
	/*flip_horizontal(b);*/

	/*rotate90(b, 1);*/

	/*fillRect(b, 0, 0, 4, 4, 1);*/
	/*behalf(b);*/
/*	draw(b);*/
	free(b);

	puts("");

	list c;
	list* d = &c;

	list_init(d);
 	list_push_back(d, 10);
	list_push_back(d, 20);
	list_push_back(d, 30);
	list_push_back(d, 40);
	list_push_back(d, 50);

	list_print(d);

	list_push_at(d, 5, 2);

	list_print(d);
	return 0;
}