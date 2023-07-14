typedef unsigned int    uint32;
typedef unsigned short  uint16;
typedef unsigned char   uint8;

#define arr2_isFull(a) (a.N == MaxArrL)
#define arr2_isEmpty(a) (a.N == 0)
#define arr2_at(a, i) a.A[i]

#define MaxArrL 1024

typedef struct {
    uint8 A[MaxArrL];
    int N;
} Arr2;

bool arr2_push_back(Arr2* pA, uint8 val){
	if (arr2_isFull((*pA)))
		return 0;
	pA->A[pA->N++]= val;
	return 1;
}

bool arr2_pop_back(Arr2* pA){
	if (arr2_isEmpty((*pA)))
		return 0;
	pA->N--;
	return 1;
}

bool arr2_push_at(Arr2* pA, uint8 val, int pos){
	if (arr2_isFull((*pA)) || pA->N +1 == MaxArrL)
		return 0;
	for(int i=pA->N; i > pos; i--)
		pA->A[i] = pA->A[i-1];	
	pA->A[pos] = val;
	return 1;
}

uint8 arr2_min(Arr2* pA){
	uint8 min = *(pA->A);
	for(int i=1; i< pA->N; i++)
		min = pA->A[i] < min ? pA->A[i] : min;
	return min;
}

float arr2_avg(Arr2* pA){
	float result = 0;
	for(int i=0; i< pA->N; i++)
		result += pA->A[i];
	return result / pA->N ;
}
