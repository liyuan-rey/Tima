//

#pragma once


class CPictureSettings;

// CSkinPicture

class CSkinPicture : public CWnd
{
	DECLARE_DYNAMIC(CSkinPicture)

public:

protected:
	CPictureSettings* m_settings;

	DECLARE_MESSAGE_MAP()
	//{{AFX_VIRTUAL(CSkinPicture)
	public:
	virtual void PreSubclassWindow();

	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

};


