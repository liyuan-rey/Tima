//

#pragma once

#include "..\include\OOEnum\Enumeration.h"

BEGIN_ENUM_DEFINITION(SkinControl)
	DEFINE_ENUM(Window)
	DEFINE_ENUM(Button)
	DEFINE_ENUM(Picture)
END_ENUM_DEFINITION()

enum FramePart {
	FPTopLeft = 0,
	FPTop,
	FPTopRight,
	FPRight,
	FPBottomRight,
	FPBottom,
	FPBottomLeft,
	FPLeft,

	_fp_count
};

enum FrameState {
	FSActive = 0,
	FSInactive,
	FSDisabled,

	_fs_count
};

enum WindowButtonPart {
	WBPHelpButton = 0,
	WBPMinButton,
	WBPRestoreButton,
	WBPMaxButton,
	WBPCloseButton,

	_wbp_count
};

enum ButtonState {
	BSNormal = 0,
	BSHot,
	BSPushed,
	BSDisabled,

	_bs_count
};

