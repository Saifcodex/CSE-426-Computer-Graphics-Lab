#include <iostream>
#include <GL/glut.h>
using namespace std;

int pntX1 = 250, pntY1 = 300, r = 80;
int dashLength = 5, gapLength = 5;
int counter = 0;

void plotDashed(int x, int y)
{
    if (counter < dashLength) {
        glBegin(GL_POINTS);
        glVertex2i(x + pntX1, y + pntY1);
        glEnd();
    }
    counter++;
    if (counter >= dashLength + gapLength) {
        counter = 0;
    }
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

void midPointCircleAlgoDashed()
{
    int x = 0;
    int y = r;
    float decision = 5.0 / 4 - r;

    while (y >= x)
    {
        plotDashed(x, y);
        plotDashed(x, -y);
        plotDashed(-x, y);
        plotDashed(-x, -y);
        plotDashed(y, x);
        plotDashed(-y, x);
        plotDashed(y, -x);
        plotDashed(-y, -x);

        if (decision < 0)
            decision += 2 * x + 3;
        else {
            decision += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    midPointCircleAlgoDashed();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Dashed Circle - Midpoint Algo");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}
