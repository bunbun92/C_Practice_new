#include <stdio.h>

void print_1(int W){
	for(int i= 0; i< W; i++){		
		for(int j= 0; j< W; j++)
			W/2 > i-j && W/2 > j-i ? printf("*") : printf(" ");
		puts("");
	}	
}

void print_2(float W, float H){	
	float s = H/W;
	for(float i= 0; i<= H; i++){
		for(float j= 0; j<= W; j++)
			W/2 < i + (s*j) && H/2 > (s*j) - i && H * 3/2 >= i + (s*j) && H / 2 >= i - (s*j) ? printf("*") : printf(" ");		
		puts("");
	}
}

