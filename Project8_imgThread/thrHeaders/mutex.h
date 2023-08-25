
class Mutex{
	CRITICAL_SECTION cs;
public:
	Mutex(){ InitializeCriticalSection(&cs); }
	~Mutex(){ DeleteCriticalSection(&cs); }
	void lock(){ EnterCriticalSection(&cs); }
	void unlock(){ LeaveCriticalSection(&cs);}
};

class Semaphore{
	HANDLE h;
public:
	Semaphore(int initCnt= 0){ h = CreateSemaphore(0, initCnt, 100, 0); }
	~Semaphore(){CloseHandle(h);}
	void wait(){ WaitForSingleObject(h, INFINITE); }
	void post(){ ReleaseSemaphore(h, 1, 0);}
};