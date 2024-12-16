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
    switch (gamemgr.currentScreen) {
    case MENU:
        kill_MainMenu();
        break;
    default:
        break;
    }
    gamemgr.currentScreen = screen;
    switch (gamemgr.currentScreen) {
    case MENU:
        init_MainMenu();
        break;
    default:
        break;
    }
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

void killGameManager() {
    switch (gamemgr.currentScreen) {
    case MENU:
        kill_MainMenu();
        break;
    default:
        break;
    }
};