//

#pragma once

enum FramePart {
	TopLeft = 0,
	Top,
	TopRight,
	Right,
	BottomRight,
	Bottom,
	BotomLeft,
	Left,
	_count
};

enum FrameState {

	Active = 0,

	Inactive,

	Disabled,

	_count
};

enum WindowButtonPart {

	SysButton = 0,

	HelpButton,

	MinButton,

	RestoreButton,

	MaxButton,

	CloseButton,

	_count
};

enum ButtonState {

	Normal = 0,

	Hot,

	Pushed,

	Disabled,

	_count
};

