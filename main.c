#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>

#include "lib/gamemgr/gamemgr.h"

#define DEBUG false

int main(int argc, char *argv[]) {
    if(argc > 1){
        if(strcmp(argv[1], "-debug") == 0) initGameManager(true);
        else initGameManager(DEBUG);
    }

    // --- INITIALIZE ---

    bool running = true;
    if(isDebug()) printf("Initializing.\n");

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Bobri (Bulanci)", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
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

    // --- ---

    while (running) {

        while (SDL_PollEvent(&event))
        {

            if (event.type == SDL_QUIT) {
                running = false;
                if(isDebug()) printf("Quit by player.\n");
            }
            if (event.type == SDL_MOUSEMOTION) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(isDebug()) printf("Mouse: [x:%d,y:%d]\n", x,y);
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