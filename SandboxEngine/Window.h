#pragma once
#include "Event.h"
#include "EventArgs.h"

struct GLFWwindow;

/*
 * 窗体类\n
 * 创建窗体以及事件处理
 */
class Window
{
	/*
	 * GLFW窗体
	 */
	GLFWwindow* mWindow;
	/*
	 * 窗体标题
	 */
	const char* mWindowTitle;

	/*
	 * 处理GLFW的键盘事件
	 */
	static void GlfwFunOnKey(GLFWwindow*, int key, int, int action, int);

	/*
	 * 注册事件，刷新窗体
	 */
	void InitWindowAndEvent() const;

public:
	/*
	 * 键盘事件
	 */
	Event<EventHandler<KeyEventArgs>> keyEvent;

	/*
	 * 创建窗体
	 */
	Window(int width, int height, const char* title, bool isFullscreen = false);

	/*
	 * 改变窗体大小
	 */
	void ChangeWindowSize(int width, int height, bool isFullscreen);

	/*
	 * 销毁窗体
	 */
	~Window();

	/*
	 * 获取实例
	 */
	static Window& GetInstance();
};
