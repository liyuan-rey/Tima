#pragma once

#include "..\include\PPHtmlDrawer\PPHtmlDrawer.h"

// CHtmlLite
#define HS_LEFT			0x00000000L
//#define HS_RIGHT		0x00000001L // not for now
#define HS_CENTER		0x00000002L
#define HS_BORDER		0x00000010L
//#define HS_SUNKEN		0x00000020L // not for now

class CHtmlLite : public CWnd
{
	DECLARE_DYNAMIC(CHtmlLite)

	static const TCHAR* WindowClassName;
	static BOOL RegisterWndClass(void) throw();

public:
	CHtmlLite();
	virtual ~CHtmlLite();

protected:
	CPPHtmlDrawer m_drawer;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};

//----------------------------------------------------------------------------
struct HTMLLITE_TEMPLMAP_ENTRY {
	UINT id;
	TCHAR* templ;
};

#define DECLARE_HTMLTEMPL_MAP() \
protected: \
	CString GetHtmlTempl(UINT idRes) throw();

#define BEGIN_HTMLTEMPL_MAP(theClass) \
	CString theClass::GetHtmlTempl(UINT idRes) \
	{ \
		ATLASSERT(idRes > 0); \
		\
		static const HTMLLITE_TEMPLMAP_ENTRY _htmlTemplMap[] = { 

#define TEMPL_ITEM(id, templ) \
			{ id, _T(templ) },

#define END_HTMLTEMPL_MAP() \
			{NULL, NULL} \
		}; \
		\
		int index = 0; \
		CString strRet; \
		while (_htmlTemplMap[index].id) \
		{ \
			if (_htmlTemplMap[index].id == idRes) { \
				strRet = _htmlTemplMap[index].templ; \
				break; \
			} \
		\
		index++; \
		} \
		\
		return strRet; \
	}
