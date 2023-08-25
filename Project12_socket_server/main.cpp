#include "def.h"
#include "debug.h"
#include "util.h"
#include "flist.h"
#include "gdi.h"
#include "socket.h"
#include "thr.h"

#include "sessionThread.h"

//SERVER
int main(){
	
	Sock::SockSysInit();
	GdiPlusInit();

	Sock sock;
	RIF(sock.open(3333));
	printf("server start\n");

	while (1){
		Sock con = sock.listen();
		if (con.isSock()){
			printf("new client connected\n");
			new SessionThread(&con);
		}
	}

	return 0;
}