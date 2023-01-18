#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <cstdlib>
#include <signal.h>

#define WIDTH 1920
#define HEIGHT 1080

bool running = true;

void signalHandler(int sig)
{
    running = false;
    SDL_Quit();
    exit(sig);
}

int main(int argc, char** argv)
{
    signal(SIGINT, signalHandler);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(__FILE__, 0, 0, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    glewInit();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    SDL_Event event;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble)WIDTH, (GLdouble)HEIGHT, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    //glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    //glDisable(GL_DEPTH_TEST);
                    //glDisable(GL_ALPHA_TEST);
                    //glDisable(GL_STENCIL_TEST);
                    //glEnable(GL_COLOR_MATERIAL);
                    //glEnable (GL_BLEND);
                    //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    for (int i = 0; i < 1000; i++)
                    {
                        float r = (float)rand() / RAND_MAX;
                        float g = (float)rand() / RAND_MAX;
                        float b = (float)rand() / RAND_MAX;
                        float a = (float)rand() / RAND_MAX;
                        glColor4f(r, g, b, a);

                        int x = rand() % WIDTH;
                        int y = rand() % HEIGHT;
                        int width = rand() % (WIDTH - x);
                        int height = rand() % (HEIGHT - y);

                        glBegin(GL_QUADS);
                        glVertex2i(x, y);
                        glVertex2i(x + width, y);
                        glVertex2i(x + width, y + height);
                        glVertex2i(x, y + height);
                        glEnd();
                    }
                    //glEnable(GL_DEPTH_TEST);
                    //glEnable(GL_ALPHA_TEST);
                    //glEnable(GL_STENCIL_TEST);
                    //glDisable(GL_BLEND);
                    glColor4f(1, 1, 1, 1);
                    glBegin(GL_QUADS);
                    glVertex2i(0, 0);
                    glVertex2i(300, 0);
                    glVertex2i(300, 300);
                    glVertex2i(0, 300);
                    glEnd();
                    //glFlush();
                    SDL_GL_SwapWindow(window);
                    glClear(GL_COLOR_BUFFER_BIT);
                    glFinish();
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP)
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    glClearColor(0.0f, 0.0f, 0.0, 1.0f);
                }
                SDL_GL_SwapWindow(window);
                glClear(GL_COLOR_BUFFER_BIT);
                glFinish();
            }
        }
    }

    return 0;
}
