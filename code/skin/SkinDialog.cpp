// SkinDialog.cpp : 实现文件
//

#include "StdAfx.h"
#include ".\skindialog.h"
#include "SkinManager.h"
#include "SkinSettings.h"


// CSkinDialog

IMPLEMENT_DYNAMIC(CSkinDialog, CDialog)


BEGIN_MESSAGE_MAP(CSkinDialog, CDialog)
END_MESSAGE_MAP()



// CSkinDialog 消息处理程序



BOOL CSkinDialog::PreCreateWindow(CREATESTRUCT& cs)
{
	
	// ToDo:  Add your specialized code here and/or call the base class
	
	return CWnd::PreCreateWindow(cs);
}

void CSkinDialog::PreInitDialog()
{
	// ToDo: Add your specialized code here or after the call to base class
	
	CDialog::PreInitDialog();
}

void CSkinDialog::PostNcDestroy()
{
	// ToDo: Add your specialized code here or after the call to base class
	
	CWnd::PostNcDestroy();
}

BOOL CSkinDialog::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// ToDo: Add your specialized code here or after the call to base class
	
	return CWnd::OnWndMsg(message, wParam, lParam, pResult);
}

