#ifndef thr_h__
#define thr_h__

class Semaphore {
	HANDLE m_hSem;
public:
	Semaphore(int initCnt=0)
		: m_hSem(CreateSemaphore(0, initCnt, 10000, 0)) {}
	~Semaphore() { CloseHandle(m_hSem); }
	void wait(bool bTry=0) {
		WaitForSingleObject(m_hSem, bTry ? 0 : INFINITE);
	}
	void post() {
		ReleaseSemaphore(m_hSem, 1, 0);
	}
};
/////////////
class Mutex {
	CRITICAL_SECTION m_cs;
public:
	Mutex() {
		InitializeCriticalSection(&m_cs);
	}
	~Mutex() {
		DeleteCriticalSection(&m_cs);
	}
	void lock() {
		EnterCriticalSection(&m_cs);
	}
	void unlock() {
		LeaveCriticalSection(&m_cs);
	}
};
/////////////
class AutoLock {
	Mutex* mutex;
public:
	AutoLock(Mutex& m) : mutex(&m) { mutex->lock(); }
	~AutoLock() { mutex->unlock(); }
};
/////////////
class Thread {

	HANDLE _hThr;
	Semaphore _sem;	

protected:
	virtual int thr() {
		_sem.post();	
		return 0; 
	}
	static int thr_init(void* param) {
		return ((Thread*)param)->thr();
	}
public:
	void start() { _hThr= thread_start(thr_init, this); }	
	void join() { _sem.wait(); }
};



template<class T>
class SyncVector : public vector<T> {
	Mutex _lock;
public:
	void push_back(T& val) {
		_lock.lock();
		vector<T>::push_back(val);
		_lock.unlock();
	}
	void pop_back(T& val) {
		_lock.lock();
		vector<T>::pop_back(val);
		_lock.unlock();
	}
	T& at(int i) {
		_lock.lock();
		T& v= vector<T>::at(i);
		_lock.unlock();
		return v;
	}
	int size() {
		_lock.lock();
		int n= vector<T>::size();
		_lock.unlock();
		return n;
	}
	void lock() { _lock.lock(); }
	void unlock() { _lock.unlock(); }
};

template<class T>
class SyncQueue {
	Mutex _lock;
	deque<T> _q;
	bool _eos;
public:
	SyncQueue() : _eos(0) {}

	void setEos() { _eos=1; }
	void push(T val) {
		_lock.lock();
		_q.push_back(val);
		_lock.unlock();
	}
	bool pop(T& v) {
		_lock.lock();

		while (_q.empty() && !_eos){
			_lock.unlock();
			Sleep(10);
			_lock.lock();
		}
		if (!_q.empty()) {
			v= _q.front();
			_q.pop_front();
			_lock.unlock();
			return 1;
		}
		_lock.unlock();
		return 0;
	}
	int size() {
		_lock.lock();
		int n= _q.size();
		_lock.unlock();
		return n;
	}

	bool empty(){
		if (size())
			return 0;
		return 1;
	}
};

#endif // thr_h__
