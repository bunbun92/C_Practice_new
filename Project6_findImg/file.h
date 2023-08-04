#include <stdio.h>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
#define RIF(x) if((x) == 0) { puts(""#x); return 0; }

class File {
	FILE* m_fd;

public:

	bool open(char* path, char* opt="rb"){
		return (m_fd = fopen(path, opt)) != 0;
	}

	void close(){
		if (m_fd)
			fclose(m_fd);
	}

	bool read(char* buf, int len){
		return fread(buf, 1, len ,m_fd) == len;
	}

	bool read(uint8* buf, int len){
		return fread(buf, 1, len, m_fd) == len;
	}

	bool readLine(char* buf){
		int len = fread(buf, 1, 128, m_fd);				
		RIF(len);

		int cnt = 0;
		char* p = buf;
		for (; *p != 0x0d && *p != 0x0a && cnt < len; p++)
			cnt++;

		int bytes = *((uint16*)p) == 0x0a0d ? 2 : 1;

		seek(bytes -(len-cnt), SEEK_CUR);

		if(cnt == 0 || cnt == len)
			return 0;

		memset(bytes + buf+cnt, 0, len - bytes - cnt);
		return 1;
	}

	bool write(char* buf, int len){
		return fwrite(buf, 1, len, m_fd) == len;
	}

	bool write(uint8* buf, int len){
		return  fwrite(buf, 1, len, m_fd) == len;
	}

	bool seek(int offset, int origin){
		return fseek(m_fd, offset, origin) ==0;
	}

	int size(){}

	static bool dup (char* src, char* dst){}
	static bool is_exist(char* path);
	void flush() {fflush(m_fd);}
};