#include "screenmgr.h"

static enum Screens currentScreen = MENU;

void setActiveScreen(enum Screens screen) {
    currentScreen = screen;
};

enum Screens getActiveScreen() {
    return currentScreen;
};

void renderActiveScreen() {
    
}