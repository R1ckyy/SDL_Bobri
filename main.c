#include <SDL2/SDL.h>
#include <stdbool.h>
#include "lib/screenmgr/screenmgr.h"

#define DEBUG false

int main(int argc, char *argv[])
{
    bool running = true;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Bobri", 
        100, 
        100, 
        1280, 
        720, 
        SDL_WINDOW_SHOWN   
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_Event event;

    while (running) {

        while (SDL_PollEvent(&event))
        {

            if (event.type == SDL_QUIT) {
                running = false;
                if(DEBUG) printf("Quit by player.\n");
            }

        }

        // Nastav barvu vykreslování na černou
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Vykresli pozadí
        SDL_RenderClear(renderer);

        // Zobraz vykreslené prvky na obrazovku
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}