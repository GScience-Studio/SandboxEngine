#pragma once
#include "Event.h"
#include "EventArgs.h"

struct GLFWwindow;

/*
 * ������\n
 * ���������Լ��¼�����
 */
class Window
{
	/*
	 * GLFW����
	 */
	GLFWwindow* mWindow;
	/*
	 * �������
	 */
	const char* mWindowTitle;

	/*
	 * ����GLFW�ļ����¼�
	 */
	static void GlfwFunOnKey(GLFWwindow*, int key, int, int action, int);

	/*
	 * ע���¼���ˢ�´���
	 */
	void InitWindowAndEvent() const;

public:
	/*
	 * �����¼�
	 */
	Event<EventHandler<KeyEventArgs>> keyEvent;

	/*
	 * ��������
	 */
	Window(int width, int height, const char* title, bool isFullscreen = false);

	/*
	 * �ı䴰���С
	 */
	void ChangeWindowSize(int width, int height, bool isFullscreen);

	/*
	 * ���ٴ���
	 */
	~Window();

	/*
	 * ��ȡʵ��
	 */
	static Window& GetInstance();
};
