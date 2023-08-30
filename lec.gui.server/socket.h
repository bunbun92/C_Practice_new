#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class Sock{
	SOCKET _sock;
#define mtu 1500

public:
	Sock() : _sock(0){}
	bool isSock() { return _sock > 0;}
	bool open(uint16 port) {
		if ((_sock= socket(AF_INET, 1, 0)) < 0)
			return 0;
		SOCKADDR_IN addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family= AF_INET;
		addr.sin_port= htons(port);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		return ::bind(_sock, (SOCKADDR*)&addr, sizeof(SOCKADDR)) >= 0;
	}
	bool open(char* ip, uint16 port){
		if((_sock= socket(AF_INET, 1, 0)) <0)
			return 0;
		SOCKADDR_IN addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family= AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(ip);
		return ::connect(_sock, (SOCKADDR*)&addr, sizeof(SOCKADDR)) >= 0;
	}
	void close(){
		if (_sock > 0)
			closesocket(_sock);
	}
	Sock listen(){
		if (::listen(_sock, 100) != 0)
			return Sock();
		SOCKADDR sender_addr;
		socklen_t size = sizeof(sender_addr);
		Sock con;
		if((con._sock = accept(_sock, (SOCKADDR*)&sender_addr, &size)) < 0)
			return Sock();
		return con;
	}
	bool read(void* buf, int len) {
		int remain = len;
		char* o = (char*)buf;
		while (remain > 0) {
			int n = ::recv(_sock, o, remain > mtu ? mtu : remain, 0);
			if (n <= 0)
				return 0;
			o += n;
			remain -= n;
		}
		return 1;
	}

	bool readStr(char* buf){
		char* o = buf;		
		while(1){
			::recv(_sock, o, 1, 0);
			if(*o == 0)
				return 0;			
			o++;
		}
		return 1;
	}

	bool write(const void* buf, int len) {
		int remain = len;
		char* o = (char*)buf;
		while (remain > 0) {
			int n = ::send(_sock, o, remain > mtu ? mtu : remain, 0);
			if (n <= 0) {
				last_error();
				return 0;
			}
			o += n;
			remain -= n;
		}
		return 1;
	}

	static bool SockSysInit(){
		WORD sockVersion;
		WSADATA wsaData;
		sockVersion = MAKEWORD(1, 1);
		int res = WSAStartup(sockVersion, &wsaData);
		return res==0;
	}
	static void last_error() {
		char *s = NULL;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, WSAGetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&s, 0, NULL);
		COUT(FY, s);
	}

};