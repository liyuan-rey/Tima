// Tima.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Tima.h"
#include "TimaDlg.h"

#include "skin\SkinManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTimaApp

BEGIN_MESSAGE_MAP(CTimaApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTimaApp construction
CTimaApp::CTimaApp()
{
	EnableHtmlHelp();

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CTimaApp object
CTimaApp theApp;

// CTimaApp initialization
BOOL CTimaApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Initialize skin configration
	int nResult = SkinManager()->LoadSkin();
	CString strInfo;
	if (nResult < 0)
	{
		AfxMessageBox(IDS_LOADSKINFAILED);
		return FALSE;
	}
	else if (nResult > 0)
	{
		AfxMessageBox(IDS_LOADSKININERROR);
	}


	CTimaDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
//	if (nResponse == IDOK)
//	{
//		// TODO: Place code here to handle when the dialog is
//		//  dismissed with OK
//	}
//	else if (nResponse == IDCANCEL)
//	{
//		// TODO: Place code here to handle when the dialog is
//		//  dismissed with Cancel
//	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
