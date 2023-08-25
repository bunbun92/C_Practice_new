#ifndef gdi_h__
#define gdi_h__

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")	 
#include <shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

inline void GdiPlusInit() {
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}
inline int GetEncoderClsid(char* extension, CLSID* pClsid) {
	WCHAR* format;
	if (!strcmp(extension, "png"))
		format = L"image/png";
	else if (!strcmp(extension, "jpg"))
		format = L"image/jpeg";
	else if (!strcmp(extension, "bmp"))
		format = L"image/bmp";

	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes
	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure
	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j) {
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}
	free(pImageCodecInfo);
	return -1;  // Failure
}
inline void rgb24_to_gray8(uint8* pSrc, int w, int h, uint8* dst) {
	uint8* end= dst+w*h;
	for (uint8* s=pSrc, *d=dst; d<end; d++, s+=3)
		*d = *s*0.299 + *(s+1)*0.587 + *(s+2)*0.114;
}
inline void gray8_to_rgb24(uint8* gray, int w, int h, uint8* dst) {
	for (uint8* p=gray, *d=dst; p<gray+w*h; p++, d+=3)
		*d=*(d+1)=*(d+2) = *p;
}
//////////////////////////////////////////////////////////////////////////
class Img {
	Bitmap* m_pBmp;
public:
	int W, H;
	Img() : m_pBmp(0), W(0), H(0) {}
	Img(int w, int h) {
		m_pBmp = new Bitmap(w, h);
		W = w, H = h;
	}
	Img(char* path) : m_pBmp(0) { load(path); }
	Img(Img& s) {
		m_pBmp= s.m_pBmp->Clone(0, 0, s.W, s.H, PixelFormat24bppRGB);
		W=s.W, H=s.H;
	}
	bool load(char* fname) {
		unload();
		uint16* p = ansi_to_unicode(fname);
		Image img((WCHAR*)p);
		delete p;
		W=img.GetWidth(), H=img.GetHeight();
		if ((W==0) || (H==0))
			return 0;
		m_pBmp = new Bitmap(W, H);
		Graphics g(m_pBmp);
		g.DrawImage(&img, 0, 0, W, H);
		return 1;
	}
	bool load(char* buf, int len) {
		IStream* stream = SHCreateMemStream((BYTE*)buf, len);
		m_pBmp= Bitmap::FromStream(stream);
		RIF(m_pBmp->GetLastStatus()==Ok);
		W= m_pBmp->GetWidth();
		H= m_pBmp->GetHeight();
		stream->Release();
		return 1;
	}
	void unload() {
		if (m_pBmp)
			delete m_pBmp;
		m_pBmp = 0;
	}
	bool save(char* fname) {
		if (!m_pBmp)
			return 0;
		CLSID pngClsid;
		GetEncoderClsid(getExtension(fname), &pngClsid);
		uint16* p = ansi_to_unicode(fname);
		m_pBmp->Save((WCHAR*)p, &pngClsid, NULL);
		delete p;
		return 1;
	}
	uint8* save(uint32& l, char* ext, ULONG quality=90) {
		if (!m_pBmp)
			return 0;
		CLSID clsid;
		GetEncoderClsid(ext, &clsid);

		EncoderParameters eps;
		eps.Count=1;
		eps.Parameter[0].Guid= EncoderQuality;
		eps.Parameter[0].Type= EncoderParameterValueTypeLong;
		eps.Parameter[0].NumberOfValues= 1;
		eps.Parameter[0].Value= &quality;

		IStream* stream = SHCreateMemStream(NULL, 0);
		m_pBmp->Save(stream, &clsid, &eps);
		STATSTG stat;
		stream->Stat(&stat, STATFLAG_NONAME);
		LARGE_INTEGER zero ={0};
		stream->Seek(zero, STREAM_SEEK_SET, NULL);
		l = static_cast<ULONG>(stat.cbSize.QuadPart);
		uint8* data = new uint8[l];
		stream->Read(data, l, NULL);
		stream->Release(); 
		return data;
	}
	bool isLoaded() { return m_pBmp!=0; }
	void clear(Color c) {
		Graphics g(m_pBmp);
		g.Clear(c);
	}
	Color getPixel(int x, int y) {
		Color c;
		m_pBmp->GetPixel(x, y, &c);
		return c;
	}
	void setPixel(int x, int y, Color c) {
		m_pBmp->SetPixel(x, y, c);
	}
	uint8* getBits() {
		BitmapData bmpData;
		Rect r(0, 0, W, H);
		Status s= m_pBmp->LockBits(&r, ImageLockModeRead, PixelFormat24bppRGB, &bmpData);
		int strid = W * 3;
		uint8* buf = new uint8[strid*H];
		uint8* pw=buf, *pr=(uint8*)bmpData.Scan0;
		for (int i=0; i<H; i++) {
			memcpy(pw, pr, strid);
			pw += strid, pr += bmpData.Stride;
		}
		m_pBmp->UnlockBits(&bmpData);
		return buf;
	}
	void setBits(uint8* pBits) {
		BitmapData bmpData={0};
		Rect r(0, 0, W, H);
		while (m_pBmp->LockBits(&r, ImageLockModeWrite, PixelFormat24bppRGB, &bmpData)==ObjectBusy)
			Sleep(1);
		int strid = W * 3;
		uint8* pr=pBits, *pw=(uint8*)bmpData.Scan0;
		for (int i=0; i<H; i++) {
			memcpy(pw, pr, strid);
			pr += strid, pw += bmpData.Stride;
		}
		m_pBmp->UnlockBits(&bmpData);
	}
	uint8* getGray() {
		uint8* rgb = getBits();
		uint8* gray = new uint8[W*H];
		rgb24_to_gray8(rgb, W, H, gray);
		delete rgb;
		return gray;
	}
	void setGray(uint8* gray) {
		uint8* rgb = new uint8[W*H*3];
		gray8_to_rgb24(gray, W, H, rgb);
		setBits(rgb);
		delete rgb;
	}
};
//////////////////////////////////////////////////////////////////////////
class GrayImg {
	uint8* p;
public:
	int W, H;
	bool is_open() { return p!=0; }
	GrayImg(char* path) {
		p=0;
		load(path);
	}
	GrayImg(Img& img) {
		p= img.getGray();
		W=img.W, H=img.H;
	}
	GrayImg(uint8* g, int w, int h) {
		p = new uint8[w*h];
		memcpy(p, g, w*h);
		W=w, H=h;
	}
	GrayImg() : p(0), W(0), H(0) {}
	GrayImg(int w, int h, bool set=1) {
		p = new uint8[w*h];
		if (set)
			memset(p, 0, w*h);
		W=w, H=h;
	}
	bool load(char* path) {
		free();
		Img img(path);
		RIF(img.isLoaded());
		p=img.getGray();
		W=img.W, H=img.H;
		img.unload();
		return 1;
	}
	bool load(char* buf, int len) {
		Img t;
		RIF(t.load(buf, len));
		fromImg(t);
		return 1;
	}
	void free() {
		_Delete(p);
	}
	void toImg(Img& d) {
		d.setGray(p);
	}
	void fromImg(Img& img) {
		free();
		p= img.getGray();
		W= img.W, H=img.H;
	}
	bool save(char* path) {
		Img img(W, H);
		toImg(img);
		img.save(path);
		return 1;
	}
	char* save(char* ext, uint32& l, ULONG quality=90) {
		Img t(W, H);
		toImg(t);
		return (char*)t.save(l, ext, quality);
	}
	uint8& at(int x, int y) {
		return p[y*W+x];
	}
	float avg(int X, int Y, int w, int h) {
		uint32 u=0;
		int n=0;
		for (int y=0; y<h; y++) {
			for (int x=0; x<w; x++) {
				if (_In(0, X+x, W) && _In(0, Y+y, H))
					u+= at(X+x, Y+y), n++;
			}
		}
		return (float)u/n;
	}
};
#endif // gdi_h__
