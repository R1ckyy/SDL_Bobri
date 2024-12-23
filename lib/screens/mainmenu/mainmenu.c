#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../../utils/textrender/textrender.h"
#include "../../buttonmgr/buttonmgr.h"
#include "../../gamemgr/gamemgr.h"
#include "../../../utils/imgrender/imgrender.h"

#include "mainmenu.h"

static TTF_Font *titlefont;
static TTF_Font *mainfont;

void btnAction_StartGame() {
    setActiveScreen(GAME);
};

void btnAction_Settings() {
    setActiveScreen(SETTINGS);
};

void btnAction_LeaderBoard() {
    setActiveScreen(LEADERBOARD);
};

void btnAction_Quit() {
    quitGame();
    if(isDebug()) printf("Quitting by menu button.\n");
};

void init_MainMenu() {
    titlefont = TTF_OpenFont("fonts/Galindo.ttf", 72);
    mainfont = TTF_OpenFont("fonts/Roboto.ttf", 72);

    SDL_Color white = {255, 255, 255, 255};
SDL_Color grey = {150, 150, 150, 255};
SDL_Color high = {0, 255, 255, 255};
SDL_Color red = {255, 0, 0, 255};

    createButton("start", mainfont, "Start Game", 550, 300, 300, 75, grey, high, btnAction_StartGame);
    createButton("settings", mainfont, "Settings", 575, 400, 250, 75, grey, high, btnAction_Settings);
    createButton("leaderboard", mainfont, "Leaderboard", 550, 500, 300, 75, grey, high, btnAction_LeaderBoard);
    createButton("quit", mainfont, "Quit", 625, 600, 150, 75, grey, red, btnAction_Quit);
};

void render_MainMenu() {
SDL_Color white = {255, 255, 255, 255};
SDL_Color grey = {150, 150, 150, 255};
SDL_Color high = {0, 255, 255, 255};
SDL_Color red = {255, 0, 0, 255};

    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);

    renderImage("images/background_menu.png", 0, 0, 1400, 800);

    createText(titlefont, white, "Bobranci", 500, 100, 400, 150);

    createText(mainfont, grey, "Copyright Erik Graf 2024/2025, All rights reserved", 0, 785, 300, 15);

    renderButtons();
};

void kill_MainMenu() {
    TTF_CloseFont(titlefont);
    TTF_CloseFont(mainfont);
};