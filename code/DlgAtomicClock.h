#pragma once
#include "htmllite\htmllite.h"
#include "skin\skinpicture.h"


// CDlgAtomicClock 对话框

class CDlgAtomicClock : public CDialog
{
	DECLARE_DYNAMIC(CDlgAtomicClock)

public:
	CDlgAtomicClock(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAtomicClock();

// 对话框数据
	enum { IDD = IDD_ATOMICCLOCK };

private:
	CBrush m_bgBrush;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

protected:
	void ApplySkin(void);

	CHtmlLite m_htmAC1;
	CHtmlLite m_htmAC2;
	CHtmlLite m_htmAC3;
	CHtmlLite m_htmAC4;
	CHtmlLite m_htmStatus;
	CHtmlLite m_htmSysTime;
	CHtmlLite m_htmSvrTime;
	CHtmlLite m_htmDiffTime;

	CSkinPicture m_picAC1;
	CSkinPicture m_picAC2;
	CSkinPicture m_picAC3;
	CSkinPicture m_picAC4;

	CButton m_chkStart;
	CButton m_chkEstab;
	CButton m_chkEvery;
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


	DECLARE_HTMLTEMPL_MAP();
//	CString GetHtmlTempl(UINT idRes) throw();
public:
	afx_msg void OnBnClickedBtnAccheck();
};
