// TimaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tima.h"
#include "TimaDlg.h"
#include ".\timadlg.h"

#include "skin\SkinManager.h"
#include "skin\Skin.h"

#include "DlgAtomicClock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTimaDlg dialog
CTimaDlg::CTimaDlg(CWnd* pParent /*=NULL*/)
	: CSkinDialog(CTimaDlg::IDD, pParent)
	, m_nActivedPanel(0), m_pdlgAtomicClock(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimaDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICT_1, m_pic1);
	DDX_Control(pDX, IDC_PICT_2, m_pic2);
	DDX_Control(pDX, IDC_PICT_3, m_pic3);
	DDX_Control(pDX, IDC_RBN_ATOMICCLOCK, m_rbnAtomicClock);
	DDX_Control(pDX, IDC_RBN_TRAYCLOCK, m_rbnTrayClock);
	DDX_Control(pDX, IDC_RBN_WEATHER, m_rbnWeather);
	DDX_Control(pDX, IDC_RBN_REMINDER, m_rbnReminder);
	DDX_Control(pDX, IDC_RBN_CALENDER, m_rbnCalender);
	DDX_Control(pDX, IDC_RBN_STOPWATCH, m_rbnStopWatch);
	DDX_Control(pDX, IDC_RBN_SETTINGS, m_rbnSettings);
	DDX_Control(pDX, IDC_RBN_ABOUT, m_rbnAbout);
	DDX_Radio(pDX, IDC_RBN_ATOMICCLOCK, m_nActivedPanel);
}

BEGIN_MESSAGE_MAP(CTimaDlg, CSkinDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RBN_ATOMICCLOCK, IDC_RBN_ABOUT, OnChangePanel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CTimaDlg message handlers
BOOL CTimaDlg::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	ApplySkin();

	// create sub dlg
	CSkinPtr spSkin = SkinManager::Instance().GetCurrentSkin();
	ATLASSERT(spSkin);

	RECT rcArea = {0};
	spSkin->GetCustomSetting(CSkin::GCSRect, 1, &rcArea);
	ATLASSERT(CRect(rcArea).IsRectEmpty() == FALSE);

	m_pdlgAtomicClock = new CDlgAtomicClock(this);
	m_pdlgAtomicClock->Create(CDlgAtomicClock::IDD, this);
	ATLASSERT(m_pdlgAtomicClock->GetSafeHwnd());
	m_pdlgAtomicClock->MoveWindow(&rcArea, FALSE);
	m_pdlgAtomicClock->ShowWindow(SW_NORMAL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTimaDlg::ApplySkin()
{
	m_pic1.ApplySkin();
	m_pic2.ApplySkin();
	m_pic3.ApplySkin();

	m_rbnAtomicClock.ApplySkin();
	m_rbnTrayClock.ApplySkin();
	m_rbnWeather.ApplySkin();
	m_rbnReminder.ApplySkin();
	m_rbnCalender.ApplySkin();
	m_rbnStopWatch.ApplySkin();
	m_rbnSettings.ApplySkin();
	m_rbnAbout.ApplySkin();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CTimaDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CSkinDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTimaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTimaDlg::OnChangePanel(UINT id)
{
	UpdateData(TRUE);

	if (m_nActivedPanel != id)
	{
		CString strMsg;
		strMsg.Format("To active %d panel.", id);
		AfxMessageBox(strMsg);
	}
}

void CTimaDlg::OnDestroy()
{
	if (m_pdlgAtomicClock->GetSafeHwnd())
	{
		m_pdlgAtomicClock->DestroyWindow();
		delete m_pdlgAtomicClock;
		m_pdlgAtomicClock = NULL;
	}

	CSkinDialog::OnDestroy();
}
