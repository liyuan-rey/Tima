//

#include "StdAfx.h"
#include ".\skinmanager.h"
#include "Skin.h"

#include "..\include\SettingsStorage\MSettingsStorageIniFile.h"
using Mortimer::CSettingsStorageIniFile;

const TCHAR CSkinManager::defaultSkinRoot[] = _T("skin");
const TCHAR CSkinManager::defaultSkinName[] = _T("default");

CSkinManager::CSkinManager(void)
{
	TCHAR szPath[MAX_PATH + 1] = _T("");
	if (::GetModuleFileName(NULL, szPath, MAX_PATH))
	{
		CPath pthTmp = szPath;

		pthTmp.RemoveFileSpec();
		pthTmp.AddBackslash();
		pthTmp += defaultSkinRoot;
		pthTmp.AddBackslash();

		SetSkinRoot(pthTmp);
	}
}

CSkinManager::~CSkinManager(void)
{
}

BOOL CSkinManager::SetSkinRoot(const CPath& path)
{
	if (path.IsDirectory() && path.FileExists())
	{
		m_pthSkinRoot = path;
		return TRUE;
	}
	else
	{
		ATLTRACE(_T("#Warning: SetSkinRoot failed, maybe specified path not exist.\n"));
		return FALSE;
	}
}

CPath CSkinManager::GetSkinRoot()
{
	return m_pthSkinRoot;
}

BOOL CSkinManager::GetAllSkins(CStringArray& arrSkinNames)
{
	return FALSE;
}

BOOL CSkinManager::GetSkinInfo(LPCTSTR szSkinName, CSkinInfo& si)
{
	if (m_pthSkinRoot.FileExists())
	{
		CPath pthSkinCfgFile = m_pthSkinRoot;
		pthSkinCfgFile += szSkinName;
		pthSkinCfgFile.AddBackslash();
		pthSkinCfgFile += CSkin::defaultSkinConfigFile;

		if (pthSkinCfgFile.FileExists())
		{
			CSettingsStorageIniFile stg;
			stg.SetIniFileName(pthSkinCfgFile, _T("SkinInfo"));

			return si.Load(stg);
		}
	}

	return FALSE;
}

int CSkinManager::LoadSkin(LPCTSTR szSkinName/* = defaultSkinName*/)
{
	CPath pthSkin = m_pthSkinRoot;
	pthSkin += szSkinName;

	if (pthSkin.FileExists())
	{
		if (m_spCurrentSkin != NULL)
		{
			ATLTRACE(_T("#Warning: We are not support dynamic change skin for now."));
			return FALSE; // 
		}

		m_spCurrentSkin = new CSkin();
		return m_spCurrentSkin->Load(pthSkin);
	}

	return FALSE;
}
