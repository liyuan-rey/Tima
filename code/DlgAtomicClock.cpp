// DlgAtomicClock.cpp : 实现文件
//

#include "stdafx.h"
#include "Tima.h"
#include "DlgAtomicClock.h"

#include <ATLComTime.h>

#include "skin\skinmanager.h"

// CDlgAtomicClock 对话框

IMPLEMENT_DYNAMIC(CDlgAtomicClock, CDialog)

CDlgAtomicClock::CDlgAtomicClock(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAtomicClock::IDD, pParent), m_bNeedAdjust(FALSE)
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
	DDX_Control(pDX, IDC_HTMCTL_ACLASTSTATUS, m_htmLastStatus);
	DDX_Control(pDX, IDC_HTMCTL_ACNEXTSTATUS, m_htmNextStatus);
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
	DDX_Control(pDX, IDC_CHK_ACONLY, m_chkOnly);
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
	CTimaSettings& theSettings = theApp.GetSettings();
	DDX_Check(pDX, IDC_CHK_ACSTART, theSettings.AtomicClock.AdjustOnStart);
	DDX_Check(pDX, IDC_CHK_ACESTAB, theSettings.AtomicClock.AdjustOnConnect);
	DDX_Check(pDX, IDC_CHK_ACEVERY, theSettings.AtomicClock.AdjustEvery);
	DDX_Text(pDX, IDC_EDT_ACEVERYNUM, theSettings.AtomicClock.AdjustEveryNum);
	DDX_CBIndex(pDX, IDC_CMB_ACEVERYUNIT, theSettings.AtomicClock.AdjustEveryUnit);
	DDX_Check(pDX, IDC_CHK_ACONLY, theSettings.AtomicClock.AdjustOnly);
	DDX_Check(pDX, IDC_CHK_ACOFFSET, theSettings.AtomicClock.UserOffset);
	DDX_CBIndex(pDX, IDC_CMB_ACOFFSIGN, theSettings.AtomicClock.OffsetSign);
	DDX_Text(pDX, IDC_EDT_ACOFFHOUR, theSettings.AtomicClock.OffsetHour);
	DDX_Text(pDX, IDC_EDT_ACOFFMIN, theSettings.AtomicClock.OffsetMin);
	DDX_Text(pDX, IDC_EDT_ACOFFSEC, theSettings.AtomicClock.OffsetSec);
	DDX_Text(pDX, IDC_EDT_ACOFFMS, theSettings.AtomicClock.OffsetMS);
}


BEGIN_MESSAGE_MAP(CDlgAtomicClock, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_ACCHECK, OnBnClickedBtnACCheck)
	ON_BN_CLICKED(IDC_BTN_ACADJUST, OnBnClickedBtnACAdjust)
	ON_MESSAGE(WM_TIMA_NTPRESPONSED, OnNtpResponsed)
	//
	ON_BN_CLICKED(IDC_CHK_ACSTART, UpdateNextTime)
	ON_BN_CLICKED(IDC_CHK_ACESTAB, UpdateNextTime)
	ON_BN_CLICKED(IDC_CHK_ACEVERY, OnBnClickedChkACEvery)
	ON_EN_KILLFOCUS(IDC_EDT_ACEVERYNUM, OnBnClickedChkACEvery)
	ON_CBN_SELCHANGE(IDC_CMB_ACEVERYUNIT, OnBnClickedChkACEvery)
	ON_BN_CLICKED(IDC_CHK_ACOFFSET, UpdateCtrls)
	ON_EN_KILLFOCUS(IDC_EDT_ACOFFHOUR, UpdateCtrls)
	ON_EN_KILLFOCUS(IDC_EDT_ACOFFMIN, UpdateCtrls)
	ON_EN_KILLFOCUS(IDC_EDT_ACOFFSEC, UpdateCtrls)
	ON_EN_KILLFOCUS(IDC_EDT_ACOFFMS, UpdateCtrls)
END_MESSAGE_MAP()


BEGIN_HTMLTEMPL_MAP(CDlgAtomicClock)
	TEMPL_ITEM(IDC_HTMCTL_ACSYSTIME, "<font color=\"black\"><b>%s</b></font>")
	TEMPL_ITEM(IDC_HTMCTL_ACSVRTIME, "<font color=\"darkgreen\"><b>%s</b></font>")
	TEMPL_ITEM(IDC_HTMCTL_ACDIFFTIME, "<font color=\"darkred\"><b>%s</b></font>")
	TEMPL_ITEM(IDC_HTMCTL_ACLASTSTATUS, "<center>Last adjust in<br>%s</center>")
	TEMPL_ITEM(IDC_HTMCTL_ACNEXTSTATUS, "<center>Next will be<br>%s</center>")
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
	UpdateData(TRUE);

	CDialog::OnDestroy();
}

BOOL CDlgAtomicClock::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Initial skin
	ApplySkin();

	// Initial controls
	m_spnEveryNum.SetRange(1, 240);
	m_spnOffHour.SetRange(0, 23);
	m_spnOffMin.SetRange(0, 59);
	m_spnOffSec.SetRange(0, 59);
	m_spnOffMS.SetRange(0, 999);

	m_lstServer.InsertColumn(0, _T("Server"), LVCFMT_LEFT, 160);
	m_lstServer.InsertColumn(1, _T("Location"), LVCFMT_LEFT, 170);

	UpdateActivedServer();

	// Initial states
	UpdateCtrls();

	//
	CString strText;
	strText.Format(GetHtmlTempl(IDC_HTMCTL_ACDIFFTIME), _T("Press button to manual adjust."));
	m_htmDiffTime.SetWindowText(strText);

	//
	ShowNextAdjustInfo(theApp.GetSettings().AtomicClock.LastAdjustAt);

	// Adjust time on startup
	if (BST_CHECKED == m_chkStart.GetCheck())
		CheckTime(TRUE);

	// Set auto-adjust timer
	SetACEveryTimer();

	return TRUE;
}

void CDlgAtomicClock::UpdateActivedServer()
{
	m_lstServer.DeleteAllItems();

	CSntpServers* pServers = &(theApp.GetSettings().AtomicClock.ActivedServers);
	INT_PTR nCount = pServers->GetCount();
	for (int i = 0; i < nCount; i++)
	{
		m_lstServer.InsertItem(i, pServers->GetAt(i).URL);
		m_lstServer.SetItemText(i, 1, pServers->GetAt(i).Name);

		m_TimeServer.AddServer(pServers->GetAt(i).URL);
	}
}

void CDlgAtomicClock::UpdateCtrls()
{
	BOOL bEnable = (BST_CHECKED == m_chkEvery.GetCheck());
	m_edtEveryNum.EnableWindow(bEnable);
	m_spnEveryNum.EnableWindow(bEnable);
	m_cmbEveryUnit.EnableWindow(bEnable);

	bEnable = (BST_CHECKED == m_chkOffset.GetCheck());
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
	else
		return TRUE;

	return FALSE;
}

void CDlgAtomicClock::SetACEveryTimer()
{
	KillTimer(TIMA_TIMERID_ACEVERY);

	if (BST_UNCHECKED != m_chkEvery.GetCheck())
	{
		// get passed time since we last adjust
		COleDateTime odtSysTime = COleDateTime::GetCurrentTime();
		COleDateTime odtLastAdjustTime(theApp.GetSettings().AtomicClock.LastAdjustAt);

		COleDateTimeSpan spanSys = std::max<COleDateTimeSpan>(
									odtLastAdjustTime - odtSysTime,
									COleDateTimeSpan(0, 0, 0, 0));

		// get user-defined time span
		LONG days = 0;
		int hours = 0, mins = 0, secs = 0;
		int num = (int)GetDlgItemInt(m_edtEveryNum.GetDlgCtrlID());

		int nSelected = m_cmbEveryUnit.GetCurSel();
		int nNum = GetDlgItemInt(IDC_EDT_ACEVERYNUM);
		COleDateTimeSpan spanUser(
			0 == nSelected ? nNum : 0,
			1 == nSelected ? nNum : 0,
			2 == nSelected ? nNum : 0,
			3 == nSelected ? nNum : 0);

		// already over user-defined time span, adjust immediately
		if (spanSys >= spanUser)
		{
			CheckTime(TRUE);
			return;
		}

		// else SetTimer for next adjust
		UINT nElapse = UINT(double(spanUser - spanSys) * 24 * 3600 * 1000);
//		UINT nElapseFix =  std::min<UINT>(USER_TIMER_MAXIMUM, 
//			std::max<UINT>(USER_TIMER_MINIMUM, nElapse));

		if (!SetTimer(TIMA_TIMERID_ACEVERY, nElapse, NULL))
		{
			AfxMessageBox(IDS_SETTIMER_ERROR);
			return;
		}
	}
}

HBRUSH CDlgAtomicClock::GetBgBrush()
{
	if (!m_bgBrush.GetSafeHandle())
	{
		COLORREF bgclr = SkinManager::Instance().GetCurrentSkin()->GetWindowBgColor();
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

void CDlgAtomicClock::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (TIMA_TIMERID_ACEVERY == nIDEvent)
	{
		CheckTime(TRUE);
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlgAtomicClock::ApplySkin(void)
{
	m_picAC1.ApplySkin();
	m_picAC2.ApplySkin();
	m_picAC3.ApplySkin();
	m_picAC4.ApplySkin();
}

void CDlgAtomicClock::OnBnClickedBtnACCheck()
{
	CheckTime(FALSE);
}

void CDlgAtomicClock::OnBnClickedBtnACAdjust()
{
	CheckTime(TRUE);
}

void CDlgAtomicClock::OnBnClickedChkACEvery()
{
	UpdateCtrls();

	if (BST_UNCHECKED == m_chkEvery.GetCheck())
		KillTimer(TIMA_TIMERID_ACEVERY);
	else
		SetACEveryTimer();

	UpdateNextTime();
}

void CDlgAtomicClock::UpdateNextTime()
{
	ShowNextAdjustInfo(theApp.GetSettings().AtomicClock.LastAdjustAt);
}

void CDlgAtomicClock::CheckTime(BOOL bAdjust)
{
	// should not check time again when TimeServer running
	if (m_TimeServer.IsReady())
	{
		m_bNeedAdjust = bAdjust;
		m_btnCheck.EnableWindow(FALSE);
		m_btnAdjust.EnableWindow(FALSE);

		//TODO: clear exist time info and show wait msg

		//
		m_TimeServer.StartCheck(GetSafeHwnd());
	}

	//TODO: 帮助文件增加 Windows 时间服务器指南
	//TODO: 增加国内服务器列表
}

LRESULT CDlgAtomicClock::OnNtpResponsed(WPARAM, LPARAM)
{
	double dDiff = 0;
	BOOL bSucceed = m_TimeServer.GetDifference(dDiff);

	if (!bSucceed) // No success get time info
	{
		CString strHtml;
		strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACSYSTIME), 
			_T("Unknown"), _T(""));
		m_htmSysTime.SetWindowText(strHtml);

		strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACSVRTIME), 
					_T("Unknown"), _T(""));
		m_htmSvrTime.SetWindowText(strHtml);

		strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACDIFFTIME), 
					_T("Failed to interact with atomic server. Please retry later."));
		m_htmDiffTime.SetWindowText(strHtml);
	}
	else
	{
		// local time
		SYSTEMTIME stLocal;
		GetLocalTime(&stLocal);

		COleDateTime odtLocal = stLocal;

		CString strTmp;
		strTmp.Format(_T("%s.%03d"), odtLocal.Format(LOCALE_NOUSEROVERRIDE, LOCALE_SYSTEM_DEFAULT), stLocal.wMilliseconds);

		CString strHtml;
		strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACSYSTIME), strTmp);

		m_htmSysTime.SetWindowText(strHtml);

		// diff
		CString strTmp2;
		if (BST_CHECKED == m_chkOffset.GetCheck())
		{
			double dOffset = GetDlgItemInt(IDC_EDT_ACOFFHOUR) * 3600
								+ GetDlgItemInt(IDC_EDT_ACOFFMIN) * 60
								+ GetDlgItemInt(IDC_EDT_ACOFFSEC)
								+ GetDlgItemInt(IDC_EDT_ACOFFMS) / 1000;

			dDiff = m_cmbOffSign.GetCurSel() ? (dDiff - dOffset) : (dDiff + dOffset);
			
			strTmp2 = _T("(with user offset)");
		}

		strTmp.Format(_T("%.3f %s"), dDiff, strTmp2);
		strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACDIFFTIME), strTmp);

		m_htmDiffTime.SetWindowText(strHtml);

		// server time
		SYSTEMTIME stServer = CNtpTime(stLocal) + dDiff;
		COleDateTime odtServer = stServer;

		strTmp.Format(_T("%s.%03d"), odtServer.Format(LOCALE_NOUSEROVERRIDE, LANG_USER_DEFAULT), stServer.wMilliseconds);
		strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACSVRTIME), strTmp);

		m_htmSvrTime.SetWindowText(strHtml);

		// adjust system time
		if (m_bNeedAdjust)
		{
			// check if we has wrong daylight settings with system
			if (fabs(dDiff) >= (3600-15) && BST_UNCHECKED == m_chkOnly.GetCheck())
			{
				int nRet = AfxMessageBox(_T("Tima detected your system has about 1 hour diffrence with atomic server, if \n")
							_T("your system has wrong daylight settings, use \"adjust minutes and seconds only\" option \n")
							_T("to avoid wrong time adjustting.\n\n")
							_T("Would you like to proceed?\n")
							_T("   Yes\t- only adjust time with minutes and seconds\n")
							_T("   No\t- adjust time acoording with atomic server\n")
							_T("   Cancel\t- cancel time adjustment this time"), MB_ICONQUESTION | MB_YESNOCANCEL);

				if (IDYES == nRet)
					m_chkOnly.SetCheck(BST_CHECKED);
				else if (IDCANCEL == nRet)
				{
					strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACDIFFTIME), _T("User canceled time adjustment."));
					m_htmDiffTime.SetWindowText(strHtml);

					m_btnCheck.EnableWindow(TRUE);
					m_btnAdjust.EnableWindow(TRUE);

					return 0L;
				}
			}

			// Fix diff time when only adjust minutes and seconds
			if (BST_CHECKED == m_chkOnly.GetCheck())
			{
				while (fabs(dDiff) >= 3600)
				{
					if (dDiff > 0)
						dDiff -= 3600;
					else
						dDiff += 3600;
				}
			}

			// Adjust time and output result
			CNtpTime newTime = CNtpTime::GetCurrentTime() + dDiff;
			CSNTPClient sntp;
			if (sntp.SetClientTime(newTime))
			{
				theApp.GetSettings().AtomicClock.LastAdjustAt = newTime;

				strTmp = _T("System time adjusted.");

				// Info for update time
				ShowNextAdjustInfo(newTime);
			}
			else
				strTmp = _T("Failed to set system time, please try later.");

			strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACDIFFTIME), strTmp);
			m_htmDiffTime.SetWindowText(strHtml);
		}
	}

	m_btnCheck.EnableWindow(TRUE);
	m_btnAdjust.EnableWindow(TRUE);

	return 0L;
}

void CDlgAtomicClock::ShowNextAdjustInfo(const SYSTEMTIME& stLast)
{
	COleDateTime odtLast = stLast;

	// last time
	CString strHtml;
	strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACLASTSTATUS), odtLast.Format(LOCALE_NOUSEROVERRIDE, LANG_USER_DEFAULT));
	m_htmLastStatus.SetWindowText(strHtml);

	// next time
	CString strNext;
	if (BST_CHECKED == m_chkEvery.GetCheck())
	{
		int nSelected = m_cmbEveryUnit.GetCurSel();
		int nNum = GetDlgItemInt(IDC_EDT_ACEVERYNUM);
		COleDateTimeSpan oleSpan(
			0 == nSelected ? nNum : 0,
			1 == nSelected ? nNum : 0,
			2 == nSelected ? nNum : 0,
			3 == nSelected ? nNum : 0);

		COleDateTime odtNext(stLast);
		odtNext += oleSpan;

		strNext = odtNext.Format(LOCALE_NOUSEROVERRIDE, LANG_USER_DEFAULT);
	}
	else if (BST_CHECKED == m_chkEstab.GetCheck())
	{
		strNext.LoadString(IDS_AC_NEXTESTAB);
	}
	else if (BST_CHECKED == m_chkStart.GetCheck())
	{
		strNext.LoadString(IDS_AC_NEXTSTART);
	}
	else
	{
		strNext.LoadString(IDS_AC_NEXTMANUAL);
	}

	strHtml.Format(GetHtmlTempl(IDC_HTMCTL_ACNEXTSTATUS), strNext);
	m_htmNextStatus.SetWindowText(strHtml);
}
