// SkinButton.cpp : 实现文件
//

#include "stdafx.h"
#include "..\Resource.h"

#include "SkinManager.h"
#include "SkinButton.h"
#include "SkinSettings.h"

#include "..\include\memdc\memdc.h"

extern AFX_INLINE CSkinManager* SkinManager();

// CSkinButton

CSkinButton::CSkinButton() : m_pSettings(NULL), m_bHover(FALSE),
				m_bTracking(FALSE)
{
}

CSkinButton::~CSkinButton()
{
}

IMPLEMENT_DYNAMIC(CSkinButton, CButton)

BEGIN_MESSAGE_MAP(CSkinButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
END_MESSAGE_MAP()


void CSkinButton::PreSubclassWindow()
{
	CButton::PreSubclassWindow();

	// Apply owner draw style
	ModifyStyle(0, BS_OWNERDRAW);
}

void CSkinButton::Init()
{
	// Binding skin info
	BOOL bSuccess = SkinManager()->GetCurrentSkin()->BindSkinInfo(this);
	if (!bSuccess || !m_pSettings)
	{
		AfxMessageBox(IDS_BINDINGSKINERROR);
		return;
	}

	// Apply position and size
	CRect rcTmp = m_pSettings->States[BSNormal];
	MoveWindow(m_pSettings->Position.x, m_pSettings->Position.y, 
		rcTmp.Width(), rcTmp.Height(), FALSE);
}

void CSkinButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your code to draw the specified item
	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

	if (!m_pSettings)
		Init();

	CxImage* pImage = SkinManager()->GetCurrentSkin()->GetSkinImage();
	if (!pImage || !pImage->IsValid() || !m_pSettings)
		return;

	// Draw background
	ButtonState bs = lpDrawItemStruct->itemState & ODS_DISABLED ? BSDisabled
						: lpDrawItemStruct->itemState & ODS_SELECTED ? BSPushed
						: lpDrawItemStruct->itemState & ODS_FOCUS || m_bHover ? 
						BSHot : BSNormal;

	CMemDC memDC(CDC::FromHandle(lpDrawItemStruct->hDC));

	CxImage imgTmp;
	CRect rcTmp(m_pSettings->States[bs]);
	if (!rcTmp.IsRectEmpty())
	{
		pImage->Crop(rcTmp, &imgTmp);
		imgTmp.Draw2(memDC.m_hDC, 0, 0);
	}

	// Draw icon
	rcTmp = m_pSettings->IconRect;
	if (!rcTmp.IsRectEmpty())
	{
		pImage->Crop(rcTmp, &imgTmp);
		imgTmp.Draw2(memDC.m_hDC, m_pSettings->IconPos.x, m_pSettings->IconPos.y);
	}

	// Draw text
	rcTmp = m_pSettings->TextRect;
	if (!rcTmp.IsRectEmpty())
	{
		CString strText;
		GetWindowText(strText);
		if (!strText.IsEmpty())
		{
			memDC.DrawText(strText, rcTmp,
				DT_LEFT | DT_SINGLELINE | DT_VCENTER| DT_EXTERNALLEADING 
				| DT_PATH_ELLIPSIS | DT_WORDBREAK);
		}
	}

	// 
//	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

UINT CSkinButton::GetID()
{
	return GetDlgCtrlID();
}

ESkinControl CSkinButton::GetType()
{
	return ESkinControl::Button;
}

BOOL CSkinButton::SetSkinInfo(CSettings* pInfo)
{
	ATLASSERT(pInfo);
	m_pSettings = dynamic_cast<CButtonSettings*>(pInfo);
	ATLASSERT(m_pSettings);

	return (NULL != m_pSettings);
}

ISkinComponent* CSkinButton::GetSkinParent()
{
	return dynamic_cast<ISkinComponent*>(GetParent());
}

// CSkinButton 消息处理程序

void CSkinButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}

	CButton::OnMouseMove(nFlags, point);
}

LRESULT CSkinButton::OnMouseHover(WPARAM wparam, LPARAM lparam) 
{
	m_bHover=TRUE;
	Invalidate();

	return 0;
}

LRESULT CSkinButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bTracking = FALSE;
	m_bHover=FALSE;
	Invalidate();

	return 0;
}
