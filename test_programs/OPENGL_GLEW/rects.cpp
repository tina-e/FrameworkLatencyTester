#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <signal.h>

#define WIDTH 1920
#define HEIGHT 1080

bool running = true;
bool is_pressed = false;
bool do_redraw = true;

const int n_rects = 1000;
int n_horizontal = 10;
int n_vertical = 10;
int rect_w = WIDTH / n_horizontal;
int rect_h = HEIGHT / n_vertical;

// make sure we clean up when program is interrupted
void signalHandler(int sig)
{
    running = false;
    SDL_Quit();
    exit(sig);
}

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

void drawRandomRect()
{
    glBegin(GL_QUADS);

    GLfloat *color = randomColor();
    GLfloat *position = randomPosition();

    glColor4f(color[0], color[1], color[2], color[3]);
    glVertex2f(position[0], position[1]);
    glVertex2f(position[0] + rect_w, position[1]);
    glVertex2f(position[0] + rect_w, position[1] + rect_h);
    glVertex2f(position[0], position[1] + rect_h);

    glEnd();
}

int main(int argc, char **argv)
{
    signal(SIGINT, signalHandler);

    SDL_Init(SDL_INIT_EVERYTHING); // maybe we have to reduce this?

    SDL_Window *window = SDL_CreateWindow(__FILE__, 0, 0, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    glewInit();

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    SDL_Event event;

    while (running)
    {
        bool do_redraw = false;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT && !is_pressed)
                {
                    is_pressed = true;
                    do_redraw = true;
                    glClearColor(1.0, 1.0, 1.0, 1.0);
                    glClear(GL_COLOR_BUFFER_BIT);

                    glBegin(GL_QUADS);
                    // random color

                    GLfloat *color = randomColor();

                    glColor4f(color[0], color[1], color[2], color[3]);
                    glVertex2f(0.0f, 0.0f);
                    glVertex2f(100.0f, 0.0f);
                    glVertex2f(100.0f, 100.0f);
                    glVertex2f(0.0f, 100.0f);
                    glEnd();
                    glFlush();
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT && is_pressed)
                {
                    is_pressed = false;
                    do_redraw = true;
                    glClearColor(0.0f, 0.0f, 0.0, 1.0f);
                    glClear(GL_COLOR_BUFFER_BIT);
                    glFlush();
                }
            }
        }

        SDL_GL_SwapWindow(window);
    }

    return 0;
}
