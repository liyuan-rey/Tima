//

#pragma once

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

	WBPSysButton = 0,

	WBPHelpButton,

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

