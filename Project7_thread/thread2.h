#include <windows.h>
#include <vector>
#include <atomic>

using namespace std;

atomic<bool> available = true;
void* curLock = 0;
vector<Lock*> que;

class Lock{
	bool wait = false;

public:

	Lock(){ que.push_back(this); }

	bool lock(){
		if(available && que.at(0) == this && curLock == 0){
			available = false;
			curLock = this;
			printf("lock complete.\n");
			return 1;
		}
		else{
			wait = true;
			while(wait){
				printf("lock waiting..\n");
				Sleep(1000);
			}			
			return lock();
		}

		return 0;			
	}

	bool unlock(){
		if(!available && curLock == this){
			available = true;
			curLock = 0;
			que.erase(que.begin());
			return 1;
		}
		return 0;
	}

};


class Thread2{



	int thr(){

		Lock lock;		
		lock.lock();

		for (int i= 0; i< 16; i++){
			printf("thread 진행중 = %d 초\n", i);
			Sleep(500);
		}

		lock.unlock();

		return 0;
	}

	static int thr_init(void* param){
		return ((Thread2*)param)->thr();
	}

public:

	void start(){
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thr_init, this, 0, 0);
	}

	void join(){
		
	}

};
