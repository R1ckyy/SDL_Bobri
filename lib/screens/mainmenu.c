#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../textmgr/textmgr.h"
#include "../buttonmgr/buttonmgr.h"
#include "../gamemgr/gamemgr.h"

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
    titlefont = TTF_OpenFont("fonts/Galindo.ttf",72);
    mainfont = TTF_OpenFont("fonts/Roboto.ttf", 72);

    btn_start = createButton(mainfont, "Start Game", 550, 300, 300, 75, btnAction_StartGame);
    btn_settings = createButton(mainfont, "Settings", 575, 400, 250, 75, btnAction_Settings);
    btn_leaderboard = createButton(mainfont, "Leaderboard", 550, 500, 300, 75, btnAction_LeaderBoard);
    btn_quit = createButton(mainfont, "Quit", 625, 600, 150, 75, btnAction_Quit);
};

void render_MainMenu(SDL_Renderer *renderer, int mouse_x, int mouse_y) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color grey = {150, 150, 150, 255};
    SDL_Color high = {0, 255, 255, 255};

    createText(titlefont, renderer, white, "Bobranci", 500, 100, 400, 150);

    renderButton(btn_start, renderer, grey, high, mouse_x, mouse_y);
    renderButton(btn_settings, renderer, grey, high, mouse_x, mouse_y);
    renderButton(btn_leaderboard, renderer, grey, high, mouse_x, mouse_y);
    renderButton(btn_quit, renderer, grey, high, mouse_x, mouse_y);
};

void btnclk_MainMenu(int mouse_x, int mouse_y) {
    runButtonFnc(btn_start, mouse_x, mouse_y);
    runButtonFnc(btn_settings, mouse_x, mouse_y);
    runButtonFnc(btn_leaderboard, mouse_x, mouse_y);
    runButtonFnc(btn_quit, mouse_x, mouse_y);
};

void kill_MainMenu() {
    TTF_CloseFont(titlefont);
    TTF_CloseFont(mainfont);
};