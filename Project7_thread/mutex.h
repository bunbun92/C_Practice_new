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
	Semaphore(int initV = 0) : m_hSem(CreateSemaphore((LPSECURITY_ATTRIBUTES)m_hSem, initV, 1, 0)){}
	~Semaphore(){ ReleaseSemaphore(m_hSem, 1, 0); }
	void wait() { WaitForSingleObject(m_hSem, INFINITE); }
	void post() { OpenSemaphore((DWORD)m_hSem, 1, 0); }
};