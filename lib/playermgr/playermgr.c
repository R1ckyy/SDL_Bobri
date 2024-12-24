#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../gamemgr/gamemgr.h"
#include "../../utils/imgrender/imgrender.h"

#include "playermgr.h"

#define BOBERSPEED 300
#define BOBERSIZE 140
#define WEAPONSIZE 50

static Bober *bobers;

const char *bobersTextures_paths[3] = {"images/Bober_kurwa_1.png","images/Bober_kurwa_2.png","images/Bober_kurwa_3.png"};
const char *weaponTextures_paths[3] = {"images/Double-Action_vetev.png","Parez-47.png","images/Spalkovnice.png"};
SDL_Texture *bobersTextures[3];
SDL_Texture *weaponTextures[3];

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
        for (int j = 0; j < 5; j++) {
            bobr.keysPressed[j] = false;
        }
        bobr.lastKeyPressed = DOWN;

        bobers[i] = bobr;
    }

    for (int i = 0; i < 3; i++) {
        bobersTextures[i] = IMG_LoadTexture(getRenderer(),bobersTextures_paths[i]);
        weaponTextures[i] = IMG_LoadTexture(getRenderer(),weaponTextures_paths[i]);
    }
    
};

void keyPressed(SDL_KeyCode key) {
    for (int i = 0; i < 3; i++) {
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
        for (int j = 0; j < 4; j++) {
            if(key == keyboard_layout[i][j]) bobers[i].keysPressed[j] = false;
        }      
    }
};

void movePlayers() {
    for (int i = 0; i < 3; i++) {
        if (bobers[i].keysPressed[UP]) {
            if(bobers[i].y - (BOBERSPEED * getDeltaTime()) <= 0) bobers[i].y = 0;
            else bobers[i].y -= (BOBERSPEED * getDeltaTime());
        } else if (bobers[i].keysPressed[DOWN]) {
            if(bobers[i].y + (BOBERSPEED * getDeltaTime()) >= (800 - BOBERSIZE)) bobers[i].y = (800 - BOBERSIZE);
            else bobers[i].y += (BOBERSPEED * getDeltaTime());
        } else if (bobers[i].keysPressed[LEFT]) {
            if(bobers[i].x - (BOBERSPEED * getDeltaTime()) <= 0) bobers[i].x = 0;
            else bobers[i].x -= (BOBERSPEED * getDeltaTime());
        } else if (bobers[i].keysPressed[RIGHT]) {
            if(bobers[i].x + (BOBERSPEED * getDeltaTime()) >= (1400 - BOBERSIZE)) bobers[i].x = (1400 - BOBERSIZE);
            else bobers[i].x += (BOBERSPEED * getDeltaTime());
        }          
    }
};

void renderPlayers() {
    for (int i = 0; i < 3; i++) {
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
            renderImage(weaponTextures[bobers[i].active_weapon], bobers[i].x, bobers[i].y-30-WEAPONSIZE, BOBERSIZE, WEAPONSIZE, -90, SDL_FLIP_NONE);
        } else if (angle == 90) {

        } else if (angle == 180) {

        } else {

        }

        renderImage(bobersTextures[i], bobers[i].x, bobers[i].y, BOBERSIZE, BOBERSIZE, angle,SDL_FLIP_NONE);
    }
}

void killPlayerManager() {
    free(bobers);

    for (int i = 0; i < 3; i++) {
        SDL_DestroyTexture(bobersTextures[i]);
        SDL_DestroyTexture(weaponTextures[i]);
    }
    
};