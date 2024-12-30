#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../screens/endgame/endgame.h"

#define BOBERSPEED 330
#define BOBERSIZE 110
#define WEAPONSIZE 50
#define FIRECOOLDOWN 2000
#define RESPAWNTIME 5000

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
    Uint32 lastDied;
    SDL_Rect rect; 
    double angle;
    bool keysPressed[5];
    enum Movement lastKeyPressed;
} Bober;

void initPlayerManager();

void setPlayerSetting(int id, enum PlayerSetting setting);
enum PlayerSetting getPlayerSetting(int id);

void prepToStart();

void keyPressed(SDL_KeyCode key);
void keyUnpressed(SDL_KeyCode key);

void randomPos(int id);

void movePlayers();

int PlayerRectCollision(SDL_Rect rect);
int PlayerRectCollisionExc(SDL_Rect rect, int excluding_bober);

void PlayerShot(int id, int owner_bober_id);
void respawnPlayers();

void playerHitUpgrade(int id, enum Weapon weapon);

Score getPlayerScores();

void renderPlayers();

void renderPlayersHud();

void killPlayerManager();