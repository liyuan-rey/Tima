// SkinButton.cpp : 实现文件
//

#include "stdafx.h"
#include "..\Resource.h"

#include "SkinManager.h"
#include "SkinButton.h"
#include "SkinSettings.h"

#include "..\include\memdc\memdc.h"
#include ".\skinbutton.h"

extern AFX_INLINE CSkinManager* SkinManager();

// CSkinButton

CSkinButton::CSkinButton() : m_pSettings(NULL), m_bHover(FALSE),
				m_bTracking(FALSE), m_nStyle(BS_PUSHBUTTON), m_nChecked(BST_UNCHECKED)
{
}

CSkinButton::~CSkinButton()
{
}

IMPLEMENT_DYNAMIC(CSkinButton, CButton)

BEGIN_MESSAGE_MAP(CSkinButton, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_MESSAGE(BM_SETCHECK , OnBMSetCheck)
	ON_MESSAGE(BM_GETCHECK , OnBMGetCheck)
	ON_WM_GETDLGCODE()
END_MESSAGE_MAP()


void CSkinButton::PreSubclassWindow()
{
	CButton::PreSubclassWindow();

	m_nStyle = GetButtonStyle();
	if ((m_nStyle & BS_AUTOCHECKBOX) == BS_AUTOCHECKBOX)
		m_nStyle = BS_CHECKBOX;
	else if ((m_nStyle & BS_AUTORADIOBUTTON) == BS_AUTORADIOBUTTON)
		m_nStyle = BS_RADIOBUTTON;
	else
		m_nStyle = BS_PUSHBUTTON;

	m_nChecked = GetCheck();
	// Apply owner draw style
	ModifyStyle(0, BS_OWNERDRAW);
}

void CSkinButton::ApplySkin()
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
		rcTmp.Width(), rcTmp.Height(), TRUE);
}

BOOL CSkinButton::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}

void CSkinButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your code to draw the specified item
	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

	CSkin* pSkin = SkinManager()->GetCurrentSkin();
	if (!m_pSettings || !pSkin)
		return;

	ButtonState bs = lpDrawItemStruct->itemState & ODS_DISABLED ? BSDisabled
						: lpDrawItemStruct->itemState & ODS_SELECTED ? BSPushed
						: m_bHover ? BSHot : BSNormal;

	if ((BSNormal == bs) && (GetStyle() & WS_TABSTOP)
		&& (lpDrawItemStruct->itemState & ODS_FOCUS))
		bs = BSHot;

	if (BS_PUSHBUTTON != m_nStyle)
		if (BST_UNCHECKED != m_nChecked)
			bs = BSPushed;

	CMemDC memDC(CDC::FromHandle(lpDrawItemStruct->hDC));

	// Draw background
	CRect rcTmp = m_pSettings->States[bs];
	pSkin->DrawRect(rcTmp, &memDC, 0, 0);

	// Draw icon
	rcTmp = m_pSettings->IconRect;
	int nOffset = BSPushed == bs ? 1 : 0;
	pSkin->DrawRect(rcTmp, &memDC,
			m_pSettings->IconPos.x + nOffset, m_pSettings->IconPos.y + nOffset);

	// Draw text
	rcTmp = m_pSettings->TextRect;
	if (!rcTmp.IsRectEmpty())
	{
		CString strText;
		GetWindowText(strText);
		if (!strText.IsEmpty())
		{
			if (BSPushed == bs)
				rcTmp.OffsetRect(1, 1);

			CFont* pFont = GetParent()->GetFont();
			CFont* pOldFont = memDC.SelectObject(pFont);

			memDC.SetBkMode(TRANSPARENT);
			memDC.DrawText(strText, rcTmp,
				DT_LEFT | DT_SINGLELINE | DT_VCENTER| DT_EXTERNALLEADING 
				| DT_PATH_ELLIPSIS | DT_WORDBREAK);

			memDC.SelectObject(pOldFont);
		}
	}
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
	m_bHover = FALSE;
	Invalidate();

	return 0;
}

void CSkinButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (BS_PUSHBUTTON != m_nStyle)
	{ //track mouse for radio & check buttons
		if (::GetCapture() == m_hWnd)
		{
			POINT p2 = point;
			::ClientToScreen(m_hWnd, &p2);
			HWND mouse_wnd = ::WindowFromPoint(p2);
			if (mouse_wnd == m_hWnd){ // mouse is in button
				if (m_nStyle==BS_CHECKBOX)
					SetCheck(m_nChecked ? BST_UNCHECKED : BST_CHECKED);
				else if (m_nStyle==BS_RADIOBUTTON)
					SetCheck(BST_CHECKED);
			}
		}
	}

	CButton::OnLButtonUp(nFlags, point);
}

void CSkinButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (BS_PUSHBUTTON != m_nStyle && nChar == _T(' '))
	{// needed stuff for check & radio buttons
		if (m_nStyle == BS_CHECKBOX)
			SetCheck(m_nChecked ? BST_CHECKED : BST_CHECKED);
		else if (m_nStyle == BS_RADIOBUTTON)
			SetCheck(BST_CHECKED);
	}

	CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}

LRESULT CSkinButton::OnBMSetCheck(WPARAM wparam, LPARAM)
{
	m_nChecked = (int)wparam;

	switch (m_nStyle)
	{
	case BS_RADIOBUTTON:
		if (m_nChecked) { //uncheck the other radio buttons (in the same group)
			HWND hthis, hwnd2, hpwnd;
			hpwnd = GetParent()->GetSafeHwnd();	//get button parent handle
			hwnd2 = hthis = GetSafeHwnd();			//get this button handle
			if (hthis && hpwnd){				//consistency check
				for( ; ; ){	//scan the buttons within the group
					hwnd2 = ::GetNextDlgGroupItem(hpwnd, hwnd2, 0);
					//until we reach again this button
					if ((hwnd2 == hthis)||(hwnd2 == NULL))
						break;

					//post the uncheck message
					if (::SendMessage(hwnd2, WM_GETDLGCODE, 0, 0L) & DLGC_RADIOBUTTON)
						::SendMessage(hwnd2, BM_SETCHECK, BST_UNCHECKED, 0L);
				}
			}
		}
		break;
	case BS_PUSHBUTTON:
		m_nChecked = false;
		ASSERT(false); // Must be a Check or Radio button to use this function
	}

	Invalidate();
	return 0;
}

LRESULT CSkinButton::OnBMGetCheck(WPARAM wparam, LPARAM)
{
	return m_nChecked; 
}

UINT CSkinButton::OnGetDlgCode()
{
	UINT nRet = -1;
	switch(m_nStyle)
	{
	case BS_PUSHBUTTON:
		nRet = DLGC_BUTTON;
		break;
	case BS_RADIOBUTTON:
		nRet = DLGC_RADIOBUTTON;
		break;
	case BS_CHECKBOX:
		ATLASSERT(0); // need check in msdn
		//return DLGC_BUTTON;
		break;
	default:
		ATLASSERT(0); // should never being here
	}

	return nRet;
}
