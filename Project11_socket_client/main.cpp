#include "def.h"
#include "debug.h"
#include "util.h"
#include "flist.h"
#include "gdi.h"
#include "socket.h"
#include "thr.h"

#include "receiveThread.h"

//client
//Project11_socket_client.exe ../src ../dst bright 1.2
//Project11_socket_client.exe ../src2 ../dst2 flip 0
int main(int argc, char* argv[]){
	Sock::SockSysInit();
	GdiPlusInit();

	Sock sock;
	RIF(sock.open("127.0.0.1", 3333));
	printf("client start\n");

	receiveThread thr;
	thr.init(&sock, argv);
	thr.start();

	FileList fl;
	while(1){		
		fl.clear();
		fl.search(argv[1], "jpg");

		GrayImg g;
		for(int i= 0; i < fl.size(); i++){
			g.load(fl.at(i));			
			COUT("%d, %s", i, fl.at(i));
			char* fn = strdup(fileName(fl.at(i)));
			int fnLen = strlen(fn) + 1;
			char* ext = strdup(getExtension(fn));
			
			int cmdLen = strlen(argv[3]) + strlen(argv[4]) + 1 + 1;
			char* cmd = new char[cmdLen];
			strcpy(cmd, argv[3]);
			strcat(cmd, " ");
			strcat(cmd, argv[4]);
			cmd[cmdLen -1] = 0;								
			
			sock.write(ext, 4);
			sock.write(&fnLen, 4);
			sock.write(fn, fnLen);
			sock.write(&(g.W), 4);
			sock.write(&(g.H), 4);
			sock.write(&cmdLen, 4);
			sock.write(cmd, cmdLen);
			sock.write(g.getP(), g.W * g.H);

			fl.remove(fl.at(i));
			delete fn;
			delete ext;
			delete cmd;
			g.free();						
		}

		Sleep(1000);
		sock.last_error();
	}

	sock.close();
}