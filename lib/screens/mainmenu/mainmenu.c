#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../../utils/textrender/textrender.h"
#include "../../buttonmgr/buttonmgr.h"
#include "../../gamemgr/gamemgr.h"
#include "../../../utils/imgrender/imgrender.h"

#include "mainmenu.h"

static TTF_Font *titlefont;
static TTF_Font *mainfont;

static Button btn_start;
static Button btn_settings;
static Button btn_leaderboard;
static Button btn_quit;

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

    btn_start = createButton(mainfont, "Start Game", 550, 300, 300, 75, btnAction_StartGame);
    btn_settings = createButton(mainfont, "Settings", 575, 400, 250, 75, btnAction_Settings);
    btn_leaderboard = createButton(mainfont, "Leaderboard", 550, 500, 300, 75, btnAction_LeaderBoard);
    btn_quit = createButton(mainfont, "Quit", 625, 600, 150, 75, btnAction_Quit);
};

void render_MainMenu() {
    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color grey = {150, 150, 150, 255};
    SDL_Color high = {0, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};

    renderImage("images/background_menu.png", 0, 0, 1400, 800);

    createText(titlefont, white, "Bobranci", 500, 100, 400, 150);

    createText(mainfont, grey, "Copyright Erik Graf 2024/2025, All rights reserved", 0, 785, 300, 15);

    renderButton(btn_start, grey, high);
    renderButton(btn_settings, grey, high);
    renderButton(btn_leaderboard, grey, high);
    renderButton(btn_quit, grey, red);
};

void btnclk_MainMenu() {
    runButtonFnc(btn_start);
    runButtonFnc(btn_settings);
    runButtonFnc(btn_leaderboard);
    runButtonFnc(btn_quit);
};

void kill_MainMenu() {
    TTF_CloseFont(titlefont);
    TTF_CloseFont(mainfont);
};