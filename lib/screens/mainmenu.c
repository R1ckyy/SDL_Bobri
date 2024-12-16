#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../textmgr/textmgr.h"

#include "mainmenu.h"

static TTF_Font *titlefont;
static TTF_Font *mainfont;

void init_MainMenu() {
    titlefont = TTF_OpenFont("fonts/Galindo.ttf",72);
    mainfont = TTF_OpenFont("fonts/Roboto.ttf", 32);
};

void render_MainMenu(SDL_Renderer *renderer) {
    SDL_Color white = {255, 255, 255, 255};

    createText(titlefont, renderer, white, "Bobranci (Bulanci)", 400, 50, 600, 100);
};

void kill_MainMenu() {
    TTF_CloseFont(titlefont);
    TTF_CloseFont(mainfont);
};