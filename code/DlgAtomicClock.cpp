// DlgAtomicClock.cpp : 实现文件
//

#include "stdafx.h"
#include "Tima.h"
#include "DlgAtomicClock.h"
#include ".\dlgatomicclock.h"


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
}


BEGIN_MESSAGE_MAP(CDlgAtomicClock, CDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgAtomicClock 消息处理程序

BOOL CDlgAtomicClock::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

// 	return CDialog::OnEraseBkgnd(pDC);
	return FALSE;
}

#include <uxtheme.h>
#pragma comment (lib, "UxTheme.lib")
BOOL CDlgAtomicClock::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	BOOL bSuccess = IsThemeActive();
	bSuccess = IsAppThemed();
	SetThemeAppProperties(STAP_ALLOW_CONTROLS);
	HRESULT hr = EnableTheming(TRUE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
