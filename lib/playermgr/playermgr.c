#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "../gamemgr/gamemgr.h"
#include "../../utils/imgrender/imgrender.h"
#include "../../utils/textrender/textrender.h"
#include "../../utils/colors/colors.h"
#include "../bulletsmgr/bulletsmgr.h"
#include "../wallsmgr/wallsmgr.h"

#include "playermgr.h"

static Bober *bobers;

const char *bobersTextures_paths[3] = {"images/Bober_kurwa_1.png","images/Bober_kurwa_2.png","images/Bober_kurwa_3.png"};
const char *weaponTextures_paths[3] = {"images/Double-Action_vetev.png","images/Parez-47.png","images/Spalkovnice.png"};
SDL_Texture *bobersTextures[3];
SDL_Texture *weaponTextures[3];

static SDL_Texture *point_icon;

static TTF_Font *mainfont;

static SDL_KeyCode keyboard_layout [3][5] = {
    // up     down     left   right     fire
    {SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDLK_SPACE},
    {SDLK_i, SDLK_k, SDLK_j, SDLK_l, SDLK_n},
    {SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_RSHIFT}
};

void initPlayerManager() {
    initBulletManager();

    bobers = malloc(sizeof(Bober) * 3);
    if(!bobers && isDebug()) {
        fprintf(stderr, "Memory allocation of Bobers failed.\n");
        exit(1);
    }

    srand(time(NULL));
    
    for (int i = 0; i < 3; i++) {
        bobersTextures[i] = IMG_LoadTexture(getRenderer(),bobersTextures_paths[i]);
        weaponTextures[i] = IMG_LoadTexture(getRenderer(),weaponTextures_paths[i]);
    }

    for (int i = 0; i < 3; i++) {
        Bober bobr;
        bobr.setting = HUMAN;
        bobr.alive = true;
        bobr.points = 0;
        bobr.active_weapon = i;
        bobr.ammo = 2;
        bobr.rect.x = 0;
        bobr.rect.y = 0;
        bobr.rect.w = BOBERSIZE;
        bobr.rect.h = BOBERSIZE;
        bobr.angle = 0;
        bobr.lastFired = SDL_GetTicks();
        bobr.lastDied = SDL_GetTicks();
        for (int j = 0; j < 5; j++) {
            bobr.keysPressed[j] = false;
        }
        bobr.lastKeyPressed = DOWN;

        bobers[i] = bobr;

        randomPos(i);
    }

    mainfont = TTF_OpenFont("fonts/Roboto.ttf", 72);

    point_icon = IMG_LoadTexture(getRenderer(), "images/points.png");
};

void keyPressed(SDL_KeyCode key) {
    for (int i = 0; i < 3; i++) {
        if(bobers[i].setting != HUMAN) continue;
        for (int j = 0; j < 4; j++) {
            if(key == keyboard_layout[i][j]) {
                bobers[i].keysPressed[j] = true;
                bobers[i].lastKeyPressed = j;
            } 
        } 
        if(key == keyboard_layout[i][4]) bobers[i].keysPressed[4] = true;
    }
};

void keyUnpressed(SDL_KeyCode key) {
    for (int i = 0; i < 3; i++) {
        if(bobers[i].setting != HUMAN) continue;
        for (int j = 0; j < 5; j++) {
            if(key == keyboard_layout[i][j]) bobers[i].keysPressed[j] = false;
        }      
    }
};

void randomPos(int id) {
    int x;
    int y;
    do{
        x = rand() % (1401-BOBERSIZE);
        y = rand() % (801-BOBERSIZE);

        bobers[id].rect.x = x;
        bobers[id].rect.y = y;
        if(WallRectCollision(bobers[id].rect) && isDebug()) printf("Player [%d] spawned in a wall, respawning.\n", id);
        if((PlayerRectCollisionExc(bobers[id].rect, id) != -1) && isDebug()) printf("Player [%d] spawned in another player, respawning.\n", id);
    }while(WallRectCollision(bobers[id].rect) || PlayerRectCollisionExc(bobers[id].rect, id) != -1);
};

void movePlayers() {
    for (int i = 0; i < 3; i++) {
        if(bobers[i].setting == INACTIVE) continue;
        if(!bobers[i].alive) continue;
        SDL_Rect predictedRect = bobers[i].rect;
        if (bobers[i].keysPressed[UP]) {
            predictedRect.y -= (BOBERSPEED * getDeltaTime());
            if(WallRectCollision(predictedRect)) continue;
            if(bobers[i].rect.y - (BOBERSPEED * getDeltaTime()) <= 0) bobers[i].rect.y = 0;
            else bobers[i].rect.y -= (BOBERSPEED * getDeltaTime());
        } else if (bobers[i].keysPressed[DOWN]) {
            predictedRect.y += (BOBERSPEED * getDeltaTime());
            if(WallRectCollision(predictedRect)) continue;
            if(bobers[i].rect.y + (BOBERSPEED * getDeltaTime()) >= (800 - BOBERSIZE)) bobers[i].rect.y = (800 - BOBERSIZE);
            else bobers[i].rect.y += (BOBERSPEED * getDeltaTime());
        } else if (bobers[i].keysPressed[LEFT]) {
            predictedRect.x -= (BOBERSPEED * getDeltaTime());
            if(WallRectCollision(predictedRect)) continue;
            if(bobers[i].rect.x - (BOBERSPEED * getDeltaTime()) <= 0) bobers[i].rect.x = 0;
            else bobers[i].rect.x -= (BOBERSPEED * getDeltaTime());
        } else if (bobers[i].keysPressed[RIGHT]) {
            predictedRect.x += (BOBERSPEED * getDeltaTime());
            if(WallRectCollision(predictedRect)) continue;
            if(bobers[i].rect.x + (BOBERSPEED * getDeltaTime()) >= (1400 - BOBERSIZE)) bobers[i].rect.x = (1400 - BOBERSIZE);
            else bobers[i].rect.x += (BOBERSPEED * getDeltaTime());
        }     

        //Bullets

        if(bobers[i].ammo == -1) bobers[i].active_weapon = VETEV;

        int cooldown = FIRECOOLDOWN - (bobers[i].active_weapon == PAREZ ? 1000 : 0);

        if(bobers[i].keysPressed[4] && (bobers[i].lastFired + cooldown) <= SDL_GetTicks()) {
            bobers[i].lastFired = SDL_GetTicks();
            bulletFired(bobers[i], i);
            if(bobers[i].active_weapon != VETEV) {
                bobers[i].ammo--;
                if(bobers[i].ammo == -1) bobers[i].active_weapon = VETEV;
            }
        }
    }
};

int PlayerRectCollision(SDL_Rect rect) {
    SDL_Rect result;
    for (int i = 0; i < 3; i++) {
        if(!bobers[i].alive) continue;
        if(SDL_IntersectRect(&bobers[i].rect, &rect, &result) == SDL_TRUE) return i;
    }
    return -1;
};

int PlayerRectCollisionExc(SDL_Rect rect, int excluding_bober) {
    SDL_Rect result;
    for (int i = 0; i < 3; i++) {
        if(i == excluding_bober) continue;
        if(!bobers[i].alive) continue;
        if(SDL_IntersectRect(&bobers[i].rect, &rect, &result) == SDL_TRUE) return i;
    }
    return -1;
};

void PlayerShot(int id, int owner_bober_id) {
    bobers[id].lastDied = SDL_GetTicks();
    bobers[id].alive = false;
    bobers[id].points--;
    bobers[owner_bober_id].points+=3;
    bobers[id].angle = rand() % 360;
};

void respawnPlayers() {
    for (int i = 0; i < 3; i++) {
        if(bobers[i].alive) continue;
        if(bobers[i].lastDied + RESPAWNTIME <= SDL_GetTicks()) {
            randomPos(i);
            bobers[i].active_weapon = VETEV;
            bobers[i].ammo = -1;
            bobers[i].alive = true;
        }   
    }
};

void renderPlayers() {
    for (int i = 0; i < 3; i++) {
        if(bobers[i].setting == INACTIVE) continue;

        if(bobers[i].alive) {
            SDL_SetTextureColorMod(bobersTextures[i], 255, 255, 255);

            if(bobers[i].keysPressed[UP]) bobers[i].angle = 0;
            else if(bobers[i].keysPressed[DOWN]) bobers[i].angle = 180;
            else if(bobers[i].keysPressed[LEFT]) bobers[i].angle = 270;
            else if(bobers[i].keysPressed[RIGHT]) bobers[i].angle = 90;
            else {
                if(bobers[i].lastKeyPressed == UP) bobers[i].angle = 0;
                else if(bobers[i].lastKeyPressed == DOWN) bobers[i].angle = 180;
                else if(bobers[i].lastKeyPressed == LEFT) bobers[i].angle = 270;
                else if(bobers[i].lastKeyPressed == RIGHT) bobers[i].angle = 90;
            }

            if(bobers[i].angle == 0) {
                renderImage(weaponTextures[bobers[i].active_weapon], bobers[i].rect.x+BOBERSIZE/2-WEAPONSIZE/2, bobers[i].rect.y-WEAPONSIZE, WEAPONSIZE, WEAPONSIZE, -90, SDL_FLIP_NONE);
            } else if (bobers[i].angle == 90) {
                renderImage(weaponTextures[bobers[i].active_weapon], bobers[i].rect.x+BOBERSIZE, bobers[i].rect.y+BOBERSIZE/2-WEAPONSIZE/2, WEAPONSIZE, WEAPONSIZE, 0, SDL_FLIP_NONE);
            } else if (bobers[i].angle == 180) {
                renderImage(weaponTextures[bobers[i].active_weapon], bobers[i].rect.x+BOBERSIZE/2-WEAPONSIZE/2, bobers[i].rect.y+BOBERSIZE, WEAPONSIZE, WEAPONSIZE, 90, SDL_FLIP_NONE);
            } else {
                renderImage(weaponTextures[bobers[i].active_weapon], bobers[i].rect.x-WEAPONSIZE, bobers[i].rect.y+BOBERSIZE/2-WEAPONSIZE/2, WEAPONSIZE, WEAPONSIZE, 0, SDL_FLIP_HORIZONTAL);
            }

            renderImage(bobersTextures[i], bobers[i].rect.x, bobers[i].rect.y, BOBERSIZE, BOBERSIZE, bobers[i].angle, SDL_FLIP_NONE);
        }else {
            SDL_SetTextureColorMod(bobersTextures[i], 255, 0, 0);
            renderImage(bobersTextures[i], bobers[i].rect.x, bobers[i].rect.y, BOBERSIZE, BOBERSIZE, bobers[i].angle, SDL_FLIP_NONE);
            SDL_SetTextureColorMod(bobersTextures[i], 255, 255, 255);
        }
    }
}

void renderPlayersHud() {
    for (int i = 0; i < 3; i++) {
        if(!bobers[i].alive) continue;
        char buf[5];
        sprintf(buf, "%2d", bobers[i].points);
        SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);
        createText(mainfont, white, buf, bobers[i].rect.x-10, bobers[i].rect.y, 25, 25);
        renderImage(point_icon, bobers[i].rect.x-35, bobers[i].rect.y, 25, 25, 0, SDL_FLIP_NONE);
    }
    
};

void killPlayerManager() {
    killBulletManager();
    
    free(bobers);

    for (int i = 0; i < 3; i++) {
        SDL_DestroyTexture(bobersTextures[i]);
        SDL_DestroyTexture(weaponTextures[i]);
    }

    TTF_CloseFont(mainfont);

    SDL_DestroyTexture(point_icon);
};