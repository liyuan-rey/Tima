// Tima.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CTimaApp:
// See Tima.cpp for the implementation of this class
//
class CTimaApp : public CWinApp
{
public:
	CTimaApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	protected:
	//{{AFX_MSG(CTimaApp)

	//}}AFX_MSG
DECLARE_MESSAGE_MAP()
};

extern CTimaApp theApp;
