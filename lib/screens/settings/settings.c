#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../../utils/imgrender/imgrender.h"
#include "../../../utils/textrender/textrender.h"
#include "../../gamemgr/gamemgr.h"

#include "settings.h"

static TTF_Font *titlefont;
static TTF_Font *mainfont;

void init_Settings() {
    titlefont = TTF_OpenFont("fonts/Galindo.ttf", 72);
    mainfont = TTF_OpenFont("fonts/Roboto.ttf", 72);
};

void render_Settings() {
    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);

    SDL_Color grey = {150, 150, 150, 255};

    renderImage("images/background_menu.png", 0, 0, 1400, 800);

    createText(mainfont, grey, "Copyright Erik Graf 2024/2025, All rights reserved", 0, 785, 300, 15);
};

void btnclk_Settings() {

};

void kill_Settings() {
    TTF_CloseFont(titlefont);
    TTF_CloseFont(mainfont);
};