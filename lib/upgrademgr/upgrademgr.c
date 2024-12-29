#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "../gamemgr/gamemgr.h"
#include "../wallsmgr/wallsmgr.h"
#include "../playermgr/playermgr.h"
#include "../../utils/imgrender/imgrender.h"
#include "../../utils/textrender/textrender.h"
#include "../../utils/colors/colors.h"

#include "upgrademgr.h"

SDL_Texture *parez_texture;
SDL_Texture *spalkovnice_texture;
SDL_Texture *box_texture;

TTF_Font *mainfont;

Upgrade *upgrades;

static Uint32 lastRespawned;

void initUpgradesManager() {
    parez_texture = IMG_LoadTexture(getRenderer(),"images/Parez-47.png");
    spalkovnice_texture = IMG_LoadTexture(getRenderer(),"images/Spalkovnice.png");
    box_texture = IMG_LoadTexture(getRenderer(), "images/box.webp");

    mainfont = TTF_OpenFont("fonts/Roboto.ttf", 72);

    upgrades = malloc(sizeof(Upgrade) * 2);
    if(upgrades == NULL && isDebug()) {
        fprintf(stderr, "Memory allocation for Upgrades failed.\n");
        exit(1);
    }

    lastRespawned = SDL_GetTicks();
};

void respawnUpgrades() {
    if(lastRespawned + UPGRADE_RESPAWNCOOLDOWN >= SDL_GetTicks()) return;
    for (int i = 0; i < 2; i++) {
        Upgrade upgrade;
        upgrade.active = true;
        upgrade.weapon_upgrade = (rand() % 2 +1);

        upgrade.rect.w = UPGRADE_XSIZE;
        upgrade.rect.h = UPGRADE_YSIZE;
        int x;
        int y;
        do{
            x = rand() % (1401-UPGRADE_XSIZE);
            y = rand() % (801-UPGRADE_YSIZE);

            upgrade.rect.x = x;
            upgrade.rect.y = y;
            if(WallRectCollision(upgrade.rect) && isDebug()) printf("Upgrade spawned in a wall, respawning.\n");
            if((PlayerRectCollision(upgrade.rect) != -1) && isDebug()) printf("Upgrade spawned in another player, respawning.\n");
        }while(WallRectCollision(upgrade.rect) || PlayerRectCollision(upgrade.rect) != -1);

        upgrade.rect2.x = x+UPGRADE_RECT2OFFSET;
        upgrade.rect2.y = y+UPGRADE_RECT2OFFSET;
        upgrade.rect2.w = UPGRADE_XSIZE - (2*UPGRADE_RECT2OFFSET);
        upgrade.rect2.h = UPGRADE_YSIZE - (2*UPGRADE_RECT2OFFSET);

        upgrades[i] = upgrade;
    }
    lastRespawned = SDL_GetTicks(); 
};

void renderUpgrades() {
    for (int i = 0; i < 2; i++) {
        if(!upgrades[i].active) continue;
        SDL_SetRenderDrawColor(getRenderer(), 0,0,0,0);
        char buf[22];
        sprintf(buf, "Upgrade: %s\n", upgrades[i].weapon_upgrade == 1 ? "Parez-47" : "Spalkovnice");
        createText(mainfont, white, buf, upgrades[i].rect.x, upgrades[i].rect.y-20, upgrades[i].rect.w, 20);

        renderImageOnRect(box_texture, upgrades[i].rect, 0, SDL_FLIP_NONE);
        renderImageOnRect(upgrades[i].weapon_upgrade == 1 ? parez_texture : spalkovnice_texture, upgrades[i].rect2, 0, SDL_FLIP_NONE);
    }
};

void upgradesLogic() {
    for (int i = 0; i < 2; i++) {
        if(!upgrades[i].active) continue;
        int hit = PlayerRectCollision(upgrades[i].rect);
        if(hit != -1) {
            upgrades[i].active = false;
            playerHitUpgrade(hit, upgrades[i].weapon_upgrade);
        }
    }
    
};

void killUpgradesManager() {
    SDL_DestroyTexture(parez_texture);
    SDL_DestroyTexture(spalkovnice_texture);
    SDL_DestroyTexture(box_texture);

    TTF_CloseFont(mainfont);

    free(upgrades);
};