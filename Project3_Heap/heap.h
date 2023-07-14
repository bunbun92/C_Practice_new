#include <stdlib.h>
#include <string.h>
#include "heap_tools.h"

void heap_init(Heap* h){
	set_header(h->pool, 'f', MaxHeapL - 5);
	memset(h->head, 0, MaxHeadL);
}

char** heap_alloc(Heap* h, int sz){
	char* p= 0;
	if (p = find_free(h, sz)){
		set_header(p+(sz+5), 'f', *((int*)(p+1)) - (sz+5));
		set_header(p, 'a', sz);		
	}
	return head_push_back(h, p);

}

void heap_free(Heap* h, char** p){
	set_header(*p, 'f', *((int*)((*p)+1)));
	head_pop_at(h, *p);
}

void heap_defrag(Heap* h){
	char* dst = find_free(h, 0);
	for (char* p = dst + *((int*)(dst+1)) + 5; p - (h->pool) < MaxHeapL-5; ){
		int sz = *((int*)(p+1));

		if(*p == 'f'){
			*((int*)(dst+1)) += sz + 5;
			set_null(p, 5);
			p+= sz + 5;

		}else if(*p == 'a'){
			int dst_sz = *((int*)(dst+1));
			set_header(dst, 'a', sz);
			set_null(p, 5);
			set_header(dst+(sz+5), 'f', dst_sz);
			head_refresh(h, p, dst);
			dst= find_free(h, 0);
			p= dst + *((int*)(dst+1)) + 5;
		}
	}
}
