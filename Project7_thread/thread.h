#include "mutex.h"

class Thread{
	Semaphore _sem;
	HANDLE _hThr;

protected:

	virtual int thr(){				
		_sem.post();				
		return 0;
	}

	static int thr_init(void* param){		
		return ((Thread*)param)->thr();
	}

public:	

	void start(){
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thr_init, this, 0, 0);
	}
	void join(){
		_sem.wait();
	}

};
