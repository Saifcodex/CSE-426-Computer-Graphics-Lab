#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stack>
using namespace std;

int ww = 600, wh = 500;
float green[3] = { 0.0, 1.0, 0.0 };
float red[3]   = { 1.0, 0.0, 0.0 };
float borderCol[3] = { 0.0, 0.0, 0.0 };
int r = 35;

void setPixel(int, int, float[]);
void getPixel(int, int, float[]);
void resize(int, int);
void drawPolygon(int, int, int, int);
void drawCircle(int, int, int);
void boundaryFill4(int, int, float[], float[]);
void display();
void mouse(int, int, int, int);

struct Point { int x, y; };

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ww, wh);
    glutInitWindowPosition(500, 50);
    glutCreateWindow("boundary-Fill");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutReshapeFunc(resize);
    glutMainLoop();
    return 0;
}

void setPixel(int pointx, int pointy, float f[3]) {
    glBegin(GL_POINTS);
    glColor3fv(f);
    glVertex2i(pointx, pointy);
    glEnd();
    glFlush();
}

void getPixel(int x, int y, float pixels[3]) {
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, pixels);
}

void resize(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w, 0.0, h);
    glutReshapeWindow(ww, wh);
    glViewport(0.0, 0.0, w, h);
}

void drawPolygon(int x1, int y1, int x2, int y2) {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glEnd();
    glFlush();
}

void drawCircle(int xc, int yc) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);

    while (x <= y) {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);

        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);

        if (d < 0)
            d = d + 4 * x + 6;
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    glEnd();
    glFlush();
}

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon(100, 200, 300, 300);
    drawCircle(200, 250);
    glFlush();
}

void boundaryFill4(int x, int y, float fillColor[3], float borderColor[3]) {
    stack<Point> s;
    Point p = {x, y};
    s.push(p);

    while (!s.empty()) {
        p = s.top();
        s.pop();

        float interiorColor[3];
        getPixel(p.x, p.y, interiorColor);
        bool isBorder = (interiorColor[0] == borderColor[0] &&
                         interiorColor[1] == borderColor[1] &&
                         interiorColor[2] == borderColor[2]);

        bool isFilled = (interiorColor[0] == fillColor[0] &&
                         interiorColor[1] == fillColor[1] &&
                         interiorColor[2] == fillColor[2]);

        if (!isBorder && !isFilled) {
            setPixel(p.x, p.y, fillColor);
            if (p.x + 1 < ww) s.push({p.x + 1, p.y});
            if (p.x - 1 >= 0) s.push({p.x - 1, p.y});
            if (p.y + 1 < wh) s.push({p.x, p.y + 1});
            if (p.y - 1 >= 0) s.push({p.x, p.y - 1});
        }
    }
}

void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int xi = x;
        int yi = (wh - y);
        int dx = xi - 200;
        int dy = yi - 250;
        float distance = sqrt(dx*dx + dy*dy);

        if (distance <= r) {
            boundaryFill4(xi, yi, red, borderCol);
        }
        else if (xi >= 100 && xi <= 300 && yi >= 200 && yi <= 300) {
            boundaryFill4(xi, yi, green, borderCol);
        }
        else {
            printf("Click inside the rectangle or circle to fill.\n");
        }
    }
}
