
class Peer {
	Sock _con;
	CWnd* _pDlg;
	vector<Msg> _msg;

	int thr() {
		while (1) {
			lock;
			_con.write(check);
			_con.read(&res);
			if (res.renew) {
				_msg.push_back(m);
				_pDlg->PostMessage(WM_ON_MSG);
			}
		}
	}
public:
	Peer(CWnd* dlg) : _pDlg(dlg) {}
	bool open() {

		start();
	}
	bool sendMsg(char* txt) {

	}
	bool close() {

	}
};