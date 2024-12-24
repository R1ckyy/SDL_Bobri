#include <stdlib.h>
#include <stdio.h>
#include "../gamemgr/gamemgr.h"
#include "../../utils/imgrender/imgrender.h"

#include "playermgr.h"

static Bober *bobers;

const char *bobersTextures[3] = {"images/Bober_kurwa_1.png","images/Bober_kurwa_2.png","images/Bober_kurwa_3.png"};

void initPlayerManager() {
    bobers = malloc(sizeof(Bober) * 3);
    if(!bobers && isDebug()) {
        fprintf(stderr, "Memory allocation of Bobers failed.\n");
        exit(1);
    }

    for (int i = 0; i < 3; i++) {
        Bober bobr;
        bobr.player_id = i;
        bobr.setting = HUMAN;
        bobr.alive = false;
        bobr.points = 0;
        bobr.active_weapon = VETEV;
        bobr.ammo = -1;
        bobr.x = 0;
        bobr.y = 0;

        bobers[i] = bobr;
    }
    
};

void renderPlayers() {
    for (int i = 0; i < 3; i++) {
        renderImage(bobersTextures[i], bobers[i].x, bobers[i].y, 140, 140, 0);
    }
}

void killPlayerManager() {
    free(bobers);
};