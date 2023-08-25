#include "def.h"
#include "debug.h"
#include "util.h"
#include "fio.h"
#include "flist.h"
#include "socket.h"
#include "thr.h"
#include "requestThread.h"

//client
//Project11_socket_client.exe ../src ../tmp ../dst bright 1.2
//Project11_socket_client.exe ../src ../tmp ../dst flip 0
int main(int argc, char* argv[]){
	Sock::SockSysInit();

#define thrN 4
	SyncQueue<char*> q;
	 RequestThread thrs[thrN];
	 for(int i=0; i< thrN; i++){
		 thrs[i].init(&q, argc, argv);
		 thrs[i].start();
	 }
		

	while(1){
		FileList f(argv[1], "jpg");
		for(int i= 0; f.size(); i++){
			char* fn = fileName(f.at(i));
			char* tmp = new char[64];
			sprintf(tmp, "%s/%s", argv[2], fn);
			q.push(tmp);
			::rename(f.at(i), tmp);
		}
		Sleep(500);
	}
	return 0;
}