//

#include "StdAfx.h"
#include "..\resource.h"
#include ".\skin.h"

#include "SkinTypes.h"
#include "SkinManager.h"
#include "SkinSettings.h"
#include "SkinComponent.h"

#include "..\include\SettingsStorage\MSettingsStorageIniFile.h"
using Mortimer::CSettingsStorageIniFile;

const TCHAR CSkin::defaultSkinConfigFile[] = _T("skincfg.ini");

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
		stg.SetIniFileName(m_pthSkin, CSkinSettings::defaultSectionName);

		bool bRet1 = m_settings.Load(stg);

		CPath pthSkinFolder = m_pthSkin;
		pthSkinFolder.RemoveFileSpec();
		pthSkinFolder.AddBackslash();
		pthSkinFolder += m_settings.Info.SkinImage;

		bool bRet2 = m_imgSkin.Load(pthSkinFolder, CXIMAGE_FORMAT_PNG);
		if (bRet2)
		{
			m_imgSkin.SetTransIndex(0);

			COLORREF clrKey = m_settings.Generic.ColorKey;
			RGBQUAD rgbKey = {GetBValue(clrKey), GetGValue(clrKey),
								GetRValue(clrKey), 0};
			m_imgSkin.SetTransColor(rgbKey);
		}

		return bRet1 && bRet2 ? 0 : 1;
	}

	return -1;
}

int CSkin::Save()
{
	if (!m_pthSkin.m_strPath.IsEmpty())
	{
		CSettingsStorageIniFile stg;
		stg.SetIniFileName(m_pthSkin, CSkinSettings::defaultSectionName);

		return m_settings.Save(stg) ? 0 : 1;
	}

	return -1;
}

CPath CSkin::GetPath()
{
	return m_pthSkin;
}

BOOL CSkin::BindSkinInfo(ISkinComponent* pComp)
{
	ATLASSERT(pComp);

	CSettings* pSettings = FindSetting(pComp);
	if (pSettings)
	{
		pComp->SetSkinInfo(pSettings);
		return TRUE;
	}

	return FALSE;
}

CSettings* CSkin::FindSetting(ISkinComponent* pComp)
{
	ATLASSERT(pComp);

	CSettings* pSettings = NULL;
	BOOL bFound = m_mapComponents.Lookup(pComp, pSettings);

	if (bFound && pSettings) 
		return pSettings;

	// Not create yet?
	CString strSection;
	switch(pComp->GetType())
	{
	case ESkinControl::Window:
		{
			pSettings = new CWindowSettings(&(m_settings.Window));
			strSection.Format(_T("%s.%s.%d"), CSkinSettings::defaultSectionName,
				CWindowSettings::defaultSectionName, pComp->GetID());

			break;
		}
	case ESkinControl::Button:
		{
		}
	case ESkinControl::Picture:
		{
		}
	default:
		ATLTRACE(_T("*** SkinDebug ***: Unexcepted skin control used.\n"));
	}

	if (pSettings)
	{
		CSettingsStorageIniFile stg;
		stg.SetIniFileName(m_pthSkin, strSection);

		pSettings->Load(stg) ? NULL : AfxMessageBox(IDS_LOADSKININERROR);
	}

	return pSettings;
}

CxImage* CSkin::GetSkinImage()
{
	return m_imgSkin.IsValid() ? &m_imgSkin : NULL;
}
