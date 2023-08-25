class queThread : public Thread{	
	FileList* f;
	char* src;
	SyncQueue <char*>* q;

	int thr(){		
		f->clear();
		while(1){											
			if(q->empty()){				
				Sleep(1000);
				printf("image Que reloaded. \n");
				f->clear_dir_fl(f);
				f->clear();
				f->search(src, "jpg");
				for (int i= 0; i < f->size(); i++){
					COUT("%d, %s", i, f->at(i));
					q->push(strdup(f->at(i)));
				}											
							
			}else{
				printf("processing.. \n");
				Sleep(1000);
			}
		}
		q->setEos();
		Thread::thr();

		return 0;
	}
	int thr() {
		while (1) {
			FileList fl("src");
			for (int i=0; i<fl.size(); i++) {
				char* src= fl.at(i);
				char* src2= ..."src2/%s", fileName(fl.at(i))
				CIF(::rename(src, src2));
				q->push(src2);
			}
		}
	}
public:

	void init(FileList* f, SyncQueue <char*>* q, char* src){
		this->f = f;
		this->q = q;
		this->src = src;
	}
};