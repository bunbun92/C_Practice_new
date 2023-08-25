#include "def.h"
#include "debug.h"
#include "util.h"
#include "flist.h"
#include "gdi.h"
#include "thr.h"
#include "imgThr.h"
#include "queThr.h"
#include "imgThr2.h"
/*#include "timer.h"*/
#include "queThr9.h"
#include "imgThr9.h"
#include "queThr8.h"
#include "imgThr8.h"


void img(char* argv[], char n){
	FileList f(argv[1], "jpg");

	if(n == '0'){
		printf("n==0\n");
		for (int i= 0; i< f.size(); i++){
			COUT("%d, %s", i, f.at(i));
			GrayImg g(f.at(i));
			g.operate(argv);
			char* fn= fileName(f.at(i));
			char dst[64];
			sprintf(dst, "%s/%s", argv[2], fn);
			CIF(g.save(dst));
			g.free();
		}
	}
#define thrN 2

	if (n == '1'){		
		printf("n==1\n");
		
		while (1)
		{
			ImgThread T[thrN];
			for (int i=0; i< thrN; i++){
				T[i].init(argv);
			}
			for (int i= 0; i< f.size(); i++){
				T[i % thrN].add(f.at(i));
			}
			for (int i=0; i< thrN; i++){
				T[i].start();
			}
			for (int i=0; i< thrN; i++)
				T[i].join();
		}
	}


	if (n == '2'){
		printf("n==2\n");
		SyncQueue <char*> q;
		queThread qT;
		qT.init(&f, &q, argv[1]);
		qT.start();		
		ImgThread2 iT[thrN];
		for(int i=0; i< thrN; i++){
			iT[i].init(&q, argv);
			iT[i].start();
		}
		qT.join();
		for(int i=0; i< thrN; i++)
			iT[i].join();
	}


	if (n == '9'){
		printf("n==9\n");
		SyncQueue <GrayImg*> q;
		queThread9 qT;
		qT.init(&f, &q, argv);
		qT.start();
		ImgThread9 iT[thrN];
		for (int i=0; i< thrN; i++){
			iT[i].init(&q, argv);
			iT[i].start();
		}
		qT.join();
		for (int i=0; i< thrN; i++)
			iT[i].join();

	}

	if (n == '8'){
		printf("n==8/n");
		SyncQueue <char*> q;
		queThread8 t0;
		t0.init(&f, &q, argv[1], "../src2");
	}
}


// src dst n
// src dst n bright 1.2
// Project9_imgThread.exe ../src ../dst n bright 1.2
int main(int argc, char* argv[]) {	
	GdiPlusInit();
	Timer t;
	printf("n = %d\n", *argv[3]);
	img(argv, *argv[3]);
	printf("%dms\n", t.off());
	
	return 0;
}