#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <string.h>

#include "lib/gamemgr/gamemgr.h"
#include "lib/buttonmgr/buttonmgr.h"
#include "lib/playermgr/playermgr.h"
#include "lib/wallsmgr/wallsmgr.h"

#define DEBUG false

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init(); 

    // --- INITIALIZE ---

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

    // Get the load order right (i have no idea help)

    initRenderer(renderer);

    initButtonMgr();
    initPlayerManager();

    if(argc > 1){
        if(strcmp(argv[1], "-debug") == 0) initGameManager(true);
        else initGameManager(DEBUG);
    }else initGameManager(DEBUG);
        
    initWallsManager();

    // End load order

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    SDL_Event event;

    // --- ---

    Uint64 last = SDL_GetPerformanceCounter();
    bool pressed = false;

    while (isRunning()) {
        Uint64 now = SDL_GetPerformanceCounter();

        updateDeltaTime((double)((now - last) / (double)SDL_GetPerformanceFrequency()));

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                quitGame();
                if(isDebug()) printf("Quit by Term signal.\n");
            }
            if (event.type == SDL_MOUSEMOTION) {
                updateMousePos();
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if(event.button.button == SDL_BUTTON_LEFT && pressed == false) {
                    pressed = true;
                    if(isDebug()) printf("Left mouse button pressed at [x:%d,y:%d]\n",getMousePos(X), getMousePos(Y));
                    buttonCheck();
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                if(event.button.button == SDL_BUTTON_LEFT && pressed == true) pressed = false;   
            }
            if (event.type == SDL_KEYDOWN) {
                SDL_Keycode key = event.key.keysym.sym;
                keyPressed(key);
                endGame_keyPressed(key);
            }
            if (event.type == SDL_KEYUP) {
                SDL_Keycode key = event.key.keysym.sym;
                keyUnpressed(key);
            }
        }

        if(isDebug()) printf("Mouse: [x:%d,y:%d], ActiveScreen: %d, deltaTime: %.3f\n", getMousePos(X), getMousePos(Y), getActiveScreen(), getDeltaTime());

        // Nastav barvu vykreslování na černou
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Vykresli pozadí
        SDL_RenderClear(renderer);

        renderActiveScreen();
        
        // Zobraz vykreslené prvky na obrazovku
        SDL_RenderPresent(renderer);

        last = now;
    }

    killGameManager();
    killButtonMgr();
    killWallsManager();
    killPlayerManager();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}