
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#define NO_WARN_MBCS_MFC_DEPRECATION
#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.

#pragma warning(disable:4996)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#pragma warning(disable:4786) 
#pragma warning(disable:4800) 
#pragma warning(disable:4805) 
#pragma warning(disable:4700) 
#pragma warning(disable:4305) 
#pragma warning(disable:4307) 
#pragma warning(disable:4018) 
#pragma warning(disable:4090) 
#pragma warning(disable:4819) 

#define WM_ON_MSG (WM_USER+100)

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")	

#include "core/def.h"
#include "core/debug.h"
#include "core/util.h" 
#include "core/fio.h"
#include "flist.h"
#include "gdi.h"
 

#define _IsDown(k) (GetKeyState(k) & 0x80)

inline char* fileDlg(char* filter, bool read=1) {
	char filterStr[128];
	sprintf(filterStr, "files (%s)|%s|", filter, filter);
	CFileDialog dlg(1, (LPCTSTR)"pkt", 0, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOVALIDATE, (LPCTSTR)filterStr);
	if (dlg.DoModal() != IDOK)
		return 0;
	else
		return strdup((char*)(LPCTSTR)dlg.GetPathName());
}
inline char* fileDlg2(char* filter, bool read=1) {
	CFileDialog dlg(1, (LPCTSTR)"pkt", 0, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOVALIDATE, (LPCTSTR)filter);
	if (dlg.DoModal() != IDOK)
		return 0;
	else
		return strdup((char*)(LPCTSTR)dlg.GetPathName());
}

#include <ShlObj.h>
inline int CALLBACK bcb(HWND hwnd, UINT msg, LPARAM l, LPARAM p) {
	if (msg==BFFM_INITIALIZED)
		SendMessage(hwnd, BFFM_SETSELECTION, 1, p);
	return 0;
}
inline char* folderDlg(char* init=0) {
	char dir[256];
	if (init==0) {
		GetCurrentDirectory(256, dir);
		init=dir;
	}
	char path[MAX_PATH];
	BROWSEINFO BrInfo;
	BrInfo.hwndOwner = NULL;
	BrInfo.pidlRoot = NULL;
	memset(&BrInfo, 0, sizeof(BrInfo));
	BrInfo.pszDisplayName = path;
	BrInfo.lpszTitle = "select directory";
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	if (init) {
		BrInfo.lpfn = bcb;
		BrInfo.lParam = (LPARAM)init;
	}
	ITEMIDLIST* pidlBrowse = ::SHBrowseForFolder(&BrInfo);
	if (pidlBrowse != NULL) {
		::SHGetPathFromIDList(pidlBrowse, path);
		return strdup(path);
	}
	return 0;
}


inline void cpToClip(char* str, HWND hWnd) {
	HANDLE h_data = ::GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, strlen(str)+1);
	char *p_data = (char *)::GlobalLock(h_data);
	memcpy(p_data, str, strlen(str)+1);
	::GlobalUnlock(h_data);
	if (::OpenClipboard(hWnd)) {
		::EmptyClipboard();
		::SetClipboardData(CF_TEXT, h_data);
		::CloseClipboard();
	}
}




#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����


#pragma comment(linker,"/manifestdependency:\"type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*'\
 publicKeyToken='6595b64144ccf1df' language='*'\"")









