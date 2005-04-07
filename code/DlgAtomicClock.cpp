// DlgAtomicClock.cpp : 实现文件
//

#include "stdafx.h"
#include "Tima.h"
#include "DlgAtomicClock.h"
#include ".\dlgatomicclock.h"

#include "skin\skinmanager.h"

// CDlgAtomicClock 对话框

IMPLEMENT_DYNAMIC(CDlgAtomicClock, CDialog)

CDlgAtomicClock::CDlgAtomicClock(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAtomicClock::IDD, pParent),
	m_pNtpThread(NULL), m_bNeedAdjust(FALSE)
{
}

CDlgAtomicClock::~CDlgAtomicClock()
{
}

void CDlgAtomicClock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HTMCTL_AC1, m_htmAC1);
	DDX_Control(pDX, IDC_HTMCTL_AC2, m_htmAC2);
	DDX_Control(pDX, IDC_HTMCTL_AC3, m_htmAC3);
	DDX_Control(pDX, IDC_HTMCTL_AC4, m_htmAC4);
	DDX_Control(pDX, IDC_HTMCTL_ACSTATUS, m_htmStatus);
	DDX_Control(pDX, IDC_HTMCTL_ACSYSTIME, m_htmSysTime);
	DDX_Control(pDX, IDC_HTMCTL_ACSVRTIME, m_htmSvrTime);
	DDX_Control(pDX, IDC_HTMCTL_ACDIFFTIME, m_htmDiffTime);
	DDX_Control(pDX, IDC_PICT_AC1, m_picAC1);
	DDX_Control(pDX, IDC_PICT_AC2, m_picAC2);
	DDX_Control(pDX, IDC_PICT_AC3, m_picAC3);
	DDX_Control(pDX, IDC_PICT_AC4, m_picAC4);
	DDX_Control(pDX, IDC_BTN_ACCHECK, m_btnCheck);
	DDX_Control(pDX, IDC_BTN_ACADJUST, m_btnAdjust);
	DDX_Control(pDX, IDC_CHK_ACSTART, m_chkStart);
	DDX_Control(pDX, IDC_CHK_ACESTAB, m_chkEstab);
	DDX_Control(pDX, IDC_CHK_ACEVERY, m_chkEvery);
	DDX_Control(pDX, IDC_EDT_ACEVERYNUM, m_edtEveryNum);
	DDX_Control(pDX, IDC_SPN_ACEVERYNUM, m_spnEveryNum);
	DDX_Control(pDX, IDC_CMB_ACEVERYUNIT, m_cmbEveryUnit);
	DDX_Control(pDX, IDC_LST_ACSERVER, m_lstServer);
	DDX_Control(pDX, IDC_CHK_ACOFFSET, m_chkOffset);
	DDX_Control(pDX, IDC_CMB_ACOFFSIGN, m_cmbOffSign);
	DDX_Control(pDX, IDC_EDT_ACOFFHOUR, m_edtOffHour);
	DDX_Control(pDX, IDC_SPN_ACOFFHOUR, m_spnOffHour);
	DDX_Control(pDX, IDC_EDT_ACOFFMIN, m_edtOffMin);
	DDX_Control(pDX, IDC_SPN_ACOFFMIN, m_spnOffMin);
	DDX_Control(pDX, IDC_EDT_ACOFFSEC, m_edtOffSec);
	DDX_Control(pDX, IDC_SPN_ACOFFSEC, m_spnOffSec);
	DDX_Control(pDX, IDC_EDT_ACOFFMS, m_edtOffMS);
	DDX_Control(pDX, IDC_SPN_ACOFFMS, m_spnOffMS);
	//
	DDX_Check(pDX, IDC_CHK_ACSTART, theApp.GetSettings()->AtomicClock.AdjustOnStart);
	DDX_Check(pDX, IDC_CHK_ACESTAB, theApp.GetSettings()->AtomicClock.AdjustOnConnect);
	DDX_Check(pDX, IDC_CHK_ACEVERY, theApp.GetSettings()->AtomicClock.AdjustEvery);
	DDX_Text(pDX, IDC_EDT_ACEVERYNUM, theApp.GetSettings()->AtomicClock.AdjustEveryNum);
	DDX_CBIndex(pDX, IDC_CMB_ACEVERYUNIT, theApp.GetSettings()->AtomicClock.AdjustEveryUnit);
	DDX_Check(pDX, IDC_CHK_ACOFFSET, theApp.GetSettings()->AtomicClock.UserOffset);
	DDX_CBIndex(pDX, IDC_CMB_ACOFFSIGN, theApp.GetSettings()->AtomicClock.OffsetSign);
	DDX_Text(pDX, IDC_EDT_ACOFFHOUR, theApp.GetSettings()->AtomicClock.OffsetHour);
	DDX_Text(pDX, IDC_EDT_ACOFFMIN, theApp.GetSettings()->AtomicClock.OffsetMin);
	DDX_Text(pDX, IDC_EDT_ACOFFSEC, theApp.GetSettings()->AtomicClock.OffsetSec);
	DDX_Text(pDX, IDC_EDT_ACOFFMS, theApp.GetSettings()->AtomicClock.OffsetMS);
}


BEGIN_MESSAGE_MAP(CDlgAtomicClock, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_ACCHECK, OnBnClickedBtnACCheck)
	ON_BN_CLICKED(IDC_BTN_ACADJUST, OnBnClickedBtnACAdjust)
	ON_MESSAGE(WM_TIMA_NTPRESPONSED, OnNtpResponsed)
	//
	ON_BN_CLICKED(IDC_CHK_ACEVERY, UpdateCtrls)
	ON_EN_KILLFOCUS(IDC_EDT_ACEVERYNUM, UpdateCtrls)
	ON_BN_CLICKED(IDC_CHK_ACOFFSET, UpdateCtrls)
	ON_EN_KILLFOCUS(IDC_EDT_ACOFFHOUR, UpdateCtrls)
	ON_EN_KILLFOCUS(IDC_EDT_ACOFFMIN, UpdateCtrls)
	ON_EN_KILLFOCUS(IDC_EDT_ACOFFSEC, UpdateCtrls)
	ON_EN_KILLFOCUS(IDC_EDT_ACOFFMS, UpdateCtrls)
END_MESSAGE_MAP()


BEGIN_HTMLTEMPL_MAP(CDlgAtomicClock)
	TEMPL_ITEM(IDC_HTMCTL_ACSYSTIME, "<font color=\"black\"><b>%s %s</b></font>")
	TEMPL_ITEM(IDC_HTMCTL_ACSVRTIME, "<font color=\"darkgreen\"><b>%s %s</b></font>")
	TEMPL_ITEM(IDC_HTMCTL_ACDIFFTIME, "<font color=\"darkred\"><b>%s</b></font>")
	TEMPL_ITEM(IDC_HTMCTL_ACSTATUS, "<center>Last adjust in<br>2004-03-25 17:10:53<br><br>Next will be<br>2005-03-25 18:00:00</center>")
END_HTMLTEMPL_MAP()


// CDlgAtomicClock 消息处理程序

BOOL CDlgAtomicClock::OnEraseBkgnd(CDC* pDC)
{
	CRect rcClip;
    pDC->GetClipBox(rcClip);
	FillRect(pDC->m_hDC, rcClip, GetBgBrush());

	return TRUE;
}

void CDlgAtomicClock::OnDestroy()
{
	if (m_pNtpThread) // we must insure ntp thread was finished, or PostMessage would failed.
	{
		//TODO Add some notify to user
		if (WAIT_TIMEOUT == WaitForSingleObject(*m_pNtpThread, TIMA_THREAD_TIMEOUT))
		{
			TerminateThread(*m_pNtpThread, -1);
			m_pNtpThread->Delete();
		}

		m_pNtpThread = NULL;
	}

	UpdateData(TRUE);

	CDialog::OnDestroy();
}

BOOL CDlgAtomicClock::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Initial skin
	ApplySkin();

	// Initial controls
	m_spnEveryNum.SetRange(0, 240);
	m_spnOffHour.SetRange(0, 23);
	m_spnOffMin.SetRange(0, 59);
	m_spnOffSec.SetRange(0, 59);
	m_spnOffMS.SetRange(0, 999);

	m_lstServer.InsertColumn(0, _T("Server"), LVCFMT_LEFT, 160);
	m_lstServer.InsertColumn(1, _T("Location"), LVCFMT_LEFT, 170);

	// Initial states
	UpdateCtrls();

	//
	m_ntpThreadContext.hWnd = m_hWnd;

	//
	CString strText;
	strText.Format(GetHtmlTempl(IDC_HTMCTL_ACSYSTIME), _T("2005-03-30"), _T("12:12:40.123"));
	m_htmSysTime.SetWindowText(strText);


	return TRUE;
}

void CDlgAtomicClock::UpdateCtrls()
{
	UpdateData(TRUE);

	BOOL bEnable = (0 == theApp.GetSettings()->AtomicClock.AdjustEvery ? FALSE : TRUE);
	m_edtEveryNum.EnableWindow(bEnable);
	m_spnEveryNum.EnableWindow(bEnable);
	m_cmbEveryUnit.EnableWindow(bEnable);

	bEnable = (0 == theApp.GetSettings()->AtomicClock.UserOffset ? FALSE : TRUE);
	m_cmbOffSign.EnableWindow(bEnable);
	m_edtOffHour.EnableWindow(bEnable);
	m_spnOffHour.EnableWindow(bEnable);
	m_edtOffMin.EnableWindow(bEnable);
	m_spnOffMin.EnableWindow(bEnable);
	m_edtOffSec.EnableWindow(bEnable);
	m_spnOffSec.EnableWindow(bEnable);
	m_edtOffMS.EnableWindow(bEnable);
	m_spnOffMS.EnableWindow(bEnable);

	CSpinButtonCtrl* spins[5] = { &m_spnEveryNum, &m_spnOffHour, &m_spnOffMin,
		&m_spnOffSec, &m_spnOffMS };

	for (int i = 0; i < 5; i++)
		CheckSpinRange(*(spins[i]));
}

BOOL CDlgAtomicClock::CheckSpinRange(const CSpinButtonCtrl& ctlSpin)
{
	ATLASSERT( ctlSpin.GetSafeHwnd() );

	CWnd* pWndBuddy = ctlSpin.GetBuddy();
	ATLASSERT( pWndBuddy->GetSafeHwnd() );

	UINT nIDBuddy = pWndBuddy->GetDlgCtrlID();
	ATLASSERT( nIDBuddy );

	int num = GetDlgItemInt(nIDBuddy, NULL, FALSE);
	int upper, lower;

	ctlSpin.GetRange(lower, upper);

	if (num > upper)
		SetDlgItemInt(nIDBuddy, upper, FALSE);
	else if (num < lower)
		SetDlgItemInt(nIDBuddy, lower, FALSE);

	return TRUE; //TODO if change the value then return FALSE
}

HBRUSH CDlgAtomicClock::GetBgBrush()
{
	if (!m_bgBrush.GetSafeHandle())
	{
		COLORREF bgclr = SkinManager()->GetCurrentSkin()->GetWindowBgColor();
		m_bgBrush.CreateSolidBrush(bgclr);
	}

	return m_bgBrush;
}

HBRUSH CDlgAtomicClock::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			hbr = GetBgBrush();

			break;
		}
	case CTLCOLOR_MSGBOX:
	case CTLCOLOR_EDIT:
	case CTLCOLOR_LISTBOX:
	case CTLCOLOR_BTN:
	case CTLCOLOR_DLG:
	case CTLCOLOR_SCROLLBAR:
		break;
	default:
		ATLASSERT(0);
		break;
	}

	return hbr;
}

void CDlgAtomicClock::ApplySkin(void)
{
	m_picAC1.ApplySkin();
	m_picAC2.ApplySkin();
	m_picAC3.ApplySkin();
	m_picAC4.ApplySkin();
}

UINT CDlgAtomicClock::NtpClientProc(LPVOID pParam)
{
	ATLASSERT(pParam);
	NtpThreadContext* pContext = static_cast<NtpThreadContext*>(pParam);

	CSNTPClient sntp;
	BOOL bSuccess = sntp.GetServerTime(_T("time.windows.com"), pContext->ntpResponse);//clock.isc.org

	::PostMessage(pContext->hWnd, WM_TIMA_NTPRESPONSED,	(WPARAM)bSuccess, NULL);

	return 0;
}

void CDlgAtomicClock::OnBnClickedBtnACCheck()
{
	CheckTime(FALSE);
}

void CDlgAtomicClock::OnBnClickedBtnACAdjust()
{
	CheckTime(TRUE);
}

void CDlgAtomicClock::CheckTime(BOOL bAdjust)
{
	if (NULL == m_pNtpThread)
	{
		m_bNeedAdjust = bAdjust;
		m_btnCheck.EnableWindow(FALSE);
		m_btnAdjust.EnableWindow(FALSE);

		m_pNtpThread = AfxBeginThread(CDlgAtomicClock::NtpClientProc, &m_ntpThreadContext);
	}
	else
		ATLASSERT(0); // should not check time again when m_pNtpThread running

	//TODO: 帮助文件增加 Windows 时间服务器指南
	//TODO: 增加国内服务器列表
}

LRESULT CDlgAtomicClock::OnNtpResponsed(WPARAM wp, LPARAM lp)
{
	ATLASSERT(m_pNtpThread);

	WaitForSingleObject(*m_pNtpThread, INFINITE);
	m_pNtpThread = NULL;

	if (!wp) // No success get time info
	{
		CString strHtml;
		strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACSYSTIME), 
					_T("Failed to interact with atomic server. Please check your network connection."));
		m_htmDiffTime.SetWindowText(strHtml);
	}
	else
	{
		// Set time diff info to ui
		double dDiff = m_ntpThreadContext.ntpResponse.m_LocalClockOffset;

		//
		CNtpTime ntTmp(CNtpTime::GetCurrentTime());
		SYSTEMTIME stLocal = ntTmp;
		SYSTEMTIME stServer = ntTmp + dDiff;

//		TIME_ZONE_INFORMATION tzi;
//		GetTimeZoneInformation(&tzi);
//		SystemTimeToTzSpecificLocalTime(&tzi, &stTmp, &stLocal);
//
//		//
//		stTmp = m_ntpThreadContext.ntpResponse.m_OriginateTime
//					+ m_ntpThreadContext.ntpResponse.m_LocalClockOffset;
//		SYSTEMTIME stServer;
//
//		SystemTimeToTzSpecificLocalTime(&tzi, &stTmp, &stServer);

		// local time
		CString strDate;
		GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &stLocal, NULL, strDate.GetBuffer(MAX_PATH), MAX_PATH);
		strDate.ReleaseBuffer();

		CString strTime;
		GetTimeFormat(LOCALE_USER_DEFAULT, LOCALE_NOUSEROVERRIDE, &stLocal, NULL, strTime.GetBuffer(MAX_PATH), MAX_PATH);
		strTime.ReleaseBuffer();

		CString strTmp = strTime;
		strTime.Format(_T("%s.%03d"), strTmp, stLocal.wMilliseconds);

		CString strHtml;
		strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACSYSTIME), strDate, strTime);

		m_htmSysTime.SetWindowText(strHtml);

		// server time
		GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &stServer, NULL, strDate.GetBuffer(MAX_PATH), MAX_PATH);
		strDate.ReleaseBuffer();

		GetTimeFormat(LOCALE_USER_DEFAULT, LOCALE_NOUSEROVERRIDE, &stServer, NULL, strTime.GetBuffer(MAX_PATH), MAX_PATH);
		strTime.ReleaseBuffer();

		strTmp = strTime;
		strTime.Format(_T("%s.%03d"), strTmp, stServer.wMilliseconds);

		strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACSVRTIME), strDate, strTime);

		m_htmSvrTime.SetWindowText(strHtml);

		// diff
		strTmp.Format(_T("%.3f"), dDiff);
		strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACDIFFTIME), strTmp);

		m_htmDiffTime.SetWindowText(strHtml);

		//TODO adjust system time
		if (m_bNeedAdjust)
		{

		}
	}

	m_btnCheck.EnableWindow(TRUE);
	m_btnAdjust.EnableWindow(TRUE);

	return 0L;
}
