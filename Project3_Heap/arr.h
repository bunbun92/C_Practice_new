typedef unsigned int    uint32;
typedef unsigned short  uint16;
typedef unsigned char   uint8;

typedef struct {
    uint8* A;
    int N;
    int size;
} Arr;

bool arr_alloc(Arr* pA, int size){
    pA->A = new uint8[size +1];
    pA->N = 0;
    pA->size = size;
	pA->A[pA->size]= 0;

    return pA->A != 0;
}

void arr_free(Arr* pA){
    if (pA -> A)
        delete pA->A;
    
    pA->A = 0, pA->N= pA->size= 0;
}

#define arr_isFull(a) ((a).N == (a).size)
#define arr_isEmpty(a) (a.N == 0)
#define arr_at(a, i) a.A[i]

bool arr_push_back(Arr* pA, uint8 val){
    if (pA->N == pA->size)
        return 0;
    pA->A[pA->N++]= val;
	
    return 1;
}

bool arr_pop_back(Arr* pA){
    if (pA->N == 0)
    return 0;
    pA->N--;	
    return 1;
}

bool arr_push_at(Arr* pA, uint8 val, int pos){
	if (arr_isFull(*pA))
		return false;
    if(pA->N == pA->size || pos+1 > (pA->size))
        return 0;

    if(pA->N <= pos){
        arr_push_back(pA, val);
        return 1;
    }

    for(int i= pA->N; i> pos; i--)
        pA->A[i] = pA->A[i-1];
    
    pA->A[pos] = val;
    (pA->N)++;	

    return 1;
}

uint8 arr_min(Arr* pA){

    int min = *(pA->A) - '0';
    (pA->A)++;

    for(; *(pA->A); (pA->A)++){
        if(*(pA->A) >= '0' && *(pA->A) <= '9')
            min = (*(pA->A) - '0') < min ? (*(pA->A) - '0') : min;
    }

    pA->A -= pA->size;
    return min;
}

float arr_avg(Arr* pA){

    int cnt = 0;
    float result = 0;

    for(; *(pA->A); (pA->A)++){
        if(*(pA->A) >= '0' && *(pA->A) <= '9'){
            result += *(pA->A) - '0';
            cnt++;
        }
    }

    pA->A -= pA->size;
    return result / cnt;
}