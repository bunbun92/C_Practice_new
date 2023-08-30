#pragma once
#define vW 780 
#define vH 720
#define msgW 200
#define msgH 25
#define padding 5
#define msgDY (msgH + 2 * padding)
#define msgPcs (vH / msgDY)

class ClecguiDlg : public CDialogEx
{
	Bitmap _bmp;
	Peer _peer;
	int _cursor= 0;

	void _draw() {
		Graphics g(&_bmp);
		g.Clear(Color::Black);
		drawStr(g);
		Invalidate(0);
	}

	void moveCursor(int dy){
		_cursor += dy;
		int n = _peer._msg.size();

		if(_cursor < -2 * padding)
			_cursor = 0;
		else if(_cursor > 2* padding ){
			if(n < msgPcs){
				_cursor = 2* padding;
			}else{
				if( _cursor > (n - msgPcs) * msgDY)
					_cursor = (n - msgPcs) * msgDY - 10;
			}
		}			
		//수식 간단히 할방법 생각
	}	
	
	void drawStr(Graphics& g){
		int n =_peer._msg.size();
		if(n > msgPcs)
			g.TranslateTransform(0, -(n * msgDY - vH));
		g.TranslateTransform(0, _cursor);		
		int dx = vW - msgW;
		for (int i = 0; i < n; i++){
			char msg[128];

			if (_peer._msg[i].from == _peer.myID){
				setStrForm(msg, _peer._msg[i], 0);
				g.TranslateTransform(dx, 0);
				fill_rect(g, -padding, 0, msgW, msgH, Color::AliceBlue);
				drawTxt(g, msg, -padding, 0, msgW, msgH, 14, false, 0, 1, Color::Black);
				g.TranslateTransform(-dx, 0);
			}
			else{
				setStrForm(msg, _peer._msg[i], 1);
				fill_rect(g, padding, 0, msgW, 25, Color::Yellow);
				drawTxt(g, msg, padding, 0, msgW, msgH, 14, false, 0, 1, Color::Black);
			}
			g.TranslateTransform(0, msgDY);
		}
	}

	void setStrForm(char* msg, Msg _msg, bool from= 1){
		if(from){
			itoa(_msg.from, msg, 10);
			strcat(msg, "님의 말: ");
		}			
		else{
			if(_msg.to == _msg.from){
				strcpy(msg, "나에게: ");				
			}else{				
				itoa(_msg.to, msg, 10);
				strcat(msg, "님에게: ");
			}			
		}
		strcat(msg, _msg.str);
	}

public:
	ClecguiDlg(CWnd* pParent = NULL);	 

	enum { IDD = IDD_LECGUI_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	 

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg) {
		if (pMsg->message == WM_KEYDOWN) {
			SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
			if (pMsg->wParam==VK_LEFT || pMsg->wParam==VK_RIGHT ||
				pMsg->wParam==VK_UP ||pMsg->wParam==VK_DOWN)
				return 0;
			return 0;
		}
		if (pMsg->message == WM_SYSKEYDOWN) {
			SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
			//return 1;
		}
		return CDialogEx::PreTranslateMessage(pMsg);
	}
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnMsg(WPARAM a, LPARAM b);
};
