// SkinPicture.cpp : 实现文件
//

#include "stdafx.h"
#include "SkinPicture.h"
#include "SkinSettings.h"


// CSkinPicture

IMPLEMENT_DYNAMIC(CSkinPicture, CWnd)


BEGIN_MESSAGE_MAP(CSkinPicture, CWnd)
END_MESSAGE_MAP()



// CSkinPicture 消息处理程序



void CSkinPicture::PreSubclassWindow()
{
	// ToDo: Add your specialized code here or after the call to base class
	
	CWnd::PreSubclassWindow();
}

BOOL CSkinPicture::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// ToDo: Add your specialized code here or after the call to base class
	
	return CWnd::OnWndMsg(message, wParam, lParam, pResult);
}

