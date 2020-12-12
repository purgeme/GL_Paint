// Import libraries
#if !defined(__linux__) 
#include <windows.h>
#endif
#include<FreeImage.h>
#include <GL/glut.h>
#include "functions.h"
#include "variables.h"
#include "shapes.h"
#include "Window.h"

//declaring the global variables
int x1, y01, x2, y2;

bool l_b = false;
int a = 250;
int b = 250;

int c = a;
int d = b;
int p = c;
int q = d;
int u = p;
int v = q;

int counter = 0;

bool hollow = false;

float R{ 0.0f }, G{ 0.0f }, B{ 0.0f };

int size_brush = 20;

bool lbuttonDown;
bool rbuttonDown;

int shape[5] = { 0,1,2,3,4 };
int option = shape[line];

// Initialize function
void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(R, G, B);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000, 500, 0);
    glPointSize(3.0);
}

// Display function
void myDisplay() {
    drawPallete();
    fill_fix(c, d, a, b);
    fill_fix(p, q, c, d);
    fill_fix(p, q, u, v);
    draw_pixel();
    glFlush();
}

// The main function
int main(int argc, char **argv) 
{
    FreeImage_Initialise();
    // We can also use the member functions of this class to
    // set window parameters instead of using the constructor
    Window window(1000,500,"Just PAINT",GLUT_RGB);
    glutInit(&argc, argv);                          
    window.WindowInit();
    window.createWindow();
    gllmenu();
    glutDisplayFunc(myDisplay);
    window.UserResponce();
    window.ResetWindowSize();
    myInit();
    glutMainLoop();
    FreeImage_DeInitialise();
}
