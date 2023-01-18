#include <SDL2/SDL.h>
#include <signal.h>

#ifndef RENDERER
// https://wiki.libsdl.org/SDL_RendererFlags
// supported:
// SDL_RENDERER_SOFTWARE
// SDL_RENDERER_ACCELERATED
// SDL_RENDERER_PRESENTVSYNC
// SDL_RENDERER_TARGETTEXTURE
#define RENDERER SDL_RENDERER_ACCELERATED
#endif

#ifndef DRIVER
// supported:
// opengl
// opengles2
// software
#define DRIVER "opengl"
#endif

// screen size
#define WIDTH 1920
#define HEIGHT 1080

// select SDL2 renderer: https://wiki.libsdl.org/SDL_RendererFlags
#define RENDERER SDL_RENDERER_ACCELERATED

// seems to make no big difference, so use full screen for everything
#define WINDOW_STYLE SDL_WINDOW_FULLSCREEN

// make sure we clean up when program is interrupted
void signalHandler(int sig)
{
    SDL_Quit();
    exit(sig);
}

int n_horizontal = 10;
int n_vertical = 10;
int rect_w = WIDTH / n_horizontal;
int rect_h = HEIGHT / n_vertical;
int margin = 5;

void render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < n_horizontal; i++)
    {
        for (int j = 0; j < n_vertical; j++)
        {
            SDL_Rect rect = {i * rect_w, j * rect_h, rect_w - margin, rect_h - margin};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

int main(int argc, char **argv)
{
    signal(SIGINT, signalHandler);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, DRIVER);

    // create SDL2 window and renderer
    SDL_Window *window = SDL_CreateWindow(__FILE__, 0, 0, WIDTH, HEIGHT, WINDOW_STYLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, RENDERER);

    // draw a black image
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event event;

    while (1)
    {
        // get input events via SDL
        while (SDL_PollEvent(&event))
        {
            // draw white image when mouse button is pressed
            // draw black image when mouse button is released
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_RenderClear(renderer);
                    render(renderer);
                    SDL_RenderPresent(renderer);
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                }
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_Quit();
                    return 0;
                }
            }
        }
    }

    return 0;
}
