// DlgAtomicClock.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tima.h"
#include "DlgAtomicClock.h"
#include ".\dlgatomicclock.h"


// CDlgAtomicClock �Ի���

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


// CDlgAtomicClock ��Ϣ�������

BOOL CDlgAtomicClock::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

// 	return CDialog::OnEraseBkgnd(pDC);
	return FALSE;
}

#include <uxtheme.h>
#pragma comment (lib, "UxTheme.lib")
BOOL CDlgAtomicClock::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	BOOL bSuccess = IsThemeActive();
	bSuccess = IsAppThemed();
	SetThemeAppProperties(STAP_ALLOW_CONTROLS);
	HRESULT hr = EnableTheming(TRUE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
