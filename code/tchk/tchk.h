// tchk.h : tchk DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// CtchkApp
// �йش���ʵ�ֵ���Ϣ������� tchk.cpp
//

class CtchkApp : public CWinApp
{
public:
	CtchkApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

public:
	HWND m_hWndHook;
};

extern CtchkApp theApp;
