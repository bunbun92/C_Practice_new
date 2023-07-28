#include <stdio.h>

typedef unsigned char uint8;
typedef unsigned int uint32;

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