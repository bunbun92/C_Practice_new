class SessionThread1: public Thread{
	Sock* s;
	SyncQueue<GrayImg*>* q;
	char** argv;

	int thr(){
		GrayImg* g= 0;
		while(1){
			if(q->pop(g)){
				g->operate(argv);
				CIF(g->save(g->path));
				g->free();
				/*delete g;*/
				s->last_error();
			}
		}
	}

public:

	void init(Sock* s, SyncQueue<GrayImg*>* q, char** argv){
		this->s = s;
		this->q = q;
		this->argv = argv;
	}
};