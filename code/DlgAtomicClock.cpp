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
	: CDialog(CDlgAtomicClock::IDD, pParent)
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
}


BEGIN_MESSAGE_MAP(CDlgAtomicClock, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_ACCHECK, OnBnClickedBtnAccheck)
END_MESSAGE_MAP()


BEGIN_HTMLTEMPL_MAP(CDlgAtomicClock)
	TEMPL_ITEM(IDC_HTMCTL_ACSYSTIME, "<font color=\"black\"><b>%s</b></font>")
	TEMPL_ITEM(IDC_HTMCTL_ACSVRTIME, "<font color=\"darkgreen\"><b>2005-03-30 12:12:47.000</b></font>")
	TEMPL_ITEM(IDC_HTMCTL_ACDIFFTIME, "<font color=\"darkred\"><b>-7.123</b></font>")
	TEMPL_ITEM(IDC_HTMCTL_ACSTATUS, "<center>Last adjust in<br>2004-03-25 17:10:53<br><br>Next will be<br>2005-03-25 18:00:00</center>")
END_HTMLTEMPL_MAP()


// CDlgAtomicClock 消息处理程序

BOOL CDlgAtomicClock::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

BOOL CDlgAtomicClock::OnInitDialog()
{
	CDialog::OnInitDialog();

	ApplySkin();

	CString strText;
	strText.Format(GetHtmlTempl(IDC_HTMCTL_ACSYSTIME), _T("2005-03-30 12:12:40.123"));
	m_htmSysTime.SetWindowText(strText);


	return TRUE;
}

HBRUSH CDlgAtomicClock::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		{
			if (!m_bgBrush.GetSafeHandle())
			{
				COLORREF bgclr = SkinManager()->GetCurrentSkin()->GetWindowBgColor();
				m_bgBrush.CreateSolidBrush(bgclr);
			}

			pDC->SetBkMode(TRANSPARENT);
			hbr = m_bgBrush;

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

#include "include\w3mfc\sntp.h"
void CDlgAtomicClock::OnBnClickedBtnAccheck()
{
	CSNTPClient sntp;
	NtpServerResponse respo;
	sntp.GetServerTime(_T("clock.isc.org"), respo);

	SYSTEMTIME stLocal = respo.m_OriginateTime;
	SYSTEMTIME stServer = respo.m_OriginateTime + respo.m_LocalClockOffset;
	double dDiff = respo.m_LocalClockOffset;

	//TODO: 帮助文件增加时间服务器解释
	//TODO: 增加国内服务器列表
}
