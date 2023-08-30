#include "def.h"
#include "debug.h"
#include "util.h"
#include "socket.h"
#include "thr.h"
#include "sessionThread.h"

int main(){
	Sock::SockSysInit();
	Sock sock;

	RIF(sock.open(3333));
	COUT(FG, "server start");

	vector<SessionThread*> sList;

	while(1){
		Sock con = sock.listen();
		if(con.isSock()){
			COUT(FG, "new client connected");
			new SessionThread(con, &sList);
		}
	}

	return 0;
}