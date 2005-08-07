#pragma once
#include "afxwin.h"

// CDlgTrayClock 对话框

class CDlgTrayClock : public CDialog
{
	DECLARE_DYNAMIC(CDlgTrayClock)

public:
	CDlgTrayClock(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTrayClock();

// 对话框数据
	enum { IDD = IDD_TRAYCLOCK };
	virtual UINT GetDialogSkinID() { return IDD; }

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK() {};
	virtual void OnCancel() {};

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();

	afx_msg void OnCbnSelChangeSkinList();
	afx_msg void OnUpdateTrayClock(UINT nCtrlId);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

protected:
	void ApplySkin(void);
	void UpdateCtrls();

	CHtmlLite m_htmTC1;
	CHtmlLite m_htmTC2;
	CHtmlLite m_htmTC3;

	CSkinPicture m_picTC1;
	CSkinPicture m_picTC2;
	CSkinPicture m_picTC3;

	CSliderCtrl m_sldShadow;
	CSliderCtrl m_sldOpacity;
	CButton m_chkMultiZone;
	CListBox m_lstTimeZone;
	CButton m_btnAddZone;
	CButton m_btnRemoveZone;
	CButton m_btnZoneUp;
	CButton m_btnZoneDown;

private:
	CSkinDlgBgHelper m_bgHelper;

public:
};
