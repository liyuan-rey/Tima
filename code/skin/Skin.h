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

//TODO 优化绘制代码
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

	AFX_INLINE BOOL DrawRect(const CRect& rcSrc, CDC* pDestDC, long xDest=0, long yDest=0, long cxDest = -1, long cyDest = -1) {
		if (m_imgSkin.IsValid() && !rcSrc.IsRectEmpty())
		{
			CxImage imgTmp;
			m_imgSkin.Crop(rcSrc, &imgTmp);
			return imgTmp.Draw2(pDestDC->m_hDC, xDest, yDest, cxDest, cyDest);
		}

		return FALSE;
	}

	enum GCSType {
		GCSNothing = 0,
		GCSRect
	};
	BOOL GetCustomSetting(GCSType nType, UINT id, void* pData);

	COLORREF GetWindowBgColor() {
		return m_settings.Window.BGColor;
	}
};
