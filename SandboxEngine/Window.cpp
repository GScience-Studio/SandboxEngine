#include <GL/glew.h>
#include <GL/GL.h>
#include <GLFW/glfw3.h>
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

void Window::InitWindowAndEvent() const
{
	glfwSetKeyCallback(mWindow, &GlfwFunOnKey);
	glfwMakeContextCurrent(mWindow);
	glfwShowWindow(mWindow);
}

Window::Window(const int width, const int height, const char* title, const bool isFullscreen)
{
	instance = this;

	keyEvent += [](KeyEventArgs e)
	{

	};

	mWindowTitle = title;
	glfwInit();
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	mWindow = glfwCreateWindow(640, 480, mWindowTitle, nullptr, nullptr);
	glewInit();

	ChangeWindowSize(width, height, isFullscreen);

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
	if (isFullscreen)
	{
		const auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		const auto newWindow = glfwCreateWindow(mode->width, mode->height, mWindowTitle, glfwGetPrimaryMonitor(), mWindow);
		glfwDestroyWindow(mWindow);
		mWindow = newWindow;
		glfwMakeContextCurrent(mWindow);
	}
	else
	{
		const auto newWindow = glfwCreateWindow(width, height, mWindowTitle, nullptr, mWindow);
		glfwDestroyWindow(mWindow);
		mWindow = newWindow;
	}
	InitWindowAndEvent();

	int realWidth, realHeight;
	glfwGetWindowSize(mWindow, &realWidth, &realHeight);

	glViewport(0, 0, realWidth, realHeight);
}

Window& Window::GetInstance()
{
	return *instance;
}