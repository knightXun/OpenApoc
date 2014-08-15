
#pragma once


enum class FormEventType
{
	GotFocus,
	LostFocus,
	MouseEnter,
	MouseLeave,
	MouseDown,
	MouseUp,
	MouseMove,
	MouseClick,
	KeyDown,
	KeyPress,
	KeyUp,

	ButtonClick,
	CheckBoxChange,
	ScrollBarChange
};

enum class HorizontalAlignment
{
	Left,
	Centre,
	Right
};

enum class VerticalAlignment
{
	Top,
	Centre,
	Bottom
};
