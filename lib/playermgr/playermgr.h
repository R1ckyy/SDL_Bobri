#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

#define BOBERSPEED 330
#define BOBERSIZE 110
#define WEAPONSIZE 50
#define FIRECOOLDOWN 2000

enum PlayerSetting {
    HUMAN,
    BOT,
    INACTIVE
};

enum Weapon {
    VETEV,
    PAREZ,
    SPALKOVNICE
};

enum Movement {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

typedef struct {
    enum PlayerSetting setting;
    bool alive;
    int points;
    enum Weapon active_weapon;
    int ammo;
    Uint32 lastFired;
    SDL_Rect rect; 
    double angle;
    bool keysPressed[5];
    enum Movement lastKeyPressed;
} Bober;

void initPlayerManager();

void keyPressed(SDL_KeyCode key);
void keyUnpressed(SDL_KeyCode key);

void randomPos(int id);

void movePlayers();

void renderPlayers();

void renderPlayersHud();

void killPlayerManager();