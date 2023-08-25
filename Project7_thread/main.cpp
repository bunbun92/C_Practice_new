#include <stdio.h>
#include "def.h"
#include "util.h"
#include "debug.h"
#include "fio.h"
#include "id_table.h"
#include "thread3.h"

int main(){
	
	Thread3 t;

	t.start();

	t.join();

	return 0;
}