#include <stdio.h>
#include "combi.h"
#include "bitmap.h"
#include "Timer.h"

int main(){

	Bitmap a;
	a.load("test/img3.bmp");
	a.save("test/base.bmp");

	Bitmap* b = a.getFlip();
	b->save("test/vert.bmp");

	Bitmap* c = a.getFlip(0);
	c->save("test/hor.bmp");

	Bitmap* d = a.getCrop(150, 100, 300, 240);
	d->save("test/crop.bmp");

	Bitmap e;
	e.load("test/crop.bmp");

	Timer t;
	Rect m = a.findBestMatch(e);	
	printf("%dms\n", t.off());
	a.drawRect(m, 0x00ff0000);
	a.save("test/Finded.bmp");
	return 0;
}