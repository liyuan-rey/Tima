//

#pragma once

#include "..\include\settingsstorage\msettingsstorage.h"
using Mortimer::CSettings;
using Mortimer::CColorRef;

#include ".\skintypes.h"

static const COLORREF	DEFAULT_COLORKEY		= RGB(255, 0, 255);
static const TCHAR*		DEFAULT_FONTNAME		= _T("MS Shell Dlg");
static const UINT		DEFAULT_FONTSIZE		= 8;
static const COLORREF	DEFAULT_BGCOLOR			= RGB(255, 255, 255);
static const SIZE		DEFAULT_NULLSIZE		= {0, 0};
static const RECT		DEFAULT_NULLRECT		= {0, 0, 0, 0};
static const CString	DEFAULT_EMPTYSTR		= _T("<empty>");

class CSkinInfo : public CSettings
{
public:
	DWORD Version;
	CString Name;
	CString Maker;
	CString Time;
	CString SkinImage;
	CString PreviewImage;
	CString Remark;

	BEGIN_SETTING_MAP(CSkinInfo)
		SETTING_ITEM_REQUIRE(Version)
		SETTING_ITEM_DEFAULT(Name, DEFAULT_EMPTYSTR)
		SETTING_ITEM_DEFAULT(Maker, DEFAULT_EMPTYSTR)
		SETTING_ITEM_DEFAULT(Time, DEFAULT_EMPTYSTR)
		SETTING_ITEM_DEFAULT(SkinImage, DEFAULT_EMPTYSTR)
		SETTING_ITEM_DEFAULT(PreviewImage, DEFAULT_EMPTYSTR)
		SETTING_ITEM_DEFAULT(Remark, DEFAULT_EMPTYSTR)
	END_SETTING_MAP()
};

class CGenericSettings : public CSettings
{
public:
	CColorRef ColorKey;
	CString FontName;
	UINT FontSize;

	BEGIN_SETTING_MAP(CGenericSettings)
		SETTING_ITEM_DEFAULT(ColorKey, DEFAULT_COLORKEY)
		SETTING_ITEM_DEFAULT(FontName, DEFAULT_FONTNAME)
		SETTING_ITEM_DEFAULT(FontSize, DEFAULT_FONTSIZE)
	END_SETTING_MAP()
};

class CWindowSettings : public CSettings
{
public:
	SIZE Size;
	CColorRef BGColor;
	RECT Frames[_fp_count][_fs_count];
	RECT Buttons[_wbp_count][_bs_count];

	BEGIN_SETTING_MAP(CWindowSettings)
		SETTING_ITEM_DEFAULT(Size, DEFAULT_NULLSIZE)
		SETTING_ITEM_DEFAULT(BGColor, DEFAULT_BGCOLOR)
		//
		SETTING_ITEM_DEFAULT(Frames[FPTopLeft][FSActive], DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(Frames[FPTop][FSActive], DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(Frames[FPTopRight][FSActive], DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(Frames[FPRight][FSActive], DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(Frames[FPBottomRight][FSActive], DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(Frames[FPBottom][FSActive], DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(Frames[FPBottomLeft][FSActive], DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(Frames[FPLeft][FSActive], DEFAULT_NULLRECT)

		SETTING_ITEM_DEFAULT(Frames[FPTopLeft][FSInactive], Frames[FPTopLeft][FSActive])
		SETTING_ITEM_DEFAULT(Frames[FPTop][FSInactive], Frames[FPTop][FSActive])
		SETTING_ITEM_DEFAULT(Frames[FPTopRight][FSInactive], Frames[FPTopRight][FSActive])
		SETTING_ITEM_DEFAULT(Frames[FPRight][FSInactive], Frames[FPRight][FSActive])
		SETTING_ITEM_DEFAULT(Frames[FPBottomRight][FSInactive], Frames[FPBottomRight][FSActive])
		SETTING_ITEM_DEFAULT(Frames[FPBottom][FSInactive], Frames[FPBottom][FSActive])
		SETTING_ITEM_DEFAULT(Frames[FPBottomLeft][FSInactive], Frames[FPBottomLeft][FSActive])
		SETTING_ITEM_DEFAULT(Frames[FPLeft][FSInactive], Frames[FPLeft][FSActive])

		SETTING_ITEM_DEFAULT(Frames[FPTopLeft][FSDisabled], Frames[FPTopLeft][FSInactive])
		SETTING_ITEM_DEFAULT(Frames[FPTop][FSDisabled], Frames[FPTop][FSInactive])
		SETTING_ITEM_DEFAULT(Frames[FPTopRight][FSDisabled], Frames[FPTopRight][FSInactive])
		SETTING_ITEM_DEFAULT(Frames[FPRight][FSDisabled], Frames[FPRight][FSInactive])
		SETTING_ITEM_DEFAULT(Frames[FPBottomRight][FSDisabled], Frames[FPBottomRight][FSInactive])
		SETTING_ITEM_DEFAULT(Frames[FPBottom][FSDisabled], Frames[FPBottom][FSInactive])
		SETTING_ITEM_DEFAULT(Frames[FPBottomLeft][FSDisabled], Frames[FPBottomLeft][FSInactive])
		SETTING_ITEM_DEFAULT(Frames[FPLeft][FSDisabled], Frames[FPLeft][FSInactive])
		//
		SETTING_ITEM_DEFAULT(Buttons[WBPSysButton][BSNormal], DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(Buttons[WBPHelpButton][BSNormal], DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(Buttons[WBPMinButton][BSNormal], DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(Buttons[WBPRestoreButton][BSNormal], DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(Buttons[WBPMaxButton][BSNormal], DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(Buttons[WBPCloseButton][BSNormal], DEFAULT_NULLRECT)

		SETTING_ITEM_DEFAULT(Buttons[WBPSysButton][BSHot], Buttons[WBPSysButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPHelpButton][BSHot], Buttons[WBPHelpButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPMinButton][BSHot], Buttons[WBPMinButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPRestoreButton][BSHot], Buttons[WBPRestoreButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPMaxButton][BSHot], Buttons[WBPMaxButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPCloseButton][BSHot], Buttons[WBPCloseButton][BSNormal])

		SETTING_ITEM_DEFAULT(Buttons[WBPSysButton][BSPushed], Buttons[WBPSysButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPHelpButton][BSPushed], Buttons[WBPHelpButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPMinButton][BSPushed], Buttons[WBPMinButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPRestoreButton][BSPushed], Buttons[WBPRestoreButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPMaxButton][BSPushed], Buttons[WBPMaxButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPCloseButton][BSPushed], Buttons[WBPCloseButton][BSNormal])

		SETTING_ITEM_DEFAULT(Buttons[WBPSysButton][BSDisabled], Buttons[WBPSysButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPHelpButton][BSDisabled], Buttons[WBPHelpButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPMinButton][BSDisabled], Buttons[WBPMinButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPRestoreButton][BSDisabled], Buttons[WBPRestoreButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPMaxButton][BSDisabled], Buttons[WBPMaxButton][BSNormal])
		SETTING_ITEM_DEFAULT(Buttons[WBPCloseButton][BSDisabled], Buttons[WBPCloseButton][BSNormal])
	END_SETTING_MAP()
};

class CButtonSettings : public CSettings
{
public:
	RECT TextRect;
	RECT States[_bs_count];

	BEGIN_SETTING_MAP(CButtonSettings)
		SETTING_ITEM_DEFAULT(TextRect, DEFAULT_NULLRECT)

		SETTING_ITEM_DEFAULT(States[BSNormal], DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(States[BSHot], States[BSNormal])
		SETTING_ITEM_DEFAULT(States[BSPushed], States[BSNormal])
		SETTING_ITEM_DEFAULT(States[BSDisabled], States[BSNormal])
	END_SETTING_MAP()
};

class CPictureSettings : public CSettings
{
public:
	RECT Picture;

	BEGIN_SETTING_MAP(CPictureSettings)
		SETTING_ITEM_REQUIRE(Picture)
	END_SETTING_MAP()
};

class CSkinSettings : public CSettings
{
public:
	CSkinInfo SkinInfo;
	CGenericSettings Generic;
	CWindowSettings Window;
	CButtonSettings Button;
	CPictureSettings Picture;

	BEGIN_SETTING_MAP(CSkinSettings)
		SETTING_ITEM_SUBITEM(SkinInfo)
		SETTING_ITEM_SUBITEM(Generic)
		SETTING_ITEM_SUBITEM(Window)
		SETTING_ITEM_SUBITEM(Button)
		SETTING_ITEM_SUBITEM(Picture)
	END_SETTING_MAP()
};
