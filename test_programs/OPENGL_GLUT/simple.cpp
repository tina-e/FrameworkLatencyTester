#include <GL/glut.h>
#include <signal.h>

#define WIDTH 1920
#define HEIGHT 1080

// make sure we clean up when program is interrupted
void signalHandler(int sig)
{
    exit(sig);
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    glutPostRedisplay();
}

void input(int button, int state, int x, int y)
{
    if(button == 0 && state == GLUT_DOWN)
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
    }
    else
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
}

int main(int argc, char** argv)
{
    signal(SIGINT, signalHandler);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // GLUT RBG also would work
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(__FILE__);
    glutFullScreen();

    glutDisplayFunc(render);
    glutMouseFunc(input);
    glutMainLoop();

    return 0;
}
