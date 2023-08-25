#include "mutex.h"

class ImgThread{

	Mutex& _m;
	Semaphore& _s;
	HANDLE& _h;
	
	int thr(){
		_s.post();

		_s.release();

		return 0;
	}

	static int thr_init(void* param){
		return ((ImgThread*)param)->thr();
	}

public:	


};