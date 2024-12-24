#pragma once

#include <stdbool.h>

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

typedef struct {
    int player_id;
    enum PlayerSetting setting;
    bool alive;
    int points;
    enum Weapon active_weapon;
    int ammo;
    int x;
    int y;
} Bober;

void initPlayerManager();

void renderPlayers();

void killPlayerManager();