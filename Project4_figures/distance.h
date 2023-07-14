#include <stdlib.h>
#include <math.h>

typedef unsigned char uint8;

float L1_dist(uint8* A, uint8* B, int len){	
	float result = 0;
	for(int i= 0; i< len; i++)
		result += (float)abs(*(A++) - *(B++));
	return result;
}

float L2_dist(uint8* A, uint8* B,int len){
	float result = 0;
	for(int i= 0; i< len; i++)
		result += (float) ((A[i]-B[i]) * (A[i] - B[i]));	
	return sqrt(result);
}

float dist_L1_or_L2(uint8* A, uint8* B, int len, bool L1){
	if(L1)
		return L1_dist(A, B, len);
	return L2_dist(A, B, len);
}

uint8* find_best_match(uint8* R, uint8* Q, int rN, int qN, float* pd, bool L1){
	*pd = dist_L1_or_L2(R, Q, qN, L1);
	uint8* addr = R;
	for(int i= 1; i< rN; i++){
		float temp = dist_L1_or_L2(R+i, Q, qN, L1);
		if(temp < *pd){
			addr = R+i;
			*pd = temp;
		}
	}
	return addr;
}