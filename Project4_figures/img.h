#include <string.h>
#include <math.h>

typedef unsigned char uint8;

typedef struct{
	uint8* bmp;
	int W, H;
} BinImg;

#define Max (bin->bmp[bin->W * bin->H])

void bim_init(BinImg* bin){
	memset(bin, 0, sizeof(BinImg));
}

void bim_alloc(BinImg* bin, int w, int h){
	bin->W = w;
	bin->H = h;
	bin->bmp = new uint8[w*h];
}

uint8 at(BinImg* bin, int x, int y){
	return bin->bmp[bin->W * y + x];	
}

void cut(BinImg* bin, int x, int y, int* w, int* h){
	if(bin->W - x < *w)
		*w = bin->W -x;
	if(bin->H - y < *h)
		*h = bin->H -y;
}

void fillRect(BinImg* bin, int x, int y, int w, int h, uint8 val){
	cut(bin, x, y, &w, &h);
	uint8* p = bin->bmp;
	p += (bin->W * y) + x;

	for (int i= 0; i< h; i++, p += (bin->W) - w){
		for(int j= 0; j< w; j++, p++)
			*p = val;
	}
}

//예외추가필요
void drawRect(BinImg* bin, int x, int y, int w, int h, uint8 val){	
	uint8* p = bin->bmp;
	p += (bin->W * y) + x;

	for (int i= 0; i< h && p[i * bin->W] <= bin->bmp[bin->W * bin->H]; i++){
		p[i * bin->W] = val;

		if (p[i * bin->W + (w-1)] <= bin->bmp[bin->W * bin->H])
			p[i * bin->W + (w-1)] = val;
	}
	for (int i= 1; i< w-1 && p[i] <= bin->bmp[bin->W * bin->H]; i++){
		p[i] = val;

		if (p[i+ bin->W * (h-1)] <= bin->bmp[bin->W * bin->H])
			p[i+ bin->W * (h-1)] = val;
	}
}

void exchangeDot(int* x0, int* y0, int* x1, int* y1){
	int tX = *x0;
	int tY = *y0;
	*x0 = *x1;
	*y0 = *y1;
	*x1 = tX;
	*y1 = tY;
}

void drawLine(BinImg* bin, int x0, int y0, int x1, int y1, uint8 val){

	if(x1 < x0)
		exchangeDot(&x0, &y0, &x1, &y1);

	uint8* p = bin->bmp;
	p += (bin->W * y0) + x0;
	float s = (float) y1/x1 ;
	for (int x= 0; x< x1-x0, (&p[(int)(x * bin->W + x * s)] <= &Max); x++)
		p[(int) (x * bin->W + x * s)]= val;	
}

void flip_vertical(BinImg* bin){
	int x0;
	int x1;
	int y0;
	int y1;
	
}