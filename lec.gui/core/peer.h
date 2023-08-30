typedef struct Msg{
	uint8 from, to;
	char str[128];
	bool flag= 0;
} Msg;

enum Header{
	_OPEN,
	_POLLING,
	_SEND,
	_CLOSE
};

class Peer : public Thread{
	Sock _con;
	CWnd* _pDlg;
	Mutex _m;

	int thr() {
		COUT("이 exe는 ID = %d 입니다", myID);
		while (1) {		
			uint8 h= _POLLING;
			_m.lock();
			if (!_con.write(&h, 1)) {
				_m.unlock();
				_pDlg->PostMessage(WM_ON_MSG, -1);
				break;
			}
			
			int n;
			_con.read(&n, 4);
			for(int i= 0; i< n; i++){
				Msg m;
				_con.read(&m.from, 1);
				_con.read(&m.to, 1);
				_con.readStr(m.str);
				_msg.push_back(m);
			}
			_m.unlock();
			if(n > 0)
				_pDlg->PostMessage(WM_ON_MSG, 0);
			Sleep(300);
		}

		return 0;
	}

public:
	uint8 myID = 1;
	vector<Msg> _msg;
	Peer(CWnd* dlg) : _pDlg(dlg) {}

	bool open() {
		COUT("연결시도중");
		if(_con.open("127.0.0.1", 3333) ==0)
			return open();
		
		COUT("연결완료");

		char a[3] = "SS";
		uint8 h = _OPEN;		
		_con.write(a, 3);
		_con.write(&h, 1);
		_con.read(&h, 1);
		RIF(checkRes(h));

		_con.write(&myID, 1);
		_con.read(&h, 1);
		RIF(checkRes(h));

		start();
	}
	bool sendMsg(char* txt) {
		char* p= strtok(txt, " ");
		uint8 to= atoi(p);
		p= strtok(0, "");

		uint8 h= _SEND;
		_m.lock();
		if (!_con.write(&h, 1)) {
			_m.unlock();
			_pDlg->PostMessage(WM_ON_MSG, -1);
			return 0;
		}		
		_con.write(&to, 1);
		_con.write(txt, strlen(txt) + 1);
		_con.read(&h, 1);
		_m.unlock();

		if(h == 0)
			_pDlg->PostMessage(WM_ON_MSG, -2);
		else
			_pDlg->PostMessage(WM_ON_MSG, 0);		
		return 1;
	}
	bool close() {
		uint8 h= _CLOSE;
		_m.lock();
		_con.write(&h, 1);
		_m.unlock();
		_con.close();
		return 1;
	}

	bool checkRes(uint8 h){
		if (h != 1){
			COUT("초기 연결실패");
			_pDlg->PostMessage(WM_ON_MSG, -1);
			return 0;
		}
		return 1;
	}

public:

	~Peer(){
		close();
	}
};