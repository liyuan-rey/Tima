// SkinDialog.cpp : 实现文件
//

#include "StdAfx.h"
#include ".\skindialog.h"
#include "..\resource.h"

#include "SkinTypes.h"
#include "SkinManager.h"

// CSkinDialog

IMPLEMENT_DYNAMIC(CSkinDialog, CDialog)


BEGIN_MESSAGE_MAP(CSkinDialog, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

CSkinDialog::CSkinDialog() : m_pSettings(NULL)
{
}

CSkinDialog::~CSkinDialog()
{
}

CSkinDialog::CSkinDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
	: CDialog(lpszTemplateName, pParentWnd), m_pSettings(NULL)
{
}

CSkinDialog::CSkinDialog(UINT nIDTemplate, CWnd* pParentWnd)
	: CDialog(nIDTemplate, pParentWnd), m_pSettings(NULL)
{
}

// 
extern AFX_INLINE CSkinManager* SkinManager();

void CSkinDialog::PreInitDialog()
{
	CDialog::PreInitDialog();

	// Binding skin info
	BOOL bSuccess = SkinManager()->GetCurrentSkin()->BindSkinInfo(this);
	if (!bSuccess || !m_pSettings)
	{
		AfxMessageBox(IDS_BINDINGSKINERROR);
		return;
	}

	// Apply window size
	MoveWindow(0, 0, m_pSettings->Size.cx, m_pSettings->Size.cy, FALSE);

	// Apply round window region
	const int nRoundSize = 10;

	CRect rcWindow;
	GetWindowRect(rcWindow);
	ATLASSERT(rcWindow.Height() > 2*nRoundSize && rcWindow.Width() > 2*nRoundSize);

	CRect rcTmpA(rcWindow);
	rcTmpA.DeflateRect(0, nRoundSize / 2, 0, 0);

	CRgn rgnTmpA;
	rgnTmpA.CreateRectRgnIndirect(rcTmpA);

	CRect rcTmpB(rcWindow.left + (nRoundSize / 2), rcWindow.top,
		rcWindow.right - (nRoundSize / 2), rcWindow.top + nRoundSize - 1);

	CRgn rgnTmpB;
	rgnTmpB.CreateRectRgnIndirect(rcTmpB);

	CRgn rgnTmpC;
	rgnTmpC.CreateEllipticRgnIndirect(CRect(rcWindow.TopLeft(), CSize(nRoundSize, nRoundSize)));
	
	CRgn rgnTmpD;
	rgnTmpD.CreateRectRgn(0,0,0,0);
	int status = rgnTmpD.CombineRgn(&rgnTmpB, &rgnTmpC, RGN_OR);

	rgnTmpB.CopyRgn(&rgnTmpD);

	rgnTmpC.OffsetRgn(rcWindow.Width() - nRoundSize, 0);
	status = rgnTmpD.CombineRgn(&rgnTmpB, &rgnTmpC, RGN_OR);

	CRgn rgnWindow;
	rgnWindow.CreateRectRgn(0,0,0,0);
	status = rgnWindow.CombineRgn(&rgnTmpA, &rgnTmpD, RGN_OR);
//	if (ERROR == status || NULLREGION == status)
//	{
//		AfxMessageBox(_T(""));
//	}

	SetWindowRgn((HRGN)rgnWindow.Detach(), FALSE);

	// Apply inter button

	// Apply new style and size
	ModifyStyle(WS_CAPTION | WS_THICKFRAME, WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	ModifyStyleEx(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE, 0L);

	SetWindowPos(NULL, 0, 0, 0, 0,
		SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
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

UINT CSkinDialog::GetID()
{
	return GetDialogSkinID();
}

ESkinControl CSkinDialog::GetType()
{
	return ESkinControl::Window;
}

BOOL CSkinDialog::SetSkinInfo(CSettings* pInfo)
{
	ATLASSERT(pInfo);
	m_pSettings = dynamic_cast<CWindowSettings*>(pInfo);
	ATLASSERT(m_pSettings);

	return (NULL != m_pSettings);
}

// CSkinDialog 消息处理程序


BOOL CSkinDialog::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CSkinDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CxImage* pImage = SkinManager()->GetCurrentSkin()->GetSkinImage();
	if (!pImage || !pImage->IsValid())
		return;

	CxImage imgTmp;
	pImage->Crop(m_pSettings->Frames[FPTopLeft][FSActive], &imgTmp);

	CRect rcClient;
	GetClientRect(rcClient);
	imgTmp.Draw2(dc.m_hDC, m_pSettings->Frames[FPTopLeft][FSActive]);

//	CRect rcClient;
//	GetClientRect(rcClient);
//
//	CxImage imgTmp;
//	pImage->Crop(rcClient, &imgTmp);
//
//	imgTmp.Draw2(dc.m_hDC, rcClient);
}
