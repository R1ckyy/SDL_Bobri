#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../../utils/imgrender/imgrender.h"
#include "../../../utils/textrender/textrender.h"
#include "../../../utils/colors/colors.h"
#include "../../gamemgr/gamemgr.h"
#include "../../playermgr/playermgr.h"
#include "../../wallsmgr/wallsmgr.h"

#include "ingame.h"

static bool gameStarted;

static SDL_Texture *background_texture;

static TTF_Font *mainfont;

Uint32 gameStart;

void init_Ingame() {
    gameStarted = false;

    gameStart = SDL_GetTicks() + 5400;

    background_texture = IMG_LoadTexture(getRenderer(),"images/game_background.webp");

    mainfont = TTF_OpenFont("fonts/Galindo.ttf", 72);
};

void render_Ingame() {
    renderImage(background_texture, 0, 0, 1400, 800, 0, 0);

    renderPlayers();

    renderWalls();

    if(!gameStarted) {
        char buf[16];
        sprintf(buf, "Starting in: %2d", gameStart/1000 - SDL_GetTicks()/1000);
        createText(mainfont, white, buf, 350, 300, 700, 200);
    }

};

void logic_Ingame() {

    if(!gameStarted && gameStart <= SDL_GetTicks()) {
        gameStarted = true;
    }

    if(gameStarted) {
        movePlayers();
    }
};

void kill_Ingame() {
    SDL_DestroyTexture(background_texture);

    TTF_CloseFont(mainfont);
};