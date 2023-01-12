#include <SDL2/SDL.h>
#include <signal.h>
#include <cstdlib>
#include <ctime>

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

int n_rects = 1000;
int rect_w = WIDTH / 10;
int rect_h = HEIGHT / 10;

void render(SDL_Renderer* renderer)
{
    for (int i = 0; i < n_rects; i++)
    {
        uint8_t r = rand() % 255;
        uint8_t g = rand() % 255;
        uint8_t b = rand() % 255;
        uint8_t a = 55 + rand() % 200;

        int x = rand() % (WIDTH - rect_w);
        int y = rand() % (HEIGHT - rect_h);

        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_Rect rect = { x, y, rect_w, rect_h };
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect = { 0, 0, 300, 300 };
    SDL_RenderFillRect(renderer, &rect);
}

int main(int argc, char** argv)
{
    signal(SIGINT, signalHandler);

    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, DRIVER);

    // create SDL2 window and renderer
    SDL_Window* window = SDL_CreateWindow(__FILE__, 0, 0, WIDTH, HEIGHT, WINDOW_STYLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, RENDERER);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // draw a black image
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event event;

    while(1)
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
        }
    }

    return 0;
}
