#include "utilHeaders/def.h"
#include "utilHeaders/debug.h"
/*#include "utilHeaders/file.h"*/
#include "utilHeaders/util.h"
#include "utilHeaders/fio.h"
#include "utilHeaders/flist.h"
#include "utilHeaders/gdi.h"
/*#include "imgHeaders/bitmap.h"*/
#include "thrHeaders/mutex.h"
#include "thrHeaders/syncQueue.h"
#include "thrHeaders/thread.h"
#include "thrHeaders/getThread.h"
#include "thrHeaders/imgProcThread.h"


void img(){
	FileList f("src", "jpg");

}


int main(){	

	#define thrN 2
	ImgProcThread a[thrN];
	printf("1\n");

	img();

	Sleep(100000);
	return 0;
}