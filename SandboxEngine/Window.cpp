#include <GL/glew.h>
#include <GL/GL.h>
#include <GLFW/glfw3.h>
#include "Logger.h"
#include "Window.h"

Window* instance = nullptr;

void Window::GlfwFunOnKey(GLFWwindow*, const int key, int, const int action, int)
{
	GetInstance().keyEvent.Do(KeyEventArgs
		{
			key,
			action == GLFW_PRESS ? KeyPress :
			action == GLFW_RELEASE ? KeyRelease : KeyRepeat
		});
}
void Window::GlfwFunCursorPos(GLFWwindow*, const double x, const double y)
{
	GetInstance().mouseMoveEvent.Do(MouseMoveEventArgs
		{
			x,y
		});
}

void Window::InitWindowAndEvent() const
{
	glfwSetKeyCallback(mWindow, &GlfwFunOnKey);
	glfwSetCursorPosCallback(mWindow, &GlfwFunCursorPos);
	glfwMakeContextCurrent(mWindow);
	glfwShowWindow(mWindow);
}

Window::Window(const int width, const int height, const char* title, const bool isFullscreen)
{
	if (instance != nullptr)
		LogError("There is already a window instance in the program.");

	instance = this;

	mWindowTitle = title;
	Assert(glfwInit() == GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	mWindow = glfwCreateWindow(width, height, mWindowTitle, nullptr, nullptr);
	Assert(mWindow != nullptr);
	glfwMakeContextCurrent(mWindow);
	Assert(glewInit() == GLEW_OK);

	ChangeWindowSize(width, height, isFullscreen);

	//È«ÆÁÇÐ»»°´¼ü
	keyEvent += [&](KeyEventArgs e)
	{
		if (e.key == GLFW_KEY_F11 && e.action == KeyPress)
			ChangeWindowSize(width, height, !mIsFullScreen);
	};

	while (!glfwWindowShouldClose(mWindow))
	{
		glClearColor(0, 0, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mWindow);

		glfwPollEvents();
	}
}

Window::~Window()
{
	glfwTerminate();
}

void Window::ChangeWindowSize(const int width, const int height, const bool isFullscreen)
{
	glfwHideWindow(mWindow);

	mIsFullScreen = isFullscreen;

	if (isFullscreen)
	{
		const auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		const auto newWindow = glfwCreateWindow(mode->width, mode->height, mWindowTitle, glfwGetPrimaryMonitor(), mWindow);
		Assert(newWindow != nullptr);
		glfwDestroyWindow(mWindow);
		mWindow = newWindow;
		glfwMakeContextCurrent(mWindow);
	}
	else
	{
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		const auto newWindow = glfwCreateWindow(width, height, mWindowTitle, nullptr, mWindow);
		Assert(newWindow != nullptr);
		glfwDestroyWindow(mWindow);
		mWindow = newWindow;
	}
	InitWindowAndEvent();

	int realWidth, realHeight;
	glfwGetWindowSize(mWindow, &realWidth, &realHeight);

	glViewport(0, 0, realWidth, realHeight);	
	glfwShowWindow(mWindow);
}

Window& Window::GetInstance()
{
	return *instance;
}