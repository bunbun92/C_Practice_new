class queThread9 : public Thread{
	FileList* f;
	char** argv;
	SyncQueue <GrayImg*>* q;

	int thr(){		
		while (1){			
			printf("img que reloaded.\n");
			f->clear();
			f->search(argv[1], "jpg");
			int fSize = f->size();
			for (int i=0; i < fSize; i++){
				GrayImg* g = new GrayImg;
				g->load(f->at(i));
				COUT("%d, %s", i, f->at(i));
				g->path = strdup(f->at(i));
				q->push(g);
				f->remove(f->at(i));
			}
			Sleep(1000);
		}
		q->setEos();
		Thread::thr();

		return 0;
	}

public:

	void init(FileList* f, SyncQueue <GrayImg*>* q, char** argv){
		this->f = f;
		this->q = q;
		this->argv = argv;
	}
};