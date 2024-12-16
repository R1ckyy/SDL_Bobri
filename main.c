#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <string.h>

#include "lib/gamemgr/gamemgr.h"

#define DEBUG false

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init(); 
    
    if(argc > 1){
        if(strcmp(argv[1], "-debug") == 0) initGameManager(true);
        else initGameManager(DEBUG);
    }else initGameManager(DEBUG);

    // --- INITIALIZE ---

    bool running = true;
    if(isDebug()) printf("Initializing.\n");

    SDL_Window* window = SDL_CreateWindow(
        "Bobri (Bulanci)", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        1400, 
        800, 
        SDL_WINDOW_SHOWN   
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

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
                if(isDebug()) printf("Mouse: [x:%d,y:%d], ActiveScreen: %d\n", x,y, getActiveScreen());
            }

        }

        // Nastav barvu vykreslování na černou
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Vykresli pozadí
        SDL_RenderClear(renderer);

        renderActiveScreen(renderer);
        
        // Zobraz vykreslené prvky na obrazovku
        SDL_RenderPresent(renderer);
    }

    killGameManager();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}