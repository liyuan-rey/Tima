//

#pragma once

#include <Shlwapi.h>
#include <atlpath.h>

#include "skin.h"

class CSkinManager
{
	friend class CSkinManager* SkinManager();

public:
	virtual ~CSkinManager(void);

protected:
	CSkin m_skin;
	CPath m_pthSkinRoot;

private:
	CSkinManager(void);
	static CSkinManager s_instance;

public:
	static const TCHAR defaultSkinRootName[];
	static const TCHAR defaultSkinFolder[];

	BOOL SetSkinRoot(LPCTSTR szPath);
	CPath GetSkinRoot();
	BOOL GetAllSkinFolder(CStringArray& skinFolders);
	BOOL GetSkinInfo(LPCTSTR szSkinFolder, CSkinInfo& setting);
	int LoadSkin(LPCTSTR szSkinFolder = defaultSkinFolder);

	CSkin* GetCurrentSkin();
};

AFX_INLINE CSkinManager* SkinManager() { 
	return &CSkinManager::s_instance; 
}
