//

#pragma once


class CSkinManager;
class CWindowSettings;

// CSkinDialog

class CSkinDialog : public CDialog
{
	DECLARE_DYNAMIC(CSkinDialog)

public:

protected:
	CWindowSettings* m_settings;

	DECLARE_MESSAGE_MAP()
	//{{AFX_VIRTUAL(CSkinDialog)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	virtual void PreInitDialog();

	virtual void PostNcDestroy();

	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

};


