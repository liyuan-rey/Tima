// TimaDlg.h : header file
//

#pragma once


// CTimaDlg dialog
//##ModelId=422F11CC03DF
class CTimaDlg : public CDialog
{
// Construction
public:
	//##ModelId=422F11CD0008
	CTimaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TIMA_DIALOG };

	protected:
	//##ModelId=422F11CD000A
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	//##ModelId=422F11CD0016
	HICON m_hIcon;

	// Generated message map functions
	//##ModelId=422F11CD0017
	virtual BOOL OnInitDialog();
	//##ModelId=422F11CD0019
	afx_msg void OnPaint();
	//##ModelId=422F11CD0027
	afx_msg HCURSOR OnQueryDragIcon();
	protected:
	//{{AFX_MSG(CTimaDlg)

	//}}AFX_MSG
DECLARE_MESSAGE_MAP()
};
