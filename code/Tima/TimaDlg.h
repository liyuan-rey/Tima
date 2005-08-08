// TimaDlg.h : header file
//

#pragma once

#include "skin\skindialog.h"
#include "skin\skinbutton.h"
#include "skin\skinpicture.h"

class CDlgAtomicClock;
class CDlgTrayClock;

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

	CSkinPicture m_pic1;
	CSkinPicture m_pic2;
	CSkinPicture m_pic3;
	CSkinButton m_rbnAtomicClock;
	CSkinButton m_rbnTrayClock;
	CSkinButton m_rbnWeather;
	CSkinButton m_rbnReminder;
	CSkinButton m_rbnCalender;
	CSkinButton m_rbnStopWatch;
	CSkinButton m_rbnSettings;
	CSkinButton m_rbnAbout;

	int m_nActivedPanel;
	CWnd* m_pWndActivedPanel;

	CDlgAtomicClock* m_pDlgAtomicClock;
	CDlgTrayClock* m_pDlgTrayClock;

	void ApplySkin();
	void InitPanel();

protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK() {};
	virtual void OnCancel() { CSkinDialog::OnCancel(); }

	// Generated message map functions
protected:
	//{{AFX_MSG(CTimaDlg)
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangePanel(UINT id);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
};
