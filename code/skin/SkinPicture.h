//

#pragma once

#include "SkinComponent.h"
#include "SkinTypes.h"

class CPictureSettings;

// CSkinPicture

class CSkinPicture : public CStatic, public ISkinComponent
{
	DECLARE_DYNAMIC(CSkinPicture)

public:
	CSkinPicture();
	virtual ~CSkinPicture();

	// Implement of ISkinComponent
public:
	virtual UINT GetID();
	virtual ESkinControl GetType();
	virtual BOOL SetSkinInfo(CSettings* info);
	virtual ISkinComponent* GetSkinParent();

	void ApplySkin() throw();

	//{{AFX_VIRTUAL(CSkinPicture)
	//}}AFX_VIRTUAL

protected:
	CPictureSettings* m_pSettings;

public:
	//{{AFX_MSG(CSkinPicture)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	virtual void PreSubclassWindow();
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


