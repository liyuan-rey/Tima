// TimaDlg.h : header file
//

#pragma once

#include "skin\skindialog.h"


// CTimaDlg dialog
class CTimaDlg : public CSkinDialog
{
// Construction
public:
	CTimaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TIMA_DIALOG };
	virtual UINT GetDialogSkinID() { return IDD; }

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

protected:
	//{{AFX_MSG(CTimaDlg)

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
