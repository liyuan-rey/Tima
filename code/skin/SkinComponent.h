//

#pragma once

class CSettings;

class ISkinComponent
{
public:
	virtual BOOL SetSkinInfo(CSettings& info) = 0;

	virtual void SkinChanged() = 0;

};
