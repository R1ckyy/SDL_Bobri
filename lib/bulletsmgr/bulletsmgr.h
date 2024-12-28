#pragma once

#include <stdbool.h>
#include "../playermgr/playermgr.h"

typedef struct {
    SDL_Rect rect;
    int x_vel;
    int y_vel;
    bool remove;
} Bullet;

void initBulletManager();

Bullet createBullet(Bober firing_bober);

void bulletFired(Bober firing_bober);

void bulletLogic();

void renderBullets();

void killBulletManager();