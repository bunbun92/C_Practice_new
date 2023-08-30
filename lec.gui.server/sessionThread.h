typedef struct Msg{
	uint8 from, to;
	char str[128];
	bool flag= 1;
} Msg;

enum Header{
	_OPEN,
	_POLLING,
	_SEND,
	_CLOSE
};

const uint8 RES1= 1;
const uint8 RES0= 0;

class SessionThread : public Thread{
	vector<SessionThread*>* sList;
	Sock _con;
	Mutex _m;
	vector<Msg> _msg;

	int thr(){
		RIF(conInit());

		while(1){
			uint8 h;
			if (_con.read(&h, 1) == 0){
				COUT("ID = %d 클라이언트와 연결 종료", myID);
				break;
			}

			switch (h)
			{
			case _POLLING:
				OnPolling();
				break;

			case _SEND:
				OnMsg();
				break;

			case _CLOSE:
				COUT("ID = %d 클라이언트 접속 종료", myID);
				break;
			}
		}

		_con.close();
		listOut();
		return 0;
	}

	bool conInit(){
		char a[3];
		_con.read(a, 3);
		if (strcmp("SS", a) != 0){
			_con.close();
			return 0;
		}

		uint8 h;


		_con.read(&h, 1);
		if (h == _OPEN)
			_con.write(&RES1, 1);
		else{
			_con.write(&RES0, 1);
			_con.close();
		}

		_con.read(&myID, 1);
		if(myID >= 0 || myID < 256)
			_con.write(&RES1, 1);
		else{
			_con.write(&RES0, 1);
			_con.close();
		}

		sList->push_back(this);

		return 1;
	}

	bool OnPolling(){
		int n= _msg.size();
		int n2= 0;
		for(int i= 0; i< n; i++){
			if(_msg[i].flag)
				n2++;			
		}

		_con.write(&n2, 4);
		for (int i= 0; i< n; i++){
			if(_msg[i].flag){
				_con.write(&_msg[i].from, 1);
				_con.write(&_msg[i].to, 1);
				_con.write(&_msg[i].str, strlen(_msg[i].str) + 1);
				_msg[i].flag = 0;
			}
			
		}
		return 1;
	}

	bool OnMsg(){		
		Msg m;
		m.from= myID;		
		_con.read(&m.to, 1);				
		_con.readStr(m.str);		
		if(pushMsg(m) == 0){
			COUT("ID = %d 의 메세지 전송실패", myID);
			_con.write(&RES0, 1);
			return 0;
		}		
		_con.write(&RES1, 1);
		return 1;
	}

	bool pushMsg(Msg m){
		COUT("pushMSG");		
		for(int i= 0; i< sList->size(); i++){
			if((*sList)[i]->myID == m.to){
				(*sList)[i]->_m.lock();
				(*sList)[i]->_msg.push_back(m);
				(*sList)[i]->_m.unlock();
				if(m.to != m.from){
					_m.lock();
					_msg.push_back(m);
					_m.unlock();
				}				
				return 1;
			}
		}
		return 0;
	}

	bool listOut(){
		for (int i= 0; i< sList->size(); i++){
			if ((*sList)[i]->myID == myID){
				delete sList->at(i);
				sList->erase(sList->begin() + i);
				return 1;
			}
		}
		return 0;
	}

public:
	uint8 myID;

	SessionThread(Sock _con, vector<SessionThread*>* sList){
		this->_con =_con;
		this->sList = sList;
		start();
	}

};