// Tima.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "TimaSettings.h"

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

public:
	static const TCHAR defaultSettingsFolder[];
	static const TCHAR defaultSettingsFile[];

	inline const CTimaSettings* const GetSettings() const {
		return &m_settings;
	}

	CPath GetSettingsPath();

protected:
	int LoadSettings();
	BOOL SaveSettings();

	CPath m_pthAppRoot;
	CTimaSettings m_settings;
};

extern CTimaApp theApp;
