#define thrN 2

class SessionThread : public Thread{
	Sock* sock;
	char** cmd;

	int thr(){
		SyncQueue <GrayImg*> procWaitngQueue;
		SyncQueue <GrayImg*> sendQueue;

		imgProcThread thrs[thrN];
		for(int i=0; i< thrN; i++){
			thrs[i].init(&procWaitngQueue, &sendQueue);
			thrs[i].start();
		}

		sendThread sendThr;
		sendThr.init(sock, &sendQueue);
		sendThr.start();
			

		while(1){						
			char* ext = new char[4];
			if (sock->read(ext, 4)){
				printf("received file.\n");
				if(strcmp(ext, "jpg") != 0){
					printf("NOT JPG\n");
					sock->close();
					return 0;
				}

				GrayImg* g = new GrayImg;
				int fnLen;
				sock->read(&fnLen, 4);
				g->fn = new char[fnLen]; //클라이언트에서 null까지 길이에 합쳐서 보냄
				sock->read(g->fn, fnLen); 

				sock->read(&(g->W), 4);
				sock->read(&(g->H), 4);

				int cmdLen;
				sock->read(&cmdLen, 4);
				g->cmd = new char[cmdLen]; 
				sock->read(g->cmd, cmdLen);

				uint8* p = new uint8[g->W * g->H];
				sock->read(p, g->W * g->H);
				g->setP(p);
				
				procWaitngQueue.push(g);				
			}
			delete ext;					
		}		

		sock->last_error();
		
		return 0;
	}

public:

	SessionThread(Sock* con){
		sock = con;
		thr();
	}

	void init(Sock* con){
		sock = con;
	}
};