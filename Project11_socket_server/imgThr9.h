class ImgThread9 : public Thread{
	SyncQueue<GrayImg*>* q;
	char** argv;		

	int thr(){		
		printf("thr start \n");
		GrayImg* g;				
		while (1){
			if (q->pop(g)){								
				g->operate(argv);
				char* fn= fileName((g->path));
				char dst[64];
				sprintf(dst, "%s/%s", argv[2], fn);
				CIF(g->save(dst));
				g->free();				
			}
			else{
				break;
			}
		}

		printf("thr done \n");
		Thread::thr();
		return 0;
	}

public:

	void init(SyncQueue<GrayImg*>* q, char** argv){
		this->q = q;
		this->argv = argv;		
	}

};