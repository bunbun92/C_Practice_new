#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "file.h"
#include "rect.h"


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

#define RIF(x) if((x) == 0) { puts(""#x); return 0; }
#define LEN (W * H * 3)
#define hdSize (54)

class Bitmap {
	uint8* _bmp;
	uint8* hd;

	bool hread(File f, uint8* hd){
		if (!f.read(hd, hdSize))
			return 0;
		return 1;
	}

	void cpy(uint8* dstA, uint8* a){
		memcpy(dstA, a, 3);
	}
	void cpy(uint8* dstA, uint8* dstB, uint8* a, uint8* b){
		memcpy(dstA, b, 3);
		memcpy(dstB, a, 3);
	}

	void coloring(uint8* p, int color){
		for (int i= 0; i< 3; i++, p++){
			*p = color & 255;
			color >>= 8;
		}
	}
	void coloring(uint8* p, uint8* p2, int color){
		for (int i= 0; i< 3; i++, p++, p2++){
			*p = color & 255;
			*p2 = color & 255;
			color >>= 8;
		}
	}

	long difference(int x, int y, Bitmap& q){
		uint8* p = ptr(x, y);
		uint8* pQ = q.ptr(0, 0);
		long sum = 0;
		for (int i= 0; i < q.H; i++){
			for (int j= 0; j < 3 * q.W; j++)
				sum += abs(p[j] - pQ[j]);
			p -= 3 * W;
			pQ -= 3 * q.W;
		}
		return sum;
	}

public:
	int W, H;				
	Bitmap() : _bmp(0), hd(0), W(0), H(0) {}
	Bitmap(int W, int H): W(W), H(H){ _bmp = new uint8[LEN]; hd= new uint8[hdSize]; }
	Bitmap(int W, int H, Bitmap* originBit, bool adjustSize = 0) : W(W), H(H){
		_bmp = new uint8[LEN];
		hd = new uint8[hdSize];
		memcpy(hd, originBit->hd, hdSize);
		if(adjustSize){
			*((int*)&hd[2]) = LEN + hdSize;
			*((int*)&hd[18]) = W;
			*((int*)&hd[22]) = H;			
		}		
	}

	bool load(char* path){
		File f;
		hd = new uint8[hdSize];
		RIF(f.open(path));		
		RIF(hread(f, hd));
		W = *((int*)&hd[18]);
		H = *((int*)&hd[22]);		

		_bmp = new uint8[LEN];		
		f.read(_bmp, LEN);
		f.close();
		return 1;
	}

	bool save(char* path){
		File f;
		RIF(f.open(path, "w+b"));
		RIF(f.write(hd, hdSize));
		RIF(f.write(_bmp, LEN));
		f.close();
		return 1;
	}

	uint32 at(int x, int y){
		uint32 a = 255 << 24;
		uint32 r = _bmp[ 3 * (W*y+x)] << 16;
		uint32 g = _bmp[3 * (W*y+x) + 1] << 8;
		uint32 b = _bmp[3 * (W*y+x) + 2];

		return a + r + g + b; 
	}

	uint8* ptr(int x, int y){
		return &_bmp[3 * (W* (H-1-y) +x)];
	}

	Bitmap* getFlip(bool vertical=true){		
		Bitmap* newB= new Bitmap(W, H, this);

		if(vertical){
			for(int y= 0; y < H; y++){
				uint8* dstA = newB->ptr(0, y);
				uint8* dstB = newB->ptr(W-1, y);
				uint8* a = ptr(0, y);
				uint8* b = ptr(W-1, y);
				for(int x= 0; x < W * 0.5; x++)
					cpy(dstA+ 3*x, dstB- 3*x, a+ 3*x, b- 3*x);	
				}
		}else{
			for(int y= 0; y< H * 0.5; y++){
				uint8* dstA = newB->ptr(0, y);
				uint8* dstB = newB->ptr(0, H-1-y);
				uint8* a = ptr(0, y);
				uint8* b = ptr(0, H-1-y);
				for (int x= 0; x < W; x++)
					cpy(dstA+ 3*x, dstB+ 3*x, a+ 3*x, b+ 3*x);
			}
		}
		return newB;
	}

	Bitmap* getRotate90(int nth){
		Bitmap* newB = new Bitmap(H, W, this, 1);		
		if(nth % 4 == 0){
			memcpy(newB->_bmp, _bmp, LEN);
		}else if(nth % 4 == 1){
			for(int y= 0; y< H; y++){
				for(int x= 0; x< W; x++)
					cpy(&newB->_bmp[3 * ((H*x) -y + H -1) ], &_bmp[3 * (W*y + x)]);		
			}
		}
		return newB;
	}


	void bright(float ratio){
		for(uint8* p = _bmp; p < _bmp + LEN; p++)
			*p = (float)(*p * ratio) > 255 ? 255 : (uint8) (*p * ratio);
	}

	void drawRect(int x, int y, int w, int h, int color){
		for(uint8* p = ptr(x, y); p < ptr(x+w, y); p+= 3)
			coloring(p, p-3*((h-1)* W), color);		
		for(uint8* p = ptr(x, y+1); p > ptr(x, y+h); p-= 3 * W)
			coloring(p, p + 3 * (w-1), color);		
	}

	void drawRect(Rect m, int color){
		drawRect(m.x, m.y, m.w, m.h, color);
	}


	Bitmap* getCrop(int x, int y, int w, int h){
		if(w % 4)
			return 0;					
		Bitmap* newB = new Bitmap(w, h, this, 1);
		int i= 0;
		for (uint8* p = ptr(x, y), * pNewB= newB->ptr(0, 0); i < h; p -= 3*W, pNewB -= 3*w, i++)
			memcpy(pNewB, p, 3*w);
		return newB;
	}

	Rect findBestMatch(Bitmap& q){
		Rect a(0, 0, q.W, q.H);
		long min = LONG_MAX;

		for(int y= 0; y< H - q.H; y++){
			for(int x= 0; x< W - q.W; x++){
				long sum = difference(x, y, q);
				if(sum < min){
					a.x = x;
					a.y = y;
					min = sum;
				}
			}
		}
		return a;
	}	
};