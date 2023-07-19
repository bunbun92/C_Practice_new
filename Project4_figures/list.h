typedef unsigned char uint8;

typedef struct elem {
	uint8 v;
	elem* next;
} elem;

typedef struct {
	elem* hd;
} list;

void list_init(list* l){
	l->hd = new elem[sizeof(elem)];
	l->hd->next = 0;
	l->hd->v = 0;
}

void list_push_back(list* l, uint8 v){
	elem* p = l->hd;
	for(; p->next; p= p->next);	

	p->next = new elem[sizeof(elem)];
	p->next->v = v;
	p->next->next= 0;	
}

void list_push_at(list* l, uint8 v, int idx){
	elem* p= l->hd;

	for(int i= 0; i< idx-1 && p->next; i++, p = p->next);	

	elem* t = p->next;
	p->next = new elem[sizeof(elem)];
	p->next->v = v;
	p->next->next = t;	
}

void list_pop_back(list* l, int idx){

}

void list_print(list* l){
	for (elem* p = l->hd; p; p= p->next)
		printf("%d ", p->v);
	puts("");
}