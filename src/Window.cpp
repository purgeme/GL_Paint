#include<GL/glut.h>
#include "shapes.h"
#include "functions.h"
#include "variables.h"
#include "Window.h"

int Window::s_WindowHeight = 0;
int Window::s_WindowWidth = 0;

Window::Window()
    :m_WindowPosX(0),m_WindowPosY(0),m_WindowHeight(720),m_WindowWidth(1280),m_WindowName("This is not Paint"),m_DisplayMode(0)
{
    s_WindowHeight = m_WindowHeight;
    s_WindowWidth = m_WindowWidth;
}

Window::Window(int windowWidth, int windowHeight, const char* windowName, unsigned int displayMode)
    :m_WindowPosX(0),m_WindowPosY(0),m_WindowHeight(windowHeight),m_WindowWidth(windowWidth),m_WindowName(windowName),m_DisplayMode(displayMode)
{
    s_WindowHeight = m_WindowHeight;
    s_WindowWidth = m_WindowWidth;
}

void Window::WindowInit() const
{
    glutInitDisplayMode(m_DisplayMode);
    glutInitWindowSize(m_WindowWidth, m_WindowHeight);
    glutInitWindowPosition(m_WindowPosX, m_WindowPosY);
}

void Window::createWindow() const
{
    glutCreateWindow(m_WindowName);
}

void Window::ResetWindowSize() const
{
    glutReshapeFunc([](int x, int y) { glutReshapeWindow(s_WindowWidth, s_WindowHeight); });
}

void Window::UserResponce() const
{
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutKeyboardFunc(Keyboard);
    glutPassiveMotionFunc(MotionPassive);
}

void Window::SetWindowName(const char* windowName)
{
    m_WindowName = windowName;
}

void Window::SetWindowPosition(int x, int y)
{
    m_WindowPosX = x;
    m_WindowPosY = y;
}

void Window::SetWindowDimensions(int w, int h)
{
    m_WindowWidth = w;
    m_WindowHeight = h;
}

void Window::Keyboard(unsigned char Key, int x, int y)
{
    if (Key == 'x') {
        glClear(GL_COLOR_BUFFER_BIT);
        glutPostRedisplay();
    }
    else if (Key == '+' && size_brush > 0.0f)
    {
        size_brush++;
        glutPostRedisplay();
    }
    else if (Key == 's')
    {
        saveScreenshot();
    }
    else if (Key == '-' && size_brush > 1.0f)
    {
        size_brush--;
        glutPostRedisplay();
    }
    else if (Key == 'h')
        hollow = !hollow;
    else if (option != shape[eraser])
    {
        if (Key == 'r' && R < 0.9f)
        {
            R += 0.1f;
            glColor3f(R, G, B);
            glutPostRedisplay();
        }
        else if (Key == 'b' && B < 0.9f)
        {
            B += 0.1f;
            glColor3f(R, G, B);
            glutPostRedisplay();
        }
        else if (Key == 'g' && G < 0.9f)
        {
            G += 0.1f;
            glColor3f(R, G, B);
            glutPostRedisplay();
        }
        else if (Key == '1')
        {
            R = 1.0f;
            G = 0.0f;
            B = 0.0f;
            glColor3f(R, G, B);
            glutPostRedisplay();

        }
        else if (Key == '2')
        {
            R = 0.0f;
            G = 0.0f;
            B = 1.0f;
            glColor3f(R, G, B);
            glutPostRedisplay();

        }
        else if (Key == '3')
        {
            R = 0.0f;
            G = 1.0f;
            B = 0.0f;
            glColor3f(R, G, B);
            glutPostRedisplay();

        }
        else if (Key == '4')
        {
            R = 1.0f;
            G = 0.0f;
            B = 1.0f;
            glColor3f(R, G, B);
            glutPostRedisplay();

        }
        else if (Key == '5')
        {
            R = 0.0f;
            G = 1.0f;
            B = 1.0f;
            glColor3f(R, G, B);
            glutPostRedisplay();

        }
        else if (Key == '6')
        {
            R = 1.0f;
            G = 1.0f;
            B = 0.0f;
            glColor3f(R, G, B);
            glutPostRedisplay();

        }
        else if (Key == '0')
        {
            R = 0.0f;
            G = 0.0f;
            B = 0.0f;
            glColor3f(R, G, B);
            glutPostRedisplay();

        }
        else if (Key == 'R' && R > 0.0f)
        {
            R -= 0.1f;
            glColor3f(R, G, B);
            glutPostRedisplay();
        }
        else if (Key == 'B' && B > 0)
        {
            B -= 0.1f;
            glColor3f(R, G, B);
            glutPostRedisplay();
        }
        else if (Key == 'G' && G > 0.0f)
        {
            G -= 0.1f;
            glColor3f(R, G, B);
            glutPostRedisplay();
        }
    }
}

void Window::Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            rbuttonDown = true;
            glutPostRedisplay();

        }
        else if (state == GLUT_UP)
            rbuttonDown = false;
    }
    else if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            lbuttonDown = true;
            glutPostRedisplay();
        }
        else if (state == GLUT_UP)
            lbuttonDown = false;
    }
}

void Window::Motion(int x, int y)
{
    u = p;
    v = q;
    p = c;
    q = d;
    c = a;
    d = b;
    a = x;
    b = y;
    glutPostRedisplay();
}

void Window::MotionPassive(int x, int y)
{
    u = p;
    v = q;
    p = c;
    q = d;
    c = a;
    d = b;
    a = x;
    b = y;
    glutPostRedisplay();
}

void Window::PassToCallback(int width, int height)
{
    glutReshapeWindow(s_WindowWidth, s_WindowHeight);
}
