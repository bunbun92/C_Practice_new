class RequestThread : public Thread{	
	SyncQueue <char*>* q;
	int argc;
	char** argv;

	void writeCmd(Sock* sock, int argc, char** argv){
		for (int i= 4; i < argc; i++){
			sock->write(argv[i], strlen(argv[i]));
			if (i < argc - 1)
				sock->write(" ", 1);
			else
				sock->write(0, 1);
		}
	}

	void setDst(char* dst, char* src){
		char* fn = fileName(src);
		sprintf(dst, "%s/%s", argv[3], fn);
	}

	int thr(){
		Sock sock;
		RIF(sock.open("127.0.0.1", 3333));
		printf("client start\n");

		while (1){
			char* src;
			if (q->pop(src)){
				uint32 l;
				char* p = IO::load(src, l);
				sock.write(p, l);
				writeCmd(&sock, argc, argv);

				sock.read(p, l);

				char dst[64];
				setDst(dst, src);

				if (IO::save(dst, p, l))
					::remove(src);

				delete src;
				delete p;
			}
		}
	}

public:

	void init(SyncQueue <char*>* q, int argc, char** argv){
		this->q= q;
		this->argc= argc;
		this->argv= argv;
	}
};