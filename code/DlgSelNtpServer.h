#pragma once


// CDlgSelNtpServer 对话框

class CDlgSelNtpServer : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelNtpServer)

public:
	CDlgSelNtpServer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSelNtpServer();

// 对话框数据
	enum { IDD = IDD_SELNTPSERVER };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedNtpCustomSvr();
	afx_msg void OnBnClickedNtpAutoSel();
	afx_msg void OnBnClickedNtpAdd();

protected:
	void InitServerList();
	void GetSelServer(CSntpServers& arrServers);
	
public:
	static const TCHAR defaultSntpServerListFile[];

protected:
	CListCtrl m_lvwServer;
	CString m_strSvrUrl;
	CString m_strSvrLoc;

	CSntpServerList m_ServerList;

public:
};
