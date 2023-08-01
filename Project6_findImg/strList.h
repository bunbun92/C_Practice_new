#include <stdio.h>
#include <string.h>

class Elem {
	char* str= 0;
	Elem* next= 0;

public:

	char* getStr(){return this->str;}
	void setStr(char* str, int len){
		this->str = new char[len + 1];
		strcpy(this->str, str);
	}
	void initStr(){this->str = 0;}
	void freeStr(){ delete str; }

	Elem* getNext(){return this->next;}
	void setNext(Elem* p) {this->next = p;}
};

class StrList {
	Elem* hd= 0;

public:

	StrList(): hd(new Elem) {}
	StrList(char* str, int len): hd(new Elem) {this->hd->setStr(str, len);}
	~StrList() {
		Elem* p= this->hd;		
		for (Elem* t; p; p= t){
			t = p->getNext();
			freeElem(p);
		}		
	}

	bool isEmpty(Elem* p){
		if (p->getStr() == 0 && p->getNext() == 0)
			return 1;
		return 0;
	}

	void freeElem(Elem* p){
		p->freeStr();
		delete p;
	}

	void push_front(char* str, int len){

		if(isEmpty(this->hd)){
			this->hd->setStr(str, len);
			return;
		}

		Elem* n = new Elem;
		n->setStr(str, len);
		n->setNext(this->hd);
		this->hd = n;
	}

	void push_back(char* str, int len) {

		if(isEmpty(this->hd)){
			this->hd->setStr(str, len);
			return;
		}

		Elem* p = this->hd;
		for(; p->getNext(); p= p->getNext());

		p->setNext(new Elem);
		p = p->getNext();
		p->setStr(str, len);
	}


	void pop_front() {
		if(this->hd->getNext() == 0){
			this->hd->freeStr();
			this->hd->initStr();
			return;
		}

		Elem* p = this->hd->getNext();
		freeElem(this->hd);
		this->hd = p;

	}

	void pop_back(){
		if(this->hd->getNext() == 0){
			this->hd->freeStr();
			this->hd->initStr();
			return;
		}

		Elem* p = this->hd;
		for(; p->getNext()->getNext(); p= p->getNext());

		freeElem(p->getNext());
		p->setNext(0);
	}

	void print(){
		Elem* p = this->hd;

		for(; p; p= p->getNext())
			printf("%s ", p->getStr());
		puts("");
	}

	bool save(char* path){
		FILE* f= fopen(path, "w+b");		
		for (Elem* p = this->hd; p; p= p->getNext())
			fprintf(f, p->getStr());
		fclose(f);

		return 1;
	}
	bool load(char* path, char* s, int len){
		FILE* f= fopen(path, "r");
		if(f == NULL)
			return 0;

		fgets(s, len, f);

		fclose(f);
	}

	char* at(int idx){
		Elem* p = this->hd;
		int i= 0;
		for(; i< idx && p->getNext(); i++, p= p->getNext());

		if(i< idx)
			return 0;
		
		return p->getStr();
	}

	int size(){
		int n= 0;
		for (Elem* p = this->hd; p; p= p->getNext())
			n++;
		return n;
	}
	
};