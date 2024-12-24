#include "../../../utils/imgrender/imgrender.h"
#include "../../playermgr/playermgr.h"

#include "ingame.h"

void init_Ingame() {

};

void render_Ingame() {
    renderImage("images/game_background.webp", 0, 0, 1400, 800, 0);

    renderPlayers();
};

void kill_Ingame() {

};