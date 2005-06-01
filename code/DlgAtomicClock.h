#pragma once

#include "include\w3mfc\sntp.h"

#include "skin\skindialog.h"
#include "htmllite\htmllite.h"
#include "skin\skinpicture.h"

#include "TimeServer.h"

// CDlgAtomicClock 对话框

class CDlgAtomicClock : public CDialog
{
	DECLARE_DYNAMIC(CDlgAtomicClock)

public:
	CDlgAtomicClock(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAtomicClock();

// 对话框数据
	enum { IDD = IDD_ATOMICCLOCK };
	virtual UINT GetDialogSkinID() { return IDD; }

private:
	HBRUSH GetBgBrush();
	CBrush m_bgBrush;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK() {};
	virtual void OnCancel() {};

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedBtnACCheck();
	afx_msg void OnBnClickedBtnACAdjust();
	afx_msg void OnBnClickedChkACEvery();
	afx_msg LRESULT OnNtpResponsed(WPARAM, LPARAM);
	afx_msg void UpdateCtrls();
	afx_msg void UpdateNextTime();

	DECLARE_HTMLTEMPL_MAP();
protected:
	void ApplySkin(void);
	void UpdateActivedServer();
	BOOL CheckSpinRange(const CSpinButtonCtrl& ctlSpin);
	void CheckTime(BOOL bAdjust);
	void SetACEveryTimer();
	void ShowNextAdjustInfo(const SYSTEMTIME& stLast);

	BOOL m_bNeedAdjust;

	CHtmlLite m_htmAC1;
	CHtmlLite m_htmAC2;
	CHtmlLite m_htmAC3;
	CHtmlLite m_htmAC4;
	CHtmlLite m_htmLastStatus;
	CHtmlLite m_htmNextStatus;
	CHtmlLite m_htmSysTime;
	CHtmlLite m_htmSvrTime;
	CHtmlLite m_htmDiffTime;

	CSkinPicture m_picAC1;
	CSkinPicture m_picAC2;
	CSkinPicture m_picAC3;
	CSkinPicture m_picAC4;

	CButton m_btnCheck;
	CButton m_btnAdjust;

	CButton m_chkStart;
	CButton m_chkEstab;
	CButton m_chkEvery;
	CButton m_chkOnly;
	CEdit m_edtEveryNum;
	CSpinButtonCtrl m_spnEveryNum;
	CComboBox m_cmbEveryUnit;
	CListCtrl m_lstServer;
	CButton m_chkOffset;
	CComboBox m_cmbOffSign;
	CEdit m_edtOffHour;
	CSpinButtonCtrl m_spnOffHour;
	CEdit m_edtOffMin;
	CSpinButtonCtrl m_spnOffMin;
	CEdit m_edtOffSec;
	CSpinButtonCtrl m_spnOffSec;
	CEdit m_edtOffMS;
	CSpinButtonCtrl m_spnOffMS;

	CTimeServer m_TimeServer;

public:
};
