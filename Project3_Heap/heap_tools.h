#define MaxHeapL 260
#define MaxHeadL MaxHeapL/6 + 1

typedef struct{
	char pool[MaxHeapL];
	char* head[MaxHeadL];
} Heap;

void set_null(char* p, int n){
	for (int j= 0; j< n; j++)
		p[j] = 0;
}

void set_header(char* addr, char header, int sz){
	*addr = header;
	*((int*)(addr+1))= sz;
}

char* find_free(Heap* h, int sz){
	for (int i=0; i< MaxHeapL; i++){
		if (h->pool[i] == 'a')
			i += *((int*)&(h->pool[i+1])) + 4;
		else if (h->pool[i] == 'f'){
			if (*((int*)(&h->pool[i+1])) >= sz + 5)
				return &(h->pool[i]);
			i += *((int*)&(h->pool[i+1])) + 4;
		}
	}
	return 0;
}

void head_refresh(Heap* h, char* befo, char* aftr){
	for (int i= 0; i< MaxHeadL; i++){
		if (h->head[i] == befo){
			h->head[i] = aftr;
			break;
		}
	}
}

char** head_push_back(Heap* h, char* p){
	for (int i= 0; i< MaxHeadL; i++){
		if(h->head[i] == 0){
			h->head[i] = p;
			return &(h->head[i]);
		}
	}
}

void head_pop_at(Heap* h, char* p){
	for (int i= 0; i< MaxHeadL; i++){
		if (h->head[i] == p){
// 			for (int j=i; j < h->n; j++)
// 				h->head[j] = h->head[j+1];
			h->head[i] = 0;
			break;
		}
	}
}



