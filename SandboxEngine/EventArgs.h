#pragma once
#include <memory>
#include <map>
#include "EventRawPtr.h"
#include "GameEventArgs.h"

/*
 * �����¼�
 */
enum KeyAction
{
	KeyPress,
	KeyRelease,
	KeyRepeat
};

struct KeyEventArgs
{
	int key;
	KeyAction action;
};

/*
 * ����ƶ��¼�
 */
struct MouseMoveEventArgs
{
	double mouseX, mouseY;
};
