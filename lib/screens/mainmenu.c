#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../textmgr/textmgr.h"

#include "mainmenu.h"

static TTF_Font *mainfont;

void init_MainMenu() {
    mainfont = TTF_OpenFont("../fonts/Roboto.ttf", 32);
};

void render_MainMenu(SDL_Renderer *renderer) {
    SDL_Color white = {255, 255, 255, 255};

    createText(mainfont, renderer, white, "ALL I WANT FOR CHRISTMAAS IS YOUUUU", 50, 50, 500, 100);
};

void kill_MainMenu() {
    TTF_CloseFont(mainfont);
};