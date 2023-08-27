#pragma once
#define vW 780 
#define vH 720

class ClecguiDlg : public CDialogEx
{
	Bitmap _bmp;	
	TEST t;
	float cursor= 0;

	void operateCursor(float n){
		cursor += n;
		int h= 30;
		if (cursor >= h + 10){
			t.operate(-(int) (cursor/h));
			cursor = 0;
		}			
		else if (cursor <= -(h + 10)){
			t.operate(-(int)(cursor/h));
			cursor = 0;
		}
	}

	void _draw(float n) {				
		Graphics g(&_bmp);
		g.Clear(Color::Black);
		
		operateCursor(n);
		drawStr(g, t);		
		
		Invalidate(0);
	}

	void inputMsg(char* txt){
		Graphics g(&_bmp);
		g.Clear(Color::Black);

		t.pushMsg(txt);
		t.operate(1);
		drawStr(g, t);

		Invalidate(0);
	}

	void drawStr(Graphics& g, TEST& t){

		drawVirtualStr(g, t);

		for (int i = t.curIdx, j = 0; j < MSGPCS; i++, j++){
			if (t.msgList[i].flag == 0){}

			if (t.msgList[i].ID == t.myID){
				g.TranslateTransform(550, 0);

				fill_rect(g, 0, cursor, 200, 25, Color::AliceBlue);
				drawTxt(g, t.msgList[i].str, 0, cursor, 200, 25, 14, false, 0, 1, Color::Black);
				drawTs(g, t.msgList[i].ts, -30);

				g.TranslateTransform(-550, 0);
			}
			else{
				fill_rect(g, 0, cursor, 200, 25, Color::Yellow);
				drawTxt(g, t.msgList[i].str, 0, cursor, 200, 25, 14, false, 0, 1, Color::Black);
				drawTs(g, t.msgList[i].ts, 200);
			}			

			g.TranslateTransform(0, 40);
		}

		drawVirtualStr(g, t, 0);
	}

	void drawTs(Graphics& g, int ts, int idx){
		char tmp[64];
		itoa(ts, tmp, 10);
		drawTxt(g, tmp, idx, cursor, 0, 25, 11, false, 0, 1, Color::Yellow);
	}

	void drawVirtualStr(Graphics& g, TEST& t, bool top = 1){
		int virtCurIdx;
		int degree = 40;
		if (top){
			if (t.curIdx > 0)
				virtCurIdx = t.curIdx - 1;
			else{
				return;
			}
		}
		else{
			degree = 0;
			if (t.curIdx + MSGPCS < t.msgList.size())
				virtCurIdx = t.curIdx + MSGPCS;
			else{
				return;
			}
		}

		if (t.msgList[virtCurIdx].ID == t.myID){
			g.TranslateTransform(0, degree * -1);
			g.TranslateTransform(550, 0);

			fill_rect(g, 0, cursor, 200, 25, Color::AliceBlue);
			drawTxt(g, t.msgList[virtCurIdx].str, 0, cursor, 200, 25, 14, false, 0, 1, Color::Black);
			drawTs(g, t.msgList[virtCurIdx].ts, -30);

			g.TranslateTransform(-550, 0);
			g.TranslateTransform(0, degree);
		}
		else{
			g.TranslateTransform(0, degree * -1);

			fill_rect(g, 0, cursor, 200, 25, Color::Yellow);
			drawTxt(g, t.msgList[virtCurIdx].str, 0, cursor, 200, 25, 14, false, 0, 1, Color::Black);
			drawTs(g, t.msgList[virtCurIdx].ts, 200);

			g.TranslateTransform(0, degree);
		}

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
