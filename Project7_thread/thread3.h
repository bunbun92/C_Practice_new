#include "thread.h"

class Thread3 : public Thread{
	

protected:

	int thr(){
		for(int i= 0; i< 16; i++){
			Sleep(300);
			printf("oo\n");
		}
		

		Thread::thr();

		return 0;
	}

public:	


};
