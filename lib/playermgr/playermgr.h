#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

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
    int player_id;
    enum PlayerSetting setting;
    bool alive;
    int points;
    enum Weapon active_weapon;
    int ammo;
    SDL_Rect rect;
    bool keysPressed[5];
    enum Movement lastKeyPressed;
} Bober;

void initPlayerManager();

void keyPressed(SDL_KeyCode key);
void keyUnpressed(SDL_KeyCode key);

void randomPos(int id);

void movePlayers();

void renderPlayers();

void killPlayerManager();