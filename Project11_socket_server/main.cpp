#include "def.h"
#include "debug.h"
#include "util.h"
#include "flist.h"
#include "gdi.h"
#include "socket.h"
#include "thr.h"

#include "sendThread.h"
#include "imgProcThread.h"
#include "sessionThread.h"

//server
int main(){
	Sock::SockSysInit();
	GdiPlusInit();

	Sock sock;
	RIF(sock.open(3333));
	printf("server start\n");

	while(1){
		Sock con = sock.listen();
		if(con.isSock()){
				printf("new client connected\n");
// 				SessionThread* session = new SessionThread;
// 				session->init(&con);
// 				session->start();
				new SessionThread(&con);
		}
	}
}