// DlgSelNtpServer.cpp : 实现文件
//

#include "stdafx.h"
#include "Tima.h"
#include "DlgSelNtpServer.h"

#include "include\SettingsStorage\MSettingsStorageIniFile.h"
#include ".\dlgselntpserver.h"
using Mortimer::CSettingsStorageIniFile;

// CDlgSelNtpServer 对话框
const TCHAR CDlgSelNtpServer::defaultSntpServerListFile[] = _T("servlist.ini");

IMPLEMENT_DYNAMIC(CDlgSelNtpServer, CDialog)
CDlgSelNtpServer::CDlgSelNtpServer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelNtpServer::IDD, pParent)
	, m_strSvrUrl(_T(""))
	, m_strSvrLoc(_T(""))
{
}

CDlgSelNtpServer::~CDlgSelNtpServer()
{
}

void CDlgSelNtpServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_NTPSERVER, m_lvwServer);
	DDX_Text(pDX, IDC_EDT_NTPSERVER, m_strSvrUrl);
	DDX_Text(pDX, IDC_EDT_NTPLOC, m_strSvrLoc);
}

BEGIN_MESSAGE_MAP(CDlgSelNtpServer, CDialog)
	ON_BN_CLICKED(IDC_CHK_NTPCUSTOMSVR, OnBnClickedNtpCustomSvr)
	ON_BN_CLICKED(IDC_BTN_NTPAUTOSEL, OnBnClickedNtpAutoSel)
	ON_BN_CLICKED(IDC_BTN_NTPADD, OnBnClickedNtpAdd)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgSelNtpServer 消息处理程序

BOOL CDlgSelNtpServer::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Init server list
	InitServerList();

	// Adjust interface size
	OnBnClickedNtpCustomSvr();

	return TRUE;
}

void CDlgSelNtpServer::InitServerList()
{
	m_lvwServer.SetExtendedStyle(m_lvwServer.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT);
	m_lvwServer.InsertColumn(0, _T("Server"), LVCFMT_LEFT, 150);
	m_lvwServer.InsertColumn(1, _T("Location"), LVCFMT_LEFT, 220);
	m_lvwServer.InsertColumn(2, _T("Ping (ms)"), LVCFMT_LEFT, 60);

	// Load Server
	CPath pthSettings = theApp.GetSettingsPath(defaultSntpServerListFile);
	if (pthSettings.FileExists())
	{
		CSettingsStorageIniFile stg;
		stg.SetIniFileName(pthSettings, CSntpServerList::defaultSectionName);

		m_ServerList.Load(stg);
	}

	// Add Server
	int nItem, nPing;
	INT_PTR nCount = m_ServerList.Servers.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		nItem = m_lvwServer.InsertItem(i, m_ServerList.Servers[i].URL);
		m_lvwServer.SetItemText(nItem, 1, m_ServerList.Servers[i].Name);

		nPing = _ttoi(m_ServerList.Servers[i].Ping);
		if ( nPing > 0)
			m_lvwServer.SetItemText(nItem, 1, m_ServerList.Servers[i].Name);
	}
}

void CDlgSelNtpServer::OnBnClickedNtpCustomSvr()
{
	const int NormalHeight = 398;

	CButton* pButton = (CButton*)GetDlgItem(IDC_CHK_NTPCUSTOMSVR);
	ATLASSERT( pButton->GetSafeHwnd() );

	int nHeight = NormalHeight;
	CString strText = _T("C&ustom Server");
	CRect rcWindow;
	GetWindowRect(rcWindow);

	int nState = pButton->GetCheck();
	if ( BST_UNCHECKED == nState )
	{
		CRect rcButton;
		pButton->GetWindowRect(rcButton);
		nHeight = rcButton.bottom - rcWindow.top + 10;

		strText += _T(" >>");
	}
	else
		strText += _T(" <<");

	rcWindow.bottom = rcWindow.top + nHeight;

	this->MoveWindow(rcWindow);
	pButton->SetWindowText(strText);
}

void CDlgSelNtpServer::OnBnClickedNtpAutoSel()
{
	// TODO: 在此添加控件通知处理程序代码
//	UINT nRet = AfxMessageBox(_T(""), MB_YESNO | MB_ICONQUESTION);
//	if (nRet)
}

void CDlgSelNtpServer::OnBnClickedNtpAdd()
{
	UpdateData(TRUE);

	m_strSvrUrl = m_strSvrUrl.Trim();
	m_strSvrLoc = m_strSvrLoc.Trim();

	if (m_strSvrUrl.IsEmpty() || m_strSvrLoc.IsEmpty())
	{
		AfxMessageBox(_T("Server and Location must be specified."), MB_ICONINFORMATION);
		return;
	}

	int nItem = m_lvwServer.GetItemCount();

	nItem = m_lvwServer.InsertItem(nItem, m_strSvrUrl);
	m_lvwServer.SetItemText(nItem, 1, m_strSvrLoc);

	CSntpServer sntpServer;
	sntpServer.URL = m_strSvrUrl;
	sntpServer.Name = m_strSvrLoc;

	m_ServerList.Servers.Add(sntpServer);

	m_strSvrUrl = m_strSvrLoc = _T("");
	UpdateData(FALSE);
}

void CDlgSelNtpServer::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CDlgSelNtpServer::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnCancel();
}

void CDlgSelNtpServer::GetSelServer(CSntpServers& arrServers)
{
	arrServers.RemoveAll();

	int nItem;
	CSntpServer sntpServer;

	POSITION pos = m_lvwServer.GetFirstSelectedItemPosition();
	while (pos)
	{
		nItem = m_lvwServer.GetNextSelectedItem(pos);
		arrServers.Add(m_ServerList.Servers[nItem]);
	}
}

void CDlgSelNtpServer::OnDestroy()
{
	CDialog::OnDestroy();

	// Save server list
	CPath pthSettings = theApp.GetSettingsPath(defaultSntpServerListFile);

	CSettingsStorageIniFile stg;
	stg.SetIniFileName(pthSettings, CSntpServerList::defaultSectionName);

	m_ServerList.Save(stg);
}
