//

#pragma once

#include <afxtempl.h>

#include "SkinComponent.h"

class CSkinManager;
class CWindowSettings;
class CSkinButton;

#define IDC_SKIN_BASE				3001

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
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

	// Implement of ISkinComponent
public:
	virtual UINT GetID();
	virtual ESkinControl GetType();
	virtual BOOL SetSkinInfo(CSettings* info);
	virtual ISkinComponent* GetSkinParent();

	// Generated message map functions
public:
	//{{AFX_MSG(CSkinDialog)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	afx_msg void OnSysBtnClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()

protected:
	CWindowSettings* m_pSettings;
	CRect m_rcCaption;

	CArray<CSkinButton*> m_arrButtons;
};


