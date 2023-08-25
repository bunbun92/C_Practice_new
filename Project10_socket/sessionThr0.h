class SessionThread0 : public Thread{
	Sock* s;	
	char** argv;	

#define thrN 2

	int thr(){				
		SyncQueue<GrayImg*> q;		
		SessionThread1 thrs[thrN];
		for(int i= 0; i< thrN; i++){
			thrs[i].init(s, &q, argv);
			thrs[i].start();
		}		
		
		while(1){						
			GrayImg* g = new GrayImg;						
			char* ext = new char[4];
			if (s->read(ext, 4)){				
				if(strcmp(ext, "jpg") != 0){
					printf("%s\n", ext);
					printf("jpg พฦดิ\n");
					s->close();
					return 0;
				}					

				s->read(&g->W, 4);
				s->read(&g->H, 4);			

				int pathLen;
				s->read(&pathLen, 4);				
				g->path = new char[pathLen + 1];
				s->read(&g->path, pathLen + 1);
				
				uint8* p = new uint8[g->H * g->W];
				s->read(p, g->H * g->W);
				g->setP(p);

				q.push(g);										
			}			
				
			delete ext;
		}

		return 0;
	}

public:
	

	void init(Sock* s, char** argv){
		this->s = s;
		this->argv = argv;
	}
};