#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

enum Screens {
    MENU,
    SETTINGS,
    LEADERBOARD,
    INGAME
};

enum PlayerSetting {
    INACTIVE,
    HUMAN,
    BOT,
};

typedef struct {
    bool debug;
    enum Screens currentScreen;
} GameManager;

void initGameManager(bool debug);

bool isDebug();

void setActiveScreen(enum Screens);

enum Screens getActiveScreen();

void renderActiveScreen(SDL_Renderer *renderer);

void killGameManager();