class sendThread: public Thread{
	Sock* sock;
	SyncQueue<GrayImg*>* sendQ;

	int thr(){
		GrayImg* g;
		while(1){
			if(sendQ->pop(g)){
				char ext[4] = "jpg";
				sock->write(ext, 4);
				int fnLen = strlen(g->fn) + 1;
				sock->write(&fnLen, 4);
				sock->write(g->fn, fnLen);
				sock->write(&(g->W), 4);
				sock->write(&(g->H), 4);
				sock->write(g->getP(), g->W * g->H);

				g->free();
				printf("sended file\n");
				delete g;
			}
		}
		sock->last_error();
		return 0;
	}


public:

	void init(Sock* sock, SyncQueue<GrayImg*>* sendQ){
		this->sock = sock;
		this->sendQ = sendQ;
	}
};