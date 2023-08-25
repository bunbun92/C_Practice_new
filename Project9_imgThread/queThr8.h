class queThread8 : public Thread{
	FileList* f;
	char* src;
	char* src2;
	SyncQueue <char*>* q;

	int thr(){
		f->clear();
		while (1){
			char tmp[64];
			f->search(src, "jpg");
			for(int i= 0; i< f->size(); i++){
				char* fn = fileName(f->at(i));
				sprintf(tmp, "%s/%s", src2, fn);
				::rename(f->at(i), tmp);
				q->push(tmp);
			}
			Sleep(1000);
		}
		q->setEos();
		Thread::thr();

		return 0;
	}
public:

	void init(FileList* f, SyncQueue <char*>* q, char* src, char* src2){
		this->f = f;
		this->q = q;
		this->src = src;
		this->src2 = src2;
	}
};