#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../../utils/imgrender/imgrender.h"
#include "../../../utils/textrender/textrender.h"
#include "../../../utils/colors/colors.h"
#include "../../gamemgr/gamemgr.h"
#include "../../playermgr/playermgr.h"
#include "../../wallsmgr/wallsmgr.h"
#include "../../bulletsmgr/bulletsmgr.h"
#include "../../upgrademgr/upgrademgr.h"

#include "ingame.h"

static bool gameStarted;

static SDL_Texture *background_texture;

static TTF_Font *mainfont;
static TTF_Font *numberfont;

Uint32 gameStart;
Uint32 gameEnd;

void init_Ingame() {
    gameStarted = false;

    gameStart = SDL_GetTicks() + STARTCOUNTDOWN;
    gameEnd = SDL_GetTicks() + STARTCOUNTDOWN + GAMETIME;

    background_texture = IMG_LoadTexture(getRenderer(),"images/game_background.jpg");

    mainfont = TTF_OpenFont("fonts/Galindo.ttf", 72);
    numberfont = TTF_OpenFont("fonts/Monomaniac.ttf", 144);

    prepToStart();

    initUpgradesManager();

    initBulletManager();
};

void render_Ingame() {
    SDL_SetRenderDrawColor(getRenderer(), 0,0,0,0);

    renderImage(background_texture, 0, 0, 1400, 800, 0, 0);

    renderUpgrades();

    renderPlayers();

    renderBullets();

    renderWalls();

    renderPlayersHud();

    if(!gameStarted) {
        char buf[4];
        sprintf(buf, " %d", gameStart/1000 - SDL_GetTicks()/1000);
        createText(mainfont, white, "Starting in:", 350, 300, 550, 200);
        createText(numberfont, white, buf, 900, 300, 120, 170);
    }else{
        char buf[3];
        sprintf(buf, "%02d", gameEnd/1000 - SDL_GetTicks()/1000);
        createText(numberfont, white, buf, 650, 0, 100, 100);
    }

};

void logic_Ingame() {

    if(!gameStarted && gameStart <= SDL_GetTicks()) {
        gameStarted = true;
    }

    if(gameStarted) {
        respawnUpgrades();
        upgradesLogic();
        respawnPlayers();
        movePlayers();
        bulletLogic();
    }

    if(gameEnd <= SDL_GetTicks() && gameStarted) {
        gameStarted = false; 
        setActiveScreen(ENDGAME);
    }
};

void kill_Ingame() {
    killBulletManager();

    SDL_DestroyTexture(background_texture);

    TTF_CloseFont(mainfont);
    TTF_CloseFont(numberfont);

    killUpgradesManager();
};