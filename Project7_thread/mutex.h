#include <windows.h>

class Mutex{
	CRITICAL_SECTION m_cs;
public:
	Mutex() { InitializeCriticalSection(&m_cs); }
	~Mutex() { DeleteCriticalSection(&m_cs); }
	void lock() { EnterCriticalSection(&m_cs); }
	void unlock(){ LeaveCriticalSection(&m_cs); }
};

class Semaphore{
	HANDLE m_hSem;
public:
	Semaphore(int initV = 1, int keys = 1) : m_hSem(CreateSemaphore((LPSECURITY_ATTRIBUTES)m_hSem, initV, keys, 0)){}
	~Semaphore(){ CloseHandle(m_hSem); }	
	void post() { WaitForSingleObject(m_hSem, INFINITE); }
	void release() { ReleaseSemaphore(m_hSem, 1, 0); }
};