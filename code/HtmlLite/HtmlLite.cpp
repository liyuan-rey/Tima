// HtmlLite.cpp : 实现文件
//

#include "stdafx.h"
#include "HtmlLite.h"


// CHtmlLite
const TCHAR* CHtmlLite::WindowClassName = _T("HtmlLite");

IMPLEMENT_DYNAMIC(CHtmlLite, CWnd)

CHtmlLite::CHtmlLite()
{
	RegisterWndClass();
}

CHtmlLite::~CHtmlLite()
{
}


BEGIN_MESSAGE_MAP(CHtmlLite, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
END_MESSAGE_MAP()



// CHtmlLite 消息处理程序


BOOL CHtmlLite::RegisterWndClass(void)
{
	WNDCLASS windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASS));

	HINSTANCE hInst = AfxGetInstanceHandle();

	//Check weather the class is registerd already
	if (!(::GetClassInfo(hInst, WindowClassName, &windowclass)))
	{
		//If not then we have to register the new class
		windowclass.lpszClassName = WindowClassName;
		windowclass.style = CS_GLOBALCLASS | CS_SAVEBITS;// CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		windowclass.lpfnWndProc = ::DefWindowProc;
		windowclass.hInstance = hInst;
//		windowclass.hIcon = NULL;
		windowclass.hCursor = ::LoadCursor(NULL, IDC_ARROW);
//		windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
//		windowclass.lpszMenuName = NULL;

		if (!AfxRegisterClass(&windowclass))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CHtmlLite::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

void CHtmlLite::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rcOutput;
	GetClientRect(rcOutput);

//	if (dc.m_ps.fErase)
	{
		HBRUSH hbr = (HBRUSH)GetParent()->SendMessage(WM_CTLCOLORSTATIC,
						(WPARAM)dc.m_hDC, (LPARAM)m_hWnd);
		::FillRect(dc.m_hDC, rcOutput, hbr);
	}

	DWORD dwStyle = GetStyle();
	if ((dwStyle & HS_BORDER) == HS_BORDER)
	{
		CBrush br;
		br.CreateSysColorBrush(COLOR_BTNSHADOW);
		dc.FrameRect(rcOutput, &br);
		rcOutput.DeflateRect(1, 1);
	}

	CString strHtml;
	GetWindowText(strHtml);
	if (strHtml.IsEmpty())
		return;

	CSize szPrep = m_drawer.PrepareOutput(&dc, strHtml);

	if ((dwStyle & HS_CENTER) == HS_CENTER)
	{
		int xFix = (rcOutput.Width() - szPrep.cx) / 2;
		int yFix = (rcOutput.Height() - szPrep.cy) / 2;

		rcOutput.DeflateRect(xFix, yFix);
	}

	m_drawer.DrawPreparedOutput(&dc, strHtml, rcOutput);
}

LRESULT CHtmlLite::OnSetText(WPARAM wp, LPARAM lp)
{
	LRESULT lRet = DefWindowProc(WM_SETTEXT, wp, lp);
	Invalidate(TRUE);

	return lRet;
}