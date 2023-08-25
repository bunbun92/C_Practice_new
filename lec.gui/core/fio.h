#ifndef ___fio_h__
#define ___fio_h__

#include "util.h"

class IO {
	FILE* _fd;
public:
	IO() : _fd(0) {}
	/* w+b, a+b, rb
	*/
	bool open(char* fname, const char* opt) {
		return (_fd = fopen(fname, opt))!=0;
	}
	bool is_open() { return _fd!=0; }
	void close() {
		if (_fd)
			fclose(_fd);
	}
	
	static char* load(char* path, uint32& l) {
		IO io;
		RIF(io.open(path, "rb"));
		l= (uint32)io.size();
		char* buf = new char[l];
		RIF(io.read(buf, l));
		io.close();
		return buf;
	}
	static bool save(char* path, char* data, int len) {
		IO io;
		RIF(io.open(path, "w+b"));
		RIF(io.write(data, len));
		io.close();
		return 1;
	}
	static bool save(char* path, char* str) {
		IO io;
		RIF(io.open(path, "w+b"));
		RIF(io.write(str, strlen(str)));
		io.close();
		return 1;
	}
	bool read(void* buf, uint32 sz) {
		return fread(buf, 1, sz, _fd)==(uint32)sz;
	}
	bool write(void* buf, int sz) {
		return fwrite(buf, 1, sz, _fd)==(uint32)sz;
	}
	bool write(char* str) {
		return write(str, strlen(str));
	}
	bool readLine(char* dst) {
		char *p=dst, c;
		while (1) {
			if (!read(&c, 1))
				return 0;
			if (c==0x0d) {
				if (!read(&c, 1))
					return 0;
				break;
			}
			if (c==0x0a)
				break;
			*p++ = c;
		}
		*p=0;
		return 1;
	}
	void printf(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		vfprintf(_fd, fmt, args);
		va_end(args);
	}
	void printf_ln(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		vfprintf(_fd, fmt, args);
		va_end(args);
		write("\r\n", 2);
	}
	bool seek(int offset, int origin) {
		return fseek(_fd, offset, origin)==0;
	};
	void flush() {
		fflush(_fd);
	}
	__int64 size() {
		return fileSize(_fd);
	}
	int cur() {
		int nCur;
		if ((nCur=ftell(_fd)) == -1)
			return -1;
		return nCur;
	}
	static uint32 fileSize(FILE* fd) {
		uint32 nCur, sz;
		if ((nCur=ftell(fd)) == -1)
			return -1;
		if (fseek(fd, 0, SEEK_END))
			return -1;
		if ((sz = ftell(fd)) == -1)
			return -1;
		if (fseek(fd, nCur, SEEK_SET))
			return -1;
		return sz;
	}
	static bool is_exist(char* path) {
		IO io;
		bool b = io.open(path, "rb");
		if (b)
			io.close();
		return b;
	}
	static vector<char*> get_lines(char* path) {
		vector<char*> L;
		IO io;
		if (!io.open(path, "rb"))
			return L;
		char buf[512];
		while (io.readLine(buf))
			L.push_back(strdup(buf));
		io.close();
		return L;
	}
	 
}; 

#endif // ___fio_h__
