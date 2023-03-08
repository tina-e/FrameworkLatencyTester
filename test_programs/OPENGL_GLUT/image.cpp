// this application was refined using ChatGPT
#include <GL/glut.h>
#include <signal.h>
#include <SOIL/SOIL.h>
#include <iostream>

// make sure we clean up when program is interrupted
void signalHandler(int sig)
{
    exit(sig);
}

int imageWidth, imageHeight;
unsigned char* image;
int windowWidth = 1920;
int windowHeight = 1080;
int pressed = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (pressed == 1)
    {
        // Set up the texture
        glEnable(GL_TEXTURE_2D);
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Draw the textured quad
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        pressed = 1;
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        pressed = 0;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    signal(SIGINT, signalHandler);
    image = SOIL_load_image("noise.png", &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB);
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
