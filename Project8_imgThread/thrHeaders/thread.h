class Thread{
	HANDLE h;
	Semaphore sem;

protected:
	virtual int thr(){
		sem.post();
		return 0;
	}

	static int thr_init(void* param){
		return ((Thread*)param)->thr();
	}

public:	
	void start(){ thread_start(thr_init, this);	}
	void join(){ sem.wait(); }

};