#include "def.h"
#include "debug.h"
#include "util.h"
#include "fio.h"
#include "flist.h"
#include "socket.h"
#include "thr.h"

typedef struct{
	int ID;
	char* msg;
}Data;
#include "socketThread.h"
#include "writeThread.h"



void dataScanf(Data* d, char* ID, char* msg){
	scanf("%s %s", ID, msg);	
	d->ID = atoi(ID);
	d->msg = msg;	
}

int main(){
	Sock::SockSysInit();
	SyncQueue<Data*> q;
	SocketThread thr(&q);	

	while(1){
		Data* d = new Data;
		char ID[64];
		char msg[1024];

		dataScanf(d, ID, msg);		
		q.push(d);
	}

	return 0;
}