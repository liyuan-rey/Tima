// tchk.h : tchk DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h" // 主符号

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// CtchkApp
// 有关此类实现的信息，请参阅 tchk.cpp
//

class CtchkApp : public CWinApp
{
  public:
	CtchkApp();

	// 重写
  public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()

  public:
	HWND m_hWndHook;
};

extern CtchkApp theApp;
