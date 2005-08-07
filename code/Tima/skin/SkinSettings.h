//

#pragma once

#include "..\include\settingsstorage\msettingsstorage.h"
using Mortimer::CSettings;
using Mortimer::CColorRef;

#include "SettingUtil.h"
#include ".\skintypes.h"


class CSkinInfo : public CSettings
{
public:
	static const TCHAR defaultSectionName[];

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
	static const TCHAR defaultSectionName[];

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
	const CWindowSettings* const m_pModel;

public:
	static const TCHAR defaultSectionName[];

	CWindowSettings(const CWindowSettings* const pModel = NULL) : m_pModel(pModel) {
		InternalSaveLoad(true, NULL, false, true);
	};
	virtual ~CWindowSettings() {};

	SIZE Size;
	CColorRef BGColor;
	SIZE CaptionSize;
	POINT IconPos;
	RECT IconRect;

	RECT Frames[_fp_count][_fs_count];
	RECT Buttons[_wbp_count][_bs_count];
	POINT ButtonsPos[_wbp_count];

	BEGIN_SETTING_MAP_NOCTOR(CWindowSettings)
		SETTING_ITEM_DEFAULT(Size, DEFAULT_NULLSIZE)
		SETTING_ITEM_DEFAULT_EX(BGColor, DEFAULT_BGCOLOR, m_pModel)
		SETTING_ITEM_DEFAULT(CaptionSize, DEFAULT_NULLSIZE)
		SETTING_ITEM_DEFAULT_EX(IconPos, DEFAULT_NULLPOINT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(IconRect, DEFAULT_NULLRECT, m_pModel)
		//
		SETTING_ITEM_DEFAULT_EX(Frames[FPTopLeft][FSActive], DEFAULT_NULLRECT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(Frames[FPTop][FSActive], DEFAULT_NULLRECT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(Frames[FPTopRight][FSActive], DEFAULT_NULLRECT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(Frames[FPRight][FSActive], DEFAULT_NULLRECT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(Frames[FPBottomRight][FSActive], DEFAULT_NULLRECT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(Frames[FPBottom][FSActive], DEFAULT_NULLRECT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(Frames[FPBottomLeft][FSActive], DEFAULT_NULLRECT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(Frames[FPLeft][FSActive], DEFAULT_NULLRECT, m_pModel)

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
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPHelpButton][BSNormal], DEFAULT_NULLRECT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPMinButton][BSNormal], DEFAULT_NULLRECT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPRestoreButton][BSNormal], DEFAULT_NULLRECT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPMaxButton][BSNormal], DEFAULT_NULLRECT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPCloseButton][BSNormal], DEFAULT_NULLRECT, m_pModel)

		SETTING_ITEM_DEFAULT_EX(Buttons[WBPHelpButton][BSHot], Buttons[WBPHelpButton][BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPMinButton][BSHot], Buttons[WBPMinButton][BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPRestoreButton][BSHot], Buttons[WBPRestoreButton][BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPMaxButton][BSHot], Buttons[WBPMaxButton][BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPCloseButton][BSHot], Buttons[WBPCloseButton][BSNormal], m_pModel)

		SETTING_ITEM_DEFAULT_EX(Buttons[WBPHelpButton][BSPushed], Buttons[WBPHelpButton][BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPMinButton][BSPushed], Buttons[WBPMinButton][BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPRestoreButton][BSPushed], Buttons[WBPRestoreButton][BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPMaxButton][BSPushed], Buttons[WBPMaxButton][BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPCloseButton][BSPushed], Buttons[WBPCloseButton][BSNormal], m_pModel)

		SETTING_ITEM_DEFAULT_EX(Buttons[WBPHelpButton][BSDisabled], Buttons[WBPHelpButton][BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPMinButton][BSDisabled], Buttons[WBPMinButton][BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPRestoreButton][BSDisabled], Buttons[WBPRestoreButton][BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPMaxButton][BSDisabled], Buttons[WBPMaxButton][BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(Buttons[WBPCloseButton][BSDisabled], Buttons[WBPCloseButton][BSNormal], m_pModel)
		//
		SETTING_ITEM_DEFAULT_EX(ButtonsPos[WBPHelpButton], DEFAULT_NULLPOINT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(ButtonsPos[WBPMinButton], DEFAULT_NULLPOINT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(ButtonsPos[WBPRestoreButton], DEFAULT_NULLPOINT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(ButtonsPos[WBPMaxButton], DEFAULT_NULLPOINT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(ButtonsPos[WBPCloseButton], DEFAULT_NULLPOINT, m_pModel)
	END_SETTING_MAP()
};

class CButtonSettings : public CSettings
{
	const CButtonSettings* const m_pModel;

public:
	static const TCHAR defaultSectionName[];

	CButtonSettings(const CButtonSettings* const pModel = NULL) : m_pModel(pModel) {
		InternalSaveLoad(true, NULL, false, true);
	};
	virtual ~CButtonSettings() {
		int i =0;
	};

	POINT Position;
	POINT IconPos;
	RECT IconRect;
	RECT TextRect;
	RECT States[_bs_count];

	BEGIN_SETTING_MAP_NOCTOR(CButtonSettings)
		SETTING_ITEM_DEFAULT_EX(Position, DEFAULT_NULLPOINT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(IconPos, DEFAULT_NULLPOINT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(IconRect, DEFAULT_NULLRECT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(TextRect, DEFAULT_NULLRECT, m_pModel)

		SETTING_ITEM_DEFAULT_EX(States[BSNormal], DEFAULT_NULLRECT, m_pModel)
		SETTING_ITEM_DEFAULT_EX(States[BSHot], States[BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(States[BSPushed], States[BSNormal], m_pModel)
		SETTING_ITEM_DEFAULT_EX(States[BSDisabled], States[BSNormal], m_pModel)
	END_SETTING_MAP()
};

class CPictureSettings : public CSettings
{
public:
	static const TCHAR defaultSectionName[];

	RECT Background;
	RECT Area;

	BEGIN_SETTING_MAP(CPictureSettings)
		SETTING_ITEM_DEFAULT(Background, DEFAULT_NULLRECT)
		SETTING_ITEM_DEFAULT(Area, DEFAULT_NULLRECT)
	END_SETTING_MAP()
};

class CSkinSettings : public CSettings
{
public:
	static const TCHAR defaultSectionName[];

	CSkinInfo Info;
	CGenericSettings Generic;
	CWindowSettings Window;
	CButtonSettings Button;
	CPictureSettings Picture;

	CArray<RECT> CustomRects;

	BEGIN_SETTING_MAP(CSkinSettings)
		SETTING_ITEM_SUBITEM(Info)
		SETTING_ITEM_SUBITEM(Generic)
		SETTING_ITEM_SUBITEM(Window)
		SETTING_ITEM_SUBITEM(Button)
		SETTING_ITEM_SUBITEM(Picture)

		SETTING_ITEM_ALONE_ARRAY(CustomRects, RECT);
	END_SETTING_MAP()
};
