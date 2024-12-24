#include "../../../utils/imgrender/imgrender.h"
#include "../../gamemgr/gamemgr.h"
#include "../../playermgr/playermgr.h"

#include "ingame.h"

static bool gameStarted;

static SDL_Texture *background_texture;

void init_Ingame() {
    gameStarted = true;

    background_texture = IMG_LoadTexture(getRenderer(),"images/game_background.webp");
};

void render_Ingame() {
    renderImage(background_texture, 0, 0, 1400, 800, 0, 0);

    if(gameStarted) {
        movePlayers();
    }

    renderPlayers();
};

void kill_Ingame() {
    SDL_DestroyTexture(background_texture);
};