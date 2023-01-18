#include <iostream>
#include <GL/glut.h>
#include <cstdlib>

/* define the window size */
#define WIDTH 1920
#define HEIGHT 1080

const int n_rects = 1000;
int n_horizontal = 10;
int n_vertical = 10;
int rect_w = WIDTH / n_horizontal;
int rect_h = HEIGHT / n_vertical;

bool is_pressed = false;
bool do_redraw = false;

GLfloat *randomColor()
{
    GLfloat *color = new GLfloat[4];
    color[0] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    color[1] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    color[2] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    color[3] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return color;
}

GLfloat *randomPosition()
{
    GLfloat *position = new GLfloat[2];
    position[0] = static_cast<float>(rand() % (WIDTH - rect_w));
    position[1] = static_cast<float>(rand() % (HEIGHT - rect_h));
    return position;
}

void drawRectangles()
{
    glBegin(GL_QUADS);

    for (int i = 0; i < n_rects; i++)
    {
        GLfloat *color = randomColor();
        GLfloat *position = randomPosition();

        glColor4f(color[0], color[1], color[2], color[3]);
        glVertex2f(position[0], position[1]);
        glVertex2f(position[0] + rect_w, position[1]);
        glVertex2f(position[0] + rect_w, position[1] + rect_h);
        glVertex2f(position[0], position[1] + rect_h);
    }

    // white rect top left corner
    int w = 300;
    int h = 300;
    GLfloat *color = new GLfloat[3];
    color[0] = 1.0;
    color[1] = 1.0;
    color[2] = 1.0;
    GLfloat *position = new GLfloat[2];
    position[0] = 0.0;
    position[1] = HEIGHT - h;

    glColor3f(color[0], color[1], color[2]);
    glVertex2f(position[0], position[1]);
    glVertex2f(position[0] + w, position[1]);
    glVertex2f(position[0] + w, position[1] + h);
    glVertex2f(position[0], position[1] + h);

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (is_pressed)
        drawRectangles();
    glFlush();
}

void input(int button, int state, int x, int y)
{
    if (button == 0 && state == GLUT_DOWN && !is_pressed)
    {
        is_pressed = true;
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glutSwapBuffers();
        glutPostRedisplay();
    }
    else if (is_pressed)
    {
        is_pressed = false;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glutSwapBuffers();
        glutPostRedisplay();
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)WIDTH, 0.0, (GLdouble)HEIGHT);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(__FILE__);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(input);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutMainLoop();
    return 0;
}