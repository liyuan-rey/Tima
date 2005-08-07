// DlgTrayClock.cpp : 实现文件
//

#include "stdafx.h"
#include "Tima.h"
#include "DlgTrayClock.h"
#include ".\dlgtrayclock.h"


// CDlgTrayClock 对话框

IMPLEMENT_DYNAMIC(CDlgTrayClock, CDialog)
CDlgTrayClock::CDlgTrayClock(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrayClock::IDD, pParent), m_hWndHook(NULL)
{
}

CDlgTrayClock::~CDlgTrayClock()
{
}

void CDlgTrayClock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HTMCTL_TC1, m_htmTC1);
	DDX_Control(pDX, IDC_HTMCTL_TC2, m_htmTC2);
	DDX_Control(pDX, IDC_HTMCTL_TC3, m_htmTC3);
	DDX_Control(pDX, IDC_PICT_TC1, m_picTC1);
	DDX_Control(pDX, IDC_PICT_TC2, m_picTC2);
	DDX_Control(pDX, IDC_PICT_TC3, m_picTC3);
	DDX_Control(pDX, IDC_SLD_TCSHADOW, m_sldShadow);
	DDX_Control(pDX, IDC_SLD_TCOPACITY, m_sldOpacity);
	DDX_Control(pDX, IDC_LST_TCZONELIST, m_lstTimeZone);
	DDX_Control(pDX, IDC_BTN_TCADDZONE, m_btnAddZone);
	DDX_Control(pDX, IDC_BTN_TCREMOVEZONE, m_btnRemoveZone);
	DDX_Control(pDX, IDC_BTN_TCZONEUP, m_btnZoneUp);
	DDX_Control(pDX, IDC_BTN_TCZONEDOWN, m_btnZoneDown);
	//
	CTimaSettings& theSettings = theApp.GetSettings();
	DDX_CBString(pDX, IDC_CMB_TCSKINLIST, theSettings.TrayClock.CurrentSkinName);
	DDX_Check(pDX, IDC_CHK_TC12HOURS, theSettings.TrayClock.Use12HoursFormat);
	DDX_Check(pDX, IDC_CHK_TCSHOWDATE, theSettings.TrayClock.ShowDate);
	DDX_Check(pDX, IDC_CHK_TCSHOWWEEK, theSettings.TrayClock.ShowWeek);
	DDX_Check(pDX, IDC_CHK_TCSHOWSECONDS, theSettings.TrayClock.ShowSeconds);
	DDX_Check(pDX, IDC_CHK_TCSHOWZERO, theSettings.TrayClock.ShowZero);
	DDX_Check(pDX, IDC_CHK_TCBLINK, theSettings.TrayClock.BlinkColon);
	DDX_Slider(pDX, IDC_SLD_TCSHADOW, theSettings.TrayClock.Shadow);
	DDX_Check(pDX, IDC_CHK_TCALWAYSTIP, theSettings.TrayClock.AlwaysShowTooltip);
	DDX_Slider(pDX, IDC_SLD_TCOPACITY, theSettings.TrayClock.TooltipOpacity);
	DDX_Check(pDX, IDC_CHK_TCMUTILZONE, theSettings.TrayClock.ShowMultiTimeZone);
	DDX_Control(pDX, IDC_CHK_TCMUTILZONE, m_chkMultiZone);
}


BEGIN_MESSAGE_MAP(CDlgTrayClock, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_CMB_TCSKINLIST, OnCbnSelChangeSkinList)
	ON_COMMAND_RANGE(IDC_CHK_TC12HOURS, IDC_CHK_TCMUTILZONE, OnUpdateTrayClock)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_TCADDZONE, OnBnClickedAddzone)
	ON_BN_CLICKED(IDC_BTN_TCREMOVEZONE, OnBnClickedRemovezone)
END_MESSAGE_MAP()


// CDlgTrayClock 消息处理程序

BOOL CDlgTrayClock::OnEraseBkgnd(CDC* pDC)
{
	return m_bgHelper.OnEraseBkgnd(pDC);
}

HBRUSH CDlgTrayClock::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return m_bgHelper.OnCtlColor(pDC, pWnd, nCtlColor, hbr);
}

void CDlgTrayClock::OnDestroy()
{
	UpdateData(TRUE);

	CDialog::OnDestroy();
}

BOOL CDlgTrayClock::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Initial skin
	ApplySkin();

	// Initial ctrls
	m_sldShadow.SetRange(0, 10);
	m_sldOpacity.SetRange(0, 10);

	// Initial states
	UpdateCtrls();

	return TRUE;
}

void CDlgTrayClock::ApplySkin(void)
{
	m_picTC1.ApplySkin();
	m_picTC2.ApplySkin();
	m_picTC3.ApplySkin();
}

void CDlgTrayClock::UpdateCtrls(void)
{
	BOOL bEnable = (m_chkMultiZone.GetCheck() != BST_UNCHECKED);

	m_lstTimeZone.EnableWindow(bEnable);

	CWnd* pChildWnd = GetDlgItem(IDC_BTN_TCADDZONE);
	pChildWnd->EnableWindow(bEnable);
	pChildWnd = GetDlgItem(IDC_BTN_TCREMOVEZONE);
	pChildWnd->EnableWindow(bEnable);
	pChildWnd = GetDlgItem(IDC_BTN_TCZONEUP);
	pChildWnd->EnableWindow(bEnable);
	pChildWnd = GetDlgItem(IDC_BTN_TCZONEDOWN);
	pChildWnd->EnableWindow(bEnable);
}

void CDlgTrayClock::OnCbnSelChangeSkinList()
{
	OnUpdateTrayClock(IDC_CMB_TCSKINLIST);
}

void CDlgTrayClock::OnUpdateTrayClock(UINT nCtrlId)
{
	if (IDC_CHK_TCMUTILZONE == nCtrlId)
		UpdateCtrls();

//AfxMessageBox("");
}

void CDlgTrayClock::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	if (TB_ENDTRACK == nSBCode)
		OnUpdateTrayClock(pScrollBar->GetDlgCtrlID());
}

void CDlgTrayClock::OnBnClickedAddZone()
{
	InstallTrayClockHook();
}

void CDlgTrayClock::OnBnClickedRemoveZone()
{
	UninstallTrayClockHook();
}

BOOL CDlgTrayClock::InstallTrayClockHook()
{
	if (NULL != m_hWndHook)
	{
		ATLASSERT( FALSE && "Tray clock window hook have already set." );
		return;
	}

	// Find system tray clock window
	HWND hWndShellTray = ::FindWindow(_T("Shell_TrayWnd"), _T(""));
	if (NULL == hWndShellTray)
	{
		AfxMessageBox(_T("Could not find shell tray window, tray clock may not function correctly."), MB_ICONWARNING);
		return;
	}

	m_hWndHook = ::FindWindowEx(hWndShellTray, NULL, _T("TrayClockWClass"), NULL);
	if (NULL == m_hWndHook)
	{
		AfxMessageBox(_T("Could not find clock tray window, tray clock may not function correctly."), MB_ICONWARNING);
		return;
	}

	// 
	DWORD dwHookedThreadId = ::GetWindowThreadProcessId(m_hWndHook, NULL);
//	HANDLE hHook = ::SetWindowsHookEx(WH_GETMESSAGE)
}

BOOL CDlgTrayClock::UninstallTrayClockHook()
{
	if (NULL == m_hWndHook)
	{
		ATLASSERT( FALSE && "Tray clock window hook is not been set yet." );
		return;
	}

	ATLASSERT( ::IsWindow(m_hWndHook) );


}
