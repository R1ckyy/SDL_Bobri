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
#include "../wallsmgr/wallsmgr.h"

#include "playermgr.h"

#define BOBERSPEED 330
#define BOBERSIZE 110
#define WEAPONSIZE 50

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
        bobr.player_id = i;
        bobr.setting = HUMAN;
        bobr.alive = false;
        bobr.points = 99;
        bobr.active_weapon = VETEV;
        bobr.ammo = -1;
        bobr.rect.x = 0;
        bobr.rect.y = 0;
        bobr.rect.w = BOBERSIZE;
        bobr.rect.h = BOBERSIZE;
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
    }
};

void keyUnpressed(SDL_KeyCode key) {
    for (int i = 0; i < 3; i++) {
        if(bobers[i].setting != HUMAN) continue;
        for (int j = 0; j < 4; j++) {
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
    }while(WallRectCollision(bobers[id].rect));
};

void movePlayers() {
    for (int i = 0; i < 3; i++) {
        if(bobers[i].setting == INACTIVE) continue;
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
    }
};

void renderPlayers() {
    for (int i = 0; i < 3; i++) {
        if(bobers[i].setting == INACTIVE) continue;
        double angle;

        if(bobers[i].keysPressed[UP]) angle = 0;
        else if(bobers[i].keysPressed[DOWN]) angle = 180;
        else if(bobers[i].keysPressed[LEFT]) angle = 270;
        else if(bobers[i].keysPressed[RIGHT]) angle = 90;
        else {
            if(bobers[i].lastKeyPressed == UP) angle = 0;
            else if(bobers[i].lastKeyPressed == DOWN) angle = 180;
            else if(bobers[i].lastKeyPressed == LEFT) angle = 270;
            else if(bobers[i].lastKeyPressed == RIGHT) angle = 90;
        }

        if(angle == 0) {
            renderImage(weaponTextures[bobers[i].active_weapon], bobers[i].rect.x+BOBERSIZE/2-WEAPONSIZE/2, bobers[i].rect.y-WEAPONSIZE, WEAPONSIZE, WEAPONSIZE, -90, SDL_FLIP_NONE);
        } else if (angle == 90) {
            renderImage(weaponTextures[bobers[i].active_weapon], bobers[i].rect.x+BOBERSIZE/2+WEAPONSIZE, bobers[i].rect.y+BOBERSIZE/2-WEAPONSIZE/2, WEAPONSIZE, WEAPONSIZE, 0, SDL_FLIP_NONE);
        } else if (angle == 180) {
            renderImage(weaponTextures[bobers[i].active_weapon], bobers[i].rect.x+BOBERSIZE/2-WEAPONSIZE/2, bobers[i].rect.y+BOBERSIZE/2+WEAPONSIZE, WEAPONSIZE, WEAPONSIZE, 90, SDL_FLIP_NONE);
        } else {
            renderImage(weaponTextures[bobers[i].active_weapon], bobers[i].rect.x-WEAPONSIZE, bobers[i].rect.y+BOBERSIZE/2-WEAPONSIZE/2, WEAPONSIZE, WEAPONSIZE, 0, SDL_FLIP_HORIZONTAL);
        }

        renderImage(bobersTextures[i], bobers[i].rect.x, bobers[i].rect.y, BOBERSIZE, BOBERSIZE, angle, SDL_FLIP_NONE);

        char buf[5];
        sprintf(buf, "%2d", bobers[i].points);
        SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);
        createText(mainfont, white, buf, bobers[i].rect.x-10, bobers[i].rect.y, 25, 25);
        renderImage(point_icon, bobers[i].rect.x-35, bobers[i].rect.y, 25, 25, 0, SDL_FLIP_NONE);
    }
}

void killPlayerManager() {
    free(bobers);

    for (int i = 0; i < 3; i++) {
        SDL_DestroyTexture(bobersTextures[i]);
        SDL_DestroyTexture(weaponTextures[i]);
    }

    TTF_CloseFont(mainfont);

    SDL_DestroyTexture(point_icon);    
};