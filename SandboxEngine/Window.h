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
	 * 窗体状态
	 */
	//是否全屏
	bool mIsFullScreen = false;
	//GLFW窗体
	GLFWwindow* mWindow;
	//窗体标题
	const char* mWindowTitle;

	/*
	 * 处理GLFW事件
	 */
	//键盘
	static void GlfwFunOnKey(GLFWwindow*, int key, int, int action, int);
	//鼠标
	static void GlfwFunCursorPos(GLFWwindow*, double x, double y);

	//注册事件，刷新窗体
	void InitWindowAndEvent() const;

public:
	/*
	 *事件
	 */
	//键盘
	Event<EventHandler<KeyEventArgs>> keyEvent;
	//鼠标
	Event<EventHandler<MouseMoveEventArgs>> mouseMoveEvent;

	//创建窗体
	Window(int width, int height, const char* title, bool isFullscreen = false);
	//销毁窗体
	~Window();

	//进入窗体主循环
	void Run();

	//改变窗体大小
	void ChangeWindowSize(int width, int height, bool isFullscreen);

	//获取实例
	static Window& GetInstance();
};
