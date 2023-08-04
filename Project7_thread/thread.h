#include "mutex.h"

class Thread{
	Mutex& m;
	Semaphore _sem;
	HANDLE _hThr;
	

	int thr(){		
		for(int i= 0; i< 1600; i++){
			m.lock();
			printf("thread ������ = %d ��", i);
			puts(".");
			m.unlock();
		}
		return 0;
	}

	static int thr_init(void* param){
		return ((Thread*)param)->thr();
	}
public:
	Thread(Mutex& t) : m(t) {} 
	void start(){
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thr_init, this, 0, 0);
	}

	void join(){
		_sem.wait();
	}

};
