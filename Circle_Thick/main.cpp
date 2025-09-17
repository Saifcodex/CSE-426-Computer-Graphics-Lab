#include <iostream>
#include <GL/glut.h>
using namespace std;
int pntX1 = 250, pntY1 = 300, r = 80;
int thickness = 5;
void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x + pntX1, y + pntY1);
    glEnd();
}
void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void midPointCircleAlgo(int r)
{
    int x = 0;
    int y = r;
    float decision = 5.0 / 4 - r;

    while (y >= x)
    {

        plot(x, y);
        plot(x, -y);
        plot(-x, y);
        plot(-x, -y);
        plot(y, x);
        plot(-y, x);
        plot(y, -x);
        plot(-y, -x);

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
}
}
void thickCircle()
{
    for (int i = 0; i < thickness; i++)
    {
        midPointCircleAlgo(r + i);
    }
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    thickCircle();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Thick Circle - Midpoint Algo");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}
