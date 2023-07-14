#include <stdio.h>
#include <stdlib.h>

void main(){

	int arr[] = {1, 4, 2, 5, 3};
	int arr_len = 5;

// 	int* stk = (int*)malloc(1024 * 4);
// 	*stk++ = *arr;
// 	for (int i= 1; i< arr_len;){
// 		if (*stk < arr[i]){
// 			*(stk+1) = arr[i++];
// 			stk++;
// 		}
// 		else{
// 			*stk = *(stk+1);
// 			stk--;
// 		}
// 	}

	int* stk = (int*)malloc(1024 * 4);
	int* p = stk;
	*p++ = arr[0];

	for (int i= 1; i< arr_len;){
		if (*(p-1) < arr[i])
			*p++ = arr[i++];
		else
			*(p-1) = *p--;
	}

	printf("%d %d %d\n", *stk, *(stk+1), *(stk+2));
}