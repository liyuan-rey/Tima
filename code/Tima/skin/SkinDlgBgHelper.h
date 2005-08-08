#pragma once

class CSkinDlgBgHelper
{
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC) {
		CRect rcClip;
		pDC->GetClipBox(rcClip);
		FillRect(pDC->m_hDC, rcClip, GetBgBrush());

		return TRUE;
	}

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor, HBRUSH hbr) {

		switch (nCtlColor)
		{
		case CTLCOLOR_STATIC:
			{
				pDC->SetBkMode(TRANSPARENT);
				hbr = GetBgBrush();

				break;
			}
		case CTLCOLOR_MSGBOX:
		case CTLCOLOR_EDIT:
		case CTLCOLOR_LISTBOX:
		case CTLCOLOR_BTN:
		case CTLCOLOR_DLG:
		case CTLCOLOR_SCROLLBAR:
			break;
		default:
			ATLASSERT(0);
			break;
		}

		return hbr;
	}

private:
	HBRUSH GetBgBrush() {
		if (!m_bgBrush.GetSafeHandle())
		{
			COLORREF bgclr = SkinManager::Instance().GetCurrentSkin()->GetWindowBgColor();
			m_bgBrush.CreateSolidBrush(bgclr);
		}

		return m_bgBrush;
	}

	CBrush m_bgBrush;
};
