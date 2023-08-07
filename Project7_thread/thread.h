#include "mutex.h"

class Thread{
	Mutex& m;
	Semaphore& _sem;
	HANDLE& _hThr;
	char name;
	

	int thr(){		
		_sem.post();		
		for(int i= 0; i< 15; i++){						
			printf("  %c thread 진행중 = %2d 초", name, i);
			puts(".");			
			Sleep(400);
		}
		_sem.release();
		printf("  %c thread 끝\n", name);		
		return 0;
	}

	static int thr_init(void* param){
		return ((Thread*)param)->thr();
	}
public:	
	Thread(Mutex& m, Semaphore& t, HANDLE& h, char name) : m(m), _sem(t), _hThr(h), name(name) {}

	void start(){
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thr_init, this, 0, 0);
	}

	void join(){
		_sem.post();
	}

};
