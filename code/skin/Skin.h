//

#pragma once

#include <Shlwapi.h>
#include <atlpath.h>

#include "SkinSettings.h"

class CSkinManager;
class ISkinComponent;

class CSkin
{
	friend class CSkinManager;

public:
	virtual ~CSkin();

protected:
	CSkin();
	CSkinSettings m_settings;
	CPath m_pthSkin;

public:
	static const TCHAR defaultSkinConfigFile[];
	static const TCHAR defaultSkinSection[];

	// > 0 Ok but with some error
	// = 0 Success
	// < 0 Failed
	int Load(LPCTSTR szPath);
	BOOL Save();

	CPath GetPath();

	BOOL BindSkinInfo(LPCTSTR szType, UINT nResID, ISkinComponent* pComp);

};
