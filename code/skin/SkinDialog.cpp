// SkinDialog.cpp : 实现文件
//

#include "StdAfx.h"
#include ".\skindialog.h"
#include "..\resource.h"

#include "..\include\memdc\memdc.h"

#include "SkinTypes.h"
#include "SkinManager.h"
#include "SkinButton.h"


// CSkinDialog

CSkinDialog::CSkinDialog() : m_pSettings(NULL), m_rcCaption(0,0,0,0)
{
}

CSkinDialog::~CSkinDialog()
{
	if (!m_arrButtons.IsEmpty())
	{
		CSkinButton* pButton = NULL;
		INT_PTR nCount = m_arrButtons.GetCount();
		for (int i = 0; i < nCount; i++)
		{
			pButton = m_arrButtons.GetAt(i);
			if (pButton)
			{
				if (pButton->m_hWnd) {
					ATLTRACE(_T("*** SkinDebug ***: Delete non-destroy window, maybe cause mem leak.\n"));
					pButton->DestroyWindow();
				}

				delete pButton;
			}
		}

		m_arrButtons.RemoveAll();
	}
}

CSkinDialog::CSkinDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
	: CDialog(lpszTemplateName, pParentWnd), m_pSettings(NULL)
{
}

CSkinDialog::CSkinDialog(UINT nIDTemplate, CWnd* pParentWnd)
	: CDialog(nIDTemplate, pParentWnd), m_pSettings(NULL)
{
}

IMPLEMENT_DYNAMIC(CSkinDialog, CDialog)

BEGIN_MESSAGE_MAP(CSkinDialog, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	//
	ON_CONTROL_RANGE(BN_CLICKED, IDC_SKIN_BASE, IDC_SKIN_BASE+_wbp_count-1, OnSysBtnClicked)
END_MESSAGE_MAP()

// 

BOOL CSkinDialog::OnInitDialog()
{
	BOOL bRet = CDialog::OnInitDialog();

	// Binding skin info
	BOOL bSuccess = SkinManager::Instance().GetCurrentSkin()->BindSkinInfo(this);
	if (!bSuccess || !m_pSettings)
	{
		AfxMessageBox(IDS_BINDINGSKINERROR);
		return bRet;
	}

	// Apply window size
	MoveWindow(0, 0, m_pSettings->Size.cx, m_pSettings->Size.cy, FALSE);

	CRect rcWindow;
	GetWindowRect(rcWindow);

	// Pre-calculate caption area
	m_rcCaption = rcWindow;
	if (m_pSettings->CaptionSize.cx != -1)
		m_rcCaption.right = m_rcCaption.left + m_pSettings->CaptionSize.cx;
	if (m_pSettings->CaptionSize.cy != -1)
		m_rcCaption.bottom = m_rcCaption.top + m_pSettings->CaptionSize.cy;

	// Apply round window region
	const int nRoundSize = 14;

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

	SetWindowRgn((HRGN)rgnWindow.Detach(), FALSE);

	// Apply inter button
	CRect rcTmp;
	CSkinButton* pButton = NULL;
	for (int i = _wbp_count - 1; i >= 0; i--)
	{
		rcTmp = m_pSettings->Buttons[i][BSNormal];
		if (rcTmp.IsRectEmpty())
			continue;

		rcTmp.MoveToXY(m_pSettings->ButtonsPos[i]);
		pButton = new CSkinButton();
		pButton->Create(_T(""), WS_CHILD | WS_VISIBLE,
					rcTmp, this, IDC_SKIN_BASE + i);
		pButton->ApplySkin();
		m_arrButtons.Add(pButton);
	}

	// Apply new style
	ModifyStyle(WS_CAPTION | WS_THICKFRAME, WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	ModifyStyleEx(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE, 0L);

	SetWindowPos(NULL, 0, 0, 0, 0,
		SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

	return bRet;
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

ISkinComponent* CSkinDialog::GetSkinParent()
{
	return dynamic_cast<ISkinComponent*>(GetParent());
}

// CSkinDialog 消息处理程序


BOOL CSkinDialog::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

void CSkinDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CSkinPtr spSkin = SkinManager::Instance().GetCurrentSkin();
	if (!m_pSettings || !spSkin)
		return;

	CMemDC memDC(&dc);

	CRect rcClient;
	GetClientRect(rcClient);

	FrameState fs = IsWindowEnabled() ?
		(::GetActiveWindow() == m_hWnd ? FSActive : FSInactive)
		: FSDisabled;

	// Draw background
	memDC.FillSolidRect(rcClient, m_pSettings->BGColor);

	// Draw border
	CRect rcTmp = m_pSettings->Frames[FPLeft][fs];
	spSkin->DrawRect(rcTmp, &memDC, rcClient.left, rcClient.top, rcTmp.Width(),
			rcClient.Height());

	rcTmp = m_pSettings->Frames[FPRight][fs];
	spSkin->DrawRect(rcTmp, &memDC, rcClient.right - rcTmp.Width(), rcClient.top,
			rcTmp.Width(), rcClient.Height());

	rcTmp = m_pSettings->Frames[FPBottom][fs];
	spSkin->DrawRect(rcTmp, &memDC, rcClient.left, rcClient.bottom - rcTmp.Height(),
			rcClient.Width(), rcTmp.Height());

	rcTmp = m_pSettings->Frames[FPTop][fs];
	spSkin->DrawRect(rcTmp, &memDC, rcClient.left, rcClient.top, rcClient.Width(),
				rcTmp.Height());

	// Draw corner
	rcTmp = m_pSettings->Frames[FPTopLeft][fs];
	spSkin->DrawRect(rcTmp, &memDC, rcClient.left, rcClient.top);

	rcTmp = m_pSettings->Frames[FPTopRight][fs];
	spSkin->DrawRect(rcTmp, &memDC, rcClient.right - rcTmp.Width(), rcClient.top);

	rcTmp = m_pSettings->Frames[FPBottomLeft][fs];
	spSkin->DrawRect(rcTmp, &memDC, rcClient.left, rcClient.bottom - rcTmp.Height());

	rcTmp = m_pSettings->Frames[FPBottomRight][fs];
	spSkin->DrawRect(rcTmp, &memDC, rcClient.right - rcTmp.Width(), 
				rcClient.bottom - rcTmp.Height());
}

UINT CSkinDialog::OnNcHitTest(CPoint point)
{
	POINT pt = point;
	ScreenToClient(&pt);
	if (m_pSettings)
	{
		CRect rcTmp = m_pSettings->IconRect;
		rcTmp.MoveToXY(m_pSettings->IconPos);
		if (rcTmp.PtInRect(pt))
			return HTSYSMENU;

		if (m_rcCaption.PtInRect(pt))
			return HTCAPTION;
	}

	return CDialog::OnNcHitTest(point);
}

void CSkinDialog::OnSysBtnClicked(UINT nCmdID)
{
	WPARAM wp;
	WPARAM lp = NULL;
	switch(static_cast<WindowButtonPart>(nCmdID-IDC_SKIN_BASE))
	{
	case WBPHelpButton:
		wp = SC_CONTEXTHELP;
		break;
	case WBPMinButton:
		wp = SC_MINIMIZE;
		break;
	case WBPRestoreButton:
		wp = SC_RESTORE;
		break;
	case WBPMaxButton:
		wp = SC_MAXIMIZE;
		break;
	case WBPCloseButton:
		wp = SC_CLOSE;
		break;
	default:
		ATLTRACE(_T("*** SkinDebug ***: Unexcepted window button part used.\n"));
		return;
	}

	SendMessage(WM_SYSCOMMAND, wp, lp);
}