#include <stdbool.h>
#include <stdio.h>

#include "gamemgr.h"

static GameManager gamemgr;

void initGameManager(bool debug) {
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

void renderActiveScreen() {
    
};