#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "../screens/mainmenu/mainmenu.h"
#include "../screens/settings/settings.h"
#include "../screens/leaderboard/leaderboard.h"
#include "../screens/ingame/ingame.h"
#include "../buttonmgr/buttonmgr.h"

#include "gamemgr.h"

static GameManager gamemgr;

void initGameManager(bool debug) {
    init_MainMenu();
    gamemgr.running = true;
    gamemgr.currentScreen = MENU;
    gamemgr.debug = debug;
    if(isDebug()) printf("-------------------\nDEBUG MODE ACTIVE\n-------------------\n");
};

void initRenderer(SDL_Renderer *renderer) {
    gamemgr.renderer = renderer;
};

SDL_Renderer* getRenderer() {
    return gamemgr.renderer;
};

bool isRunning() {
    return gamemgr.running;
}

void quitGame() {
    gamemgr.running = false;
}

bool isDebug() {
    return gamemgr.debug;
};

void updateDeltaTime(double deltaTime) {
    gamemgr.deltaTime = deltaTime;
};

double getDeltaTime() {
    return gamemgr.deltaTime;
};

void updateMousePos() {
    SDL_GetMouseState(&gamemgr.mouse_x, &gamemgr.mouse_y);
}

int getMousePos(enum MousePos xy) {
    return xy == X ? gamemgr.mouse_x : gamemgr.mouse_y;
};

void setActiveScreen(enum Screens screen) {
    if(isDebug()) printf("Switching to screen: %d\n", screen);
    cleanButtons();
    switch (gamemgr.currentScreen) {
    case MENU:
        kill_MainMenu();
        break;
    case SETTINGS:
        kill_Settings();
        break;
    case LEADERBOARD:
        kill_Leaderboard();
        break;
    case GAME:
        kill_Ingame();
        break;
    default:
        break;
    }
    gamemgr.currentScreen = screen;
    switch (gamemgr.currentScreen) {
    case MENU:
        init_MainMenu();
        break;
    case SETTINGS:
        init_Settings();
        break;
    case LEADERBOARD:
        init_Leaderboard();
        break;
    case GAME:
        init_Ingame();
        break;
    default:
        break;
    }
};

enum Screens getActiveScreen() {
    return gamemgr.currentScreen;
};

void renderActiveScreen() {
    switch (gamemgr.currentScreen) {
    case MENU:
        render_MainMenu();
        break;
    case SETTINGS:
        render_Settings();
        break;
    case LEADERBOARD:
        render_Leaderboard();
        break;
    case GAME:
        render_Ingame();
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
    case SETTINGS:
        kill_Settings();
        break;
    case LEADERBOARD:
        kill_Leaderboard();
        break;
    case GAME:
        kill_Ingame();
        break;
    default:
        break;
    }
};