#ifndef util_h__
#define util_h__

#define RIF(x) { \
	if (!(x)) {\
		COUT(FR, "FAILED in " #x); \
		return 0; \
	}\
}
#define CIF(x) { if (!(x)) \
	{ COUT(FR, "FAILED in " #x " continue.."); continue; }}
#define JIF(x) { if (!(x)) \
	{ COUT(FR, "FAILED in " #x); return; }}

inline char* getExtension(char* pFilePath) {
	char* p;
	for (p=pFilePath+strlen(pFilePath)-1; pFilePath<p && *p != '.'; p--);
	if (*p=='.' && (strchr(p, '/') || strchr(p, '\\')))
		return 0;
	return *p == '.' ? p+1 : 0;
}
inline void changeExtension(char* path, char* ext) {
	char* p = getExtension(path);
	strcpy(p, ext);
}
inline void eraseExtension(char* path) {
	char* p;
	for (p=path+strlen(path)-1; path<p && *p!='.' && *p != '/' && *p != '\\'; p--);
	if (*p=='.')
		*p=0;
}
inline char* fileName(char* path) {
	char* p;
	for (p=path+strlen(path)-1; path<p && *p != '/' && *p != '\\'; p--);
	return *p == '/' ? p+1 : *p == '\\' ? p+1 : p;
}
inline void fileName(char* dst, char* path) {
	strcpy(dst, fileName(path));
}
inline void fileName2(char* dst, char* path) {
	strcpy(dst, fileName(path));
	eraseExtension(dst);
}
inline char* str_trim(char* str) {
	char* p;
	for (p=str+strlen(str)-1; str<p && (*p == ' ' || *p == '\t'); p--);
	*(p+1)=0;
	for (p=str; *p && (*p == ' ' || *p == '\t'); p++);
	return p;
}
class Timer {
	uint32 m_s;
public:
	Timer(bool bOn=1) {
		if (bOn)
			on();
	}
	void on() { m_s = GetClock(); }
	int get() { return GetClock() - m_s; }
	int off(bool reon=0) {
		int r = GetClock() - m_s;
		if (reon)
			on();
		return r;
	}
};
inline unsigned short* ansi_to_unicode(char* src, int* pLen=0) {
	int len = MultiByteToWideChar(CP_ACP, 0, src, -1, 0, 0);
	unsigned short* uni = new unsigned short[len*2];
	memset(uni, 1, len*2);
	MultiByteToWideChar(CP_ACP, 0, src, -1, (LPWSTR)uni, len);
	if (pLen)
		*pLen = len;
	return uni;
}
inline char *unicode_to_ansi(char *src, int &len){
	len = (int)wcslen((WCHAR *)src)*2;
	char *temp = new char[len+20];
	memset(temp, 0, len+20);
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)src, -1, temp, len+20, 0, 0);
	return temp;
}
inline char* ansi_to_utf8(char* src, int* pLen=0) {
	int uniLen;
	uint16* uni = ansi_to_unicode(src, &uniLen);
	int utfLen = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)uni, -1, 0, 0, 0, 0);
	char* utf = new char[utfLen];
	memset(utf, 0, utfLen);
	WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)uni, uniLen, utf, utfLen, 0, 0);
	delete[] uni;
	if (pLen)
		*pLen = utfLen;
	return utf;
}
inline char* utf8_to_ansi(const char* src) {
	int uniLen = MultiByteToWideChar(CP_UTF8, 0, src, -1, 0, 0);
	uint16* uni = new uint16[uniLen+1];
	memset(uni, 0, uniLen*2+2);
	MultiByteToWideChar(CP_UTF8, 0, src, -1, (LPWSTR)uni, uniLen);
	int len;
	return unicode_to_ansi((char*)uni, len);
}

 

#endif // util_h__
