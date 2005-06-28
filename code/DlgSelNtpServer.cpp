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
	, m_strSvrUrl(_T("")), m_strSvrLoc(_T("")), m_bNeedUpdateFile(FALSE)
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
	//
	ON_MESSAGE(WM_TIMA_NTPRESPONSED, OnNtpResponsed)
END_MESSAGE_MAP()


// CDlgSelNtpServer 消息处理程序

BOOL CDlgSelNtpServer::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Init server list
	m_lvwServer.SetExtendedStyle(m_lvwServer.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_lvwServer.InsertColumn(0, _T("Server"), LVCFMT_LEFT, 150);
	m_lvwServer.InsertColumn(1, _T("Location"), LVCFMT_LEFT, 200);
	m_lvwServer.InsertColumn(2, _T("Ping (ms)"), LVCFMT_LEFT, 62);

	// Load Server
	CPath pthSettings = theApp.GetSettingsPath(defaultSntpServerListFile);
	if (pthSettings.FileExists())
	{
		CSettingsStorageIniFile stg;
		stg.SetIniFileName(pthSettings, CSntpServerList::defaultSectionName);

		m_ServerList.Load(stg);
	}

	UpdateServerList();

	// Adjust interface size
	OnBnClickedNtpCustomSvr();

	return TRUE;
}

void CDlgSelNtpServer::UpdateServerList()
{
	m_lvwServer.DeleteAllItems();

	// Add Server
	int nItem, nPing;
	INT_PTR nCount = m_ServerList.Servers.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		nItem = m_lvwServer.InsertItem(i, m_ServerList.Servers[i].URL);
		m_lvwServer.SetItemText(nItem, 1, m_ServerList.Servers[i].Location);

		nPing = _ttoi(m_ServerList.Servers[i].Ping);
		if (nPing > 0 && nPing < TIMA_THREAD_TIMEOUT)
			m_lvwServer.SetItemText(nItem, 2, m_ServerList.Servers[i].Ping);
	}
}

void CDlgSelNtpServer::OnBnClickedNtpCustomSvr()
{
	const int border_bottom_height = 10;

	//
	CButton* pBtnCustom = (CButton*)GetDlgItem(IDC_CHK_NTPCUSTOMSVR);
	ATLASSERT( pBtnCustom->GetSafeHwnd() );

	CRect rcBtnCustom;
	pBtnCustom->GetWindowRect(rcBtnCustom);

	CButton* pBtnAdd = (CButton*)GetDlgItem(IDC_BTN_NTPADD);
	ATLASSERT( pBtnAdd->GetSafeHwnd() );

	CRect rcBtnAdd;
	pBtnAdd->GetWindowRect(rcBtnAdd);

	// 
	CString strText;
	int nWndHeight;

	CRect rcWindow;
	GetWindowRect(rcWindow);

	int nState = pBtnCustom->GetCheck();
	if ( BST_UNCHECKED == nState )
	{
		strText = _T("C&ustom Server >>");
		nWndHeight = rcBtnCustom.bottom - rcWindow.top + border_bottom_height;

		CWnd* pWndControl = GetDlgItem(IDC_EDT_NTPSERVER);
		ATLASSERT( pWndControl->GetSafeHwnd() );
		pWndControl->EnableWindow(FALSE);

		pWndControl = GetDlgItem(IDC_EDT_NTPLOC);
		ATLASSERT( pWndControl->GetSafeHwnd() );
		pWndControl->EnableWindow(FALSE);

		pBtnAdd->EnableWindow(FALSE);
	}
	else
	{
		strText = _T("C&ustom Server <<");
		nWndHeight = rcBtnAdd.bottom - rcWindow.top + border_bottom_height;

		CWnd* pWndControl = GetDlgItem(IDC_EDT_NTPSERVER);
		ATLASSERT( pWndControl->GetSafeHwnd() );
		pWndControl->EnableWindow(TRUE);

		pWndControl = GetDlgItem(IDC_EDT_NTPLOC);
		ATLASSERT( pWndControl->GetSafeHwnd() );
		pWndControl->EnableWindow(TRUE);

		pBtnAdd->EnableWindow(TRUE);
	}

	rcWindow.bottom = rcWindow.top + nWndHeight;

	this->MoveWindow(rcWindow);
	pBtnCustom->SetWindowText(strText);
}

void CDlgSelNtpServer::OnBnClickedNtpAutoSel()
{
	UINT nRet = AfxMessageBox(_T("Auto select server may take a while to determine which servers are\n most fit for you.\n\n would you like to continue?\n"), MB_YESNO | MB_ICONQUESTION);
	if (IDYES != nRet)
		return;

	//
	m_TimeServer.RemoveAllServer();

	INT_PTR nCount = m_ServerList.Servers.GetCount();
	for (int i = 0; i < nCount; i++)
		m_TimeServer.AddServer(m_ServerList.Servers[i].URL);

	//
	if (m_TimeServer.IsReady())
	{
		//TODO: disable interface and show wait msg

		//
		m_TimeServer.StartCheck(GetSafeHwnd());
	}

}

int Compare_CSntpServer(const void* arg1, const void* arg2 )
{
	const CSntpServer* s1 = static_cast<const CSntpServer*>(arg1);
	const CSntpServer* s2 = static_cast<const CSntpServer*>(arg2);

	ATLASSERT(s1 && s2);

	double ping1 = _tstof(s1->Ping);
	double ping2 = _tstof(s2->Ping);

	return ( ping1 > ping2 ? 1 : (ping1 < ping2 ? -1 : 0) );
}

LRESULT CDlgSelNtpServer::OnNtpResponsed(WPARAM, LPARAM)
{
	// Get ntp server info
	CTimeServer::CNtpContextPtr spNtpContext;

	INT_PTR nCount = m_ServerList.Servers.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		spNtpContext = m_TimeServer.GetServerInfo(m_ServerList.Servers[i].URL);
		CSntpServer& sntpServer = m_ServerList.Servers[i];

		BOOL flag;
		if (spNtpContext && spNtpContext->m_bHasResult
			&& spNtpContext->m_ntpResponse.m_RoundTripDelay > 0)
		{
			flag = TRUE;
			sntpServer.Ping.Format(_T("%.0f"), spNtpContext->m_ntpResponse.m_RoundTripDelay * 1000);
		}
		else
		{
			flag = FALSE;
			sntpServer.Ping.Format(_T("%d"), TIMA_THREAD_TIMEOUT);
		}

//		ATLTRACE("Item %03d [%s]\t: %s\t\t\t\t%s\n", i, flag ? "TRUE" : "FALSE", sntpServer.URL, sntpServer.Ping);
	}

	//sort
	void* pData = (void*)&m_ServerList.Servers[0];
	size_t num = nCount;
	size_t width = sizeof(CSntpServer);
	
	qsort(pData, num, width, Compare_CSntpServer);

	//update listview
	UpdateServerList();

	//select the first 5 items
	const int auto_sel_item_count = 5;

	nCount = std::min<int>(m_lvwServer.GetItemCount(), auto_sel_item_count);
	for (int i = 0; i < nCount; i++)
		m_lvwServer.SetCheck(i);

	//
	AfxMessageBox(_T("Auto select server done."));
	m_bNeedUpdateFile = TRUE;

	return 0L;
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
	sntpServer.Location = m_strSvrLoc;

	m_ServerList.Servers.Add(sntpServer);
	m_bNeedUpdateFile = TRUE;

	m_strSvrUrl = m_strSvrLoc = _T("");
	UpdateData(FALSE);
}

void CDlgSelNtpServer::OnOK()
{
	// Add selected server
	m_arrSelServers.RemoveAll();

	CSntpServer sntpServer;

	int nCount = m_lvwServer.GetItemCount();
	for (int i = 0; i < nCount; i++)
	{
		if (m_lvwServer.GetCheck(i))
			m_arrSelServers.Add(m_ServerList.Servers[i]);
	}

	if (m_arrSelServers.GetCount() < 1)
	{
		AfxMessageBox(_T("Please select at least one server."), MB_ICONINFORMATION);
		return;
	}

	CDialog::OnOK();
}

void CDlgSelNtpServer::OnDestroy()
{
	// Save server list
	if (m_bNeedUpdateFile)
	{
		//TODO: Improve efficiency of saving 
		CPath pthSettings = theApp.GetSettingsPath(defaultSntpServerListFile);

		CSettingsStorageIniFile stg;
		stg.SetIniFileName(pthSettings, CSntpServerList::defaultSectionName);

		m_ServerList.Save(stg);
	}

	CDialog::OnDestroy();
}
