//

#pragma once

#include <Shlwapi.h>
#include <atlpath.h>

#include <Singleton.h>
#include <SmartPtr.h>

#include "skin.h"

typedef Loki::SmartPtr<CSkin> CSkinPtr;

class CSkinManager
{
	friend struct Loki::CreateUsingNew;

public:
	static const TCHAR defaultSkinRoot[]; // SkinRoot is a path to the folder which all skin folders placed in
	static const TCHAR defaultSkinName[]; // SkinName is the name of the folder which skin's files placed in

	BOOL SetSkinRoot(const CPath& path);
	CPath GetSkinRoot();

	BOOL GetAllSkins(CStringArray& arrSkinNames);
	BOOL GetSkinInfo(LPCTSTR szSkinName, CSkinInfo& si); // Skin name is the name of the folder which the skin in

	int LoadSkin(LPCTSTR szSkinName = defaultSkinName);

	AFX_INLINE CSkinPtr GetCurrentSkin() {
		return m_spCurrentSkin;
	}

protected:
	CSkinPtr m_spCurrentSkin;
	CPath m_pthSkinRoot;

private:
	CSkinManager(void);
	virtual ~CSkinManager(void);

	CSkinManager(const CSkinManager&);
	CSkinManager& operator=(const CSkinManager&);
	CSkinManager* operator&(CSkinManager&);
};

typedef Loki::SingletonHolder<CSkinManager> SkinManager;
