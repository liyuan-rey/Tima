//

#pragma once

#include "SkinComponent.h"

class CSkinManager;
class CWindowSettings;

// CSkinDialog

class CSkinDialog : public CDialog, public ISkinComponent
{
	DECLARE_DYNAMIC(CSkinDialog)

public:
	CSkinDialog();
	virtual ~CSkinDialog();

	CSkinDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	CSkinDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);

	virtual UINT GetDialogSkinID() = 0;

public:
	//{{AFX_VIRTUAL(CSkinDialog)
	virtual void PreInitDialog();
	virtual void PostNcDestroy();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

	// Implement of ISkinComponent
public:
	virtual UINT GetID();
	virtual ESkinControl GetType();
	virtual BOOL SetSkinInfo(CSettings* info);

	// Generated message map functions
public:
	//{{AFX_MSG(CSkinDialog)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CWindowSettings* m_pSettings;
};


