#include <stdio.h>
#include "file.h"
#include "bitmap_structure.h"

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

#define RIF(x) if((x) == 0) return 0
#define LEN (W * H * 3 + hdSize)

class Bitmap{
	uint8* _bmp;
public:
	int W, H;	
	File f;
	BitmapStruct b;	
	Bitmap() : _bmp(0), W(0), H(0) {}
	~Bitmap(){}

	bool hcheck(uint8* buf){
		f.read(buf, 2);
		if(*((short*)buf) != 0x4D42){
			puts("not BMP file");
			return 0;
		}
		buf += 2;

		for(int i= 1; i< bsLen; i++){
			if(f.read(buf, b.bs[i].bytes) == 0){
				printf("%s read error\n", b.bs[i].field);				
				return 0;
			}				
			buf += b.bs[i].bytes;
		}
		return 1;
	}

	bool hread(char* path, uint8* hd){		
		f.open(path);		
		return hcheck(hd);
	}

	bool load(char* path){
		uint8* hd = new uint8[hdSize];		
		RIF(hread(path, hd));
		W = *((int*)&hd[18]);
		H = *((int*)&hd[22]);
		delete hd;

		_bmp = new uint8[LEN];
		f.seek(0, SEEK_SET);
		f.read(_bmp, LEN);
		f.close();
		return 1;
	}

	bool save(char* path){
		f.open(path, "w+b");
		RIF(f.write(_bmp, LEN));
		f.close();
		return 1;
	}

	uint32 at(int x, int y){
		_bmp

	}

	uint8* ptr(int x, int y){}

	Bitmap* getFlip(bool vertical=true){}
	Bitmap* getRotate90(int nth){}

	void bright(float ratio){}
	void drawRect(int x, int y, int w, int h, int color){}

	Bitmap* getCrop(int x, int y, int w, int h);
	
};