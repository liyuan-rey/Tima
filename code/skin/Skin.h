//

#pragma once

#include <Shlwapi.h>
#include <atlpath.h>
#include <afxtempl.h>
#include <afxcoll.h>

#include "ximage.h"

#include "SkinSettings.h"

class CSkinManager;
class ISkinComponent;
class ESkinControl;

class CSkin
{
	friend class CSkinManager;

public:
	virtual ~CSkin();

protected:
	CSkin();
	CSkinSettings m_settings;
	CPath m_pthSkin;
	CTypedPtrMap<CMapPtrToPtr, ISkinComponent*, CSettings*> m_mapComponents;
	CxImage m_imgSkin;

public:
	static const TCHAR defaultSkinConfigFile[];

	// > 0 Ok but with some error
	// = 0 Success
	// < 0 Failed
	int Load(LPCTSTR szPath);
	int Save();

	CPath GetPath();

	BOOL BindSkinInfo(ISkinComponent* pComp);
	CSettings* FindSetting(ISkinComponent* pComp);
	CxImage* GetSkinImage();
};
