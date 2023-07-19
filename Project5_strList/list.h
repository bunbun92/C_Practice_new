#include <stdio.h>

typedef unsigned int uint8;

class node{

	uint8 v;
	node* next= 0;

public:

	void setV(uint8 v){ this->v = v; }
	uint8 getV(){ return this->v; }
	void setNext(node* next) { this->next = next; }
	node* getNext() { return this->next; }
};

class list{
	
	node* hd= 0;

public:

	list() : hd(new node) {}
	list(uint8 v) : hd(new node) { hd->setV(v); }

	void push_back(uint8 v){
		node* p = this->hd;
		for(; p->getNext(); p= p->getNext());

		if (p == this->hd && this->hd->getV() == 0){
			p->setV(v);
			return;
		}

		p->setNext(new node);
		p->getNext()->setV(v);
	}

	void push_at(uint8 v, int idx){

		if(idx == 0){
			node* n = new node;
			n->setV(v);
			n->setNext(this->hd);
			this->hd = n;
			return;
		}

		node* p = this->hd;
		int i= 0;

		for (; i< idx-1 && p->getNext(); p= p->getNext(), i++);

		if(i < idx-1)
			return;

		node* t = p->getNext();
		p->setNext(new node);
		p = p->getNext();
		p->setV(v);
		p->setNext(t);
	}

	uint8 pop_back(){
		node* p = this->hd;

		if(p->getNext() == 0){
			uint8 r = p->getV();
			p->setV(0);
			return r;
		}

		for(; p->getNext()->getNext(); p= p->getNext());

		uint8 r = p->getNext()->getV();		
		delete p->getNext();
		p->setNext(0);

		return r;
	}

	void print(){
		node* p = this->hd;
		for(; p; p=p->getNext())
			printf("%d ", p->getV());
		puts("");
	}
};