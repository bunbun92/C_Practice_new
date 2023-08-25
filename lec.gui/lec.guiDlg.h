#pragma once
#define vW 780 
#define vH 720

class ClecguiDlg : public CDialogEx
{
	Bitmap _bmp;

	void _draw() {
		Graphics g(&_bmp);
		g.Clear(Color::Black);

		fill_rect(g, 0, 0, 200, 60, Color::Yellow);
		drawTxt(g, "hello", 0, 0, 200, 60, 14, false, 0, 1, Color::Black);

		g.TranslateTransform(0, 80);

		fill_rect(g, 0, 0, 200, 60, Color::Lime);
		drawTxt(g, "hi", 0, 0, 200, 60, 14, false, 0, 1, Color::Black);

		g.TranslateTransform(0, 80);

		fill_rect(g, 0, 0, 200, 60, Color::Lime);
		drawTxt(g, "hi", 0, 0, 200, 60, 14, false, 0, 1, Color::Black);

		Invalidate(0);
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
