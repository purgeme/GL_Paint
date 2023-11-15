#include <FreeImage.h>
#include <GLFW/glfw3.h>
#include "shapes.h"
#include "variables.h"

//i sawed these functions in half!!!
static brushshapes* shapes = new circlebrush();

void saveScreenshot(float imageWidth, float imageHeight, float windowWidth, float windowHeight) {
    
    int bufferSize = windowWidth * windowHeight;
    BYTE* pixelArray = new BYTE[3 * bufferSize];
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, windowWidth, windowHeight, 0x80E0, GL_UNSIGNED_BYTE, pixelArray);

    FIBITMAP* image = FreeImage_ConvertFromRawBits(pixelArray, imageWidth, imageHeight, windowWidth * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);

    FreeImage_Save(FIF_JPEG, image, "screenshot.jpeg", 0);
    delete[] pixelArray;
}

void draw_pixel(int option, float x, float y, float size) 
{
    if (option == shape[line])
    {
        shapes->drawShape(x, y, 5);
    }
    else if (hollow && option != shape[eraser])
    {
        shapes->drawHollow(x, y, size);
    }
    else
    {         
        shapes->drawShape(x, y, size);
    }
}

void setShape(int type)
{
    if (type == shape[square])
    {
        // option = shape[square];
        shapes = new squarebrush();
    }
    else if (type == shape[triangle])
    {
        // option = shape[triangle];
        shapes = new trianglebrush();
    }
    else if (type == shape[eraser])
    {
        // option = shape[eraser];
        shapes = new squarebrush();
    }
    else
    {
        // option = shape[circle];
        shapes = new circlebrush();
    }
}

// void menu(int value)
// {
//     option = value;
//     value == shape[eraser] ? glColor3f(1.0, 1.0, 1.0) : glColor3f(R, G, B);
//     //to delete the previos heap allocated memory
//     delete shapes;
//     shapes = nullptr;
//     setShape(shapes, option);
// }

// void gllmenu()
// {
//     glutCreateMenu(menu);

//     glutAddMenuEntry("Circle", shape[circle]);
//     glutAddMenuEntry("square", shape[square]);
//     glutAddMenuEntry("triangle", shape[triangle]);
//     glutAddMenuEntry("line", shape[line]);
//     glutAddMenuEntry("eraser", shape[eraser]);
    
//     glutAttachMenu(GLUT_RIGHT_BUTTON);

// }

// void passive_draw_pixel(int r, int s)
//  {
//      if (lbuttonDown)
//      {
//          if (option == shape[line])
//          {
//              shapes->drawShape(r, s, 5);
//          }
//          else if (hollow && option != shape[eraser])
//          {
//              shapes->drawHollow(r, s, brushSize);
//          }
//          else
//          {
//              shapes->drawShape(r, s, brushSize);
//          }
//      }
//  }

// void fill_fix(int x1, int y1, int x2, int y2) {
// 	int dx, dy, i, e;
// 	int incx, incy, inc1, inc2;
// 	int x,y;

// 	dx = x2-x1;
// 	dy = y2-y1;

// 	if (dx < 0) dx = -dx;
// 	if (dy < 0) dy = -dy;
// 	incx = 1;
// 	if (x2 < x1) incx = -1;
// 	incy = 1;
// 	if (y2 < y1) incy = -1;
// 	x = x1; y = y1;
// 	if (dx > dy) {
// 		passive_draw_pixel(x, y);
// 		e = 2 * dy-dx;
// 		inc1 = 2*(dy-dx);
// 		inc2 = 2*dy;
// 		for (i=0; i<dx; i++) {
// 			if (e >= 0) {
// 				y += incy;
// 				e +=
// 			inc1;}
// 			else
// 				e += inc2;
// 			x += incx;
// 			passive_draw_pixel(x, y);
// 		}

// 	} else {
// 		passive_draw_pixel(x, y);
// 		e = 2*dx-dy;
// 		inc1 = 2*(dx-dy);
// 		inc2 = 2*dx;
// 		for (i=0; i<dy; i++) {
// 			if (e >= 0) {
// 				x += incx;
// 				e += inc1;
// 			}
// 			else
// 				e += inc2;
// 			y += incy;
// 			passive_draw_pixel(x, y);
// 		}
// 	}
// }
