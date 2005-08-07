//

#pragma once

#include "..\include\settingsstorage\msettingsstorage.h"
using Mortimer::CSettings;

#include "SkinTypes.h"

class ISkinComponent
{
public:
	virtual UINT GetID() = 0;
	virtual ESkinControl GetType() = 0;
	virtual BOOL SetSkinInfo(CSettings* info) = 0;
	virtual ISkinComponent* GetSkinParent() = 0;
};
