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
	 * ����״̬
	 */
	//�Ƿ�ȫ��
	bool mIsFullScreen = false;
	//GLFW����
	GLFWwindow* mWindow;
	//�������
	const char* mWindowTitle;

	/*
	 * ����GLFW�¼�
	 */
	//����
	static void GlfwFunOnKey(GLFWwindow*, int key, int, int action, int);
	//���
	static void GlfwFunCursorPos(GLFWwindow*, double x, double y);

	//ע���¼���ˢ�´���
	void InitWindowAndEvent() const;

public:
	/*
	 *�¼�
	 */
	//����
	Event<EventHandler<KeyEventArgs>> keyEvent;
	//���
	Event<EventHandler<MouseMoveEventArgs>> mouseMoveEvent;

	//��������
	Window(int width, int height, const char* title, bool isFullscreen = false);
	//���ٴ���
	~Window();

	//���봰����ѭ��
	void Run();

	//�ı䴰���С
	void ChangeWindowSize(int width, int height, bool isFullscreen);

	//��ȡʵ��
	static Window& GetInstance();
};
