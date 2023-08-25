#include "def.h"
#include "debug.h"
#include "util.h"
#include "flist.h"
#include "gdi.h"
#include "socket.h"
#include "thr.h"
#include "sessionThr1.h"
#include "sessionThr0.h"
#include "serverThr.h"


//Project10_socket.exe ../src ../dst n bright 1.2
int main(int argc, char* argv[]){	
	Sock::SockSysInit();	
	GdiPlusInit();

	ServerThread server;
	server.init(argv);
	server.start();
	
	Sock s;
	RIF(s.open("127.0.0.1", 3333));

	FileList f;
	while(1){		
		f.clear();		
		f.search(argv[1], "jpg");							
		GrayImg g;		
		for (int i=0; i < f.size(); i++){	
			g.load(f.at(i));
			COUT("%d, %s", i, f.at(i));
			char* fn = strdup(fileName(f.at(i)));			
			char dst[64];
			sprintf(dst, "%s/%s", argv[2], fn);
			g.path = strdup(dst);				
			char* ext = strdup(getExtension(fn));				
			s.write(ext, 4);			
			s.write(&g.W, 4);
			s.write(&g.H, 4);
			int pathLen =strlen(g.path);
			s.write(&pathLen, 4);
			s.write(&g.path, pathLen + 1);
			/*delete g.path;*/
			s.write(g.getP(), g.W * g.H);
			f.remove(f.at(i));			
			delete ext;



		}
		g.free();
		Sleep(1000);
	}

	s.close();
}