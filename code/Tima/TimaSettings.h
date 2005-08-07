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

	CString Location;
	CString URL;
	CString Ping;

	BEGIN_SETTING_MAP(CSntpServer)
		SETTING_ITEM(Location)
		SETTING_ITEM(URL)
		SETTING_ITEM_DEFAULT(Ping, DEFAULT_EMPTYSTR)
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

class CTrayClockSettings : public CSettings
{
public:
	static const TCHAR defaultSectionName[];

	CString CurrentSkinName;
	int Use12HoursFormat;
	int ShowDate;
	int ShowWeek;
	int ShowSeconds;
	int ShowZero;
	int BlinkColon;
	int Shadow;
	int AlwaysShowTooltip;
	int TooltipOpacity;
	int ShowMultiTimeZone;

	BEGIN_SETTING_MAP(CTrayClockSettings)
		SETTING_ITEM_DEFAULT(CurrentSkinName, DEFAULT_EMPTYSTR)
		SETTING_ITEM_DEFAULT(Use12HoursFormat, 0)
		SETTING_ITEM_DEFAULT(ShowDate, 1)
		SETTING_ITEM_DEFAULT(ShowWeek, 1)
		SETTING_ITEM_DEFAULT(ShowSeconds, 1)
		SETTING_ITEM_DEFAULT(ShowZero, 0)
		SETTING_ITEM_DEFAULT(BlinkColon, 1)
		SETTING_ITEM_DEFAULT(Shadow, 0)
		SETTING_ITEM_DEFAULT(AlwaysShowTooltip, 0)
		SETTING_ITEM_DEFAULT(TooltipOpacity, 0)
		SETTING_ITEM_DEFAULT(ShowMultiTimeZone, 0)
	END_SETTING_MAP()
};

class CTimaSettings : public CSettings
{
public:
	static const TCHAR defaultSectionName[];

	CTimaInfo Info;
	CAtomicClockSettings AtomicClock;
	CTrayClockSettings TrayClock;

	BEGIN_SETTING_MAP(CTimaSettings)
		SETTING_ITEM_SUBITEM(Info)
		SETTING_ITEM_SUBITEM(AtomicClock)
		SETTING_ITEM_SUBITEM(TrayClock)
	END_SETTING_MAP()
};

// ========================================

class CSntpServerList : public CSettings
{
public:
	static const TCHAR defaultSectionName[];

	CSntpServers Servers;

	BEGIN_SETTING_MAP(CSntpServerList)
		SETTING_ITEM_ARRAY(Servers, CSntpServer)
	END_SETTING_MAP()
};
