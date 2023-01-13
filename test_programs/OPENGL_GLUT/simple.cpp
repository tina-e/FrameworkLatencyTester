// this application was refined using ChatGPT
#include <GL/glut.h>
#include <signal.h>

// make sure we clean up when program is interrupted
void signalHandler(int sig)
{
    exit(sig);
}

int windowWidth = 1920;
int windowHeight = 1080;

int colorR = 0;
int colorG = 0;
int colorB = 0;

void display() {
    glClearColor(colorR, colorG, colorB, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        colorR = 1.0;
        colorG = 1.0;
        colorB = 1.0;
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        colorR = 0.0;
        colorG = 0.0;
        colorB = 0.0;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    signal(SIGINT, signalHandler);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("GLUT Test Application");
    glutFullScreen();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
