#include "mutex.h"

class Thread{
	Mutex& m;
	Semaphore& _sem;
	HANDLE& _hThr;
	

	int thr(){		
		/*_sem.post();*/
		m.lock();
		for(int i= 0; i< 15; i++){						
			printf("thread 진행중 = %d 초", i);
			puts(".");			
			Sleep(300);
		}
		m.unlock();
		/*CloseHandle(_hThr);*/
		return 0;
	}

	static int thr_init(void* param){
		return ((Thread*)param)->thr();
	}
public:	
	Thread(Mutex& m, Semaphore& t, HANDLE& h) : m(m), _sem(t), _hThr(h) {}

	void start(){
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thr_init, this, 0, 0);
	}

	void join(){
		_sem.wait();
	}

};
