#include <stdio.h>

class Combi {
	int* A;
	int* A2;
	int n= 0;
	int len = 0;
	int cnt = 1;

public:	

	void setReady(int* A, int A_len, int n){
		this->A = A;
		this->n = n;
		len = A_len;
		A2 = new int[4 * n];
		for(int i= 0; i< n; i++)		
			A2[i]= i;		
	}

	bool refresh(){
		for(int i= n-1; i >= 0; i--){
			if(A2[i] != A[len-1 -((n-1)-i)]){
				A2[i]++;
				for(int j= i; j< n-1; j++)
					A2[j+1] = A2[j]+1;				
				return 1;
			}	
		}
		return 0;
	}

	void loop(){
		while(true){
			if(A2[n-1] == A[len-1] +1){
				A2[n-1]-= 1;
				if(refresh() == 0)
					break;
			}
			for(int i=0; i< n; i++)
				printf("%d, ", A2[i]);
			printf(" cnt = %d \n", cnt);
			A2[n-1]++;
			cnt++;
		}
	}

// 	bool isLess(int num){
// 		int cnt = 0;
// 
// 		for(int i= 0; i< n; i++){
// 			for(int j= 0; j< n; j++){
// 				if(A3[i] == A2[j]){
// 					cnt++;
// 					break;
// 				}
// 			}
// 		}
// 
// 		if(cnt > num)
// 			return 0;
// 		return 1;
// 	}

	void loop2(int num){

	}
};