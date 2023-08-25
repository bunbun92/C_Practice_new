class receiveThread : public Thread{
	Sock* sock;	
	char** argv;

	int thr(){
		while(1){
			char* ext = new char[4];
			if(sock->read(ext, 4)){
				printf("file received!\n");				

				if(strcmp(ext, "jpg") != 0){
					printf("client: NOT JPG\n");
					sock->close();
					return 0;
				}

				GrayImg g;
				int fnLen;
				sock->read(&fnLen, 4);

				g.fn = new char[fnLen];
				sock->read(g.fn, fnLen);
				sock->read(&(g.W), 4);
				sock->read(&(g.H), 4);

				uint8* p = new uint8[g.W * g.H];
				sock->read(p, g.W * g.H);
				g.setP(p);

				char dst[64];
				sprintf(dst,"%s/%s", argv[2], g.fn);
				g.save(dst);
				g.free();
			}
			delete ext;
		}
		sock->last_error();
	}

public:

	void init(Sock* sock, char** argv){
		this->sock= sock;
		this->argv= argv;
	}
};