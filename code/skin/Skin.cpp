//

#include "StdAfx.h"
#include ".\skin.h"
#include "SkinManager.h"
#include "SkinSettings.h"
#include "SkinComponent.h"

#include "..\include\SettingsStorage\MSettingsStorageIniFile.h"
using Mortimer::CSettingsStorageIniFile;

const TCHAR CSkin::defaultSkinConfigFile[] = _T("skincfg.ini");
const TCHAR CSkin::defaultSkinSection[] = _T("");

CSkin::CSkin()
{
}

CSkin::~CSkin()
{
}


int CSkin::Load(LPCTSTR szPath)
{
	CPath pthTmp = szPath;
	pthTmp.AddBackslash();
	pthTmp += defaultSkinConfigFile;

	if (pthTmp.FileExists())
	{
		m_pthSkin = pthTmp;

		CSettingsStorageIniFile stg;
		stg.SetIniFileName(m_pthSkin, defaultSkinSection);

		return m_settings.Load(stg) ? 0 : 1;
	}

	return -1;
}

BOOL CSkin::Save()
{
	return FALSE;
}

CPath CSkin::GetPath()
{
	return m_pthSkin;
}

BOOL CSkin::BindSkinInfo(LPCTSTR szType, UINT nResID, ISkinComponent* pComp)
{
	// TODO: Add your specialized code here.
	// NOTE: Requires a correct return value to compile.

	return FALSE;
}

