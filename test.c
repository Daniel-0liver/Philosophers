#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("My Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Calculate the circle points
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    int x = w / 2, y = h / 2, radius = 50;
    int circle_points[360][2];
    for (int i = 0; i < 360; i++) {
        circle_points[i][0] = (int)(x + radius * cos(i * M_PI / 180));
        circle_points[i][1] = (int)(y + radius * sin(i * M_PI / 180));
    }

    SDL_Texture* circle_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetRenderTarget(renderer, circle_texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    for (int i = 0; i < 360; i++) {
        SDL_RenderDrawPoint(renderer, circle_points[i][0], circle_points[i][1]);
    }

    SDL_SetRenderTarget(renderer, NULL);

    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    printf("Key pressed: %d\n", event.key.keysym.sym);
                    break;
            }
        }

        // Render the circle texture
        SDL_RenderCopy(renderer, circle_texture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(circle_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
