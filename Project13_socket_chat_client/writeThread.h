class WriteThread: public Thread{
	Sock* sock;
	SyncQueue<Data*>* q;
	Mutex* m;
	int myID;

	int thr(){
		while(1){
			if(q->size() > 0){
				m->lock;
				writeMsg();
				m->unlock();
			}
		}
	}

	bool writeMsg(){
		Data* d= 0;
		RIF(q->pop(d));
		uint8 h= HEADER3;
		sock->write(&h, 1);
		sock->write(&(d->ID), 4);
		sock->write(&(myID), 4);
		sock->write(d->msg, strlen(d->msg));
		delete d;
		char p= 0;
		sock->write(&p, 1);
		printf("메세지 전송 완료\n");
		return 1;
	}

public:

	WriteThread(Sock* sock, SyncQueue<Data*>* q, Mutex* m, int myID){
		this->sock = sock;
		this->q = q;
		this->m = m;
		this->myID = myID;
		start();
	}
};