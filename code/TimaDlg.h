// TimaDlg.h : header file
//

#pragma once


// CTimaDlg dialog
class CTimaDlg : public CDialog
{
// Construction
public:
	CTimaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TIMA_DIALOG };

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
