#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../../utils/imgrender/imgrender.h"
#include "../../../utils/textrender/textrender.h"
#include "../../../utils/colors/colors.h"
#include "../../gamemgr/gamemgr.h"
#include "../../buttonmgr/buttonmgr.h"

#include "settings.h"

static TTF_Font *titlefont;
static TTF_Font *mainfont;

void btnAction_SReturnToMenu() {
    setActiveScreen(MENU);
};

void init_Settings() {
    titlefont = TTF_OpenFont("fonts/Galindo.ttf", 72);
    mainfont = TTF_OpenFont("fonts/Roboto.ttf", 72);

    createButton("set_returntomain", mainfont, "Return to menu", 50, 700, 300, 50, grey, white, btnAction_SReturnToMenu);
};

void render_Settings() {
    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);

    renderImage("images/background_menu.png", 0, 0, 1400, 800, 0);

    createText(titlefont, white, "Settings", 50, 50, 300, 100);
    createText(mainfont, grey, "Copyright Erik Graf 2024/2025, All rights reserved", 0, 785, 300, 15);
    createText(titlefont, white, "Coming soon Skbiid", 700, 200, 300, 300);

    renderButtons();
};

void kill_Settings() {
    TTF_CloseFont(titlefont);
    TTF_CloseFont(mainfont);
};