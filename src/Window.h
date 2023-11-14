#pragma once
#include<GLFW/glfw3.h>
class Window
{
public:	

    GLFWwindow *window;

	Window();
	Window(int windowWidth, int windowHeight, const char* windowName);
	bool WindowInit() const;
	bool createWindow();
	// void ResetWindowSize() const;
	// void UserResponce() const;
	// void SetWindowPosition(int x, int y);
	// void SetWindowDimensions(int w, int h);
	// void SetWindowName(const char* windowName);
	// static void Keyboard(unsigned char Key, int x, int y);
	// static void Mouse(int button, int state, int x, int y);
	// static void Motion(int x, int y);
	// static void MotionPassive(int x, int y);
	// static void PassToCallback(int width, int height);

private:

	int m_WindowPosX, m_WindowPosY;
	int m_WindowHeight, m_WindowWidth;
	const char* m_WindowName;
	static int s_WindowHeight, s_WindowWidth;

};