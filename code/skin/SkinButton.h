//

#pragma once

#include "SkinComponent.h"
#include "SkinTypes.h"

class CButtonSettings;

// CSkinButton

class CSkinButton : public CButton, public ISkinComponent
{
	DECLARE_DYNAMIC(CSkinButton)

public:
	CSkinButton();
	virtual ~CSkinButton();

	// Implement of ISkinComponent
public:
	virtual UINT GetID();
	virtual ESkinControl GetType();
	virtual BOOL SetSkinInfo(CSettings* info);
	virtual ISkinComponent* GetSkinParent();

	void ApplySkin() throw();

protected:
	CButtonSettings* m_pSettings;
	BOOL m_bHover; // indicates if mouse is over the button
	BOOL m_bTracking;
	UINT m_nStyle; // Remember button type when subclass
	int m_nChecked;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
	// Generated message map functions
protected:
	//{{AFX_MSG(CSkinButton)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam) ;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnBMSetCheck(WPARAM, LPARAM);
	afx_msg LRESULT OnBMGetCheck(WPARAM, LPARAM);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg UINT OnGetDlgCode();
};
