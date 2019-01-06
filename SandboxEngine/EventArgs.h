#pragma once

/*
 * 键盘事件
 */
enum KeyAction
{
	KeyPress, KeyRelease, KeyRepeat
};
struct KeyEventArgs
{
	int key;
	KeyAction action;
};

/*
 * 鼠标移动事件
 */
struct MouseMoveEventArgs
{
	double mouseX, mouseY;
};
