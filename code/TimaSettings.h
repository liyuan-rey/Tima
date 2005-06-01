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

class CSntpServer : public CSettings
{
public:
	static const TCHAR defaultSectionName[];

	CString Name;
	CString URL;

	BEGIN_SETTING_MAP(CSntpServer)
		SETTING_ITEM(Name)
		SETTING_ITEM(URL)
	END_SETTING_MAP()
};

typedef CArray<CSntpServer, CSntpServer&> CSntpServers;

class CAtomicClockSettings : public CSettings
{
public:
	static const TCHAR defaultSectionName[];

	SYSTEMTIME LastAdjustAt;
	int ManualAdjustInterval;
	int AdjustOnStart;
	int AdjustOnConnect;
	int AdjustEvery;
	int AdjustEveryNum;
	int AdjustEveryUnit;
	int AdjustOnly;
	int UserOffset;
	int OffsetSign;
	int OffsetHour;
	int OffsetMin;
	int OffsetSec;
	int OffsetMS;
	CSntpServers ActivedServers;

	BEGIN_SETTING_MAP(CAtomicClockSettings)
		SETTING_ITEM_BINARY_DEFAULT(LastAdjustAt, sizeof(SYSTEMTIME), &DEFAULT_ZEROTIME)
		SETTING_ITEM_DEFAULT(ManualAdjustInterval, 40)
		SETTING_ITEM_DEFAULT(AdjustOnStart, 0)
		SETTING_ITEM_DEFAULT(AdjustOnConnect, 1)
		SETTING_ITEM_DEFAULT(AdjustEvery, 1)
		SETTING_ITEM_DEFAULT(AdjustEveryNum, 1)
		SETTING_ITEM_DEFAULT(AdjustEveryUnit, 1)
		SETTING_ITEM_DEFAULT(AdjustOnly, 0)
		SETTING_ITEM_DEFAULT(UserOffset, 0)
		SETTING_ITEM_DEFAULT(OffsetSign, 0)
		SETTING_ITEM_DEFAULT(OffsetHour, 0)
		SETTING_ITEM_DEFAULT(OffsetMin, 0)
		SETTING_ITEM_DEFAULT(OffsetSec, 0)
		SETTING_ITEM_DEFAULT(OffsetMS, 0)
		SETTING_ITEM_ARRAY(ActivedServers, CSntpServer)
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
