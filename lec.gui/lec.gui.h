
// lec.gui.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// ClecguiApp:
// �� Ŭ������ ������ ���ؼ��� lec.gui.cpp�� �����Ͻʽÿ�.
//

class ClecguiApp : public CWinApp
{
public:
	ClecguiApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern ClecguiApp theApp;