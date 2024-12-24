#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

enum Screens {
    MENU,
    SETTINGS,
    LEADERBOARD,
    GAME
};

enum MousePos {
    X,
    Y
};

typedef struct {
    bool running;
    bool debug;
    enum Screens currentScreen;
    SDL_Renderer *renderer;
    int mouse_x;
    int mouse_y;
    double deltaTime;
} GameManager;

void initGameManager(bool debug);

void initRenderer(SDL_Renderer *renderer);
SDL_Renderer* getRenderer();

bool isRunning();

void quitGame();

bool isDebug();

void updateDeltaTime(double deltaTime);
double getDeltaTime();

void updateMousePos();
int getMousePos(enum MousePos);

void setActiveScreen(enum Screens);
enum Screens getActiveScreen();
void renderActiveScreen();

void killGameManager();