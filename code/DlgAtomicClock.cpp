// DlgAtomicClock.cpp : 实现文件
//

#include "stdafx.h"
#include "Tima.h"
#include "DlgAtomicClock.h"


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
END_MESSAGE_MAP()


// CDlgAtomicClock 消息处理程序
