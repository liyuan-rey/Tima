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

private:
	void Init() throw();

protected:
	CButtonSettings* m_pSettings;
	BOOL m_bHover;						// indicates if mouse is over the button
	BOOL m_bTracking;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinButton)
protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
	// Generated message map functions
protected:
	//{{AFX_MSG(CHoverButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam) ;
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
