//

#pragma once


class CButtonSettings;

// CSkinButton

class CSkinButton : public CButton
{
	DECLARE_DYNAMIC(CSkinButton)

public:

protected:
	CButtonSettings* m_settings;

	DECLARE_MESSAGE_MAP()
	//{{AFX_VIRTUAL(CSkinButton)
	public:
	virtual void PreSubclassWindow();

	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

};


