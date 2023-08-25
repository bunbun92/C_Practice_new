class SessionThread : public Thread{
	Sock* sock;

	int thr(){
		while(1){
			int fileSize;
			sock->read(&fileSize, 4);
// 			uint16 SOI;
// 			sock->read(&SOI, 2);
// 			if(SOI != 0xFFD8){
// 				sock->close();
// 				return 0;
// 			}
			char* p = new char[fileSize];
			sock->read(p, fileSize);

			char cmd[64];
			sock->readStr(cmd);			

			GrayImg g;
			//jpg -> bmp 디코딩
			g.operate(cmd);
			//bmp -> jpg 인코딩

			sock->write(p, fileSize);
			delete p;
		}		
	}

public:

	SessionThread(Sock* con){
		sock = con;
		thr();
	}
};