//

#include "StdAfx.h"
#include ".\skinmanager.h"
#include "Skin.h"

#include "..\include\SettingsStorage\MSettingsStorageIniFile.h"
using Mortimer::CSettingsStorageIniFile;

CSkinManager CSkinManager::s_instance;

const TCHAR CSkinManager::defaultSkinRootName[] = _T("skin");
const TCHAR CSkinManager::defaultSkinFolder[] = _T("default");

CSkinManager::CSkinManager(void)
{
	TCHAR szPath[MAX_PATH + 1] = _T("");
	if (::GetModuleFileName((HMODULE)::GetCurrentProcess(), szPath, MAX_PATH))
	{
		CPath pthTmp = szPath;

		pthTmp.RemoveFileSpec();
		pthTmp.AddBackslash();
		pthTmp += defaultSkinRootName;
		pthTmp.AddBackslash();

		if (pthTmp.FileExists())
			m_pthSkinRoot = pthTmp;
	}
}

CSkinManager::~CSkinManager(void)
{
}

BOOL CSkinManager::SetSkinRoot(LPCTSTR szPath)
{
	CPath pthTmp = szPath;
	if (pthTmp.IsDirectory() && pthTmp.FileExists())
	{
		m_pthSkinRoot = pthTmp;
		return TRUE;
	}

	return FALSE;
}

CPath CSkinManager::GetSkinRoot()
{
	return m_pthSkinRoot;
}

BOOL CSkinManager::GetAllSkinFolder(CStringArray& skinFolders)
{
	return FALSE;
}

BOOL CSkinManager::GetSkinInfo(LPCTSTR szSkinFolder, CSkinInfo& setting)
{
	if (m_pthSkinRoot.FileExists())
	{
		m_pthSkinRoot += szSkinFolder;
		m_pthSkinRoot.AddBackslash();
		m_pthSkinRoot += (LPCTSTR)CSkin::defaultSkinConfigFile;

		if (m_pthSkinRoot.FileExists())
		{
			CSettingsStorageIniFile stg;
			stg.SetIniFileName(m_pthSkinRoot, _T("SkinInfo"));
			return setting.Load(stg);
		}
	}

	return FALSE;
}

int CSkinManager::LoadSkin(LPCTSTR szSkinFolder)
{
	return m_skin.Load(m_pthSkinRoot += szSkinFolder);
}

CSkin* CSkinManager::GetCurrentSkin()
{
	return &m_skin;
}
