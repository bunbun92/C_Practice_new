class ImgThread2 : public Thread{
	SyncQueue<char*>* q;
	char** argv;
	char* path;

	int thr(){
		printf("thr start \n");
			while(1){
				if(q->pop(path)){					
					GrayImg g(path);
					g.operate(argv);
					char* fn= fileName(path);
					char dst[64];
					sprintf(dst, "%s/%s", argv[2], fn);
					CIF(g.save(dst));
					g.free();					
				}else{
					break;
				}				
			}

		printf("thr done \n");
		Thread::thr();
		return 0;
	}

public:

	void init(SyncQueue<char*>* q, char** argv){
		this->q = q;
		this->argv = argv;
	}

};