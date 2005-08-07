#pragma once

#include "TimeServer.h"

// CDlgSelNtpServer �Ի���

class CDlgSelNtpServer : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelNtpServer)

public:
	CDlgSelNtpServer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSelNtpServer();

// �Ի�������
	enum { IDD = IDD_SELNTPSERVER };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedNtpCustomSvr();
	afx_msg void OnBnClickedNtpAutoSel();
	afx_msg void OnBnClickedNtpAdd();

	afx_msg LRESULT OnNtpResponsed(WPARAM, LPARAM);

protected:
	void UpdateServerList();
	
public:
	static const TCHAR defaultSntpServerListFile[];
	CSntpServers m_arrSelServers;

protected:
	CListCtrl m_lvwServer;
	CString m_strSvrUrl;
	CString m_strSvrLoc;

	CSntpServerList m_ServerList;
	CTimeServer m_TimeServer;

private:
	BOOL m_bNeedUpdateFile;

public:
};
