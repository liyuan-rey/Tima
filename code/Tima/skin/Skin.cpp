//

#include "StdAfx.h"
#include "..\resource.h"
#include ".\skin.h"

#include "SkinTypes.h"
#include "SkinManager.h"
#include "SkinSettings.h"
#include "SkinComponent.h"
#include "SkinDialog.h"

#include "..\include\SettingsStorage\MSettingsStorageIniFile.h"
using Mortimer::CSettingsStorageIniFile;

const TCHAR CSkin::defaultSkinConfigFile[] = _T("skincfg.ini");

CSkin::CSkin()
{
}

CSkin::~CSkin()
{
	POSITION pos = m_mapComponents.GetStartPosition();
	ISkinComponent* pComp = NULL;
	CSettings* pSettings = NULL;
	while (NULL != pos)
	{
		m_mapComponents.GetNextAssoc(pos, pComp, pSettings);
		delete pSettings;
	}

	m_mapComponents.RemoveAll();
}


int CSkin::Load(LPCTSTR szPath)
{
	if (!m_pthSkin.m_strPath.IsEmpty())
		return -1; // Not support dynamic reload skin currently

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
			pSettings = new CButtonSettings(&(m_settings.Button));

			UINT id = pComp->GetID();
			strSection.Format(_T("%s.%s.%d"), CSkinSettings::defaultSectionName,
				CButtonSettings::defaultSectionName, id);

			break;
		}
	case ESkinControl::Picture:
		{
			pSettings = new CPictureSettings();

			UINT id = pComp->GetID();
			strSection.Format(_T("%s.%s.%d"), CSkinSettings::defaultSectionName,
				CPictureSettings::defaultSectionName, id);

			break;
		}
	default:
		ATLTRACE(_T("*** SkinDebug ***: Unexcepted skin control used.\n"));
	}

	if (pSettings)
	{
		CSettingsStorageIniFile stg;
		stg.SetIniFileName(m_pthSkin, strSection);

		pSettings->Load(stg) ? NULL : AfxMessageBox(IDS_LOADSKININERROR);

		// crack for window inner button
		UINT id = pComp->GetID();
		if (id >= IDC_SKIN_BASE && id-IDC_SKIN_BASE < _wbp_count)
		{
			ISkinComponent* pSkinParent = pComp->GetSkinParent();
			if (pSkinParent)
			{
				CSettings* pParentSettings = NULL;
				bFound = m_mapComponents.Lookup(pSkinParent, pParentSettings);
				if (bFound && pParentSettings)
				{
					WindowButtonPart wbp = static_cast<WindowButtonPart>(id-IDC_SKIN_BASE);
					((CButtonSettings*)pSettings)->Position = 
						((CWindowSettings*)pParentSettings)->ButtonsPos[wbp];
					for (int i = 0; i < _bs_count; i++)
						((CButtonSettings*)pSettings)->States[i] = 
						((CWindowSettings*)pParentSettings)->Buttons[wbp][i];
				}
			}
		}

		m_mapComponents.SetAt(pComp, pSettings);
	}

	return pSettings;
}

BOOL CSkin::GetCustomSetting(GCSType type, UINT id, void* pData)
{
	if (!pData)
	{
		ATLASSERT(0);
		return FALSE;
	}

	BOOL bRet = FALSE;
	UINT count = 0;

	switch (type)
	{
	case GCSNothing:
		break;
	case GCSRect:
		count = (UINT)m_settings.CustomRects.GetCount();
		if (count > id)
		{
			const RECT& rcData = m_settings.CustomRects.GetAt(id);
			memcpy(pData, &rcData, sizeof(RECT));
			bRet = TRUE;
		}

		break;
	default:
		ATLASSERT(0); // maybe need support more types
	}

	return bRet;
}
