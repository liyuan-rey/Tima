#pragma once


// CDlgAtomicClock 对话框

class CDlgAtomicClock : public CDialog
{
	DECLARE_DYNAMIC(CDlgAtomicClock)

public:
	CDlgAtomicClock(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAtomicClock();

// 对话框数据
	enum { IDD = IDD_ATOMICCLOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
};
