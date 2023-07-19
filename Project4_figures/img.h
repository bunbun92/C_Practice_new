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
	memset(bin->bmp, 0, w * h);
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

//예외처리 필요
void drawRect(BinImg* bin, int x, int y, int w, int h, uint8 val){	
	uint8* p = bin->bmp;
	p += (bin->W * y) + x;

	for (int i= 0; i< h && p[i * bin->W] <= bin->bmp[bin->W * bin->H]; i++){
		p[i * bin->W] = val;		
		p[i * bin->W + (w-1)] = val;
	}
	for (int i= 1; i< w-1 && p[i] <= bin->bmp[bin->W * bin->H]; i++){
		p[i] = val;		
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

	float s = (float)(x1 - x0) / (y1 - y0) ;

	if(x0 == x1){
		for (int y= 0; y< (y1-y0) && (&p[y * bin->W] <= &Max); y++)
			p[y * bin->W]= val;
	}else if (y0 == y1){
		for (int x= 0; x< (x1-x0) && (&p[x + bin->W * (bin->H - y1 - 1)] <= &Max); x++)
			p[x]= val;
	}else{
		for (int y= 0; y< (x1-x0)/s && (&p[(int)(y * bin->W + y * s)] <= &Max); y++)
			p[(int)(y * bin->W + y * s)]= val;
	}
}

void flip_vertical(BinImg* bin){
	uint8 t;
	uint8* p = bin->bmp;

	for(int i= 0; i< bin->H; i++){
		for(int j= 0; j < bin->W / 2; j++){
			t = p[j];
			p[j] = p[bin->W -1 -j];
			p[bin->W -1 -j] = t;
		}
		p+= bin->W;
	}
	
}

void flip_horizontal(BinImg* bin){
	uint8 t;
	uint8* p = bin->bmp;
	uint8* p2 = bin->bmp + (bin->H - 1) * bin->W;

	for(int i= 0; i< bin->H / 2; i++){
		for(int j= 0; j< bin->W; j++){
			t= p[j];
			p[j] = p2[j];
			p2[j] = t;
		}
		p += bin->W;
		p2 -= bin->W;
	}
}

void rotate90(BinImg* bin, int n){
	int W = bin->H;
	int H = bin->W;
	uint8* bmp2 = new uint8[W * H];
	memset(bmp2, 0, W * H);
	uint8* p = bin->bmp;

	for(int i= 0; i< n; i++){
		for (int y= 0; y< W; y++){
			for (int x= 0; x< H; x++){
				bmp2[(x*W) + (W-1-y)] = p[x];
			}
			p += H;
		}
	}

	delete bin->bmp;
	bin->W = H;
	bin->H = W;	
	bin->bmp = bmp2;	
}



void behalf(BinImg* bin){
	int W = (int) (bin->W/2 + 0.5);
	int H = (int) (bin->H/2 + 0.5);
	uint8* bmp2 = new uint8[W * H];
	memset(bmp2, 0, W * H);
	uint8* p = bin->bmp;

	for(int y= 0; y < H; y++){
		for(int x= 0; x< W; x++){
			if (p[x*2] + p[x*2 + 1] + p[bin->W + x*2] + p[bin->W + x*2 + 1])
				bmp2[y*W + x] = 1;
		}
		p += 2 * bin->W;
	}

	delete bin->bmp;
	bin->W = W;
	bin->H = H;
	bin->bmp = bmp2;
}

void draw(BinImg* bin){
	for(int i= 0; i< bin->H; i++){
		for(int j= 0; j< bin->W; j++)
			bin->bmp[bin->W * i + j] ? printf("*") : printf(" ");	
		puts("");
	}
}

void free(BinImg* bin){
	delete bin->bmp;
	bim_init(bin);
}