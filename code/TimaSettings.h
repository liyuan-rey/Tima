//

#pragma once

#include "skin\settingutil.h"

#include "include\settingsstorage\msettingsstorage.h"
using Mortimer::CSettings;

static const DWORD TIMA_SETTING_VERSION = 1;

class CTimaInfo : public CSettings
{
public:
	static const TCHAR defaultSectionName[];

	DWORD Version;
	CString Remark;

	BEGIN_SETTING_MAP(CTimaInfo)
		SETTING_ITEM_DEFAULT(Version, TIMA_SETTING_VERSION)
		SETTING_ITEM_DEFAULT(Remark, DEFAULT_EMPTYSTR)
	END_SETTING_MAP()
};

class CAtomicClockSettings : public CSettings
{
public:
	static const TCHAR defaultSectionName[];

	DWORD LastAdjustAt;
	int ManualAdjustInterval;
	bool AdjustOnStart;
	bool AdjustOnConnect;
	bool AdjustEvery;
	int AdjustEveryNum;
	int AdjustEveryUnit;
	bool UserOffset;
	int OffsetSign;
	int OffsetHour;
	int OffsetMin;
	int OffsetSec;
	int OffsetMS;
	CStringArray ActivedServers;

	BEGIN_SETTING_MAP(CAtomicClockSettings)
		SETTING_ITEM_DEFAULT(LastAdjustAt, 0)
		SETTING_ITEM_DEFAULT(ManualAdjustInterval, 40)
		SETTING_ITEM_DEFAULT(AdjustOnStart, false)
		SETTING_ITEM_DEFAULT(AdjustOnConnect, true)
		SETTING_ITEM_DEFAULT(AdjustEvery, true)
		SETTING_ITEM_DEFAULT(AdjustEveryNum, 1)
		SETTING_ITEM_DEFAULT(AdjustEveryUnit, 0)
		SETTING_ITEM_DEFAULT(UserOffset, false)
		SETTING_ITEM_DEFAULT(OffsetSign, 0)
		SETTING_ITEM_DEFAULT(OffsetHour, 0)
		SETTING_ITEM_DEFAULT(OffsetMin, 0)
		SETTING_ITEM_DEFAULT(OffsetSec, 0)
		SETTING_ITEM_DEFAULT(OffsetMS, 0)
		SETTING_ITEM_ALONE_ARRAY(ActivedServers, CString)
	END_SETTING_MAP()
};

class CTimaSettings : public CSettings
{
public:
	static const TCHAR defaultSectionName[];

	CTimaInfo Info;
	CAtomicClockSettings AtomicClock;

	BEGIN_SETTING_MAP(CTimaSettings)
		SETTING_ITEM_SUBITEM(Info)
		SETTING_ITEM_SUBITEM(AtomicClock)
	END_SETTING_MAP()
};