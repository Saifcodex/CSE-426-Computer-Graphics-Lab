#include <iostream>
#include <GL/glut.h>
using namespace std;
int r = 50;

void plot(int xCenter, int yCenter, int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x + xCenter, y + yCenter);
    glVertex2i(-x + xCenter, y + yCenter);
    glVertex2i(x + xCenter, -y + yCenter);
    glVertex2i(-x + xCenter, -y + yCenter);
    glVertex2i(y + xCenter, x + yCenter);
    glVertex2i(-y + xCenter, x + yCenter);
    glVertex2i(y + xCenter, -x + yCenter);
    glVertex2i(-y + xCenter, -x + yCenter);
    glEnd();
}

void midPointCircleAlgo(int xCenter, int yCenter)
{
    int x = 0;
    int y = r;
    float decision = 1 - r;

    plot(xCenter, yCenter, x, y);

    while (y > x)
    {
        if (decision < 0)
        {
            x++;
            decision += 2 * x + 1;
        }
        else
        {
            y--;
            x++;
            decision += 2 * (x - y) + 1;
        }
        plot(xCenter, yCenter, x, y);
    }
}

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

// Mouse callback function
void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int xCenter = x;
        int yCenter = 480 - y; // Flip y-axis for OpenGL coords

        midPointCircleAlgo(xCenter, yCenter);
        glFlush();
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Interactive Midpoint Circle Drawing");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouseClick); // Register mouse click handler
    glutMainLoop();
}
