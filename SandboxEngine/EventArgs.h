#pragma once

/*
 * ¼üÅÌÊÂ¼ş
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
