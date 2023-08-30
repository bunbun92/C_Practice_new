#include "stdafx.h"
#include "lec.gui.h"
#include "lec.guiDlg.h"
#include "afxdialogex.h"

 
ClecguiDlg::ClecguiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ClecguiDlg::IDD, pParent), _bmp(vW, vH), _peer(this) 
{
}

void ClecguiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ClecguiDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON1, &ClecguiDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_ON_MSG, OnMsg)
END_MESSAGE_MAP()

BOOL ClecguiDlg::OnInitDialog()
{	
	_draw();
	_peer.open();
	CDialogEx::OnInitDialog();
	return 1;
}
 
void ClecguiDlg::OnPaint()
{
	CPaintDC dc(this);
	Graphics g(dc.m_hDC);
	g.DrawImage(&_bmp, 0, 0);
}
 
void ClecguiDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case VK_LEFT:
		break;
	case VK_RIGHT:		
		break;
	case VK_UP:
		moveCursor(5);
		_draw();
		break;
	case VK_DOWN:
		moveCursor(-5);
		_draw();
		break;
	case VK_PRIOR:
		moveCursor(25);
		_draw();
		break;
	case VK_NEXT:
		moveCursor(-25);
		_draw();
		break;
	case VK_RETURN:
		OnBnClickedButton1();
		break;
	case 'B':
		PostMessage(WM_ON_MSG, nChar);
		break;
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
void ClecguiDlg::OnMouseMove(UINT nFlags, CPoint p) {

	CDialogEx::OnMouseMove(nFlags, p);
}
BOOL ClecguiDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta > 0) {
		moveCursor(15);
		_draw();
	}
	else if (zDelta < 0) {
		moveCursor(-15);
		_draw();
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

void ClecguiDlg::OnBnClickedButton1()
{
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);	
	char* txt= (char*)(LPCTSTR)str;
	/*COUT(txt);	*/
	_peer.sendMsg(txt);	
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
}

LRESULT ClecguiDlg::OnMsg(WPARAM a, LPARAM b)
{
	if (a==0)
		_draw();
	else if (a==-1)
		COUT(FY, "connection error!!!");
	else if (a==-2)
		COUT(FY, "전송 실패!");
	return 1;
}
