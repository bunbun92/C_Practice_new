#ifndef debug_h__
#define debug_h__

#define Dlog __Log
#define Dlog2 __Log2
#define COUT __cout
#define COUT2 __cout2

#define log_path "__log.txt"
static FILE* __fd_log=0;

inline void __Log(const char* fmt, ...) {
	static char __buffer[1024];
	if (!__fd_log)
		__fd_log=fopen(log_path, "w+b");
	char* p=__buffer;
	va_list args;
	va_start(args, fmt);
	vsprintf(p, fmt, args);
	strcat(p, "\r\n");
	fwrite(__buffer, strlen(__buffer), 1, __fd_log);
	fflush(__fd_log);
	va_end(args);
}
inline void __Log2(const char* fmt, ...) {
	static char __buffer[1024];
	if (!__fd_log)
		__fd_log=fopen(log_path, "w+b");
	char* p=__buffer;
	va_list args;
	va_start(args, fmt);
	vsprintf(p, fmt, args);
	fwrite(__buffer, strlen(__buffer), 1, __fd_log);
	fflush(__fd_log);
	va_end(args);
}
inline char* _STR(const char* lpszFormat, ...) {
	va_list args;
	va_start(args, lpszFormat);
	static char buf[1024];
	vsprintf(buf, lpszFormat, args);
	va_end(args);
	return buf;
}
static int __is_con_color_set=0;
inline void __con_color_set() {
	CONSOLE_SCREEN_BUFFER_INFOEX cbi;
	cbi.cbSize= sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &cbi);
	cbi.ColorTable[1]= RGB(255, 102, 0);
	cbi.ColorTable[2]= RGB(204, 153, 0);
	cbi.ColorTable[3]= RGB(0, 153, 255);
	cbi.ColorTable[4]= RGB(125, 188, 0);
	cbi.ColorTable[5]= RGB(255, 120, 255);
	cbi.ColorTable[6]= RGB(165, 2, 3);
	cbi.ColorTable[10]= RGB(0, 255, 0);
	cbi.ColorTable[11]= RGB(0, 255, 255);
	cbi.ColorTable[12]= RGB(255, 0, 0);
	cbi.ColorTable[13]= RGB(255, 0, 255);
	cbi.ColorTable[14]= RGB(255, 255, 0);
	SetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &cbi);
}
#	define FO 1
#	define FS 2 
#	define FA 3 
#	define FM 4
#	define FP 5
#	define FB 6
#	define FG 10
#	define FC 11
#	define FR 12
#	define FV 13
#	define FY 14
#	define FW 15
#	define RE 7 
inline void __cout(int c, const char* fmt, ...) {
	if (__is_con_color_set==0)
		__con_color_set(), __is_con_color_set=1;
	char buf[1024];
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	va_list args;
	va_start(args, fmt);
	int nBuf = vsprintf(buf, fmt, args);
	Dlog(buf);
	sprintf(buf+strlen(buf), "\n");
	va_end(args);
	DWORD dwBytes;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buf, strlen(buf)+1, &dwBytes, NULL);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), csbiInfo.wAttributes);
}
inline void __cout2(int c, const char* fmt, ...) {
	char buf[1024];
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	va_list args;
	va_start(args, fmt);
	int nBuf = vsprintf(buf, fmt, args);
	Dlog(buf);
	va_end(args);
	DWORD dwBytes;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buf, strlen(buf)+1, &dwBytes, NULL);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), csbiInfo.wAttributes);
}
inline void __cout(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char buf[1024];
	int nBuf = vsprintf(buf, fmt, args);
	Dlog(buf);
	sprintf(buf+strlen(buf), "\n");
	va_end(args);
	DWORD dwBytes;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buf, strlen(buf)+1, &dwBytes, NULL);
}
inline void __cout2(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char buf[1024];
	int nBuf = vsprintf(buf, fmt, args);
	Dlog2(buf);
	va_end(args);
	DWORD dwBytes;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buf, strlen(buf)+1, &dwBytes, NULL);
}
#endif // debug_h__
