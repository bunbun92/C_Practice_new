class imgProcThread : public Thread{
	SyncQueue<GrayImg*>* q;
	SyncQueue<GrayImg*>* sendQ;	
	GrayImg* g;

	int thr(){
		
		while(1){
			if(q->pop(g)){
				char* cmd[2];
				setCmd(cmd);				
				g->operate(cmd);
				sendQ->push(g);				
			}
		}
		
		return 0;
	}
	
	void setCmd(char** cmd){		
		cmd[0] = g->cmd;
		for (int i= 0; g->cmd[i]; i++){
			if (g->cmd[i] == ' '){
				cmd[1] = &(g->cmd[i+1]);
				g->cmd[i] = 0;
			}
				
		}
	}

public:

	void init(SyncQueue<GrayImg*>* q, SyncQueue<GrayImg*>* sendQ){
		this->q = q;
		this->sendQ = sendQ;
	}


};