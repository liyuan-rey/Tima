// SkinButton.cpp : 实现文件
//

#include "stdafx.h"
#include "SkinButton.h"
#include "SkinSettings.h"


// CSkinButton

IMPLEMENT_DYNAMIC(CSkinButton, CButton)


BEGIN_MESSAGE_MAP(CSkinButton, CButton)
END_MESSAGE_MAP()



// CSkinButton 消息处理程序



void CSkinButton::PreSubclassWindow()
{
	// ToDo: Add your specialized code here or after the call to base class
	
	CWnd::PreSubclassWindow();
}

BOOL CSkinButton::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// ToDo: Add your specialized code here or after the call to base class
	
	return CWnd::OnWndMsg(message, wParam, lParam, pResult);
}

