#include "stdafx.h"
#include "lec.gui.h"
#include "lec.guiDlg.h"
#include "afxdialogex.h"

 
ClecguiDlg::ClecguiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ClecguiDlg::IDD, pParent), _bmp(vW, vH) 
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
{	_draw(0);
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
		_draw(5.0);
		break;
	case VK_DOWN:
		_draw(-5.0);
		break;
	case VK_PRIOR:
		_draw(25.0);
		break;
	case VK_NEXT:
		_draw(-25.0);
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
		_draw(15.0);
	}
	else if (zDelta < 0) {
		_draw(-15.0);
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

void ClecguiDlg::OnBnClickedButton1()
{
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	char* txt= (char*)(LPCTSTR)str;
	COUT(txt);
	inputMsg(txt);
}

LRESULT ClecguiDlg::OnMsg(WPARAM a, LPARAM b)
{
	
	return 1;
}
