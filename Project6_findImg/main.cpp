#include <stdio.h>
#include "combi.h"
#include "bitmap.h"

int main(){
// 
// 	Combi a;
// 
// 	int arr[]= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 , 15};
// 
// 	a.setReady(arr, sizeof(arr) * 0.25, 7);

	/*a.loop();*/

	Bitmap a;	
	/*a.fRead("img3.bmp");*/
	a.load("img3.bmp");
	a.save("test.bmp");
	
	puts("");
	return 0;
}