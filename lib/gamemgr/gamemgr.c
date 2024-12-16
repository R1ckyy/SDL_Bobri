#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "../screens/mainmenu.h"

#include "gamemgr.h"

static GameManager gamemgr;

void initGameManager(bool debug) {
    init_MainMenu();
    gamemgr.currentScreen = MENU;
    gamemgr.debug = debug;
    if(gamemgr.debug) printf("---------\nDEBUG MODE\n---------\n");
};

bool isDebug() {
    return gamemgr.debug;
};

void setActiveScreen(enum Screens screen) {
    gamemgr.currentScreen = screen;
};

enum Screens getActiveScreen() {
    return gamemgr.currentScreen;
};

void renderActiveScreen(SDL_Renderer *renderer) {
    switch (gamemgr.currentScreen) {
    case MENU:
        render_MainMenu(renderer);
        break;
    default:
        break;
    }
};